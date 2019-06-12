#include "Robot.h"

void Robot::insert_text(option recipe) {
	int after;
	vector<string> text_for_insert;
	parce_for_insert(recipe.row, after, text_for_insert);
	if (after < 1) after = 1;
	if (after > this->text.size()) after = this->text.size();
	int k = 0;
	for (unsigned int i = 0; i < text_for_insert.size(); i++) {
		this->text.insert(this->text.begin() + after + k, text_for_insert[k]);
		k++;
	}
}

void Robot::parce_for_insert(string recipe, int& after, vector<string>& text_for_insert) {
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
				System::String^ err_name = gcnew System::String("Помилка");
				System::String^ err_descr = gcnew System::String(ex.what());
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
				if (temp[i] == '\\' && temp[i + 1] == 'n' || temp[i] == '"') {
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

