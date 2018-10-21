#pragma once
#include <iostream>
#include <string>
#include "node.h"
using namespace std;

class Gate {
    string name;
    string type;
protected:
    Node* output;
    Node* input_1;
    Node* input_2;
public:
    Gate():output(NULL), input_1(NULL), input_2(NULL) {}
    ~Gate() {}
    void SetIn_1(Node* in_1) { input_1 = in_1; }
    void SetIn_2(Node* in_2) { input_2 = in_2; }
    void SetOut(Node* out) { output = out; }
    Node* Gate::GetIn_1() { return input_1; }
    Node* Gate::GetIn_2() { return input_2; } 
    Node* Gate::GetOut() { return output; }
    void SetName(string name_) { name = name_; }
    string GetName() { return name; }
    void SetType(string type_) { type = type_; }
    string GetType() { return type; }
    void Print() {
        cout << "[" << type << "] "<< name << ":" << endl;
        input_1->Print();
        input_2->Print();
        output->Print();   
    }
    friend ostream& operator <<(ostream& os, Gate* gate) {
        gate->Print();
        return os;
    }
    virtual void Calculate() = 0;
};

class AndGate : public Gate {
public:
    AndGate() { SetType("And"); }
    ~AndGate() {}
    void Calculate() {
        int a = input_1->GetValue();
        int b = input_2->GetValue();
        output->SetValue(a*b);
    }
};

class OrGate : public Gate {
public:
    OrGate() { SetType("Or"); }
    ~OrGate() {}
    void Calculate() {
        int a = input_1->GetValue();
        int b = input_2->GetValue();
        if (a == 0 && b == 0) output->SetValue(0);
        else output->SetValue(1);
    }
};

class NotGate : public Gate {
public:
    NotGate() { SetType("Not"); }
    ~NotGate() {}
    void Calculate() {
        int a = input_1->GetValue();
        if (a) output->SetValue(0);
        else output->SetValue(1);
    }
};

class XorGate : public Gate {
public:
    XorGate() { SetType("Xor"); }
    ~XorGate() {}
    void Calculate() {
        int a = input_1->GetValue();
        int b = input_2->GetValue();
        if (a == b) output->SetValue(0);
        else output->SetValue(1);
    }
};

class NandGate : public Gate {
public:
    NandGate() { SetType("Nand"); }
    ~NandGate() {}
    void Calculate() {
        int a = input_1->GetValue();
        int b = input_2->GetValue();
        if (a*b) output->SetValue(0);
        else output->SetValue(1);
    }
};

class NorGate : public Gate {
public:
    NorGate() { SetType("Nand"); }
    ~NorGate() {}
    void Calculate() {
        int a = input_1->GetValue();
        int b = input_2->GetValue();
        if (a == 0 && b == 0) output->SetValue(1);
        else output->SetValue(0);
    }
};



