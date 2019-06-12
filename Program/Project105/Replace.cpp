#include "Robot.h"

void Robot::parce_for_replace(string recipe, int& from, int& to, vector<string>& text_from, vector<string>& text_to) {
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
				System::String^ err_name = gcnew System::String("Помилка");
				System::String^ err_descr = gcnew System::String(ex.what());
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
				System::String^ err_name = gcnew System::String("Помилка");
				System::String^ err_descr = gcnew System::String(ex.what());
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
					this->text[i].erase(this->text[i].begin() + pos, this->text[i].begin() + size);
					int k = 1;
					for (int j = 1; j < text_to.size(); j++) {
						this->text.insert(this->text.begin() + i + k, text_to[k]);
						to++;
						k++;
					}
					this->text[i + text_to.size() - 1] += save;
				}
			}
		}
	}
	else {
		for (int i = from - 1; i < to - 1; i++) {
			bool flag = true;
			for (int k = 0; k < text_from.size(); k++) {
				for (int j = 0; j < this->text[i].size(); j++) {
					if (this->text[i + k][j] != text_from[k][j]) {
						flag = false;
						break;
					}
				}
			}
			if (flag) {
				int k = 0;
				if (text_to.size() > text_from.size()) {
					for (k = 0; k < text_from.size(); k++) {
						if (this->text[i + k].size() < text_to[k].size()) {
							int j = 0;
							while (j < this->text[i].size()) {
								this->text[i + k][j] = text_to[k][j];
								j++;
							}
							for (int q = j; q < text_to[k].size(); q++) {
								this->text[i + k] += text[k][q];
							}
						}
						else {
							for (int j = 0; j < text_to[k].size(); j++) {
								this->text[i + k][j] = text_to[k][j];
							}
						}
					}
					for (int y = 0; y < text_to.size() - k; y++) {
						this->text.insert(this->text.begin() + i + k, text_to[k + y]);
					}
				}
				if (text_from.size() > text_to.size()) {
					this->text.erase(this->text.begin() + i + k, this->text.begin() + i + k + (text_from.size() - text_to.size()));
				}
			}
		}
	}
}
