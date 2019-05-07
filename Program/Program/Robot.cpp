#include "Robot.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <stack>

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
	if (!fin.is_open()) {
		cout << "Помилка відкриття файлу!" << endl;
		system("pause");
	}
	else {
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
}

vector<string> Robot::Open_Text(string path) {
	ifstream fin;
	fin.open(path);
	if (!fin.is_open()) {
		cout << "Помилка відкриття файлу!" << endl;
		system("pause");
	}
	else {
		vector<string> q;
		string str;
		while (!fin.eof()) {
			getline(fin, str);
			q.push_back(str);
		}
		return q;
	}
}

void Robot::delete_text(option recipe) {
	int from =0;
	int to =0;
	parce_for_delete(recipe.row, from, to);
	this->text.erase(this->text.begin() + from, this->text.begin() + to);
}

void Robot::parce_for_delete(string recipe, int &from, int &to) {
	if (recipe.find("from") == string::npos) from = 0;
	if (recipe.find("to") == string::npos) to = this->text.size();
	if (from != 0 && to != 0) return;
	string temp;
	stringstream s(recipe);
	getline(s, temp, ' ');
	do {
		if (temp == "from") {
			getline(s, temp, ' ');
			try
			{
				from = stoi(temp);
			}
			catch (const std::exception&)
			{
				cout << "Error";
			}
			
		}
		if (temp == "to") {
			getline(s, temp, ' ');
			try
			{
				to = stoi(temp);
			}
			catch (const std::exception&)
			{
				cout << "Error";
			}
		}
	} while (getline(s, temp, ' '));
}

void Robot::change_text(option recipe) {
	int from;
	int to;
	vector<string> text_for_change;
	parce_for_change(recipe.row, from, to, text_for_change);
	if ((to - from) > text_for_change.size()) {
		this->text.erase(this->text.begin() + text_for_change.size() , this->text.begin() + to);
		for (unsigned int i = 0; i < text_for_change.size(); i++) {
			this->text[i + from - 1] = text_for_change[i];
		}
	}
	else {
		for (unsigned int i = from-1; i < to; i++) {
			this->text[i] = text_for_change[i];
		}
		for (unsigned int i = to; i < text_for_change.size(); i++) {
			this->text.insert(this->text.begin() + i, text_for_change[i]);
		}
	}
}

void Robot::parce_for_change(string recipe, int &from, int &to, vector<string> &text_for_change) {
	if (recipe.find("from") == string::npos) from = 0;
	if (recipe.find("to") == string::npos) to = this->text.size() - 1;
	string temp, temp1;
	stringstream s(recipe);
	getline(s, temp, ' ');
	do {
		if (temp == "from") {
			getline(s, temp, ' ');
			try
			{
				from = stoi(temp);
			}
			catch (const std::exception&)
			{
				cout << "Error";
			}

		}
		if (temp == "to") {
			getline(s, temp, ' ');
			try
			{
				to = stoi(temp);
			}
			catch (const std::exception&)
			{
				cout << "Error";
			}
		}
		if (temp == "with") {
			getline(s, temp, '"');
			getline(s, temp);
			temp1 = "";
			for (int i = 0; i < temp.size(); i++) {
				if (temp[i] == '\\' && temp[i + 1] == 'n') {
					text_for_change.push_back(temp1);
					i++;
					temp1.clear();
				}
				else if (temp[i] == '\\' && temp[i + 1] == '"') {
					temp1 += '"';
					i++;
				}
				else if (temp[i] == '\\' && temp[i + 1] == '\\') {
					temp += '\\';
				}
				else if (temp[i] == '\\') {
					temp1 += '\\';
				}
				else temp1 += temp[i];
			}
		}
	} while (getline(s, temp, ' '));
}

void Robot::insert_text(option recipe) {
	int after; 
	vector<string> text_for_insert;
	parce_for_insert(recipe.row, after, text_for_insert);
	int k = 0;
	for (unsigned int i = 0; i < text_for_insert.size(); i++) {
		this->text.insert(this->text.begin()+after+k, text_for_insert[k]);
		k++;
	}
}

