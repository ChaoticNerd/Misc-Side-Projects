#include <iostream>
#include "DoubleLinkedList.h"

void test_push_pop_front_back() {
    std::cout << "=== test_push_pop_front_back ===\n";
    LinkedList<int> list;

    list.push_back(2);
    list.push_front(1);
    list.push_back(3);

    std::cout << "List after push_front/back (expected 1, 2, 3): "
              << list << "\n";

    list.pop_front();
    std::cout << "After pop_front (expected 2, 3): " << list << "\n";

    list.pop_back();
    std::cout << "After pop_back (expected 2): " << list << "\n";

    list.pop_back();
    std::cout << "After pop_back (expected empty): " << list << "\n\n";
}

void test_push_pop_at() {
    std::cout << "=== test_push_pop_at ===\n";
    LinkedList<int> list;

    // fill via push_back
    for (int i = 0; i < 5; ++i) {
        list.push_back(i);  // 0,1,2,3,4
    }
    std::cout << "Initial list (expected 0, 1, 2, 3, 4): "
              << list << "\n";

    list.push_at(100, 0);     // front: 100,0,1,2,3,4
    list.push_at(200, 3);     // 100,0,1,200,2,3,4
    list.push_at(300, 100);   // treat as push_back: ...,4,300

    std::cout << "After pushes at (expected 100, 0, 1, 200, 2, 3, 4, 300): "
              << list << "\n";

    list.pop_at(0);           // remove 100
    list.pop_at(3);           // remove 2 (after removal at 0)
    list.pop_at(100);         // out of range: no change

    std::cout << "After pops at (expected 0, 1, 200, 3, 4, 300): "
              << list << "\n\n";
}

void test_remove_odd() {
    std::cout << "=== test_remove_odd ===\n";
    LinkedList<int> list;
    for (int i = 0; i < 10; ++i) {
        list.push_back(i);    // 0..9
    }
    std::cout << "Original (expected 0..9): " << list << "\n";
    list.RemoveOdd();
    std::cout << "After RemoveOdd (expected 0, 2, 4, 6, 8): "
              << list << "\n\n";
}

void test_copy_semantics() {
    std::cout << "=== test_copy_semantics ===\n";
    LinkedList<int> list1;
    for (int i = 1; i <= 5; ++i) list1.push_back(i); // 1..5

    LinkedList<int> list2(list1);     // copy constructor
    LinkedList<int> list3;
    list3 = list1;                    // copy assignment

    std::cout << "list1: " << list1 << "\n";
    std::cout << "list2 (copy ctor): " << list2 << "\n";
    std::cout << "list3 (copy assign): " << list3 << "\n";

    std::cout << "list1 == list2? " << (list1 == list2 ? "true" : "false") << "\n";
    std::cout << "list1 == list3? " << (list1 == list3 ? "true" : "false") << "\n";

    // Modify list2 and confirm list1 unchanged
    list2.pop_back();
    list2.push_front(100);

    std::cout << "After modifying list2:\n";
    std::cout << "list1 (expected unchanged 1, 2, 3, 4, 5): " << list1 << "\n";
    std::cout << "list2 (expected 100, 1, 2, 3, 4): " << list2 << "\n";
    std::cout << "list1 != list2? " << (list1 != list2 ? "true" : "false") << "\n\n";
}

void test_move_semantics() {
    std::cout << "=== test_move_semantics ===\n";
    LinkedList<int> list1;
    list1.push_back(10);
    list1.push_back(20);
    list1.push_back(30);

    std::cout << "list1 before move: " << list1 << "\n";

    // Move constructor
    LinkedList<int> list2(std::move(list1));
    std::cout << "list2 (moved-from list1): " << list2 << "\n";
    std::cout << "list1 after move (expected empty): "
              << (list1.empty() ? "empty" : "not empty") << "\n";

    // Move assignment
    LinkedList<int> list3;
    list3.push_back(1);
    list3.push_back(2);

    std::cout << "list3 before move assignment: " << list3 << "\n";
    list3 = std::move(list2);

    std::cout << "list3 after move assignment (expected 10, 20, 30): "
              << list3 << "\n";
    std::cout << "list2 after move assignment (expected empty): "
              << (list2.empty() ? "empty" : "not empty") << "\n\n";
}

void test_accessors_and_clear() {
    std::cout << "=== test_accessors_and_clear ===\n";
    LinkedList<int> list;
    list.push_back(5);
    list.push_back(10);
    list.push_back(15);

    std::cout << "List: " << list << "\n";
    std::cout << "front() (expected 5): " << list.front() << "\n";
    std::cout << "back()  (expected 15): " << list.back() << "\n";
    std::cout << "size()  (expected 3): " << list.size() << "\n";
    std::cout << "empty() (expected false): "
              << (list.empty() ? "true" : "false") << "\n";

    list.clear();
    std::cout << "After clear, empty() (expected true): "
              << (list.empty() ? "true" : "false") << "\n";

    // Optional: demonstrate exception on front/back of empty list
    try {
        list.front();
    } catch (const std::exception& e) {
        std::cout << "Caught exception on front() of empty list: "
                  << e.what() << "\n";
    }

    try {
        list.back();
    } catch (const std::exception& e) {
        std::cout << "Caught exception on back() of empty list: "
                  << e.what() << "\n";
    }

    std::cout << "\n";
}

// A simple custom type to show template/generic behavior
struct Point {
    int x;
    int y;
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

void test_with_custom_type() {
    std::cout << "=== test_with_custom_type (Point) ===\n";
    LinkedList<Point> points;
    points.push_back({1, 2});
    points.push_back({3, 4});
    points.push_front({0, 0});

    std::cout << "Points list (expected (0, 0), (1, 2), (3, 4)): "
              << points << "\n\n";
}

int main() {
    test_push_pop_front_back();
    test_push_pop_at();
    test_remove_odd();
    test_copy_semantics();
    test_move_semantics();
    test_accessors_and_clear();
    test_with_custom_type();

    std::cout << "All tests complete.\n";
    return 0;
}
