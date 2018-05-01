/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Lilyana Videva
* @idnumber 61887
* @task 5
* @compiler VC
*
*/

#pragma once
#include"stdafx.h"
#include"Node.h"

//class, responsible for building a tree for search and applying common operations on it like adding, searching for and printing elements
class SearchTree
{
public:
	SearchTree();
	~SearchTree();
	void add(int64_t data);
	bool search(int64_t data);
	void print(std::ostream &os, size_t n);
private:
	Node* root;

	void initialization();
	void destroy(Node* leaf);
	Node* insert(int64_t data, Node* leaf);
	bool find(int64_t data, Node* leaf);
	void printNode(Node* leaf, std::ostream &os, size_t n);
};

SearchTree::SearchTree()
{
	initialization();
}

SearchTree::~SearchTree()
{
	destroy(root);
}

void SearchTree::add(int64_t data)
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

bool SearchTree::search(int64_t data)
{
	return find(data, root);
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

Node* SearchTree::insert(int64_t data, Node* leaf)
{
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

bool SearchTree::find(int64_t data, Node* leaf)
{
	if (leaf == NULL) return false;
	else if (data < leaf->data)
	{
		return find(data, leaf->left);
	}
	else if (data > leaf->data)
	{
		return find(data, leaf->right);
	}
	else
	{
		(leaf->common)++;
		return true;
	}

	return false;
}

void SearchTree::print(std::ostream &os, size_t n)
{
	printNode(root, os, n);
}

void SearchTree::printNode(Node* leaf, std::ostream &os, size_t n)
{

	if (leaf == NULL) return;
	if (leaf->common == n)
	{
		os << leaf->data << std::endl;
	}
	printNode(leaf->left, os, n);
	printNode(leaf->right, os, n);

}