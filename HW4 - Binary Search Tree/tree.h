/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Lilyana Videva
* @idnumber 61887
* @task 4
* @compiler VC
*
*/

#pragma once
#include "node.h"

template<typename S,typename T>
class BinarySearchTree
{
private:
	Node<S,T>* root;
public:
	BinarySearchTree();
	~BinarySearchTree();
	BinarySearchTree(BinarySearchTree const &newBst);
	BinarySearchTree& operator=(BinarySearchTree const &newBst);
private:
	void Initialization();
	void Destroy(Node<S,T>* theRoot);
	void CopyBst(BinarySearchTree const &oldBst,BinarySearchTree const &newBst);
	Node<S,T>* insert(S key,T data, Node<S,T>* leaf);
	long delall(S key,long count, Node<S,T>* leaf);
	bool find(S key,T data, Node<S,T>* leaf);
public:
	long height(Node<S,T>* leaf);
	long maxHeight(long leftHeight, long rightHeight);
	Node<S,T>* rotateFromLToR(Node<S,T>* leaf);
	Node<S,T>* doubleRotateFromLToR(Node<S,T>* leaf);
	Node<S,T>* rotateFromRToL(Node<S,T>* leaf);
	Node<S,T>* doubleRotateFromRToL(Node<S,T>* leaf);

	void add(S key, T data);
	bool remove(S key, T data);
	Node<S,T>* findMinimal(Node<S,T>* leaf);
	long removeall(S key);
	bool search(S key, T data);
};

template <typename S, typename T>
BinarySearchTree<S,T>::BinarySearchTree()
{
	Initialization();
}

template <typename S, typename T>
BinarySearchTree<S,T>::~BinarySearchTree()
{
	Destroy(root);
}

template <typename S, typename T>
BinarySearchTree<S,T>::BinarySearchTree(BinarySearchTree const & newBst)
{
	Initialization();
	CopyBst(newBst.root,root);
}

template <typename S, typename T>
BinarySearchTree<S,T>& BinarySearchTree<S,T>::operator=(BinarySearchTree const &newBst)
{
	if (this != &newBst)
	{
		Destroy(root);
		CopyBst(newBst.root,root);
	}
	return *this;
}

template <typename S, typename T>
void BinarySearchTree<S,T>::Initialization()
{
	root = NULL;
}

template <typename S, typename T>
void BinarySearchTree<S,T>::Destroy(Node<S,T>* theRoot)
{
	if (!theRoot) return;				
	Destroy(theRoot->left);			
	Destroy(theRoot->right);			
	delete theRoot;					
	Initialization();
}

template <typename S, typename T>
void BinarySearchTree<S,T>::CopyBst(BinarySearchTree const& newBst,BinarySearchTree const& oldBst)
{
	if (!newBst) {					
		oldBst = NULL;				
		return;				
	}
	oldBst = new Node<S,T>();
	oldBst->key = newBst->key;
	oldBst->data = newBst->data;
	oldBst->number = newBst->number;
	oldBst->height = newBst->height;
	copyTree(newBst->left, oldBst->left);		
	copyTree(newBst->right, oldBst->right);
}

template <typename S, typename T>
long BinarySearchTree<S,T>::height(Node<S,T>* leaf)
{
	if (leaf == NULL) return -1;
	else return leaf->height;
}

template <typename S, typename T>
long BinarySearchTree<S,T>::maxHeight(long leftHeight, long rightHeight)
{
	if (leftHeight > rightHeight) return leftHeight;
	else return rightHeight;
}

template <typename S, typename T>
Node<S,T>* BinarySearchTree<S,T>::rotateFromLToR(Node<S,T>* leaf)
{
	Node<S,T>* newLeaf = leaf->left;
	leaf->left = newLeaf->right;
	newLeaf->right = leaf;
	leaf->height = maxHeight(height(leaf->left), height(leaf->right)) + 1;
	newLeaf->height = maxHeight(height(newLeaf->left), leaf->height) + 1;
	return newLeaf;
}

