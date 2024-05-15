
// COS30008, Problem Set 4, Problem 3, 2022

#pragma once
#include "BinarySearchTree.h"
#include <stack>

template<typename T>
class BinarySearchTreeIterator
{
private:
    using BSTree = BinarySearchTree<T>;
    using BNode = BinaryTreeNode<T>;
    using BTreeNode = BNode*;
    using BTNStack = std::stack<BTreeNode>;

    const BSTree& fBSTree; 
    BTNStack fStack; 

    void pushLeft(BTreeNode aNode)
    {
        while (aNode != &BNode::NIL) 
        {
            fStack.push(aNode);
            aNode = aNode->left;
        }
    }

public:
    using Iterator = BinarySearchTreeIterator<T>;

    BinarySearchTreeIterator(const BSTree& aBSTree) : fBSTree(aBSTree), fStack()
    {
        pushLeft(fBSTree.fRoot); 
    }

    const T& operator*() const
    {
        return fStack.top()->key;
    }

    Iterator& operator++()
    {

        BTreeNode lPopped = fStack.top();
        fStack.pop();
        if (lPopped->right != &BNode::NIL) {
            BTreeNode lCurrent = lPopped->right;
            while (lCurrent != &BNode::NIL) {
                fStack.push(lCurrent);
                lCurrent = lCurrent->left;
            }
        }

        if (!fStack.empty()) {
            fStack.top();
        }

        return *this;
    }

    Iterator operator++(int)
    {
        Iterator lTemp = *this;

        BTreeNode lPopped = fStack.top();
        fStack.pop();

        if (lPopped->right != &BNode::NIL) {
            BTreeNode lCurrent = lPopped->right;
            while (lCurrent != &BNode::NIL) {
                lTemp.fStack.push(lCurrent);
                lCurrent = lCurrent->left;
            }
        }

        if (!lTemp.fStack.empty()) {
            BTreeNode lNode = lTemp.fStack.top();
            lTemp.fStack.pop();
            lTemp.fStack.push(lNode);
        }

        return lTemp;
    }

    bool operator==(const Iterator& aOtherIter) const
    {
        if (fStack.empty() && aOtherIter.fStack.empty())
            return true; 
        if (fStack.empty() || aOtherIter.fStack.empty())
            return false; 
        return fStack.top() == aOtherIter.fStack.top(); 
    }

    bool operator!=(const Iterator& aOtherIter) const
    {
        return !(*this == aOtherIter);
    }

    Iterator begin() const
    {
        Iterator lTemp(*this); 
        while (!lTemp.fStack.empty()) {
            lTemp.fStack.pop();
        }

        BTreeNode lCurrent = lTemp.fBSTree.fRoot;
        while (lCurrent != &BNode::NIL) {
            lTemp.fStack.push(lCurrent);
            lCurrent = lCurrent->left;
        }
        return lTemp;
    }

    Iterator end() const
    {
        Iterator lTemp(*this); 
        while (!lTemp.fStack.empty()) {
            lTemp.fStack.pop();
        }
        return lTemp;
    }
};
