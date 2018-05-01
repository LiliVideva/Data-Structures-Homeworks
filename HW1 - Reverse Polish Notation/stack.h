/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Lilyana Videva
* @idnumber 61887
* @task 1
* @compiler VC
*
*/

#pragma once

template<typename T>
class Stack
{
	class Elements 
	{
	public:
		T data;
		Elements* next;
		Elements(T, Elements* = NULL);
	};
private:
	Elements* top;
	size_t space;
public:
	Stack();
	~Stack();
	Stack(Stack const & st);
	Stack& operator=(Stack const & newStack);
private:
	void Initialization();
	void Destroy();
	void CopyStack(Stack const & newStack);
public:
	void Push(const T & element);
	bool Pop(T& element);
	void RemoveAll();
	size_t GetSize() const;
	bool IsEmpty() const;
};

template <typename T>
Stack<T>::Elements::Elements(T data, Elements* next)
{
	this->data = data;
	this->next = next;
}

template<typename T>
Stack<T>::Stack()
{
	Initialization();
}

template<typename T>
Stack<T>::~Stack()
{
	Destroy();
}

template<typename T>
Stack<T>::Stack(Stack const & newStack)
{
	Initialization();
	CopyStack(newStack);
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack const &newStack)
{
	if (this != &newStack)
	{
		Destroy();
		CopyStack(newStack);
	}
	return *this;
}

template<typename T>
void Stack<T>::Initialization()
{
	top = 0;
	space = 0;
}

template <typename T>
void Stack<T>::Destroy()
{
	Elements* temporary;

	while (top)
	{
		temporary = top;
		top = top->next;
		delete temporary;
	}

	Initialization();
}

template<typename T>
void Stack<T>::CopyStack(Stack const& newStack)
{
	if (newStack.IsEmpty()) return;
	Stack<T>::Elements *backwards, *forwards;
	try
	{
		top = new Elements(newStack.top->data);

		backwards = top;
		forwards = newStack.top->next;

		while (forwards)
		{
			backwards->next = new Elements(forwards->data);
			backwards = backwards->next;
			forwards = forwards->next;
		}

		space = newStack.space;
	}
	catch (std::bad_alloc&)
	{
		Destroy();
		throw;
	}
}

template<typename T>
void Stack<T>::Push(const T & element)
{
	top = new Elements(element, top);
	space++;
}

template<typename T>
bool Stack<T>::Pop(T & element)
{
	if (space == 0)
		return false;

	element = top->data;

	Elements* old = top;
	top = top->next;
	delete old;

	space--;

	return true;
}

template<class T>
void Stack<T>::RemoveAll()
{
	Destroy();
}

template<typename T>
size_t Stack<T>::GetSize() const
{
	return space;
}

template<typename T>
bool Stack<T>::IsEmpty() const
{
	return (space == 0);
}

