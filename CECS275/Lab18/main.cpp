#include <iostream>
#include "DoubleLinkedList.h"
struct Point {
    int x;
    int y;
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}

int main() {
    using std::cout;
    using std::endl;

    cout << "========================" << endl;
    LinkedList<int> listA;

    listA.push_back(2);
    listA.push_front(1);
    listA.push_back(3);

    cout << "List after push_front/back (expected 1, 2, 3): "
         << listA 
         << endl;

    listA.pop_front();
    cout << "After pop_front (expected 2, 3): " << listA << endl;

    listA.pop_back();
    cout << "After pop_back (expected 2): " << listA << endl;

    listA.pop_back();
    cout << "After pop_back (expected empty): " << listA << endl;

    cout << "========================" << endl;
    LinkedList<int> listB;

    // populate linked list b
    for (int i = 0; i < 5; ++i)
        listB.push_back(i);   // 0,1,2,3,4

    cout << "Initial list (expected 0, 1, 2, 3, 4): "
         << listB << endl;

    listB.push_at(100, 0);
    listB.push_at(200, 3);
    listB.push_at(300, 100);

    cout << "After pushes at (expected 100, 0, 1, 200, 2, 3, 4, 300): " << listB << endl;

    listB.pop_at(0);
    listB.pop_at(3);
    listB.pop_at(100);

    cout << "After pops at (expected 0, 1, 200, 3, 4, 300): "
         << listB << endl;


    cout << "========================" << endl;
    LinkedList<int> listC;
    for (int i = 0; i < 10; ++i)
        listC.push_back(i);

    cout << "Original (expected 0..9): " << listC << endl;
    listC.RemoveOdd();
    cout << "After RemoveOdd (expected 0,2,4,6,8): "
         << listC << "\n\n";


    cout << "========================" << endl;
    LinkedList<int> list1;
    for (int i = 1; i <= 5; ++i)
        list1.push_back(i);

    LinkedList<int> list2(list1);  // copy constructor
    LinkedList<int> list3;
    list3 = list1;                 // copy assignment

    cout << "list1: " << list1 << endl;
    cout << "list2 (copy construct): " << list2 << endl;
    cout << "list3 (copy assign): " << list3 << endl;

    cout << "list1 == list2? " << (list1 == list2 ? "true" : "false") << endl;
    cout << "list1 == list3? " << (list1 == list3 ? "true" : "false") << endl;

    // modify list2
    list2.pop_back();
    list2.push_front(100);

    cout << "After modifying list2:" << endl;;
    cout << "list1 (expected unchanged 1,2,3,4,5): " << list1 << endl;
    cout << "list2 (expected 100,1,2,3,4): " << list2 << endl;
    cout << "list1 != list2? " << (list1 != list2 ? "true" : "false") << endl;


    cout << "========================" << endl;
    LinkedList<int> listM;
    listM.push_back(10);
    listM.push_back(20);
    listM.push_back(30);

    cout << "listM before move: " << listM << endl;

    LinkedList<int> listMovedCtor(std::move(listM));
    cout << "listMovedCtor (moved-from listM): " << listMovedCtor << endl;

    cout << "listM after move (expected empty): "
         << (listM.empty() ? "empty" : "not empty") << endl;

    LinkedList<int> listMovedAssignPrep;
    listMovedAssignPrep.push_back(1);
    listMovedAssignPrep.push_back(2);

    cout << "listMovedAssignPrep before move assignment: "
         << listMovedAssignPrep << endl;

    listMovedAssignPrep = std::move(listMovedCtor);

    cout << "listMovedAssignPrep after move assignment (expected 10,20,30): "
         << listMovedAssignPrep << endl;
         
    cout << "listMovedCtor after move assignment (expected empty): "
         << (listMovedCtor.empty() ? "empty" : "not empty") << endl;


    cout << "========================" << endl;
    LinkedList<int> listAcc;

    listAcc.push_back(5);
    listAcc.push_back(10);
    listAcc.push_back(15);

    cout << "List: " << listAcc << endl;
    cout << "front() (expected 5): " << listAcc.front() << endl;
    cout << "back()  (expected 15): " << listAcc.back() << endl;
    cout << "size()  (expected 3): " << listAcc.size() << endl;
    cout << "empty() (expected false): "
         << (listAcc.empty() ? "true" : "false") << endl;

    listAcc.clear();

    cout << "After clear, empty() (expected true): "
         << (listAcc.empty() ? "true" : "false") << endl;

    try { listAcc.front(); }
    catch (const std::exception &e) {
        cout << "Caught exception on front() of empty list: " << e.what() << endl;
    }
    try { listAcc.back(); }
    catch (const std::exception &e) {
        cout << "Caught exception on back() of empty list: " << e.what() << endl;
    }

    cout << "\n========================\n";

    LinkedList<Point> points;
    points.push_back({1, 2});
    points.push_back({3, 4});
    points.push_front({0, 0});

    cout << points << endl;
    return 0;
}
