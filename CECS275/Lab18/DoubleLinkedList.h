#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <iostream>
#include <stdexcept>

// Forward declaration
template <typename ElementType>
class LinkedList;

// External operator<< declaration
template <typename ElementType>
std::ostream& operator<<(std::ostream &os, const LinkedList<ElementType> &list);

template <typename ElementType>
class LinkedList {
private:
    struct Node {
        ElementType data;
        Node* prev;
        Node* next;

        Node(const ElementType& value, Node* p = nullptr, Node* n = nullptr)
            : data(value), prev(p), next(n) {}
    };

    Node* head;
    Node* tail;
    int   m_size;

    // Helper to copy from another list
    void copyFrom(const LinkedList& source);

    // Helper to free all nodes
    void freeList();

public:
    // Constructors / destructor / assignment
    LinkedList();                                      // default
    LinkedList(const LinkedList &source);              // copy ctor
    LinkedList(LinkedList &&source) noexcept;          // move ctor
    ~LinkedList();                                     // destructor

    LinkedList& operator=(const LinkedList &source);   // copy assign
    LinkedList& operator=(LinkedList &&source) noexcept; // move assign

    // Modifiers
    void push_front(ElementType value);
    void push_back(ElementType value);
    void push_at(ElementType value, int pos);

    void pop_front();
    void pop_back();
    void pop_at(int pos);

    void RemoveOdd();   // remove elements at indices 1,3,5,... (0-based)
    void clear();       // remove all elements

    // Accessors
    ElementType front() const;  // throws if empty
    ElementType back()  const;  // throws if empty
    int  size()   const;
    bool empty()  const;

    // Comparisons
    bool operator==(const LinkedList &rhs) const;
    bool operator!=(const LinkedList &rhs) const;

    // Give operator<< friend access (for printing)
    friend std::ostream& operator<< <>(std::ostream &os,
                                       const LinkedList<ElementType> &list);
};

#include "DoubleLinkedList.cpp"

#endif // LINKEDLIST_H
