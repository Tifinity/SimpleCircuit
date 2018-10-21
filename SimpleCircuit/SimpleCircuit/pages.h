#pragma once
#include<iostream>
using namespace std;

class Page {
public:
    void FirstPage() {
        cout << "\n";
        cout << "1.Create and connect a gate.\n";
        cout << "2.Set a gate's nodes.\n";
        cout << "3.Set a node's value.\n";
        cout << "4.Delete a gate.\n";
        cout << "5.Display all the gate.\n";
        cout << "6.Run the program.\n";
        cout << "7.Clear all connection.\n";
        cout << "8.Quit.\n";
        cout << "\n";
    }
    void CreatePage() {
        cout << "\n";
        cout << "1.Create an And_gate.\n";
        cout << "2.Create an Or_gate.\n";
        cout << "3.Create a Not_gate.\n";
        cout << "4.Create an Xor_gate.\n";
        cout << "5.Create a Nand_gate.\n";
        cout << "6.Create a Nor_gate.\n";
        cout << "\n";
    }

};