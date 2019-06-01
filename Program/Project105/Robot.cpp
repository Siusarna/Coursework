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

void Robot::delete_text(option recipe) {
	int from =0;
	int to =0;
	parce_for_delete(recipe.row, from, to);
	if (from < 1) from = 1;
	if (to > this->text.size()) to = this->text.size();
	this->text.erase(this->text.begin() + from-1, this->text.begin() + to);
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
			catch (const std::exception& ex)
			{
				System::String ^err_name = gcnew System::String("Помилка");
				System::String ^err_descr = gcnew System::String(ex.what());
				err_descr += gcnew System::String(". Поміняйте рецепт та запустіть робота ще раз");
				System::Windows::Forms::MessageBox::Show(err_descr, err_name, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
				delete err_name;
				delete err_descr;
				System::Windows::Forms::Application::Exit();
			}
			
		}
		if (temp == "to") {
			getline(s, temp, ' ');
			try
			{
				to = stoi(temp);
			}
			catch (const std::exception& ex)
			{
				System::String ^err_name = gcnew System::String("Помилка");
				System::String ^err_descr = gcnew System::String(ex.what());
				err_descr += gcnew System::String(". Поміняйте рецепт та запустіть робота ще раз");
				System::Windows::Forms::MessageBox::Show(err_descr, err_name, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
				delete err_name;
				delete err_descr;
				System::Windows::Forms::Application::Exit();
			}
		}
	} while (getline(s, temp, ' '));
}

void Robot::change_text(option recipe) {
	int from;
	int to;
	vector<string> text_for_change;
	parce_for_change(recipe.row, from, to, text_for_change);
	if (from > 0) from--;
	if (from < 1) from = 0;
	if (to > this->text.size()) to = this->text.size();
	if ((to - from) > text_for_change.size()) {
		this->text.erase(this->text.begin() + from + text_for_change.size()-1 , this->text.begin() + to-1);
		for (unsigned int i = 0; i < text_for_change.size(); i++) {
			this->text[i + from] = text_for_change[i];
		}
	}
	else {
		int k = 0;
		for (unsigned int i = from; i < to; i++) {
			this->text[i] = text_for_change[k];
			k++;
		}
		for (unsigned int i = to; i < text_for_change.size(); i++) {
			this->text.insert(this->text.begin() + i, text_for_change[k]);
			k++;
		}
	}
}

void Robot::parce_for_change(string recipe, int &from, int &to, vector<string> &text_for_change) {
	if (recipe.find("from") == string::npos) from = 0;
	if (recipe.find("to") == string::npos) to = this->text.size();
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
			catch (const std::exception& ex)
			{
				System::String ^err_name = gcnew System::String("Помилка");
				System::String ^err_descr = gcnew System::String(ex.what());
				err_descr += gcnew System::String(". Поміняйте рецепт та запустіть робота ще раз");
				System::Windows::Forms::MessageBox::Show(err_descr, err_name, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
				delete err_name;
				delete err_descr;
				System::Windows::Forms::Application::Exit();
			}
		}
		if (temp == "to") {
			getline(s, temp, ' ');
			try
			{
				to = stoi(temp);
			}
			catch (const std::exception& ex)
			{
				System::String ^err_name = gcnew System::String("Помилка");
				System::String ^err_descr = gcnew System::String(ex.what());
				err_descr += gcnew System::String(". Поміняйте рецепт та запустіть робота ще раз");
				System::Windows::Forms::MessageBox::Show(err_descr, err_name, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
				delete err_name;
				delete err_descr;
				System::Windows::Forms::Application::Exit();
			}
		}
		if (temp == "with") {
			getline(s, temp, '"');
			getline(s, temp);
			temp1 = "";
			for (int i = 0; i < temp.size(); i++) {
				if (temp[i] == '\\' && temp[i + 1] == 'n' || temp[i] == '"') {
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
	if (after < 1) after = 1;
	if (after > this->text.size()) after = this->text.size();
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
			catch (const std::exception& ex)
			{
				System::String ^err_name = gcnew System::String("Помилка");
				System::String ^err_descr = gcnew System::String(ex.what());
				err_descr += gcnew System::String(". Поміняйте рецепт та запустіть робота ще раз");
				System::Windows::Forms::MessageBox::Show(err_descr, err_name, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
				delete err_name;
				delete err_descr;
				System::Windows::Forms::Application::Exit();
			}
			getline(s, temp, '"');
			getline(s, temp);
			temp1 = "";
			for (int i = 0; i < temp.size(); i++) {
				if (temp[i] == '\\' && temp[i + 1] == 'n' || temp[i] =='"') {
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
	if (from < 1) from = 1;
	if (to > this->text.size()) to = this->text.size();
	if (text_from.size() == 1) {
		for (int i = from - 1; i < to; i++) {
			pos = 0;
			while ((pos = this->text[i].find(text_from[0], pos)) != string::npos) {
				this->text[i].replace(pos, text_from[0].length(), text_to[0]);
				pos += text_to[0].length();
				if (text_to.size() > 1) {
					string save;
					for (int l = pos; l < this->text[i].size(); l++) {
						save += this->text[i][l];
					}
					int size = this->text[i].size();
					this->text[i].erase(this->text[i].begin() + pos, this->text[i].begin() + size );
					int k = 1;
					for (int j = 1; j < text_to.size(); j++) {
						this->text.insert(this->text.begin() + i + k, text_to[k]);
						to++;
						k++;
					}
					this->text[i + text_to.size()-1] += save;
				}
			}	
		}
	}
	else {
		for (int i = from-1; i < to-1; i++) {
			bool flag=true;
			for (int k = 0; k < text_from.size(); k++) {
				for (int j = 0; j < this->text[i].size(); j++) {
					if (this->text[i + k][j] != text_from[k][j]) {
						flag = false;
						break;
					}
				}
			}
			if (flag) {
				int k;
				for (k = 0; k < text_to.size(); k++) {
					for (int j = 0; j < this->text[i].size(); j++) {
						this->text[i + k][j] = text_to[k][j];
					}
				}
				if (text_from.size() > text_to.size()) {
					this->text.erase(this->text.begin() + i + k, this->text.begin() + i + k + (text_from.size() - text_to.size()));
				}
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
			catch (const std::exception& ex)
			{
				System::String ^err_name = gcnew System::String("Помилка");
				System::String ^err_descr = gcnew System::String(ex.what());
				err_descr += gcnew System::String(". Поміняйте рецепт та запустіть робота ще раз");
				System::Windows::Forms::MessageBox::Show(err_descr, err_name, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
				delete err_name;
				delete err_descr;
				System::Windows::Forms::Application::Exit();
			}

		}
		if (temp == "to") {
			getline(s, temp, ' ');
			try
			{
				to = stoi(temp);
				getline(s, temp, '"');
				getline(s, temp, '"');
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
				text_from.push_back(temp1);
			}
			catch (const std::exception& ex)
			{
				System::String ^err_name = gcnew System::String("Помилка");
				System::String ^err_descr = gcnew System::String(ex.what());
				err_descr += gcnew System::String(". Поміняйте рецепт та запустіть робота ще раз");
				System::Windows::Forms::MessageBox::Show(err_descr, err_name, System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
				delete err_name;
				delete err_descr;
				System::Windows::Forms::Application::Exit();
			}
		}
		if (temp == "with") {
			getline(s, temp, '"');
			getline(s, temp, '"');
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
			text_to.push_back(temp1);
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
