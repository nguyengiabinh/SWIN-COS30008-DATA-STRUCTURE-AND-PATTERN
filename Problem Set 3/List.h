#pragma once

#include "DoublyLinkedList.h"
#include "DoublyLinkedListIterator.h"
#include <stdexcept>

template<typename T>
class List
{
private:
	// auxiliary definition to simplify node usage
	using Node = DoublyLinkedList<T>;

	Node* fRoot;        // the first element in the list
	size_t fCount;      // number of elements in the list

public:
	// auxiliary definition to simplify iterator usage
	using Iterator = DoublyLinkedListIterator<T>;

	List();                                    // default constructor
	List(const List& aOtherList);            // copy constructor
	List& operator=(const List& aOtherList); // assignment operator
	~List();                                   // destructor - frees all nodes

	bool isEmpty() const;                      // Is list empty?
	size_t size() const;                       // list size

	void push_front(const T& element);       // adds element at front
	void push_back(const T& element);        // adds element at back  
	void remove(const T& element);           // remove first match from list

	const T& operator[](size_t index) const; // list indexer

	Iterator begin() const;                    // return a forward iterator
	Iterator end() const;                      // return a forward iterator
	Iterator rbegin() const;                   // return a backwards iterator
	Iterator rend() const;                     // return a backwards iterator

	// move features
	List(List&& aOtherList);                 // move constructor
	List& operator=(List&& aOtherList);      // move assignment operator
	void push_front(T&& element);            // adds rvalue element at front
	void push_back(T&& element);             // adds element at back
};
