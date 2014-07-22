#include <iostream>
#include "Xor_Linked_List.h"

using namespace std;

int main() {
    Xor_Linked_List list1;
    list1.push_back(1);
    cout << list1;
    /*1*/
    list1.push_back(2);
    cout << list1;
    /*1 2*/
    list1.pop_back();
    cout << list1;
    /*1*/
    list1.push_back(2);
    cout << list1;
    /*1 2*/
    list1.pop_back();
    list1.pop_back();
    cout << list1;
    /*empty list*/
    list1.push_back(1);
    list1.push_front(2);
    list1.push_back(3);
    cout << list1;
    /*2 1 3*/
    list1.pop_front();
    list1.push_front(4);
    list1.push_front(5);
    list1.pop_back();
    cout << list1;
    /*5 4 1*/
    Xor_Linked_List list2(list1);
    list1.clear();
    cout << list1;
    /*empty list*/
    list2.pop_front();
    cout << list2;
    /*4 1*/
    list2 = list1;
    cout << list2;
    /*empty list*/
    return 0;
}

