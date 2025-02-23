// Audrey Harris and Drew Milton
// P2 - Assignment Expression Tree: Creating funtions and implementation of them

#include "ExpTree.h"                // Including ExpTree.h to call functions
#include <iostream>
#include <iomanip>                  // Input-Ouput manipulation for fixed << setprecision
#include <string>
#include <algorithm>                // Allows for the implementation of erase(), remove(), etc

using namespace std;

int main() {

    string create;                  // Using same name from ExpTree.h
    double result;                  // Using same name from ExpTree.h
    ExpTree tmp;                    // ExpTree object tmp

    cout << "Please enter an expression, ctrl-Z to stop: \t";

    while (getline(cin, create)) {  // Obtaining the input for create

        if (create == "^Z") {       // Ctrl Z will cause the loop to break
            break;
        }
        
        create.erase(remove(create.begin(), create.end(), ' '), create.end());
        
        cout << "Expression Tree created:\n";           // Requirement

        tmp.makeExpTree(create);                        // Calling makeExpTree function with object ExpTree with create passed in
        tmp.IP();                                       // Calling IP function with object ExpTree

        cout << "\n\nPostOrder: ";                      // Requirement
        tmp.postorder(cout, " ");                       // Calling postorder function with object ExpTree
        cout << endl;

        if (tmp.eval(result) == true) {                 // Calling eval function with tmp ExpTree, if true execute loop
            cout << "Evaluation Result: " << fixed << setprecision(2) << result;    // Requirement
            cout << endl;
        }
        else {
            cout << "Evaluation Failed\n";              // Requirement
        }

        cout << "Please enter an expression, ctrl-Z to stop: \t\t";       // Requirement
    }
    cout << "Press any key to continue . . .\n";        // Requirement

    return 0;
}