#include "Robot.h"
#include <fstream>
#include <sstream>
#include <iostream>

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

queue<option> Open_Recipe(string path) {
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

vector<string> Open_Text(string path) {
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