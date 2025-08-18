#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

int main(array<String^>^ argv) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	CreationKitAuditTool::MainForm form;
	Application::Run(% form);
}