void Robot::parce_for_insert(string recipe, int &after, vector<string> &text_for_insert) {
	string temp, temp1;
	stringstream s(recipe);
	getline(s, temp, ' ');
	do {
		if (temp == "after") {
			getline(s, temp, ' ');
			try
			{
				after = stoi(temp);
			}
			catch (const std::exception&)
			{
				cout << "Error";
			}
			getline(s, temp, '"');
			getline(s, temp);
			temp1 = "";
			for (int i = 0; i < temp.size(); i++) {
				if (temp[i] == '\\' && temp[i + 1] == 'n') {
					text_for_insert.push_back(temp1);
					i++;
					temp1.clear();
				}
				else if (temp[i] == '\\' && temp[i + 1] == '"') {
					temp1 += '"';
					i++;
				}
				else if (temp[i] == '\\' && temp[i + 1] == '\\') {
					temp += '\\';
				}
				else if (temp[i] == '\\') {
					temp1 += '\\';
				}
				else temp1 += temp[i];
			}
		}
	} while (getline(s, temp, ' '));
}

void Robot::replace_text(option recipe) {
	int from, to;
	size_t pos;
	vector<string> text_from, text_to;
	parce_for_replace(recipe.row, from, to, text_from, text_to);
	if (text_from.size() == 1) {
		for (int i = from - 1; i < to; i++) {
			pos = 0;
			while ((pos = this->text[i].find(text_from[0], pos)) != string::npos) {
				this->text[i].replace(pos, text_from[0].length(), text_to[0]);
				pos += text_to[0].length();
			}
		}
	}
}

void Robot::parce_for_replace(string recipe, int &from, int &to, vector<string> &text_from, vector<string> &text_to) {
	if (recipe.find("from") == string::npos) from = 0;
	if (recipe.find("to") == string::npos) to = this->text.size() - 1;
	string temp, temp1;
	stringstream s(recipe);
	getline(s, temp, ' ');
	do {
		if (temp == "from") {
			getline(s, temp, ' ');
			try
			{
				from = stoi(temp);
			}
			catch (const std::exception&)
			{
				cout << "Error";
			}

		}
		if (temp == "to") {
			getline(s, temp, ' ');
			try
			{
				to = stoi(temp);
				getline(s, temp, '"');
				getline(s, temp);
				temp1 = "";
				for (int i = 0; i < temp.size(); i++) {
					if (temp[i] == '\\' && temp[i + 1] == 'n') {
						text_from.push_back(temp1);
						i++;
						temp1.clear();
					}
					else if (temp[i] == '\\' && temp[i + 1] == '"') {
						temp1 += '"';
						i++;
					}
					else if (temp[i] == '\\' && temp[i + 1] == '\\') {
						temp += '\\';
					}
					else if (temp[i] == '\\') {
						temp1 += '\\';
					}
					else temp1 += temp[i];
				}
			}
			catch (const std::exception&)
			{
				cout << "Error";
			}
		}
		if (temp == "with") {
			getline(s, temp, '"');
			getline(s, temp);
			temp1 = "";
			for (int i = 0; i < temp.size(); i++) {
				if (temp[i] == '\\' && temp[i + 1] == 'n') {
					text_to.push_back(temp1);
					i++;
					temp1.clear();
				}
				else if (temp[i] == '\\' && temp[i + 1] == '"') {
					temp1 += '"';
					i++;
				}
				else if (temp[i] == '\\' && temp[i + 1] == '\\') {
					temp += '\\';
				}
				else if (temp[i] == '\\') {
					temp1 += '\\';
				}
				else temp1 += temp[i];
			}
		}
	} while (getline(s, temp, ' '));
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
	for(unsigned int i=0;i<temp.size();i++) {
		if (temp.front().word == "undo") {
			temp.pop();
			temp.pop();
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
}
