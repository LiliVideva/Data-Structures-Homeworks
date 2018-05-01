/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Lilyana Videva
* @idnumber 61887
* @task 6.2
* @compiler VC
*
*/

#pragma once
#include"stdafx.h"
#include"Node.h"

//class, responsible for building a tree for search and applying common operations on it like adding and printing elements
//and checking for subtrees with a concrete number of elements
class SearchTree
{
public:
	SearchTree();
	~SearchTree();
	void add(size_t data);
	void print(std::ostream &os);
	size_t checkElements(size_t n);
private:
	Node* root;

	void initialization();
	void destroy(Node* leaf);
	Node* insert(size_t data, Node* leaf);
	void printNode(Node* leaf, std::ostream &os);
	size_t checkElem(Node* leaf, size_t n, size_t count);
};

SearchTree::SearchTree()
{
	initialization();
}

SearchTree::~SearchTree()
{
	destroy(root);
}

void SearchTree::add(size_t data)
{
	if (root == NULL)
	{
		root = new Node(data);
	}
	else
	{
		root = insert(data, root);
	}
}

void SearchTree::initialization()
{
	root = NULL;
}

void SearchTree::destroy(Node* leaf)
{
	if (!leaf) return;
	destroy(leaf->right);
	destroy(leaf->left);
	delete leaf;
	initialization();
}

Node* SearchTree::insert(size_t data, Node* leaf)
{
	(leaf->elements)++;
	if (data < leaf->data)
	{
		if (leaf->left != NULL)
		{
			leaf->left = insert(data, leaf->left);
		}
		else
			leaf->left = new Node(data);
	}
	else if (data > leaf->data)
	{
		if (leaf->right != NULL)
		{
			leaf->right = insert(data, leaf->right);
		}
		else
			leaf->right = new Node(data);
	}
	return leaf;
}

void SearchTree::print(std::ostream &os)
{
	printNode(root, os);
}

void SearchTree::printNode(Node* leaf, std::ostream &os)
{

	if (leaf == NULL) return;
	os << leaf->data << std::endl;
	printNode(leaf->left, os);
	printNode(leaf->right, os);

}

size_t SearchTree::checkElements(size_t n)
{
	size_t count = 0;
	if (root != NULL) return checkElem(root, n, count);
	else return count;
}

//every leaf holds the number of leafs before it, so the checking then will be simple with a counter
size_t SearchTree::checkElem(Node* leaf, size_t n, size_t count)
{
	if (leaf == NULL) return count;
	if (n == leaf->elements) ++count;
	count = checkElem(leaf->right, n, count);
	count = checkElem(leaf->left, n, count);
	return count;
}