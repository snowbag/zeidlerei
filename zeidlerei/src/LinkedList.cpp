#include "LinkedList.h"

template <class T>
LinkedList<T>::LinkedList()
{
	head = new Node();
	last = head;
}


template <class T>
LinkedList<T>::~LinkedList()
{
	while (head->next) {
		Node* last = head;
		head = head->next;
		delete last;
	}
}

template <class T>
void LinkedList<T>::add(T& element) {
	Node* newNode = new Node(element);
	last->next = newNode;
	last = newNode;
	++size;
}
