#pragma once
#include<iostream>
#include<string>
using namespace std;

class Node {
    string name;
    int value;
public:
    Node(): value(0) {}
    Node(string name_): name(name_), value(0) {}
    Node(string name_, int value_) : name(name_), value(value_) {}
    ~Node() {}
    void SetValue(int value_) { value = value_; }
    int GetValue() { return value; }
    string GetName() { return name; }
    void Print() {
        cout << "   "<< name << ":" << value << endl;
    }
    friend ostream& operator <<(ostream& os, Node* node) {
        node->Print();
        return os;
    }
};