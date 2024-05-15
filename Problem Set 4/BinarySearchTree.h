#pragma once
#include "BinaryTreeNode.h"
#include <stdexcept>

template<typename T>
class BinarySearchTreeIterator;

template<typename T>
class BinarySearchTree
{
private:
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;

    BTreeNode fRoot;

public:
    BinarySearchTree() : fRoot(&BNode::NIL) {}

    ~BinarySearchTree()
    {
        while (!empty())
        {
            remove(fRoot->key);
        }
    }

    bool empty() const
    {
        return fRoot == &BNode::NIL;
    }

    size_t height() const
    {
        if (empty())
        {
            throw std::domain_error("Empty tree has no height.");
        }
        return fRoot->height();
    }

    bool insert(const T& aKey)
    {
        if (empty())
        {
            fRoot = new BNode(aKey);
            return true;
        }
        return fRoot->insert(aKey);
    }

    bool remove(const T& aKey)
    {
        if (empty())
        {
            throw std::domain_error("Cannot remove from an empty tree.");
        }

        if (fRoot->key == aKey && fRoot->leaf())
        {
            delete fRoot;
            fRoot = &BNode::NIL;
            return true;
        }

        return fRoot->remove(aKey, nullptr);
    }

    // Problem 3 methods
    using Iterator = BinarySearchTreeIterator<T>;

    friend class BinarySearchTreeIterator<T>; 

    Iterator begin() const
    {
        return Iterator(*this).begin();
    }

    Iterator end() const
    {
        return Iterator(*this).end();
    }
};
