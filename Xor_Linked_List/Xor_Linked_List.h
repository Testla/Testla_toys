#include <iostream>

class Xor_Linked_List {
    private:
        struct node {
            int data;
            node* adjacent;
            node (int new_data, node* new_adjacent) : data(new_data),
                                                      adjacent(new_adjacent) {}
        };
        node* head;
        node* tail;
    public:
        Xor_Linked_List();
        Xor_Linked_List(const Xor_Linked_List &src);
        ~Xor_Linked_List();
        void clear();
        bool empty() const;
        int front() const;
        int back() const;
        void push_front(const int &elem);
        void push_back(const int &elem);
        void pop_front();
        void pop_back();
        void operator= (const Xor_Linked_List &other);
        friend std::ostream& operator<<(std::ostream &out,
        const Xor_Linked_List &list);
};

