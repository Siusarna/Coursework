#include "Queue.h"
using namespace std;

void Queue::add(string data) {
	node *el=new node;
	el->data = data;
	el->next = tail;
	tail = el;
	count++;
}

bool Queue::pop(string &output) {
	node *el = tail;
	if (!el) return false;
	tail = el->next;
	output = el->data;
	return true;
}

bool Queue::isEmpty() {
	if (tail == NULL) return true;
	return false;
}