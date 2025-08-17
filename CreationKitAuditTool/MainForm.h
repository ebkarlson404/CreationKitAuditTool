#pragma once

namespace CreationKitAuditTool {

	using namespace System;
	using namespace System::IO;
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
	private: System::IO::FileSystemWatcher^ fileSystemWatcher;
	protected: bool running = false;
	protected: String^ starfieldDataFolder;
	protected: String^ starfieldXBoxDataFolder;

	protected:
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowser;
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
	private: System::Windows::Forms::CheckBox^ pscCheckBox;


	private: System::Windows::Forms::Button^ generateButton;
	private: System::Windows::Forms::Button^ quitButton;

	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Button^ stopButton;
	private: System::Windows::Forms::Button^ startButton;
	private: System::Windows::Forms::Button^ xboxWEMButton;
	private: System::Windows::Forms::Button^ importButton;
	private: System::Windows::Forms::ColumnHeader^ columnHeader1;





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
			this->fileSystemWatcher = (gcnew System::IO::FileSystemWatcher());
			this->folderBrowser = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->starfieldFolderTextBox = (gcnew System::Windows::Forms::TextBox());
			this->starfieldFolderButton = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->xboxWEMTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->pluginComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->auditListView = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->importButton = (gcnew System::Windows::Forms::Button());
			this->generateButton = (gcnew System::Windows::Forms::Button());
			this->wavCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->pscCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->stopButton = (gcnew System::Windows::Forms::Button());
			this->startButton = (gcnew System::Windows::Forms::Button());
			this->quitButton = (gcnew System::Windows::Forms::Button());
			this->xboxWEMButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fileSystemWatcher))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// fileSystemWatcher
			// 
			this->fileSystemWatcher->EnableRaisingEvents = true;
			this->fileSystemWatcher->SynchronizingObject = this;
			this->fileSystemWatcher->Changed += gcnew System::IO::FileSystemEventHandler(this, &MainForm::fileSystemWatcher_Changed);
			this->fileSystemWatcher->Created += gcnew System::IO::FileSystemEventHandler(this, &MainForm::fileSystemWatcher_Created);
			this->fileSystemWatcher->Deleted += gcnew System::IO::FileSystemEventHandler(this, &MainForm::fileSystemWatcher_Deleted);
			this->fileSystemWatcher->Renamed += gcnew System::IO::RenamedEventHandler(this, &MainForm::fileSystemWatcher_Renamed);
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
			this->auditListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) { this->columnHeader1 });
			this->auditListView->HideSelection = false;
			this->auditListView->Location = System::Drawing::Point(45, 153);
			this->auditListView->MultiSelect = false;
			this->auditListView->Name = L"auditListView";
			this->auditListView->Size = System::Drawing::Size(887, 422);
			this->auditListView->Sorting = System::Windows::Forms::SortOrder::Ascending;
			this->auditListView->TabIndex = 8;
			this->auditListView->TabStop = false;
			this->auditListView->UseCompatibleStateImageBehavior = false;
			this->auditListView->View = System::Windows::Forms::View::Details;
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"Relative Filename";
			this->columnHeader1->Width = 881;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->importButton);
			this->groupBox1->Controls->Add(this->generateButton);
			this->groupBox1->Controls->Add(this->wavCheckBox);
			this->groupBox1->Controls->Add(this->pscCheckBox);
			this->groupBox1->Location = System::Drawing::Point(47, 601);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(471, 200);
			this->groupBox1->TabIndex = 9;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"ARCHLIST Generation";
			// 
			// importButton
			// 
			this->importButton->Enabled = false;
			this->importButton->Location = System::Drawing::Point(290, 36);
			this->importButton->Name = L"importButton";
			this->importButton->Size = System::Drawing::Size(157, 48);
			this->importButton->TabIndex = 2;
			this->importButton->Text = L"Import";
			this->importButton->UseVisualStyleBackColor = true;
			this->importButton->Click += gcnew System::EventHandler(this, &MainForm::importButton_Click);
			// 
			// generateButton
			// 
			this->generateButton->Enabled = false;
			this->generateButton->Location = System::Drawing::Point(290, 131);
			this->generateButton->Name = L"generateButton";
			this->generateButton->Size = System::Drawing::Size(157, 48);
			this->generateButton->TabIndex = 3;
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
			// pscCheckBox
			// 
			this->pscCheckBox->AutoSize = true;
			this->pscCheckBox->Checked = true;
			this->pscCheckBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->pscCheckBox->Location = System::Drawing::Point(6, 28);
			this->pscCheckBox->Name = L"pscCheckBox";
			this->pscCheckBox->Size = System::Drawing::Size(155, 29);
			this->pscCheckBox->TabIndex = 0;
			this->pscCheckBox->Text = L"Exclude PSC";
			this->pscCheckBox->UseVisualStyleBackColor = true;
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
			this->stopButton->TabIndex = 5;
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
			this->startButton->TabIndex = 4;
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fileSystemWatcher))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void starfieldFolderButton_Click(System::Object^ sender, System::EventArgs^ e) {
	folderBrowser->Description = "Select the Starfield Installation Folder";
	folderBrowser->SelectedPath = starfieldFolderTextBox->Text;
	folderBrowser->ShowNewFolderButton = false;
	if (folderBrowser->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
		String^ base = folderBrowser->SelectedPath;
		starfieldFolderTextBox->Text = base;
		starfieldDataFolder = base->ToUpper() + L"\\DATA\\";
		fileSystemWatcher->Path = starfieldFolderTextBox->Text;
		fileSystemWatcher->IncludeSubdirectories = true;
		xboxWEMButton->Enabled = true;
		if (0 == String::Compare(base, 0, xboxWEMTextBox->Text, 0, base->Length)) {
			startButton->Enabled = true;
		}
		else {
			xboxWEMTextBox->Text = L"";
			startButton->Enabled = false;
		}
	}
}
private: System::Void xboxWEMButton_Click(System::Object^ sender, System::EventArgs^ e) {
	folderBrowser->Description = "Select the XBox Alternate WEM Folder";
	folderBrowser->SelectedPath = starfieldFolderTextBox->Text;
	folderBrowser->ShowNewFolderButton = true;
	if (folderBrowser->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
		String^ base = starfieldFolderTextBox->Text;
		String^ path = folderBrowser->SelectedPath;
		if (0 != String::Compare(base, 0, path, 0, base->Length)) {
			MessageBox::Show(L"XBox WEM Folder must reside within the Starfield Folder.", L"Invalid XBox WEM Folder", MessageBoxButtons::OK);
		}
		else {
			xboxWEMTextBox->Text = folderBrowser->SelectedPath;
			starfieldXBoxDataFolder = folderBrowser->SelectedPath + L"\\Data\\";
			if (!(starfieldFolderTextBox->Text->Equals(L""))) {
				startButton->Enabled = true;
			}
		}
	}
}
private: System::Void startButton_Click(System::Object^ sender, System::EventArgs^ e) {
	startButton->Enabled = false;
	stopButton->Enabled = true;
	running = true;
}
private: System::Void stopButton_Click(System::Object^ sender, System::EventArgs^ e) {
	stopButton->Enabled = false;
	startButton->Enabled = true;
	running = false;
}
private: System::Void generateButton_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void quitButton_Click(System::Object^ sender, System::EventArgs^ e) {
	this->Close();
}
private: System::Void importButton_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void fileSystemWatcher_Changed(System::Object^ sender, System::IO::FileSystemEventArgs^ e) {
	if (running) {
		if (shouldLog(e->FullPath, false)) {
			String^ rpath = relativePath(e->FullPath);
			if (nullptr == auditListView->FindItemWithText(rpath)) {
				auditListView->Items->Add(gcnew ListViewItem(rpath));
			}
		}
	}
}
private: System::Void fileSystemWatcher_Deleted(System::Object^ sender, System::IO::FileSystemEventArgs^ e) {
	if (running) {
		if (shouldLog(e->FullPath, true)) {
			auditListView->Items->Remove(auditListView->FindItemWithText(relativePath(e->FullPath)));
		}
	}
}
private: System::Void fileSystemWatcher_Created(System::Object^ sender, System::IO::FileSystemEventArgs^ e) {
	if (running) {
		if (shouldLog(e->FullPath, false)) {
			String^ rpath = relativePath(e->FullPath);
			if (nullptr == auditListView->FindItemWithText(rpath)) {
				auditListView->Items->Add(gcnew ListViewItem(rpath));
			}
		}
	}
}
private: System::Void fileSystemWatcher_Renamed(System::Object^ sender, System::IO::RenamedEventArgs^ e) {
	if (running) {
		if (shouldLog(e->OldFullPath, true)) {
			auditListView->Items->Remove(auditListView->FindItemWithText(relativePath(e->OldFullPath)));
		}
		if (shouldLog(e->FullPath, false)) {
			String^ rpath = relativePath(e->FullPath);
			if (nullptr == auditListView->FindItemWithText(rpath)) {
				auditListView->Items->Add(gcnew ListViewItem(rpath));
			}
		}
	}
}
private: bool shouldLog(String^ fullName, bool isDelete) {
	if (!isDelete) {
		try {
			FileAttributes attr = File::GetAttributes(fullName);
			if (attr.HasFlag(FileAttributes::Directory) || attr.HasFlag(FileAttributes::Hidden)) {
				return false;
			}
		}
		catch (System::Exception^ e) {
			// Assume that the file was deleted prior to processing this notification, so
			// we should not log it.  We should get a DELETE notification later on that
			// will remove this file from the audit list.
			return false;
		}
	}

	// Ignore any file not under the Starfield Data or Starfield XBox folders
	if ((fullName->Length < starfieldDataFolder->Length ||
			0 != String::Compare(fullName, 0, starfieldDataFolder, 0, starfieldDataFolder->Length, true)) &&
		(fullName->Length < starfieldXBoxDataFolder->Length ||
			0 != String::Compare(fullName, 0, starfieldXBoxDataFolder, 0, starfieldXBoxDataFolder->Length, true))) {
		return false;
	}

	// Ignore the ESP & ESM files.  Also the TEMP.WEM files that are generated by WWise.
	if (fullName->EndsWith(L".esm", StringComparison::InvariantCultureIgnoreCase) ||
		fullName->EndsWith(L".esp", StringComparison::InvariantCultureIgnoreCase) ||
		fullName->EndsWith(L"Temp.wem", StringComparison::InvariantCultureIgnoreCase)) {
		return false;
	}

	// Ignore the Papyrus Source files if so indicated
	if (pscCheckBox->Checked && fullName->EndsWith(".psc", StringComparison::InvariantCultureIgnoreCase)) {
		return false;
	}

	// Ignore the WAV Audio Files if so indicated
	if (wavCheckBox->Checked && fullName->EndsWith(".wav", StringComparison::InvariantCultureIgnoreCase)) {
		return false;
	}
	return true;
}
private: String^ relativePath(String^ fullname) {
	// If the file resides in the Starfield XBox Alternate Data folder, we have to construct
	// the special relative path that will resolve properly when the Creation Kit processes
	// the ARCHLIST file.
	if (fullname->Length >= starfieldXBoxDataFolder->Length &&
		0 == String::Compare(fullname, 0, starfieldXBoxDataFolder, 0, starfieldXBoxDataFolder->Length, true)) {
		return L"Data\\..\\" + fullname->Substring(starfieldFolderTextBox->Text->Length + 1);
	}

	// A normal Starfield Data file, just compute a simple relative path
	return fullname->Substring(starfieldFolderTextBox->Text->Length + 1);
}
};
}
