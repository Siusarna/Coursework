#include<iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector<string> Open_Parce(string path) {
	ifstream fin;
	fin.open(path);
	if (!fin.is_open()) {
		cout << "Помилка відкриття файлу!" << endl;
		system("pause");
	}
	else {
		vector<string> arr;
		string str;
		while (!fin.eof()) {
			getline(fin, str);
			arr.push_back(str);
		}
		return arr;
	}
}