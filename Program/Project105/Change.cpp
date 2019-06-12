#include "Robot.h"


void Robot::change_text(option recipe) {
	int from;
	int to;
	vector<string> text_for_change;
	parce_for_change(recipe.row, from, to, text_for_change);
	if (from > 0) from--;
	if (from < 1) from = 0;
	if (to > this->text.size()) to = this->text.size();
	if ((to - from) > text_for_change.size()) {
		this->text.erase(this->text.begin() + from + text_for_change.size() - 1, this->text.begin() + to - 1);
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

void Robot::parce_for_change(string recipe, int& from, int& to, vector<string>& text_for_change) {
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