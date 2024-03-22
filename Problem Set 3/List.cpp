#include "List.h"

using namespace std;

template<typename T>
List<T>::List() : fRoot(nullptr), fCount(0) {}

template<typename T>
List<T>::~List() {
    while (fRoot != nullptr) {
        if (fRoot->getPrevious() != nullptr) {
            Node* temp = fRoot->getPrevious();
            temp->isolate();
            delete temp;
        }
        else {
            delete fRoot;
            break;
        }
    }
}

template<typename T>
bool List<T>::isEmpty() const {
    return fRoot == nullptr;
}


template<typename T>
size_t List<T>::size() const {
    return fCount;
}

template<typename T>
void List<T>::push_front(const T& aElement) {
    if (isEmpty()) {
        fRoot = new Node(aElement);
    }
    else {
        Node* lNode = new Node(aElement);
        fRoot->push_front(*lNode);
        fRoot = lNode;
    }
    ++fCount;
}

template<typename T>
void List<T>::remove(const T& aElement) {
    Node* lNode = fRoot;
    while (lNode != nullptr) {
        if (*lNode->getData() == aElement) {
            if (fCount != 1) {
                if (lNode == fRoot) {
                    fRoot = lNode->getNext();
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
        if (lNode != fRoot->getPrevious()) {
            lNode = lNode->getNext();
        }
        else {
            lNode = nullptr;
        }
    }
}

template<typename T>
typename List<T>::Iterator List<T>::begin() const {
    return Iterator(fRoot).begin();
}


template<typename T>
typename List<T>::Iterator List<T>::end() const {
    return Iterator(fRoot).end();
}


template<typename T>
typename List<T>::Iterator List<T>::rbegin() const {
    return Iterator(fRoot).rbegin();
}


template<typename T>
typename List<T>::Iterator List<T>::rend() const {
    return Iterator(fRoot).rend();
}


