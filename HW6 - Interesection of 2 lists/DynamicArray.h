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

//class, responsible for creating a dynamic array and inserting elements in it
class DynamicArray
{
private:
	size_t size, space;

	//help functions for resizing the array if it's capacity is not enough
	void ensureSize(size_t size);
	void resize(size_t newSpace);
public:
	size_t* data;

	DynamicArray(int initialSpace = 16);
	~DynamicArray();
	void append(const size_t& element);
	void clear();
	size_t getSize() const;
};

DynamicArray::DynamicArray(int initialSpace)
{
	data = nullptr;
	size = 0;
	space = initialSpace;
	assert(initialSpace > 0);
	data = new size_t[space];
}

DynamicArray::~DynamicArray()
{
	clear();
}

void DynamicArray::append(const size_t& element)
{
	ensureSize(size + 1);
	data[size] = element;
	++size;
}

void DynamicArray::clear()
{
	delete[] data;
	data = nullptr;
	size = 0;
	space = 16;
	data = new size_t[space];
}

size_t DynamicArray::getSize() const
{
	return size;
}

void DynamicArray::ensureSize(size_t size)
{
	assert(!data || space != 0);

	size_t newSize = data ? space : 1;
	while (newSize < size)
		newSize *= 2;

	if (newSize != space)
		resize(newSize);
}

void DynamicArray::resize(size_t newSpace)
{
	size_t* newData = new size_t[newSpace];

	for (size_t i = 0; i < size && i < newSpace; ++i)
		newData[i] = data[i];

	delete[] data;
	data = newData;
	space = newSpace;
	size = size < space ? size : space;
}
