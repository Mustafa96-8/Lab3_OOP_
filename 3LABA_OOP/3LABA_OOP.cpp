#include <iostream>

class Base {
public:
    virtual void print(){}
    ~Base() {
        printf("~Base()\n");
    }
};

class Point : public Base {
private:
    int x = 0;
    int y = 0;
public:
    void print() override {
        printf("  x%i y%i\n", x, y);
    }
    void SetXY(int x,int y) {
        printf("SetXY()\n");
        this->x = x;
        this->y = y;
    }
    ~Point(){
        printf("~Point\n");
    }
};

class StorageList {
private:
    void remove_first() {
        if (isEmpty()) return;


        Node* temp = first;
        first = temp->next;
        delete temp;
    }
    void remove_last() {
        if (isEmpty()) return;
        if (last == first) {
            remove_first();
            return;
        }

        Node* temp = first;
        while (temp->next != last) {
            temp = temp->next;
        }
        delete temp->next;
        temp->next = nullptr;
        last = temp;
        
    }

public:
    class Node {
    public:
        Base* obj;
        //int value;      //значение задает пользователь
        Node* next;     //указатель на следующую ячейку списка

        //изменение
        bool isEOL() { return (this==nullptr ? 1 : 0); }
        Node(Base* _obj) : obj(_obj), next(nullptr) {}
        ~Node() {
            printf("~Node(): %p\n", this);
            //delete obj; 
        }
    };

    Node* first;
    Node* last;

    StorageList() : first(nullptr), last(nullptr) {}

    bool isEmpty() {
        return first == nullptr;
    }

    void push_back(Base* _obj) {
        //создаем УЗЕЛ со значением _obj
        Node* another = new Node(_obj);
        //один узел в списке
        if (isEmpty()) {
            first = another;
            last = another;
            return;
        }
        last->next = another;
        last = another;
    }

    void remove_node(Base* _obj) {
        if (isEmpty()) return;
        if (last->obj == _obj) {
            remove_last();
            return;
        }
        if (first->obj == _obj) {
            remove_first();
            return;
        }
        
        Node* current = first;
        while (current->next != nullptr && current->next->obj != _obj) {
            current = current->next;
        }
        if (current->next == nullptr) {
            printf("Такого элемента нет в списке\n");
            return;
        }
        Node* tmp_next = current->next;
        current->next = current->next->next;
        delete tmp_next;
    }

    Base* getNode(int i) {
        int j = 1;
        Node* current = first;
        while (j < i && !(current->isEOL())) {
            current = current->next;
            j++;
        }
        return(current->obj);
    }

    Base* getdelNode(int i) {
        Base* ret=getNode(i);
        remove_node(ret);
        return ret;
    }

    void print_list() {
        Node* current = first;
        while (!(current->isEOL())) {
            current->obj->print();
            current = current->next;
        }
    }

    ~StorageList() {
        if (!(isEmpty())) {
           Node* tmp = last;
        while (tmp!=first) {
            remove_last();
            tmp = last;
        }
        remove_first();
        }
        
    }
};

int main()
{
    Point* p1 = new Point;
    Point* p2 = new Point;
    Point* p3 = new Point;
    Point* p4 = new Point;
    Point* p5 = new Point;

    p1->SetXY(1, 1);
    p2->SetXY(2, 2);
    p3->SetXY(3, 3);
    p4->SetXY(4, 4);
    p5->SetXY(5, 5);

    Base* test;

    StorageList list;
    list.push_back(p1);
    list.push_back(p2);
    list.push_back(p3);
    list.push_back(p4);
    list.push_back(p5);

    list.print_list();
    printf("\n\n");
    test = list.getNode(3);
    test->print();
    printf("\n\n");
    test = list.getdelNode(2);
    test->print();
    printf("\n\n\n");
    list.print_list();
    delete p1;
    delete p2;
    delete p3;
    delete p4;
    delete p5;
}