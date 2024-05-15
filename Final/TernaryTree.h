// COS30008, Final Exam, 2022

#pragma once

#include <stdexcept>
#include <algorithm>

using namespace std;

template<typename T>
class TernaryTreePrefixIterator;

template<typename T>
class TernaryTree
{
public:

    using TTree = TernaryTree<T>;
    using TSubTree = TTree*;

private:

    T fKey;
    TSubTree fSubTrees[3];

    // private default constructor used for declaration of NIL
    TernaryTree() :
        fKey(T())
    {
        for (size_t i = 0; i < 3; i++)
        {
            fSubTrees[i] = &NIL;
        }
    }

public:

    using Iterator = TernaryTreePrefixIterator<T>;

    static TTree NIL;           // sentinel

    // getters for subtrees
    const TTree& getLeft() const { return *fSubTrees[0]; }
    const TTree& getMiddle() const { return *fSubTrees[1]; }
    const TTree& getRight() const { return *fSubTrees[2]; }

    // add a subtree
    void addLeft(const TTree& aTTree) { addSubTree(0, aTTree); }
    void addMiddle(const TTree& aTTree) { addSubTree(1, aTTree); }
    void addRight(const TTree& aTTree) { addSubTree(2, aTTree); }

    // remove a subtree, may through a domain error
    const TTree& removeLeft() { return removeSubTree(0); }
    const TTree& removeMiddle() { return removeSubTree(1); }
    const TTree& removeRight() { return removeSubTree(2); }

/////////////////////////////////////////////////////////////////////////
// // Problem 1: TernaryTree Basic Infrastructure

private:

    // remove a subtree, may throw a domain error [22]
    const TTree& removeSubTree(size_t aSubtreeIndex) {
        if (aSubtreeIndex >= 3 || fSubTrees[aSubtreeIndex] == &NIL) {
            throw std::domain_error("Subtree is NIL");
        }
        const TTree* removedTree = fSubTrees[aSubtreeIndex];
        fSubTrees[aSubtreeIndex] = &NIL;
        return *removedTree;
    }

    // add a subtree; must avoid memory leaks; may throw domain error [18]
    void addSubTree(size_t aSubtreeIndex, const TTree& aTTree) {
        if (aSubtreeIndex >= 3 || fSubTrees[aSubtreeIndex] != &NIL) {
            throw std::domain_error("Subtree is not NIL");
        }
        fSubTrees[aSubtreeIndex] = new TTree(aTTree);
    }

public:

    // TernaryTree l-value constructor [10]
    TernaryTree(const T& aKey) : fKey(aKey) {
        std::fill_n(fSubTrees, 3, &NIL);
    }

    // destructor (free sub-trees, must not free empty trees) [14]
    ~TernaryTree() {
        for (auto& subtree : fSubTrees) {
            if (subtree != &NIL) {
                delete subtree;
                subtree = &NIL;
            }
        }
    }

    // return key value, may throw domain_error if empty [2]
    const T& operator*() const {
        if (this == &NIL) throw std::domain_error("Dereferencing NIL");
        return fKey;
    }

    // returns true if this ternary tree is empty [4]
    bool empty() const {
        return this == &NIL;
    }

    // returns true if this ternary tree is a leaf [10]
    bool leaf() const {
        return std::all_of(std::begin(fSubTrees), std::end(fSubTrees), [](const TSubTree& subtree) { return subtree == &NIL; });
    }

    // return height of ternary tree, may throw domain_error if empty [48]
    size_t height() const {
        if (this == &NIL) throw std::domain_error("Operation not supported");
        size_t heights[] = { 0, 0, 0 };
        for (int i = 0; i < 3; ++i) {
            if (fSubTrees[i] != &NIL) {
                heights[i] = 1 + fSubTrees[i]->height();
            }
        }
        return *std::max_element(std::begin(heights), std::end(heights));
    }

/////////////////////////////////////////////////////////////////////////
//// Problem 2: TernaryTree Copy Semantics

    // copy constructor, must not copy empty ternary tree
    TernaryTree(const TernaryTree& aOtherTTree) {
        if (&aOtherTTree == &NIL) {
            throw std::domain_error("NIL as source not permitted.");
        }
        fKey = aOtherTTree.fKey;
        for (size_t i = 0; i < 3; ++i) {
            if (aOtherTTree.fSubTrees[i] != &NIL) {
                fSubTrees[i] = new TernaryTree(*(aOtherTTree.fSubTrees[i]));
            }
            else {
                fSubTrees[i] = &NIL;
            }
        }
    }

    // copy assignment operator, must not copy empty ternary tree
    // may throw a domain error on attempts to copy NIL
    TernaryTree& operator=(const TernaryTree& aOtherTTree) {
        if (this != &aOtherTTree) { // Protect against self-assignment
            if (&aOtherTTree == &NIL) {
                throw std::domain_error("NIL as source not permitted.");
            }
            // Clean up existing resources
            for (auto& subtree : fSubTrees) {
                if (subtree != &NIL) {
                    delete subtree;
                }
            }
            // Copying
            fKey = aOtherTTree.fKey;
            for (size_t i = 0; i < 3; ++i) {
                if (aOtherTTree.fSubTrees[i] != &NIL) {
                    fSubTrees[i] = new TernaryTree(*(aOtherTTree.fSubTrees[i]));
                }
                else {
                    fSubTrees[i] = &NIL;
                }
            }
        }
        return *this;
    }

    // clone ternary tree, must not copy empty trees
    TSubTree clone() const {
        if (this == &NIL) {
            // Use const_cast to safely cast away constness since we know NIL won't be modified
            return const_cast<TSubTree>(this);
        }
        else {
            return new TernaryTree(*this);
        }
    }

/////////////////////////////////////////////////////////////////////////
//// Problem 3: TernaryTree Move Semantics

    // TTree r-value constructor
    TernaryTree(T&& aKey) : fKey(std::move(aKey)) {
        std::fill_n(fSubTrees, 3, &NIL);
    }

    // move constructor, must not copy empty ternary tree
    TernaryTree(TernaryTree&& aOtherTTree) noexcept : fKey(std::move(aOtherTTree.fKey)) {
        for (size_t i = 0; i < 3; ++i) {
            fSubTrees[i] = aOtherTTree.fSubTrees[i];
            aOtherTTree.fSubTrees[i] = &NIL; // Leave aOtherTTree in a valid state
        }
    }


    // move assignment operator, must not copy empty ternary tree
    TernaryTree& operator=(TernaryTree&& aOtherTTree) noexcept {
        if (this != &aOtherTTree) {
            for (auto& subtree : fSubTrees) {
                if (subtree != &NIL) delete subtree;
            }

            fKey = std::move(aOtherTTree.fKey);
            for (size_t i = 0; i < 3; ++i) {
                fSubTrees[i] = aOtherTTree.fSubTrees[i];
                aOtherTTree.fSubTrees[i] = &NIL;
            }
        }
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////
    // Problem 4: TernaryTree Prefix Iterator

        // return ternary tree prefix iterator positioned at start
    Iterator begin() const
    {
        return Iterator(this).begin();
    }

    // return ternary prefix iterator positioned at end
    Iterator end() const
    {
        return Iterator(this).end();
    }
};

template<typename T>
TernaryTree<T> TernaryTree<T>::NIL;
