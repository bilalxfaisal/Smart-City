#include"../utils/Nodes.h"


class RouteStack {
	struct RouteNode {
		string StopName;
		RouteNode* next;
		RouteNode* prev;
		RouteNode(const string& name) : StopName(name), next(nullptr), prev(nullptr) {}
	};
	RouteNode* head;
	RouteNode* tail;
	int size;
public:
	RouteStack() : head(nullptr), tail(nullptr), size(0) {}
	~RouteStack() {
		while (!isEmpty()) 
		{
			pop();
		}
	}
	void push(const string& routeName) {
		RouteNode* newNode = new RouteNode(routeName);
		if (isEmpty()) {
			head = tail = newNode;
		}
		else {
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
		size++;
	}
	void pop() {
		if (isEmpty())
		{
			return;
		}
		RouteNode* temp = head;
		head = head->next;
		if (head)
		{
			head->prev = nullptr;
		}
		else 
		{
			tail = nullptr; // Stack is now empty
		}
		delete temp;
		size--;
	}
	string top() const {
		if (isEmpty()) 
		{
			throw std::runtime_error("Stack is empty");
		}
		return head->StopName;
	}
	bool isEmpty() const {
		return size == 0;
	}
	int getSize() const {
		return size;
	}
};