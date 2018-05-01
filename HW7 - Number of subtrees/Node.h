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

//class, representing an element of the tree and its connections to the next elements
class Node
{
public:
	size_t data;
	size_t elements;
	Node* right;
	Node* left;
	Node(size_t, size_t = 0, Node* = NULL, Node* = NULL);
};

Node::Node(size_t data, size_t elements, Node* right, Node* left)
{
	this->data = data;
	this->elements = elements;
	this->right = right;
	this->left = left;
}