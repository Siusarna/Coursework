#include "Robot.h"


bool parce_row(string &row) {
	stringstream s(row);
	string temp;
	string word = "delete change insert replace undo";
	do {
		getline(s, temp, ' ');
		if (word.find(temp) != string::npos) {
			row = temp;
			return true;
		}
	} while (getline(s, temp, ' '));
	return false;
}

queue<option> Robot::Open_Recipe(string path) {
	ifstream fin;
	fin.open(path);
	queue<option> q;
	string str;
	string t;
	option temp;
	while (!fin.eof()) {
		getline(fin, str);
		t = str;
		if (parce_row(str)) {
			temp.word = str;
			temp.row = t;
			q.push(temp);
		}
	}
	return q;
}

vector<string> Robot::Open_Text(string path) {
	ifstream fin;
	fin.open(path);
	vector<string> q;
	string str;
	while (!fin.eof()) {
		getline(fin, str);
		q.push_back(str);
	}
	return q;
}


queue<option> reversQueue(queue<option> q) {
	stack<option> stack;
	while (!q.empty()) {
		stack.push(q.front());
		q.pop();
	}
	while (!stack.empty()) {
		q.push(stack.top());
		stack.pop();
	}
	return q;
}

void Robot::start_work() {
	queue<option> temp = reversQueue(this->que);
	string str;
	queue<option> temp1;
	unsigned int size = temp.size();
	for(unsigned int i=0;i<size;i++) {
		if (temp.front().word == "undo") {
			temp.pop();
			temp.pop();
			size--;
		}
		else {
			temp1.push(temp.front());
			temp.pop();
		}
	}
	this->que = reversQueue(temp1);
	while (!this->que.empty()){
		str = this->que.front().word;
		if (str == "delete") delete_text(this->que.front());
		if (str == "change") change_text(this->que.front());
		if (str == "insert") insert_text(this->que.front());
		if (str == "replace") replace_text(this->que.front());
		this->que.pop();
	}
	ofstream out("result.txt");
	for (int i = 0; i < this->text.size(); i++) {
		out << this->text[i] << "\n";
	}
}

Robot::Robot(string path_recipe, string path_text)
{
	this->que = Open_Recipe(path_recipe);
	this->text = Open_Text(path_text);
	this->path_recipe = path_recipe;
	this->path_text = path_text;
}
