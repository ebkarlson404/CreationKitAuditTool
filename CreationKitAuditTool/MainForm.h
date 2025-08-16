#pragma once

namespace CreationKitAuditTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::IO::FileSystemWatcher^ fileSystemWatcher1;
	protected:
	private: System::Windows::Forms::FolderBrowserDialog^ starfieldFolderBrowser;
	private: System::Windows::Forms::TextBox^ starfieldFolderTextBox;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ starfieldFolderButton;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ xboxWEMTextBox;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ComboBox^ pluginComboBox;
	private: System::Windows::Forms::GroupBox^ groupBox1;


	private: System::Windows::Forms::ListView^ auditListView;
	private: System::Windows::Forms::CheckBox^ wavCheckBox;

	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Button^ generateButton;
	private: System::Windows::Forms::Button^ quitButton;

	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Button^ stopButton;
	private: System::Windows::Forms::Button^ startButton;
	private: System::Windows::Forms::Button^ xboxWEMButton;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->fileSystemWatcher1 = (gcnew System::IO::FileSystemWatcher());
			this->starfieldFolderBrowser = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->starfieldFolderTextBox = (gcnew System::Windows::Forms::TextBox());
			this->starfieldFolderButton = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->xboxWEMTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->pluginComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->auditListView = (gcnew System::Windows::Forms::ListView());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->generateButton = (gcnew System::Windows::Forms::Button());
			this->wavCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->stopButton = (gcnew System::Windows::Forms::Button());
			this->startButton = (gcnew System::Windows::Forms::Button());
			this->quitButton = (gcnew System::Windows::Forms::Button());
			this->xboxWEMButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fileSystemWatcher1))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// fileSystemWatcher1
			// 
			this->fileSystemWatcher1->EnableRaisingEvents = true;
			this->fileSystemWatcher1->SynchronizingObject = this;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(40, 26);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(240, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Starfield Installation Folder";
			// 
			// starfieldFolderTextBox
			// 
			this->starfieldFolderTextBox->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->starfieldFolderTextBox->Location = System::Drawing::Point(286, 22);
			this->starfieldFolderTextBox->Name = L"starfieldFolderTextBox";
			this->starfieldFolderTextBox->ReadOnly = true;
			this->starfieldFolderTextBox->Size = System::Drawing::Size(646, 29);
			this->starfieldFolderTextBox->TabIndex = 1;
			// 
			// starfieldFolderButton
			// 
			this->starfieldFolderButton->Location = System::Drawing::Point(963, 18);
			this->starfieldFolderButton->Name = L"starfieldFolderButton";
			this->starfieldFolderButton->Size = System::Drawing::Size(47, 39);
			this->starfieldFolderButton->TabIndex = 2;
			this->starfieldFolderButton->Text = L"...";
			this->starfieldFolderButton->UseVisualStyleBackColor = true;
			this->starfieldFolderButton->Click += gcnew System::EventHandler(this, &MainForm::starfieldFolderButton_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(40, 66);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(184, 25);
			this->label2->TabIndex = 3;
			this->label2->Text = L"XBOX WEM Folder";
			// 
			// xboxWEMTextBox
			// 
			this->xboxWEMTextBox->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->xboxWEMTextBox->Location = System::Drawing::Point(286, 63);
			this->xboxWEMTextBox->Name = L"xboxWEMTextBox";
			this->xboxWEMTextBox->ReadOnly = true;
			this->xboxWEMTextBox->Size = System::Drawing::Size(646, 29);
			this->xboxWEMTextBox->TabIndex = 4;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(40, 107);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(201, 25);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Plugin Base Filename";
			// 
			// pluginComboBox
			// 
			this->pluginComboBox->FormattingEnabled = true;
			this->pluginComboBox->Location = System::Drawing::Point(286, 104);
			this->pluginComboBox->Name = L"pluginComboBox";
			this->pluginComboBox->Size = System::Drawing::Size(646, 32);
			this->pluginComboBox->TabIndex = 7;
			// 
			// auditListView
			// 
			this->auditListView->HideSelection = false;
			this->auditListView->Location = System::Drawing::Point(45, 153);
			this->auditListView->Name = L"auditListView";
			this->auditListView->Size = System::Drawing::Size(887, 422);
			this->auditListView->TabIndex = 8;
			this->auditListView->UseCompatibleStateImageBehavior = false;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->generateButton);
			this->groupBox1->Controls->Add(this->wavCheckBox);
			this->groupBox1->Controls->Add(this->checkBox1);
			this->groupBox1->Location = System::Drawing::Point(47, 601);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(471, 110);
			this->groupBox1->TabIndex = 9;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"ARCHLIST Generation";
			// 
			// generateButton
			// 
			this->generateButton->Enabled = false;
			this->generateButton->Location = System::Drawing::Point(293, 36);
			this->generateButton->Name = L"generateButton";
			this->generateButton->Size = System::Drawing::Size(157, 48);
			this->generateButton->TabIndex = 2;
			this->generateButton->Text = L"Generate";
			this->generateButton->UseVisualStyleBackColor = true;
			this->generateButton->Click += gcnew System::EventHandler(this, &MainForm::generateButton_Click);
			// 
			// wavCheckBox
			// 
			this->wavCheckBox->AutoSize = true;
			this->wavCheckBox->Checked = true;
			this->wavCheckBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->wavCheckBox->Location = System::Drawing::Point(6, 63);
			this->wavCheckBox->Name = L"wavCheckBox";
			this->wavCheckBox->Size = System::Drawing::Size(161, 29);
			this->wavCheckBox->TabIndex = 1;
			this->wavCheckBox->Text = L"Exclude WAV";
			this->wavCheckBox->UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Checked = true;
			this->checkBox1->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBox1->Location = System::Drawing::Point(6, 28);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(155, 29);
			this->checkBox1->TabIndex = 0;
			this->checkBox1->Text = L"Exclude PSC";
			this->checkBox1->UseVisualStyleBackColor = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->stopButton);
			this->groupBox2->Controls->Add(this->startButton);
			this->groupBox2->Location = System::Drawing::Point(547, 601);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(385, 110);
			this->groupBox2->TabIndex = 10;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"File Watcher";
			// 
			// stopButton
			// 
			this->stopButton->Enabled = false;
			this->stopButton->Location = System::Drawing::Point(205, 36);
			this->stopButton->Name = L"stopButton";
			this->stopButton->Size = System::Drawing::Size(157, 48);
			this->stopButton->TabIndex = 4;
			this->stopButton->Text = L"Stop";
			this->stopButton->UseVisualStyleBackColor = true;
			this->stopButton->Click += gcnew System::EventHandler(this, &MainForm::stopButton_Click);
			// 
			// startButton
			// 
			this->startButton->Enabled = false;
			this->startButton->Location = System::Drawing::Point(6, 36);
			this->startButton->Name = L"startButton";
			this->startButton->Size = System::Drawing::Size(157, 48);
			this->startButton->TabIndex = 3;
			this->startButton->Text = L"Start";
			this->startButton->UseVisualStyleBackColor = true;
			this->startButton->Click += gcnew System::EventHandler(this, &MainForm::startButton_Click);
			// 
			// quitButton
			// 
			this->quitButton->Location = System::Drawing::Point(752, 732);
			this->quitButton->Name = L"quitButton";
			this->quitButton->Size = System::Drawing::Size(157, 48);
			this->quitButton->TabIndex = 11;
			this->quitButton->Text = L"Quit";
			this->quitButton->UseVisualStyleBackColor = true;
			this->quitButton->Click += gcnew System::EventHandler(this, &MainForm::quitButton_Click);
			// 
			// xboxWEMButton
			// 
			this->xboxWEMButton->Enabled = false;
			this->xboxWEMButton->Location = System::Drawing::Point(963, 63);
			this->xboxWEMButton->Name = L"xboxWEMButton";
			this->xboxWEMButton->Size = System::Drawing::Size(47, 39);
			this->xboxWEMButton->TabIndex = 5;
			this->xboxWEMButton->Text = L"...";
			this->xboxWEMButton->UseVisualStyleBackColor = true;
			this->xboxWEMButton->Click += gcnew System::EventHandler(this, &MainForm::xboxWEMButton_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1035, 813);
			this->Controls->Add(this->xboxWEMButton);
			this->Controls->Add(this->quitButton);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->auditListView);
			this->Controls->Add(this->pluginComboBox);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->xboxWEMTextBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->starfieldFolderButton);
			this->Controls->Add(this->starfieldFolderTextBox);
			this->Controls->Add(this->label1);
			this->MinimumSize = System::Drawing::Size(1059, 877);
			this->Name = L"MainForm";
			this->Text = L"Starfield Creation Kit Audit Tool";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fileSystemWatcher1))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void starfieldFolderButton_Click(System::Object^ sender, System::EventArgs^ e) {
	starfieldFolderBrowser->Description = "Select the Starfield Installation Folder";
	starfieldFolderBrowser->SelectedPath = starfieldFolderTextBox->Text;
	starfieldFolderBrowser->ShowNewFolderButton = false;
	if (starfieldFolderBrowser->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
		starfieldFolderTextBox->Text = starfieldFolderBrowser->SelectedPath;
		fileSystemWatcher1->Path = starfieldFolderTextBox->Text;
		xboxWEMButton->Enabled = true;
		if (!(xboxWEMTextBox->Text->Equals(L""))) {
			startButton->Enabled = true;
		}
	}
}
private: System::Void xboxWEMButton_Click(System::Object^ sender, System::EventArgs^ e) {
	starfieldFolderBrowser->Description = "Select the XBox Alternate WEM Folder";
	if (!xboxWEMTextBox->Text->Equals(L"")) {
		starfieldFolderBrowser->SelectedPath = xboxWEMTextBox->Text;
	}
	else {
		starfieldFolderBrowser->SelectedPath = starfieldFolderTextBox->Text;
	}
	starfieldFolderBrowser->ShowNewFolderButton = true;
	if (starfieldFolderBrowser->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
		xboxWEMTextBox->Text = starfieldFolderBrowser->SelectedPath;
		if (!(starfieldFolderTextBox->Text->Equals(L""))) {
			startButton->Enabled = true;
		}
	}
}
private: System::Void startButton_Click(System::Object^ sender, System::EventArgs^ e) {
	startButton->Enabled = false;
	stopButton->Enabled = true;
}
private: System::Void stopButton_Click(System::Object^ sender, System::EventArgs^ e) {
	stopButton->Enabled = false;
	startButton->Enabled = true;
}
private: System::Void generateButton_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void quitButton_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Close();
}
};
}
