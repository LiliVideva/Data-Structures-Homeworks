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

#include<iostream>
#include"stdafx.h"
#include"List.h"
#include"DynamicArray.h"

//help function for combining two lists
List* combineLists(List* first, List* second, size_t size)
{
	//variable that will store the new list
	List* combinedList = new List();
	DynamicArray* arr = new DynamicArray(size);
	size_t i = 0;
	//add all of the first list's elements in the dynamic array
	while (first != NULL)
	{
		arr->data[i] = first->data;
		first = first->next;
		i++;
	}
	while (second != NULL)
	{
		//check every element in the array if it is the same as the current one in the second list
		for (size_t k = 0; k < size; k++)
		{
			if (arr->data[k] == second->data)
			{
				//if there is a next element in the new list
				if (combinedList->next != NULL || combinedList->data != NULL)
				{
					//if the value in the list is smaller or equal as the data in the array,
					//the data from the array is inserted after the proper element in the new list
					if (combinedList->data <= arr->data[k])
					{
						while (combinedList->next != NULL && combinedList->next->data <= arr->data[k])
						{
							combinedList->next = combinedList->next->next;
						}
						insertAfter(combinedList, arr->data[k]);
					}
					//otherwise it is inserted before the current element in the list,
					//because the data in the array has a smaller value
					else
					{
						insertBefore(combinedList, arr->data[k]);
					}
				}
				//if there is no next element, the value is inserted at the beginning
				else insertBegin(combinedList, arr->data[k]);
			}
		}
		second = second->next;
	}
	return combinedList;
}

//function, creating the intersection of elements of the two lists
List* intersectionOfLists(List* first, List* second)
{
	//variable that will store the new list
	List* combinedList = new List();
	//creating a dynamic array with the size of the smaller list
	size_t size1 = getSize(first), size2 = getSize(second);
	size_t size = (size1 < size2) ? size1 : size2;
	//if the size is the same as the size of the first list and different from the size of the second one
	if (size == size1 && size != size2)
	{
		//we call the help function with the following arguments
		combinedList = combineLists(first, second, size);
	}
	//otherwise we switch the places of the first two arguments
	else combinedList = combineLists(second, first, size);
	return combinedList;
}

int main()
{
	//an example, how the program works
	List* first = new List();
	List* second = new List();
	insertBegin(first, 1);
	insertBefore(first, 102);
	insertBefore(first, 37);
	insertBefore(first, 64);
	insertBefore(first, 45);
	insertBefore(first, 5);
	insertBegin(second, 5);
	insertBefore(second, 256);
	insertBefore(second, 37);
	insertBefore(second, 45);
	insertBefore(second, 1);
	std::cout << getSize(first) << " " << getSize(second) << std::endl;
	List* combinedList = intersectionOfLists(first, second);
	//printing the intersection of the two lists
	while (combinedList != NULL)
	{
		std::cout << combinedList->data << std::endl;
		combinedList = combinedList->next;
	}
	//free the allocated space
	delete first;
	delete second;
	delete combinedList;
	return 0;
}