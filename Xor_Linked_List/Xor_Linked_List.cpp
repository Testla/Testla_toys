#include "Xor_Linked_List.h"

Xor_Linked_List::Xor_Linked_List() {
    head = 0;
    tail = 0;
}

Xor_Linked_List::Xor_Linked_List(const Xor_Linked_List &src) {
    head = 0;
    tail = 0;
    *this = src;
}

Xor_Linked_List::~Xor_Linked_List() {
    clear();
}

void Xor_Linked_List::clear() {
    Xor_Linked_List::node *last = 0, *now = head, *temp;
    while (now != 0) {
        temp = now;
        now = reinterpret_cast<Xor_Linked_List::node*>(
        reinterpret_cast<uintptr_t>(now->adjacent)
        ^ reinterpret_cast<uintptr_t>(last));
        last = temp;
        delete temp;
    }
    head = 0;
    tail = 0;
}

bool Xor_Linked_List::empty() const {
    return (head == 0);
}

int Xor_Linked_List::front() const {
    return head->data;
}

int Xor_Linked_List::back() const {
    return tail->data;
}

void Xor_Linked_List::push_front(const int &elem) {
    head = new node(elem, head  /*0 ^ head*/);
    if (tail == 0) {  /*the list was empty*/
        tail = head;
    } else {
        head->adjacent->adjacent = reinterpret_cast<Xor_Linked_List::node*>(
        reinterpret_cast<uintptr_t>(head->adjacent->adjacent)
        ^ reinterpret_cast<uintptr_t>(head));
    }
}

void Xor_Linked_List::push_back(const int &elem) {
    tail = new node(elem, tail  /*0 ^ tail*/);
    if (head == 0) {  /*the list was empty*/
        head = tail;
    } else {
        tail->adjacent->adjacent = reinterpret_cast<Xor_Linked_List::node*>(
        reinterpret_cast<uintptr_t>(tail->adjacent->adjacent)
        ^ reinterpret_cast<uintptr_t>(tail));
    }
}

void Xor_Linked_List::pop_front() {
    if (empty() == true)
        return;
    if (head->adjacent == 0) {  /*only one element left*/
        tail = 0;
    } else {
        /*ignored "^= 0"*/
        head->adjacent->adjacent = reinterpret_cast<Xor_Linked_List::node*>(
        reinterpret_cast<uintptr_t>(head->adjacent->adjacent)
        ^ reinterpret_cast<uintptr_t>(head));
    }
    node* temp = head;
    head = head->adjacent;
    delete temp;
}

void Xor_Linked_List::pop_back() {
    if (empty() == true)
        return;
    if (tail->adjacent == 0) {  /*only one element left*/
        head = 0;
    } else {
        /*ignored "^= 0"*/
        tail->adjacent->adjacent = reinterpret_cast<Xor_Linked_List::node*>(
        reinterpret_cast<uintptr_t>(tail->adjacent->adjacent)
        ^ reinterpret_cast<uintptr_t>(tail));
    }
    node* temp = tail;
    tail = tail->adjacent;
    delete temp;
}

void Xor_Linked_List::operator= (const Xor_Linked_List &other) {
    clear();
    Xor_Linked_List::node *last = 0, *now = other.head, *temp;
    while (now != 0) {
        push_back(now->data);
        temp = now;
        now = reinterpret_cast<Xor_Linked_List::node*>(
        reinterpret_cast<uintptr_t>(now->adjacent)
        ^ reinterpret_cast<uintptr_t>(last));
        last = temp;
    }
}

std::ostream& operator<<(std::ostream &out, const Xor_Linked_List &list) {
    if (list.empty() == true) {
        std::cout << "empty list" << std::endl;
    } else {
        Xor_Linked_List::node *last = 0, *now = list.head, *temp;
        while (now != 0) {
            out << now->data << ((now == list.tail) ? '\n' : ' ');
            temp = now;
            now = reinterpret_cast<Xor_Linked_List::node*>(
            reinterpret_cast<uintptr_t>(now->adjacent)
            ^ reinterpret_cast<uintptr_t>(last));
            last = temp;
        }
    }
    return out;
}

