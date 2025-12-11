#include "DoubleLinkedList.h"
#ifndef DOUBLELINKEDLIST_TPP
#define DOUBLELINKEDLIST_TPP

template <class T>
void LinkedList<T>::copyFrom(const LinkedList &source) {
    head = nullptr;
    tail = nullptr;
    m_size = 0;

    Node* current = source.head;
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }
}

template <class T>
void LinkedList<T>::freeList() {
    Node* current = head;
    while (current != nullptr) {
        Node* toDelete = current;
        current = current->next;
        delete toDelete;
    }
    head = nullptr;
    tail = nullptr;
    m_size = 0;
}

template <class T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), m_size(0) {}

template <class T>
LinkedList<T>::LinkedList(const LinkedList &source) : head(nullptr), 
                                                      tail(nullptr), m_size(0) {
    copyFrom(source);
}

template <class T>
LinkedList<T>::LinkedList(LinkedList &&source) : head(source.head), 
                                                tail(source.tail),
                                                m_size(source.m_size) {
    source.head = nullptr;
    source.tail = nullptr;
    source.m_size = 0;
}

template <class T>
LinkedList<T>::~LinkedList() {
    freeList();
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList &source) {

    if (this != &source) {
        freeList();
        copyFrom(source);
    }
    return *this;
}

template <class T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList &&source) {

    if (this != &source) {
        freeList();
        head = source.head;
        tail = source.tail;
        m_size = source.m_size;

        source.head = nullptr;
        source.tail = nullptr;
        source.m_size = 0;
    }
    return *this;
}

template <class T>
void LinkedList<T>::push_front(T value) {
    Node* newNode = new Node(value, nullptr, head);
    if (head != nullptr) {
        head->prev = newNode;
    } else {
        // was empty
        tail = newNode;
    }
    head = newNode;
    ++m_size;
}

template <class T>
void LinkedList<T>::push_back(T value) {
    Node* newNode = new Node(value, tail, nullptr);
    if (tail != nullptr) {
        tail->next = newNode;
    } else {
        // was empty
        head = newNode;
    }
    tail = newNode;
    ++m_size;
}

template <class T>
void LinkedList<T>::push_at(T value, int pos) {
    if (pos <= 0) {
        push_front(value);
        return;
    }
    if (pos >= m_size) {
        push_back(value);
        return;
    }

    // Find node currently at index pos
    Node* current = head;
    int idx = 0;
    while (current != nullptr && idx < pos) {
        current = current->next;
        ++idx;
    }

    // insert before "current"
    Node* prevNode = current->prev;
    Node* newNode = new Node(value, prevNode, current);
    prevNode->next = newNode;
    current->prev = newNode;
    ++m_size;
}

template <class T>
void LinkedList<T>::pop_front() {
    if (head == nullptr) {
        return; // list empty
    }

    Node* toDelete = head;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        // list now empty
        tail = nullptr;
    }

    delete toDelete;
    --m_size;
}

template <class T>
void LinkedList<T>::pop_back() {
    if (tail == nullptr) {
        return; // list empty
    }

    Node* toDelete = tail;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        // list now empty
        head = nullptr;
    }

    delete toDelete;
    --m_size;
}

template <class T>
void LinkedList<T>::pop_at(int pos) {
    if (head == nullptr || pos < 0 || pos >= m_size) {
        return; // nothing to do
    }

    if (pos == 0) {
        pop_front();
        return;
    }
    if (pos == m_size - 1) {
        pop_back();
        return;
    }

    // interior node
    Node* current = head;
    int idx = 0;
    while (current != nullptr && idx < pos) {
        current = current->next;
        ++idx;
    }

    if (current == nullptr) return;

    Node* prevNode = current->prev;
    Node* nextNode = current->next;

    prevNode->next = nextNode;
    if (nextNode != nullptr) {
        nextNode->prev = prevNode;
    }

    delete current;
    --m_size;
}

// Remove all odd-indexed elements (1,3,5,...) using original indices
template <class T>
void LinkedList<T>::RemoveOdd() {
    if (m_size <= 1) return;

    Node* current = head;
    int index = 0;

    while (current != nullptr) {
        Node* next = current->next;
        if (index % 2 == 1) {
            // remove current
            Node* prevNode = current->prev;
            Node* nextNode = current->next;

            if (prevNode != nullptr) {
                prevNode->next = nextNode;
            }
            if (nextNode != nullptr) {
                nextNode->prev = prevNode;
            }

            if (current == head) head = nextNode;
            if (current == tail) tail = prevNode;

            delete current;
            --m_size;
        }
        ++index;
        current = next;
    }

    // after removal, head/tail should already be consistent
}

template <class T>
void LinkedList<T>::clear() {
    freeList();
}

template <class T>
T LinkedList<T>::front() const {
    if (head == nullptr) {
        throw std::out_of_range("LinkedList::front() on empty list");
    }
    return head->data;
}

template <class T>
T LinkedList<T>::back() const {
    if (tail == nullptr) {
        throw std::out_of_range("LinkedList::back() on empty list");
    }
    return tail->data;
}

template <class T>
int LinkedList<T>::size() const {
    return m_size;
}

template <class T>
bool LinkedList<T>::empty() const {
    return (m_size == 0);
}

template <class T>
bool LinkedList<T>::operator==(const LinkedList &rhs) const {
    if (m_size != rhs.m_size) return false;

    Node* a = head;
    Node* b = rhs.head;

    while (a != nullptr && b != nullptr) {
        if (!(a->data == b->data)) {
            return false;
        }
        a = a->next;
        b = b->next;
    }

    return true;
}

template <class T>
bool LinkedList<T>::operator!=(const LinkedList &rhs) const {
    return !(*this == rhs);
}

template <class T>
std::ostream& operator<<(std::ostream &os, const LinkedList<T> &list) {
    class LinkedList<T>::Node* current = list.head;

    while (current != nullptr) {
        os << current->data;
        if (current->next != nullptr) {
            os << ", ";
        }
        current = current->next;
    }
    return os;
}

#endif // LINKEDLIST_TPP
