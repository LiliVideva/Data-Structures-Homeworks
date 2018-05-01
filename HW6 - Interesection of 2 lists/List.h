/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Lilyana Videva
* @idnumber 61887
* @task 6.1
* @compiler VC
*
*/

#pragma once
#include<iostream>
#include<assert.h>

//class for creating a list of elements
class List {
public:
	size_t data;
	List* next;
	List(size_t = NULL, List* = NULL);
};

void insertBefore(List* element, size_t data);
void insertAfter(List* element, size_t data);
size_t getSize(List* element);

List::List(size_t data, List* next)
{
	this->data = data;
	this->next = next;
}

//functions for adding elements in a list at the beginning, before and after an element
void insertBegin(List* element, size_t data)
{
	element->data = data;
}

void insertAfter(List* element, size_t data)
{
	List* temporary = new List();
	temporary->data = data;
	temporary->next = element->next;
	element->next = temporary;
}

void insertBefore(List* element, size_t data)
{
	List* temporary = new List();
	*temporary = *element;
	element->data = data;
	element->next = temporary;

}

size_t getSize(List* element)
{
	size_t space = 0;
	while (element->next != NULL)
	{
		space++;
		element = element->next;
	}
	if (space>0) space++;
	return space;
}