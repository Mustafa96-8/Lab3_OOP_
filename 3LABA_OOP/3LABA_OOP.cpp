#include <iostream>
///------------------------------------------------—
class Base {
protected:
	char code = 'B';
	int x, y;
public:
	virtual char getCode() {
		return code;
	}
	virtual void print() {}
	~Base() {
		printf("~Base()\n");
	}
};

class Segment :public Base {
private:
	int x1, x2, y1, y2;
public:
	char getCode() override {
		return 'S';
	}
	Segment() {
		x1 = 0;
		y1 = 0;
		x2 = 0;
		y2 = 0;
	}
	Segment(Segment* s) {
		x1 = s->x1;
		x2 = s->x2;
		y1 = s->y1;
		y2 = s->y2;
	}

	void print() override {
		printf(" x1%i y1%i x2%i y2%i\n", x1, y1, x2, y2);
	}
	~Segment() {
		printf("~Segment\n");
	}
};

class Point : public Base {
private:
	int x, y;
public:

	char getCode() override {
		return 'P';
	}

	Point() {
		x = 0;
		y = 0;
	}

	Point(Point* p) {
		x = p->getX();
		y = p->getY();
	}


	void print() override {
		printf(" x%i y%i\n", x, y);
	}

	void SetXY(int x, int y) {
		printf("SetXY()\n");
		this->x = x;
		this->y = y;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}

	~Point() {
		printf("~Point\n");
	}
};

class Cat:public Base {
private:
	char Name[20];
	char Color[30];
public:
	void print() override {
		printf("Cat name= %s , is the color=%s\n",Name,Color);
	}
	
};


class MyBaseFactory{
public:
	MyBaseFactory() {
	}
	Base* createBase(char code, Base* p)
	{
		Base* _base = nullptr;
		switch (code)
		{
		case 'P':
			_base = new Point((Point*)(p));
			break;
		case 'S':
			_base = new Segment((Segment*)(p));
			break;
		case 'H':
			_base = new Segment((Segment*)(p));
			break;
		case 'M':
			_base = new Segment((Segment*)(p));
			break;
		case 'C':
			_base = new Segment((Segment*)(p));
			break;
		case 'D':
			_base = new Segment((Segment*)(p));
			break;
		default:;
		}
		return _base;
	}
};


class BaseList {

private:

	class Node {
	public:
		Base* _base;

		Node* next; //указатель на следующую ячейку списка

		//изменение
		bool isEOL() { return (this == nullptr ? 1 : 0); }
		Node(Base* __base) : next(nullptr) {
			MyBaseFactory facrory;
			_base = facrory.createBase(__base->getCode(), __base);
		}
		~Node() {
			printf("~Node(): %p\n", this);
			delete _base;
		}
	};


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


	Node* first;
	Node* last;

	void add(Base* _base) {
		//создаем УЗЕЛ со значением __base

		Node* another = new Node(_base);

		//один узел в списке
		if (isEmpty()) {
			first = another;
			last = another;
			return;
		}
		last->next = another;
		last = another;
	}

	bool isEmpty() {
		return first == nullptr;
	}


	void remove_node(Base* __base) {
		if (isEmpty()) return;
		if (last->_base == __base) {
			remove_last();
			return;
		}
		if (first->_base == __base) {
			remove_first();
			return;
		}

		Node* current = first;
		while (current->next != nullptr && current->next->_base != __base) {
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
		return(current->_base);
	}

	Base* getdelNode(int i) {
		Base* ret = getNode(i);
		Base* tmp;
		MyBaseFactory facrory;
		tmp = facrory.createBase(ret->getCode(),ret);
		remove_node(ret);
		return tmp;
	}
	
	void print_list() {
		Node* current = first;
		while (!(current->isEOL())) {
			current->_base->print();
			current = current->next;
		}
	}

	~BaseList() {
		if (!(isEmpty())) {
			Node* tmp = last;
			while (tmp != first) {
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

	BaseList list;
	list.add(p1);
	list.add(p2);
	list.add(p3);
	list.add(p4);
	list.add(p5);

	list.print_list();
	printf("\n\n");
	test = list.getNode(3);
	test->print();
	printf("\n\n");
	test = list.getdelNode(2);
	printf("\n\n");
	test->print();
	printf("\n\n\n");
	list.print_list();
	delete p1;
	delete p2;
	delete p3;
	delete p4;
	delete p5;
	system("pause");
}