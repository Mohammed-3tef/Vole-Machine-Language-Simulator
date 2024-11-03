#include <bits/stdc++.h>
#include "Machine.h"

using namespace std;

int main() {
    cout << "Welcome to Our Vole Machine Simulator Program!\n";
    Machine m;
    string choice;
    bool running = true;

    while (running) {
        cout << "\nMenu:\n";
        cout << "1) Load new program\n";
        cout << "2) Run program as a whole\n";
        cout << "3) Run step by step\n";
        cout << "4) Exit\n";
        cout << "Choose an option: ";
        getline(cin,choice);
        while (choice != "1" && choice != "2" && choice != "3" && choice != "4"){
            cout << "\nInvalid choice. Please select a valid option.\n";
            cout << "\nMenu:\n";
            cout << "1) Load new program\n";
            cout << "2) Run program as a whole\n";
            cout << "3) Run step by step\n";
            cout << "4) Exit\n";
            cout << "Choose an option: ";
            getline(cin,choice);
        }
        if (choice == "1"){
            cout << "\nLoading a new program...\n";
            m.LoadNewProgram();
        }
        else if (choice == "2"){
            cout << "\nRunning program as a whole...\n";
            m.RunAll();
        }
        else if (choice == "3"){
            cout << "\nRunning program step by step...\n";
            m.RunStepByStep();
        }
        else if (choice == "4"){
            cout << "\nExiting the program. Thank you for using our simulator!\n";
            running = false;
        }
    }
    return 0;
}