template <typename S, typename T>
Node<S,T>* BinarySearchTree<S,T>::rotateFromRToL(Node<S,T>* leaf)
{
	Node<S,T>* newLeaf = leaf->right;
	leaf->right = newLeaf->left;
	newLeaf->left = leaf;
	leaf->height = maxHeight(height(leaf->left), height(leaf->right)) + 1;
	newLeaf->height = maxHeight(height(newLeaf->right), leaf->height) + 1;
	return newLeaf;
}

template <typename S, typename T>
Node<S,T>* BinarySearchTree<S,T>::doubleRotateFromLToR(Node<S,T>* leaf)
{
	leaf->left = rotateFromRToL(leaf->left);
	return rotateFromLToR(leaf);
}

template <typename S, typename T>
Node<S,T>* BinarySearchTree<S,T>::doubleRotateFromRToL(Node<S,T>* leaf)
{
	leaf->right = rotateFromLToR(leaf->right);
	return rotateFromRToL(leaf);
}

template <typename S, typename T>
void BinarySearchTree<S,T>::add(S key, T data)
{
	if (root!=NULL)
	{
		root=insert(key,data, root);
	}
	else 
	{
		root = new Node<S, T>(key, data);
	}
}

template <typename S, typename T>
Node<S,T>* BinarySearchTree<S,T>::insert(S key,T data, Node<S,T>* leaf)
{
	if (key< leaf->key)
	{
		if (leaf->left != NULL)
			leaf->left=insert(key,data,leaf->left);
		else
		{
			leaf->left = new Node<S,T>(key,data);
		}
		//if the tree is not balanced,we balance it
		if (height(leaf->left) - height(leaf->right) == 2)
		{
			if (key < leaf->left->key) leaf = rotateFromLToR(leaf);
			else leaf = doubleRotateFromLToR(leaf);
		}
	}
	else if (key > leaf->key)
	{
		if (leaf->right != NULL)
			leaf->right=insert(key,data,leaf->right);
		else
		{
			leaf->right = new Node<S,T>(key,data);
		}
		//if the tree is not balanced,we balance it
		if (height(leaf->right) - height(leaf->left) == 2)
		{
			if (key< leaf->right->key) leaf = rotateFromRToL(leaf);
			else leaf = doubleRotateFromRToL(leaf);
		}
	}
	else if (key == leaf->key)
	{
		//if this leaf already exist,we count it once more and do not create new leaf
		if(data==leaf->data)
		{
			leaf->number++;
		}
		//otherwise we add it on the right side
		else
		{
			if (leaf->right != NULL)
				leaf->right = insert(key,data, leaf->right);
			else
			{
				leaf->right = new Node<S,T>(key,data);
			}
			//if the tree is not balanced,we balance it
			if (height(leaf->right) - height(leaf->left) == 2)
			{
				if (key < leaf->right->key) leaf = rotateFromRToL(leaf);
				else leaf = doubleRotateFromRToL(leaf);
			}
		}
	}
	//we update the height of the tree according to the position of the leaf
	leaf->height = maxHeight(height(leaf->left), height(leaf->right)) + 1;
	return leaf;
}

