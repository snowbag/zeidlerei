#pragma once
template <class T>
class LinkedList
{
public:
	LinkedList();
	~LinkedList();
	void add(T& element);


private:
	struct Node {
		T content;
		Node* next = std::nullptr_t;
	};
	Node* head;
	Node* last;
	int size = 0;
};

