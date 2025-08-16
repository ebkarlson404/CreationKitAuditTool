#include "MainForm.h"

using namespace System;
using namespace System::Windows::Forms;

void main(array<String^>^ argv) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	CreationKitAuditTool::MainForm form;
	Application::Run(% form);
}