template <typename S, typename T>
bool BinarySearchTree<S,T>::remove(S key, T data)
{
	bool found = false;
	if (root==NULL)
	{
		found = false;
	}

	Node<S,T>* currentLeaf = new Node<S,T>();
	Node<S,T>* parent = new Node<S,T>();
	currentLeaf = root;

	while (currentLeaf != NULL)
	{
		if (key == currentLeaf->key)
		{
			if(data==currentLeaf->data)
			{
				found = true;
				break;
			}
			//if we have found the same key but different data,we check on the right
			else
			{
				parent = currentLeaf;
				currentLeaf = currentLeaf->right;
			}
		}
		else
		{
			parent = currentLeaf;
			if (key < currentLeaf->key) currentLeaf = currentLeaf->left;
			else currentLeaf = currentLeaf->right;
		}
	}
	if (!found)
	{
		return false;
	}
	//the current leaf has only one child
	if ((currentLeaf->left == NULL && currentLeaf->right != NULL) || (currentLeaf->left != NULL && currentLeaf->right == NULL))
	{
		//the current leaf has only right child
		if (currentLeaf->left == NULL && currentLeaf->right != NULL)
		{
			if (parent->left == currentLeaf)
			{
				parent->left = currentLeaf->right;
				delete currentLeaf;
			}
			else
			{
				parent->right = currentLeaf->right;
				if (currentLeaf == root) root = parent->right;
				delete currentLeaf;
			}
		}
		//the current leaf has only left child
		else
		{
			if (parent->left == currentLeaf)
			{
				parent->left = currentLeaf->left;
				delete currentLeaf;
			}
			else
			{
				parent->right = currentLeaf->left;
				if (currentLeaf == root) root = parent->right;
				delete currentLeaf;
			}
		}
		return true;
	}
	//the current leaf has no children
	if (currentLeaf->left == NULL && currentLeaf->right == NULL)
	{
		if (currentLeaf == root) Destroy(root);
		else
		{
			if (parent->left == currentLeaf) parent->left = NULL;
			else parent->right = NULL;
			delete currentLeaf;
		}
		return true;
	}

	//the current leaf has 2 children
	//we find the smallest value on the right and put it on the current leaf's place
	if (currentLeaf->left != NULL && currentLeaf->right != NULL)
	{
		Node<S,T>* findTheSmallest=new Node<S,T>();
		findTheSmallest = currentLeaf->right;
		//the right child has no children
		if ((findTheSmallest->left == NULL) && (findTheSmallest->right == NULL))
		{
			if (currentLeaf == root) root = findTheSmallest;
			currentLeaf = findTheSmallest;
			delete findTheSmallest;
			currentLeaf->right = NULL;
		}
		//the right child has chlidren
		else 
		{
			//if it has a left child,we search deeper to find the smallest element
			if ((currentLeaf->right)->left != NULL)
			{
				Node<S,T>* leftSmallest=new Node<S,T>();
				Node<S,T>* rightChild=new Node<S,T>();
				rightChild = currentLeaf->right;
				leftSmallest = (currentLeaf->right)->left;
				while (leftSmallest->left != NULL)
				{
					rightChild = leftSmallest;
					leftSmallest = leftSmallest->left;
				}
				if (currentLeaf == root)
				{
					root->key = leftSmallest->key;
					root->data = leftSmallest->data;
					root->number = leftSmallest->number;
				}
				currentLeaf->key = leftSmallest->key;
				currentLeaf->data = leftSmallest->data;
				currentLeaf->number = leftSmallest->number;
				delete leftSmallest;
				rightChild->left = NULL;
			}
			else
			{
				Node<S,T>* temporary=new Node<S,T>();
				temporary = currentLeaf->right;
				if (currentLeaf == root)
				{
					root->key = temporary->key;
					root->data = temporary->data;
					root->number = temporary->number;
					root->right = temporary->right;
				}
				currentLeaf->key = temporary->key;
				currentLeaf->data = temporary->data;
				currentLeaf->number = temporary->number;
				currentLeaf->right = temporary->right;
				delete temporary;
			}

		}
		return true;
	}
	return false;
}

template <typename S, typename T>
Node<S,T>* BinarySearchTree<S,T>::findMinimal(Node<S,T>* leaf)
{
	while (NULL != leaf->left) leaf = leaf->left;
	return leaf;
}

template <typename S, typename T>
long BinarySearchTree<S,T>::removeall(S key)
{
	long count = 0;
	return delall(key,count,root);
}

