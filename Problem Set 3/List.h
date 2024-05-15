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

	List() : fRoot(nullptr), fCount(0) {} // default constructor     

	List(const List& aOtherList) : fRoot(nullptr), fCount(0) {
		*this = aOtherList;
	}// copy constructor

	List& operator=(const List& aOtherList) {

		if (&aOtherList != this) {

			this->~List();
			this->fCount = 0;

			for (auto& element : aOtherList)
			{
				this->push_back(element);
			}
		}
		return *this;
	} // assignment operator

	~List()
	{
		while (fRoot != nullptr)
		{
			if (fRoot != &fRoot->getPrevious())
			{
				Node* lTemp = const_cast<Node*>(&fRoot->getPrevious());
				lTemp->isolate();
				delete lTemp;
			}
			else
			{
				delete fRoot;
				break;
			}
		}
	} // destructor - frees all nodes

	bool isEmpty() const {
		return fRoot == nullptr;
	}// Is list empty?

	size_t size() const {
		return fCount;
	}                       // list size

	void push_front(const T& aElement)
	{
		if (isEmpty())
		{
			fRoot = new Node(aElement);
		}
		else
		{
			Node* lNode = new Node(aElement);
			fRoot->push_front(*lNode);
			fRoot = lNode;
		}
		fCount++;
	} // adds aElement at front

	void push_back(const T& aElement) {

		Node* node = new Node(aElement);
		if (!isEmpty()) {
			fRoot->push_front(*node);
		}
		else {
			fRoot = node;
		}
		fCount++;
	} // adds element at back  

	void remove(const T& aElement)
	{
		Node* lNode = fRoot;
		while (lNode != nullptr) {
			if (**lNode == aElement) {
				if (fCount != 1) {
					if (lNode == fRoot) {
						fRoot = const_cast<Node*>(&fRoot->getNext());
					}
				}
				else {
					fRoot = nullptr;
				}
				lNode->isolate();
				delete lNode;
				fCount--;
				return;
			}
			if (lNode != &fRoot->getPrevious()) {
				lNode = const_cast<Node*>(&lNode->getNext());
			}
			else {
				lNode = nullptr;
			}
		}
	}

	const T& operator[](size_t aIndex) const
	{
		if (aIndex >= fCount || aIndex < 0)
		{
			throw std::out_of_range("Index out of bounds.");
		}

		Iterator iterator = Iterator(fRoot).begin();
		for (size_t i = 0; i < aIndex; i++)
		{
			iterator++;
		}
		return *iterator;
	} // list indexer

	Iterator begin() const
	{
		return Iterator(fRoot).begin();
	} // return a forward iterator

	Iterator end() const
	{
		return Iterator(fRoot).end();
	} // return a forward end iterator

	Iterator rbegin() const
	{
		return Iterator(fRoot).rbegin();
	} // return a backwards iterator

	Iterator rend() const
	{
		return Iterator(fRoot).rend();
	} // return a backwards end iterator                 


	List(List&& aOtherList) : fRoot(nullptr), fCount(0) {
		*this = std::move(aOtherList);
	}// move constructor

	List& operator=(List&& aOtherList) {
		if (&aOtherList != this) {

			this->~List();
			this->fCount = 0;

			for (auto& element : aOtherList)
			{
				this->push_back(std::move(element));
			}
		}

		return *this;
	}// move assignment operator

	void push_front(T&& aElement) {

		if (isEmpty())
		{
			fRoot = new Node(aElement);
		}
		else
		{
			Node* lNode = new Node(std::move(aElement));
			fRoot->push_front(*lNode);
			fRoot = lNode;
		}
		fCount++;
	} // adds aElement at front

	void push_back(T&& aElement) {
		Node* node = new Node(std::move(aElement));

		if (!isEmpty()) {
			fRoot->push_front(*node);
		}
		else {
			fRoot = node;
		}
		fCount++;
	} // adds aElement at back
};
