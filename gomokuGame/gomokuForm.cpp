#include "stdafx.h"
#include "gomokuForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void Main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	gomokuGame::gomokuForm form;
	Application::Run(%form);
}
