#pragma once
#include <string>
using namespace std;
struct node
{
	node *next;
	string data;
};

class Queue
{
public:
	node *tail=NULL;
	void add(string data);
	bool pop(string &output);
	bool isEmpty();
private:
	int count = 0;
};
