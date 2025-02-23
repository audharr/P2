// Class declaration and imp file: BT.cpp
// This file contains pointer implementation of the binary tree ADT. 

template <class E>
binary_tree<E>::binary_tree()	{
	root = nullptr;
}

// == operator - returns true if two trees have the same structure and data everywhere. 
// Call to this function:
// binary_tree<int> tree1, tree2;
// .... store data in the tree1 and tree2
// if (tree1==tree2) // tree1.operator==(tree2);
//	 cout << "Same Tree.\n";
template <class E>
bool binary_tree<E>::operator==(binary_tree<E> tree2) // tree here is the right operand
{
	return TreeEqual(root, tree2.root); 	// or return TreeEqual(this->root, tree2.root);
}

template <class E>
bool binary_tree<E>::TreeEqual(node<E>* root1, node<E>* root2)
{
	if (root1==NULL && root2==NULL) // both empty
		return true;
	else if (root1==NULL || root2==NULL) // one is empty, could the other one be empty? NO
		return false;
	else if (root1->item==root2->item) // roots have the same data
		return TreeEqual(root1->left, root2->left) && 
				TreeEqual(root1->right, root2->right);
	else // roots have different value at item field
		return false;
}		

// Copy constructor created to supports deep copy, use example:
// binary_tree<int> bt;	
//  .... read data into bt
// binary_tree<int> bt2(bt); // initialize bt2 with bt data
template <class E> 
binary_tree<E>::binary_tree(const binary_tree<E> &bt) // bt doesnt change
{
	root = copyTree(bt.root); // make a new tree and copy its root to root of default object 
							//	(ie., *this), this->root = ...
}		

// overload the Assignment operator, i.e.,
// bt2=bt1; // bt2.operator=(bt1);
template <class E>
binary_tree<E>& binary_tree<E>::operator = (const binary_tree<E> &bt)
{
	destroyTree(root); // delete the old tree, recycle the memory
	root = copyTree(bt.root); 
	return *this; // why?
	// so that we can use the = operator in a statement like this:
	// bt3=(bt2=bt1); same as the statement below
	// bt3.operator=(bt2.operator=(bt1));
}		

// CopyTree make a new tree that is equal to the argument tree and 
// returns the root of the new tree.
// T1.copyTree(T2.root); is not acceptable 
template <class E>
node<E>* binary_tree<E>::copyTree(node<E>* subRoot) const
{
	node<E> *newsubRoot=nullptr;
	if (subRoot != NULL)
	{
		newsubRoot = new node<E>(subRoot->item); // copy data from subroot
		newsubRoot->left = copyTree(subRoot->left); // recursively copy left sub
		newsubRoot->right = copyTree(subRoot->right); // recursively copy right sub
		// same as	
	//  newsubRoot = new node<E>(subRoot->item, 
	//						copyTree(subRoot->left),
	//						copyTree(subRoot->right));
	}
	return newsubRoot;
}

// Destructor. 
template <class E>
binary_tree<E>::~binary_tree()
{
	destroyTree(root);
	root = nullptr; // indicates tree is empty
}

// Returns all memory for each node by recursively destroying   
// the two subtrees, and then deleting the node itself.             
template <class E>
void binary_tree<E>::destroyTree(node<E>* treeRoot)
{
	if (treeRoot != NULL) // This is done from leaf nodes up, postorder
	{
		destroyTree(treeRoot->left);
		destroyTree(treeRoot->right);	
		delete treeRoot;  
	}
}

template <class E>
bool binary_tree<E>::isEmpty() const {
	return root == NULL;
}

// Preorder print - interface to the public
// in main: binary_tree<int> tree;
// .... // read data
// tree.preorder(fout, "\n"); // print the tree in preorder, 
template <class E>
void binary_tree<E>::preorder(ostream &os, string S) const
{
	preorder(root, os, S); // S is a user provided string to saperate the items
}

// preorder - internal use, implemented recursively
template <class E>
void binary_tree<E>::preorder(node<E>* treeRoot, ostream &os, string S) const
{
	if (treeRoot != nullptr)
	{
		os << treeRoot->item << S; // S is a user provided string to separate the items
		if (treeRoot->left!=NULL)
		  preorder(treeRoot->left, os, S);
		if (treeRoot->right!=NULL)
		  preorder(treeRoot->right, os, S);
	}
}

// Inorder print - public
template <class E>
void binary_tree<E>::inorder(ostream &os, string S) const {
	inorder(root, os, S);
}

// Internal inorder 
template <class E>
void binary_tree<E>::inorder(node<E>* treeRoot, ostream &os, string S) const
{
	if (treeRoot != NULL)
	{
		inorder(treeRoot->left, os, S);
		os << treeRoot->item << S;
		inorder(treeRoot->right, os, S);
	}
}

// Function postorder. //
// exampel of call to this function from main
// binary_tree<int> bst;
// bst.postorder(cout);
template <class E>
void binary_tree<E>::postorder(ostream &os, string S) const
{
	postorder(root, os, S);
}

// Internal postorder
template <class E>
void binary_tree<E>::postorder(node<E>* treeRoot, ostream &os, string S) const
{
	if (treeRoot != NULL)
	{
		postorder(treeRoot->left, os, S);
		postorder(treeRoot->right, os, S);
		os << treeRoot->item << S;
	}
}

// return the height of the tree bt.
template <class E>
int binary_tree<E>::treeHeight(node<E>* rt) 
{
	int H1, H2;
	// base case - empty tree
	if (rt==NULL) 
	   return 0;
	else
	return // return (a>b)? a : b;
	((H1=treeHeight(rt->left))>(H2=treeHeight(rt->right)))? H1+1:H2+1;
/* same as
	   int H1=treeHeight(rt->left); // height of the left sub
	   int H2=treeHeight(rt->right); // height of the right sub
	   if (H1 > H2) 
	      return H1+1;
	   else
	       return H2+1;	
  */
}

template <class E>
int binary_tree<E>::size(node<E>* rt) 
{
	if (!rt) // empty tree
		return 0;
	else
		return size(rt->left)+size(rt->right)+1;
}

template<class E> // is balanced
bool binary_tree<E>::balancedHelper(node<E> * subRoot)
{
	if (subRoot == NULL) // !subRoot
		return true;
	else if (balancedHelper(subRoot->left) && balancedHelper(subRoot->right))
	{
		int LH = treeHeight(subRoot->left),
			RH = treeHeight(subRoot->right);

		return((LH - RH) <= 1) && ((LH - RH) >= -1);
	}
	else 
		return false;
}

template<class E>
vector<E> binary_tree<E>::toVectorLevel(node<E>* subRoot)
{
	queue<node<E>*> Q; // queue of pointers to save space, be green
	vector<E> R;	// initiallly empty
	if (subRoot == nullptr)
		return R;
	Q.push(subRoot);
	while (!Q.empty())
	{
		node<E>* cur = Q.front();
		Q.pop();
		R.push_back(cur->item);
		if (cur->left)
			Q.push(cur->left);
		if (cur->right)
			Q.push(cur->right);
	}
 	return R;
}

// Indentation Print 
template <class E>
void binary_tree<E>::IP1(node<E>* rt, int Indent)
{
	if (rt != NULL)
	{
		for (int k = 0; k < Indent; k++)
			cout << " ";
		cout << rt->item << endl;
		IP1(rt->left, Indent + 3);
		IP1(rt->right, Indent + 3);
	}
}