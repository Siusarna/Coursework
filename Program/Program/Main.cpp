#include<iostream>
#include <string>
#include <vector>
#include "Open_Parce_Input.h"
#include "Queue.h"
using namespace std;

int main() {
	vector<string> arr;
	arr = Open_Parce("dict_processed.txt");
	Queue que;
	que.add("5");
	que.add("10");
	que.add("11");
	string output;
	if (que.pop(output)) cout << output << endl;
	if (que.pop(output)) cout << output << endl;
	if (que.pop(output)) cout << output << endl;
	if (que.pop(output)) cout << output << endl;
	que.add("11");
	if (que.pop(output)) cout << output << endl;
	cout << que.isEmpty() << endl;
	system("pause");
}