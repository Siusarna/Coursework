#include<iostream>
#include <string>
#include <vector>
#include "Robot.h"
using namespace std;

int main() {
	Robot text_editor("recipe.txt", "text.txt");
	text_editor.start_work();
	system("pause");
}