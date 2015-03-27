#include <iostream>

class Xor_Linked_List {
    private:
        struct node {
            int data;
            node* adjacent;
            node(int init_data, node* init_adjacent);
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

        struct iterator {
            public:
                iterator();
                friend class Xor_Linked_List;  /*for the constructor*/
                int& operator* ();
                iterator& operator++();
                iterator& operator--();
                iterator operator++(int);
                iterator operator--(int);
                bool operator==(const iterator& other);
                bool operator!=(const iterator& other);
            private:
                node* last;
                node* current;
                iterator(node* init_last, node* init_current);
        };
        iterator begin();
        iterator end();
};

