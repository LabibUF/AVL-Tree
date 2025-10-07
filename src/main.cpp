#include "AVL.h"
#include <iostream>
#include <sstream>

bool isEightDigitString(const string &idStr) {
    if (idStr.size() != 8) return false;
    for (char c : idStr) {
        if (!isdigit(c)) return false;
    }
    return true;
}

int main() {

    // Create an instance of the AVLTree class
    AVLTree tree;

    // Declare a variable to store the number of commands, read commands, and ignore newline characters
    int n;
    cin >> n;
    cin.ignore();

    // stores each input command and loops through them reading the command with parsing
    string command;
    while (n--) {
        getline(cin, command);
        istringstream ss(command);
        string operation;
        ss >> operation;

        if (operation == "insert") {
            string name;
            string idStr;
            ss.ignore();
            getline(ss, name, '\"');
            getline(ss, name, '\"');
            ss >> idStr;

            if (!tree.isValidName(name)) {
                cout << "unsuccessful" << endl;
                continue;
            }
            if (!isEightDigitString(idStr)) {
                cout << "unsuccessful" << endl;
                continue;
            }
            int idVal = stoi(idStr);
            tree.insert(name, idVal);

        } else if (operation == "remove") {
            string idStr;
            if (!(ss >> idStr)) {
                cout << "unsuccessful" << endl;
                continue;
            }
            if (!isEightDigitString(idStr)) {
                cout << "unsuccessful" << endl;
                continue;
            }
            int idVal = stoi(idStr);
            tree.remove(idVal);

        } else if (operation == "removeInorder") {
            int nth;
            if (ss >> nth) {
                tree.removeNth(nth);
            } else {
                cout << "unsuccessful" << endl;
            }
        } else if (operation == "printInorder") {
            tree.printInorder();
        } else if (operation == "printPreorder") {
            tree.printPreorder();
        } else if (operation == "printPostorder") {
            tree.printPostorder();
        } else if (operation == "printLevelCount") {
            tree.printLevelCount();
        } else if (operation == "search") {
            if (command.find('\"') != string::npos) {
                string name;
                getline(ss >> ws, name, '\"');
                getline(ss, name, '\"');
                tree.searchName(name);
            } else {
                string idStr;
                if (!(ss >> idStr)) {
                    cout << "unsuccessful" << endl;
                    continue;
                }
                if (!isEightDigitString(idStr)) {
                    cout << "unsuccessful" << endl;
                    continue;
                }
                int idVal = stoi(idStr);
                tree.searchID(idVal);
            }
        } else {
            cout << "unsuccessful" << endl;
        }
    }
    return 0;
}
