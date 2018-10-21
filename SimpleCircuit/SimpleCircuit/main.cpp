#include<iostream>
#include<vector>
#include"functions.h"
using namespace std;

vector<Gate*> gates;
vector<Node*> nodes;
Functions *fun;
Page *pg;
bool run = 1;

int main() {
    while (run) {
        pg->FirstPage();
        char choice = 0;
        cin >> choice;
        switch (choice) {
        case '1': {
            fun->Create(pg, gates, nodes);
            break;
        }//create
        case '2': {
            fun->SetNodes(pg, gates, nodes);
            break;
        }//set nodes
        case '3': {
            fun->SetNodeValue(gates, nodes);
            break;
        }//set value
        case '4': {
            fun->Delete(gates, nodes);
            break;
        }//delete
        case '5': {
            fun->Display(gates);
            break;
        }//dispaly
        case '6': {
            fun->Run(gates);
            break;
        }//run
        case '7': {
            fun->Clear(gates, nodes);
            break;
        }//clear
        case '8': {
            fun->Clear(gates, nodes);
            run = false;
            break;
        }//quit
        default: {
            cout << "Please enter the right choice.\n";
            break;
        }
        }
    }
    return 0;
}