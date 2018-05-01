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

//class, representing an element of the tree and its connections to the next elements
class Node
{
public:
	int64_t data;
	int64_t common;
	Node* right;
	Node* left;
	Node(int64_t, int64_t = 0, Node* = NULL, Node* = NULL);
};

Node::Node(int64_t data, int64_t common, Node* right, Node* left)
{
	this->data = data;
	this->common = common;
	this->right = right;
	this->left = left;
}
