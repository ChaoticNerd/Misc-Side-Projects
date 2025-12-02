#include "DoubleLinkedList.h"
#ifndef DOUBLELINKEDLIST_TPP
#define DOUBLELINKEDLIST_TPP

// =====================
// Private helpers
// =====================

template <typename ElementType>
void LinkedList<ElementType>::copyFrom(const LinkedList &source) {
    head = nullptr;
    tail = nullptr;
    m_size = 0;

    Node* current = source.head;
    while (current != nullptr) {
        push_back(current->data);
        current = current->next;
    }
}

template <typename ElementType>
void LinkedList<ElementType>::freeList() {
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

// =====================
// Constructors / Destructor / Assignment
// =====================

template <typename ElementType>
LinkedList<ElementType>::LinkedList()
    : head(nullptr), tail(nullptr), m_size(0) {}

template <typename ElementType>
LinkedList<ElementType>::LinkedList(const LinkedList &source)
    : head(nullptr), tail(nullptr), m_size(0) {
    copyFrom(source);
}

template <typename ElementType>
LinkedList<ElementType>::LinkedList(LinkedList &&source) noexcept
    : head(source.head), tail(source.tail), m_size(source.m_size) {
    source.head = nullptr;
    source.tail = nullptr;
    source.m_size = 0;
}

template <typename ElementType>
LinkedList<ElementType>::~LinkedList() {
    freeList();
}

template <typename ElementType>
LinkedList<ElementType>& LinkedList<ElementType>::operator=(
    const LinkedList &source) {

    if (this != &source) {
        freeList();
        copyFrom(source);
    }
    return *this;
}

template <typename ElementType>
LinkedList<ElementType>& LinkedList<ElementType>::operator=(
    LinkedList &&source) noexcept {

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

// =====================
// Modifiers
// =====================

template <typename ElementType>
void LinkedList<ElementType>::push_front(ElementType value) {
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

template <typename ElementType>
void LinkedList<ElementType>::push_back(ElementType value) {
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

template <typename ElementType>
void LinkedList<ElementType>::push_at(ElementType value, int pos) {
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

template <typename ElementType>
void LinkedList<ElementType>::pop_front() {
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

template <typename ElementType>
void LinkedList<ElementType>::pop_back() {
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

template <typename ElementType>
void LinkedList<ElementType>::pop_at(int pos) {
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
template <typename ElementType>
void LinkedList<ElementType>::RemoveOdd() {
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

template <typename ElementType>
void LinkedList<ElementType>::clear() {
    freeList();
}

// =====================
// Accessors
// =====================

template <typename ElementType>
ElementType LinkedList<ElementType>::front() const {
    if (head == nullptr) {
        throw std::out_of_range("LinkedList::front() on empty list");
    }
    return head->data;
}

template <typename ElementType>
ElementType LinkedList<ElementType>::back() const {
    if (tail == nullptr) {
        throw std::out_of_range("LinkedList::back() on empty list");
    }
    return tail->data;
}

template <typename ElementType>
int LinkedList<ElementType>::size() const {
    return m_size;
}

template <typename ElementType>
bool LinkedList<ElementType>::empty() const {
    return (m_size == 0);
}

// =====================
// Comparisons
// =====================

template <typename ElementType>
bool LinkedList<ElementType>::operator==(const LinkedList &rhs) const {
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

template <typename ElementType>
bool LinkedList<ElementType>::operator!=(const LinkedList &rhs) const {
    return !(*this == rhs);
}

// =====================
// External operator<<
// =====================

template <typename ElementType>
std::ostream& operator<<(std::ostream &os, const LinkedList<ElementType> &list) {
    typename LinkedList<ElementType>::Node* current = list.head;

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
