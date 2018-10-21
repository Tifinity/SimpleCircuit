#pragma once
#include<iostream>
#include<vector>
#include<queue>
#include"gate.h"
#include"pages.h"
using namespace std;

class Functions {
public:
    Gate* Contain(vector<Gate*> gates, string gate_name) {
        for (int i = 0; i < gates.size(); i++) {
            if (gate_name == gates[i]->GetName()) return gates[i];
        }
        return NULL;
    }
    Node* Contain(vector<Node*> nodes, string node_name) {
        for (int i = 0; i < nodes.size(); i++) {
            if (node_name == nodes[i]->GetName()) return nodes[i];
        }
        return NULL;
    }
    void Create(Page* pg, vector<Gate*>& gates, vector<Node*>& nodes) {
        pg->CreatePage();
        char gate_choice = 0;
        cin >> gate_choice;

        Gate* gate = NULL;
        if (gate_choice == '1') {
            gate = new AndGate();
        }
        else if (gate_choice == '2') {
            gate = new OrGate();
        }
        else if (gate_choice == '3') {
            gate = new NotGate();
        }
        else if (gate_choice == '4') {
            gate = new XorGate();
        }
        else if (gate_choice == '5') {
            gate = new NandGate();
        }
        else if (gate_choice == '6') {
            gate = new NorGate();
        }
        else {
            cout << "Please choose the right gate type.\n";
            return;
        }

        string gate_name;
        cout << "Please enter the gate's name.\n";
        cin >> gate_name;
        if (Contain(gates, gate_name)) {
            cout << "This name has ready exist,please enter once more.\n";
            return;
        }

        gate->SetName(gate_name);
        gates.push_back(gate);

        string in1, in2, out;
        Node *node = NULL;

        cout << "Please enter the input_1's name.\n";
        cin >> in1;
        node = Contain(nodes, in1);
        if (node == NULL) {
            node = new Node(in1);
            nodes.push_back(node);
            gate->SetIn_1(node);
        }
        else gate->SetIn_1(node);//set in_1

        if (gate->GetType() != "Not") {
            cout << "Please enter the input_2's name.\n";
            cin >> in2;
            node = Contain(nodes, in2);
            if (node == NULL) {
                node = new Node(in2);
                nodes.push_back(node);
                gate->SetIn_2(node);
            }
            else gate->SetIn_2(node);
        }
        else gate->SetIn_2(gate->GetIn_1());//set in_2

        cout << "Please enter the output's name.\n";
        cin >> out;
        node = Contain(nodes, out);
        if (node == NULL) {
            node = new Node(out);
            nodes.push_back(node);
            gate->SetOut(node);
        }
        else gate->SetOut(node);//set out
    }
    void SetNodes(Page* pg, vector<Gate*>& gates, vector<Node*>& nodes) {
        string gate_name;
        cout << "Please enter gate's name that you want to set.\n";
        cin >> gate_name;

        Gate *gate = Contain(gates, gate_name);;
        if (gate == NULL) {
            cout << "Invalid gate name,\n";
            return;
        }
        else {
            gate->Print();
            cout << "Please reset the nodes.\n";
        }

        string in1, in2, out;
        Node *node = NULL;
        cout << "Please enter the input_1's name.\n";
        cin >> in1;
        node = Contain(nodes, in1);
        if (node == NULL) {
            node = new Node(in1);
            nodes.push_back(node);
            gate->SetIn_1(node);
        }
        else gate->SetIn_1(node);//set in_1

        if (gate->GetType() != "Not") {
            cout << "Please enter the input_2's name.\n";
            cin >> in2;
            node = Contain(nodes, in2);
            if (node == NULL) {
                node = new Node(in2);
                nodes.push_back(node);
                gate->SetIn_2(node);
            }
            else gate->SetIn_2(node);
        }
        else gate->SetIn_2(gate->GetIn_1());//set in_2

        cout << "Please enter the output's name.\n";
        cin >> out;
        node = Contain(nodes, out);
        if (node == NULL) {
            node = new Node(out);
            nodes.push_back(node);
            gate->SetOut(node);
        }
        else gate->SetOut(node);//set out
    }
    void SetNodeValue(vector<Gate*>& gates, vector<Node*>& nodes) {
        cout << "Please enter the node's name.\n";
        string node_name;
        cin >> node_name;
        int i = 0;
        for (i = 0; i < nodes.size(); i++) {
            if (node_name == nodes[i]->GetName()) break;
        }
        if (i == nodes.size()) {
            cout << "Please write the right name.\n";
            return;
        }
        char value = 0;
        cout << "Please set the value(0 or 1).\n";
        cin >> value;
        if (value != '0' && value != '1') {
            cout << "Please set 0 or 1.\n";
            return;
        }
        else nodes[i]->SetValue(value - '0');
    }
    void Delete(vector<Gate*>& gates, vector<Node*>& nodes) {
        cout << "Please enter the gate'name that you want to delete.\n";
        string gate_name;
        cin >> gate_name;
        vector<Gate*>::iterator it;
        for (it = gates.begin(); it != gates.end(); it++) {
            if ((*it)->GetName() == gate_name) break;
        }
        if (it == gates.end()) {
            cout << "Invalid name.\n";
        }
        else {
            cout << "The gate <" << (*it)->GetName() << "> has been deleted.\n";
            gates.erase(it);
        }
    }
    void Display(vector<Gate*>& gates) {
        for (int i = 0; i < gates.size(); i++) cout << gates[i];
    }
    void Run(vector<Gate*>& gates) {
        try {
            CheckCircle(gates);
            CheckOut(gates);
            for (int count = 0; count < gates.size(); count++) {
                for (int i = 0; i < gates.size(); i++) {
                    gates[i]->Calculate();
                }
            }
        }
        catch (int) { 
            cout << "Your circuit have a circle.\nPlease check it.\n"; 
        }
        catch (double) {
            cout << "Short-circuit.\n";
        }
    }
    void Clear(vector<Gate*>& gates, vector<Node*>& nodes) {
        gates.clear();
        nodes.clear();
        cout << "You clear all gates.\n";
    }
    void CheckCircle(vector<Gate*>& gates) {
        for (int i = 0; i < gates.size(); i++) {
            vector<int> visit;
            for (int j = 0; j < gates.size(); j++) visit.push_back(0);
            queue<Node*> q_node;
            q_node.push(gates[i]->GetOut());
            visit[i] = 1;
            while (!q_node.empty()) {
                Node* node = q_node.front();
                q_node.pop();
                for (int k = 0; k < gates.size(); k++) {
                    if (gates[k]->GetIn_1() == node || gates[k]->GetIn_2() == node) {
                        if (visit[k] == 1) throw 1;
                        else {
                            q_node.push(gates[k]->GetOut());
                            visit[k] = 1;
                        }
                    }
                }
            } 
        }
    }
    void CheckOut(vector<Gate*>& gates) {
        for (int i = 0; i < gates.size(); i++) {
            Node *node = gates[i]->GetOut();
            for (int j = 0; j < gates.size(); j++) {
                if (gates[j]->GetOut() == node && j != i) throw 0.1;
            }
        }
    }
};