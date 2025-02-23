/*
 @file ExpTree.h */
 
#ifndef _EXP_TREE
#define _EXP_TREE

#include "BT.h"
#include <string>

using namespace std;

class ExpTree  : public binary_tree<string>
{
private:
//	vector<symtolType> symbolTable;

protected:
	node<string> * makeExpTree(string s, int f, int l);

	// Part 2 - Recursive funtion that will return true id eval is successful
	bool eval(node<string>* rt, double &result);
	
public:
	void makeExpTree(string create);
	bool eval(double &result); 								// or double eal();
}; // end BinaryNodeTree

//#include "ExpTree.cpp"

node<string> * ExpTree::makeExpTree(string s, int f, int l) {

	int parentheses = 0;
    int lowestPriority = 999999;
    int indexOP = -1;

    // Check the string from left to right
    for (int i = f; i <= l; ++i) {

        //Checks if current i is a parenthesses
        if (s[i] == '(') {
            parentheses++;
        }
        else if (s[i] == ')') {
            parentheses--;
        }

        else if (parentheses == 0 && (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/')) { // Inside of parentheses
            int priority; // Priority of symbols
            if (s[i] == '+' || s[i] == '-') {
                priority = 1;
            }
            else {
                priority = 2;
            }
            if (priority <= lowestPriority) {
                lowestPriority = priority;
                indexOP = i;
            }
        }
    }

    // If theres none operators, then it is a number
    if (indexOP == -1) {
        // Check for outer parentheses
        if (s[f] == '(' && s[l] == ')') {
            return makeExpTree(s, f + 1, l - 1);
        }
        else {
            return new node<string>(s.substr(f, l - f + 1));
        }
    }

    // Creates a new node for the operator
    node<string>* root = new node<string>(string(1, s[indexOP]));

    // Recursively build left and right subtrees
    root->left = makeExpTree(s, f, indexOP - 1);
    root->right = makeExpTree(s, indexOP + 1, l);

    return root;

}

bool ExpTree::eval(node <string>* rt, double& result) {
    if (!root) 		{										// Without a root a tree is ubable to be formed
        return false;
	}

	// If there is a root, need to move throughout the tree
	double leftPlace;										// Evaluating to the left of the node
	double rightPlace;										// Evaluating to the right of the nodes

    if (isdigit(rt->item[0])) {  							// If passed in value is a digit, evaluate numbers
        result = stod(rt->item);  							// Stod(): makes integer that's passed through into double (utilizing decimal placing)
        return true; 										
    }

	// If current node has digits on the left and the right execute
    if (eval(rt->left, leftPlace) && eval(rt->right, rightPlace)) { 

        if (rt->item == "+") {								 
            result = leftPlace + rightPlace;				// Result of addition
        }
        else if (rt->item == "-") {							
            result = leftPlace - rightPlace;				// Result of subtraction
        }
        else if (rt->item == "*") {
            result = leftPlace * rightPlace;				// Result of multiplication

        }
        else if (rt->item == "/") {							
            if (rightPlace != 0)							// If the denominator is not 0 we can do division
                result = leftPlace / rightPlace;			// Result of division
            else {											// If the denominator is 0, division can not be done
                cout << "Inf" << endl;						// Requirement
                return false;
            }
        }
        else {
            cerr << "Evaluation Failed" << endl;			// Requirement
            return false;
        }
        return true;
    }
    return false;											
}

// Creating the tree in assigned order
void ExpTree::makeExpTree(string create) {				
    root = makeExpTree(create, 0, create.length() - 1); 
}

// Expression tree funciton that assigns result to the reference argument
bool ExpTree::eval(double &result) {
	if (root != nullptr) {								// If root is not null, return eval() that tree exists
		return eval(root, result);						// Recursion functions
	}
	else {
		cout << "Evaluation Failed";					// Requirement  
	}
}
#endif