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

template<typename S, typename T>
class Node
{
public:
	S key;
	T data;
	long number;
	long height;
	Node* left;
	Node* right;
	Node();
	Node(S, T, long = 0, long = 1, Node* = NULL, Node* = NULL);
};

template <typename S, typename T>
Node<S, T>::Node()
{
	key = 0;
	number = 1;
	height = 0;
	left = NULL;
	right = NULL;
}

template <typename S, typename T>
Node<S, T>::Node(S key, T data, long height, long number, Node* left, Node* right)
{
	this->key = key;
	this->data = data;
	this->number = number;
	this->height = height;
	this->left = left;
	this->right = right;
}

