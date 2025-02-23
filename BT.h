// Class declaration BT.h - This file contains pointer definition of the binary tree ADT. 
#ifndef BIN_TREE_H
#define BIN_TREE_H

#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <math.h>
#include <queue>
#include <vector>

using namespace std;

template <class E>		// a template struct, to declare a node 
struct node				// use node<data_type> obj; ex., node<int> obj
{						// node<int>* pt;
	E item;
	node<E>* left;
	node<E>* right;
	node () {
		left = right = nullptr;
	}
	node (E it, node<E>* l=NULL, node<E>* r=NULL)
	{			 // example of using this struct
		item=it; // node<int> *p;
		left=l;	 // p = new node<int>(10, q, r); 
				 // q is left child, r is right child
		right=r; // p = new node<int>(10); // p is a leaf node
	}			 // y->left = new node<int>(10); 
				 // add a left child for y, 
}; 

template <class E> 
class binary_tree	// E is the type parameter of the template class
{
protected:
	node<E>* root;		// THE ONLY MEMBER ELEMENT REQUIRED FOR ACCESS
	
	// Below are member functions available on a need-to-know bases - 
	// they are usually called by other member functions, not by users
	bool TreeEqual(node<E>*, node<E>*);
	node<E>* copyTree(node<E>* treeRoot) const;
	void destroyTree(node<E>* treeRoot);
	int treeHeight(node<E>* rt);
	int size(node<E>* rt); // countNode

	void preorder(node<E>* treeRoot, ostream &, string) const;
	void inorder(node<E>* treeRoot, ostream &, string) const;
	void postorder(node<E>* treeRoot, ostream &, string) const;
	bool balancedHelper(node<E>*);
	vector<E> toVectorLevel(node<E>*);
	void IP1(node<E>* rt, int);

public:
	// Class constructors
	binary_tree();
	binary_tree(const binary_tree<E> &bt); // copy constructor to support deep copy

	// Class destructor
	~binary_tree(); // return dynamic memory to heap before the function ends

	// operator overloading
	binary_tree<E>& operator= (const binary_tree<E> &bt);
	bool operator== (binary_tree<E>);

	// Other member functions
	bool isEmpty() const;
	int treeHeight() { return treeHeight(root); }

	int size() { return size(root); }

	// interface functions for the users of the class
	void preorder(ostream &, string) const;
	// example of a call:
	// binary_tree<int> tree;
	// .... store data in the tree
	// tree.preorder(cout);
	// preorder(root); 
	void inorder(ostream &, string) const;
	void postorder(ostream &, string) const;
	bool balanced()	{
		return balancedHelper(root);
	}
	vector<E> toVectorLevel() { return toVectorLevel(root); }
	void IP() { IP1(root, 0); }
};
#include "BT.CPP"
#endif
