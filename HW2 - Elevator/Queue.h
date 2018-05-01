/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Lilyana Videva
* @idnumber 61887
* @task 2
* @compiler VC
*
*/

#pragma once
#include<assert.h>

template <typename T>
class Queue
{
public:
	Queue();
	~Queue();
	Queue(Queue const & newQueue);
	Queue& operator=(Queue const & newQueue);

	void Enqueue(const T &);
	T Dequeue();
	T& GetFront();
	size_t GetSize() const;
	bool IsEmpty() const;

private:
	T *data;
	size_t size;
	size_t max_size;
	const size_t capacity = 2;
	size_t front;
	size_t back;

	void Initialization();
	void Destroy();
	void CopyQueue(Queue const & newQueue);
	void Resize();
};

template <typename T>
Queue<T>::Queue()
{
	Initialization();
}

template <typename T>
Queue<T>::~Queue()
{
	Destroy();
}

template <typename T>
Queue<T>::Queue(Queue const &newQueue)
{
	Initialization();
	CopyQueue(newQueue);
}

template <typename T>
Queue<T>& Queue<T>::operator=(Queue const &newQueue)
{
	if (this != &newQueue)
	{
		Destroy();
		CopyQueue(newQueue);
	}
	return *this;
}

template<typename T>
void Queue<T>::Initialization()
{
	data = new T[capacity];
	size = 0;
	max_size = capacity;
	front = back = 0;
}

template <typename T>
void Queue<T>::Destroy()
{
	delete[]data;

	Initialization();
}

template<typename T>
void Queue<T>::CopyQueue(Queue const& newQueue)
{
	if (newQueue.IsEmpty()) return;
	try
	{
		size = newQueue.size;
		max_size = newQueue.max_size;
		front = newQueue.front;
		back = newQueue.back;
		data = new T[max_size];
		for (size_t i = 0; i<size; i++)
			data[i] = newQueue.data[i];
	}
	catch (std::bad_alloc&)
	{
		Destroy();
		throw;
	}
}

template <typename T>
void Queue<T>::Enqueue(const T &element)
{
	if (size >= max_size)
		Resize();
	data[size] = element;
	back++;
	size++;
}
template <typename T>
T Queue<T>::Dequeue()
{
	T temp = data[0];
	for (size_t i = 0; i < size - 1; i++)
	{
		data[i] = data[i + 1];
	}
	front++;
	size--;
	return temp;
}

template <typename T>
T& Queue<T>::GetFront()
{
	assert(size != 0);
	return data[0];
}


template <typename T>
size_t Queue<T>::GetSize() const
{
	return size;
}

template <typename T>
bool Queue<T>::IsEmpty() const
{
	return (size == 0);
}

template <typename T>
void Queue<T>::Resize()
{
	max_size = k;
	T *temp = new T[max_size];
	for (size_t i = 0; i < size; i++)
	{
		temp[i] = data[i];
	}
	delete[]data;
	data = temp;
	front = 0;
	back = max_size - k;
}