#include <queue>
#include <vector>
#include <string>

using namespace std;

struct option
{
	string word;
	string row;
};

class Robot
{
public:
	Robot(string path_recipe, string path_text);

	void start_work();
	void delete_text(option recipe);
	void change_text(option recipe);
	void insert_text(option recipe);
	void replace_text(option recipe);

private:
	queue<option> que;
	vector<string> text;

	void parce_for_delete(string recipe, int &from, int &to);
	void parce_for_change(string recipe, int &from, int &to, vector<string> &text_for_change);
	void parce_for_insert(string recipe, int &after, vector<string> &text_for_insert);
	void parce_for_replace(string recipe, int &from, int &to, vector<string> &text_from, vector<string> &text_to);

	vector<string> Open_Text(string path);
	queue<option> Open_Recipe(string path);
	
};

Robot::Robot(string path_recipe, string path_text)
{
	this->que = Open_Recipe(path_recipe);
	this->text = Open_Text(path_text);
}
