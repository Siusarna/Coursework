#include "MyForm.h"

using namespace System;

using namespace System::Windows::Forms;

[STAThreadAttribute]

void main(cli::array<String^>^ args){

	Application::EnableVisualStyles(); 
	Application::SetCompatibleTextRenderingDefault(false);
	Project105::MyForm form;
	Application::Run(%form);

}