template <typename S, typename T>
long BinarySearchTree<S,T>::delall(S key,long count, Node<S,T>* leaf)
{
	bool found = false;
	if (root==NULL)
	{
		found = false;
	}

	Node<S,T>* currentLeaf;
	Node<S,T>* parent=new Node<S,T>();
	currentLeaf = root;

	while (currentLeaf != NULL)
	{
		if (currentLeaf->key == key)
		{
				found = true;
				count+=(currentLeaf->number);
				break;
		}
		else
		{
			parent = currentLeaf;
			if (key > currentLeaf->key) currentLeaf = currentLeaf->right;
			else currentLeaf = currentLeaf->left;
		}
	}
	if (!found)
	{
		return count;
	}
	//the current leaf has only one child
	if ((currentLeaf->left == NULL && currentLeaf->right != NULL) || (currentLeaf->left != NULL && currentLeaf->right == NULL))
	{
		//the current leaf has only right child
		if (currentLeaf->left == NULL && currentLeaf->right != NULL)
		{
			if (parent->left == currentLeaf)
			{
				parent->left = currentLeaf->right;
				delete currentLeaf;
			}
			else
			{
				parent->right = currentLeaf->right;
				if (currentLeaf == root) root = parent->right;
				delete currentLeaf;
			}
		}
		//the current leaf has only left child
		else
		{
			if (parent->left == currentLeaf)
			{
				parent->left = currentLeaf->left;
				delete currentLeaf;
			}
			else
			{
				parent->right = currentLeaf->left;
				if (currentLeaf == root) root = parent->right;
				delete currentLeaf;
			}
		}
		count = delall(key, count, root);
	}
	//the current leaf has no children
	if (currentLeaf->left == NULL && currentLeaf->right == NULL)
	{
		if (currentLeaf == root) Destroy(root);
		else
		{
			if (parent->left == currentLeaf) parent->left = NULL;
			else parent->right = NULL;
			delete currentLeaf;
		}
		count = delall(key, count, root);
	}

	//the current leaf has 2 children
	//we find the smallest value on the right and put it on the current leaf's place
	if (currentLeaf->left != NULL && currentLeaf->right != NULL)
	{
		Node<S,T>* findTheSmallest = new Node<S,T>();
		findTheSmallest = currentLeaf->right;
		//the right child has no chlidren
		if ((findTheSmallest->left == NULL) && (findTheSmallest->right == NULL))
		{
			if (currentLeaf == root)
			{
				root->key = findTheSmallest->key;
				root->data = findTheSmallest->data;
				root->number = findTheSmallest->number;
			}
			currentLeaf = findTheSmallest;
			delete findTheSmallest;
			currentLeaf->right = NULL;
		}
		//the right chlid has children
		else 
		{
			//if it has a left child,we search deeper to find the smallest element
			if ((currentLeaf->right)->left != NULL)
			{
				Node<S,T>* leftSmallest = new Node<S,T>();
				Node<S,T>* rightChild = new Node<S,T>();
				rightChild = currentLeaf->right;
				leftSmallest = (currentLeaf->right)->left;
				while (leftSmallest->left != NULL)
				{
					rightChild = leftSmallest;
					leftSmallest = leftSmallest->left;
				}
				if (currentLeaf == root)
				{
					root->key = leftSmallest->key;
					root->data = leftSmallest->data;
					root->number = leftSmallest->number;
				}
				currentLeaf->key = leftSmallest->key;
				currentLeaf->data = leftSmallest->data;
				currentLeaf->number = leftSmallest->number;
				delete leftSmallest;
				rightChild->left = NULL;
			}
			else
			{
				Node<S,T>* temporary = new Node<S,T>();
				temporary = currentLeaf->right;
				if (currentLeaf == root)
				{
					root->key = temporary->key;
					root->data = temporary->data;
					root->number = temporary->number;
					root->right = temporary->right;
				}
				currentLeaf->key = temporary->key;
				currentLeaf->data = temporary->data;
				currentLeaf->number = temporary->number;
				currentLeaf->right = temporary->right;
				delete temporary;
			}

		}
		count = delall(key, count, root);
	}
	return count;
}

template <typename S, typename T>
bool BinarySearchTree<S,T>::search(S key, T data)
{
	return find(key,data, root);
}

template <typename S, typename T>
bool BinarySearchTree<S,T>::find(S key,T data, Node<S,T>* leaf)
{
	if (leaf == NULL) return false;
	//if the key is smaller than the leaf key,we search on the left
	else if (key < leaf->key)
	{
		return find(key,data, leaf->left);
	}
	//if the key is bigger than the leaf key,we search on the right
	else if (key > leaf->key)
	{
		return find(key,data, leaf->right);
	}
	//if the key is the same
	else if (key == leaf->key)
	{
		//if the data is the same,we have found the element
		if(data==leaf->data)
		{
			return true;
		}
		//otherwise we search on the right
		else
		{
			return find(key,data, leaf->right);
		}
	}
	return false;
}