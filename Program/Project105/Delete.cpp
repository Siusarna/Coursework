#include "Robot.h"

void Robot::delete_text(option recipe) {
	int from = 0;
	int to = 0;
	parce_for_delete(recipe.row, from, to);
	if (from < 1) from = 1;
	if (to > this->text.size()) to = this->text.size();
	this->text.erase(this->text.begin() + from - 1, this->text.begin() + to);
}

void Robot::parce_for_delete(string recipe, int& from, int& to) {
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
	} while (getline(s, temp, ' '));
}