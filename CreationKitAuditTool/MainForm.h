#pragma once


namespace CreationKitAuditTool {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Microsoft::Win32;
	using namespace System::Runtime::Serialization::Json;

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
			// Record initial window size
			lastHeight = this->Height;
			lastWidth = this->Width;

			// Reload the last parameter values for the Starfield Folder and XBox WEM Folder
			Object^ value = ReadSetting(registryNameStarfieldFolder);
			if (nullptr != value) {
				starfieldFolderTextBox->Text = (String^)value;
			}
			value = ReadSetting(registryNameXBoxWEMFolder);
			if (nullptr != value && xboxWEMTextBox->Enabled) {
				xboxWEMTextBox->Text = (String^)value;
			}

			// Generate the name of the folder that Creation Kit Audit Tool will
			// use for storing manifests and generated ARCHLIST files
			String^ docFolder = System::Environment::GetFolderPath(System::Environment::SpecialFolder::MyDocuments);
			userGameFolder = docFolder + L"\\My Games\\Starfield\\CreationKitAuditTool";
			System::IO::Directory::CreateDirectory(userGameFolder);
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
	protected: int lastHeight = -1;
	protected: int lastWidth = -1;
	protected: String^ registryKey = L"SOFTWARE\\GrizBane\\CreationKitAuditTool";
	protected: String^ registryNameStarfieldFolder = L"StarfieldFolder";
	protected: String^ registryNameXBoxWEMFolder = L"XBoxWEMFolder";
	protected: String^ userGameFolder;
	protected: String^ manifestFileExt = L".manifest";

	protected:
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowser;
	private: System::Windows::Forms::TextBox^ starfieldFolderTextBox;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ starfieldFolderButton;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ xboxWEMTextBox;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ComboBox^ pluginComboBox;
	private: System::Windows::Forms::GroupBox^ achlistGroupBox;


	private: System::Windows::Forms::ListView^ auditListView;
	private: System::Windows::Forms::CheckBox^ wavCheckBox;
	private: System::Windows::Forms::CheckBox^ pscCheckBox;
	private: System::Windows::Forms::Button^ generateButton;
	private: System::Windows::Forms::Button^ quitButton;
	private: System::Windows::Forms::GroupBox^ fileWatcherGroupBox;

	private: System::Windows::Forms::Button^ stopButton;
	private: System::Windows::Forms::Button^ startButton;
	private: System::Windows::Forms::Button^ xboxWEMButton;
	private: System::Windows::Forms::Button^ importButton;
	private: System::Windows::Forms::ColumnHeader^ columnHeader1;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ aboutToolStripMenuItem;
	private: System::Windows::Forms::BindingSource^ pluginEnumerator;
	private: System::Data::DataSet^ dataSet1;
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->fileSystemWatcher = (gcnew System::IO::FileSystemWatcher());
			this->folderBrowser = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->starfieldFolderTextBox = (gcnew System::Windows::Forms::TextBox());
			this->starfieldFolderButton = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->xboxWEMTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->pluginComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->pluginEnumerator = (gcnew System::Windows::Forms::BindingSource(this->components));
			this->dataSet1 = (gcnew System::Data::DataSet());
			this->auditListView = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->achlistGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->importButton = (gcnew System::Windows::Forms::Button());
			this->generateButton = (gcnew System::Windows::Forms::Button());
			this->wavCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->pscCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->fileWatcherGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->stopButton = (gcnew System::Windows::Forms::Button());
			this->startButton = (gcnew System::Windows::Forms::Button());
			this->quitButton = (gcnew System::Windows::Forms::Button());
			this->xboxWEMButton = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fileSystemWatcher))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pluginEnumerator))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSet1))->BeginInit();
			this->achlistGroupBox->SuspendLayout();
			this->fileWatcherGroupBox->SuspendLayout();
			this->menuStrip1->SuspendLayout();
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
			this->label1->Location = System::Drawing::Point(40, 63);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(240, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Starfield Installation Folder";
			// 
			// starfieldFolderTextBox
			// 
			this->starfieldFolderTextBox->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->starfieldFolderTextBox->Location = System::Drawing::Point(286, 63);
			this->starfieldFolderTextBox->Name = L"starfieldFolderTextBox";
			this->starfieldFolderTextBox->ReadOnly = true;
			this->starfieldFolderTextBox->Size = System::Drawing::Size(646, 29);
			this->starfieldFolderTextBox->TabIndex = 1;
			this->starfieldFolderTextBox->TextChanged += gcnew System::EventHandler(this, &MainForm::starfieldFolderTextBox_TextChanged);
			// 
			// starfieldFolderButton
			// 
			this->starfieldFolderButton->Location = System::Drawing::Point(963, 63);
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
			this->label2->Location = System::Drawing::Point(40, 102);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(184, 25);
			this->label2->TabIndex = 3;
			this->label2->Text = L"XBOX WEM Folder";
			// 
			// xboxWEMTextBox
			// 
			this->xboxWEMTextBox->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->xboxWEMTextBox->Location = System::Drawing::Point(286, 102);
			this->xboxWEMTextBox->Name = L"xboxWEMTextBox";
			this->xboxWEMTextBox->ReadOnly = true;
			this->xboxWEMTextBox->Size = System::Drawing::Size(646, 29);
			this->xboxWEMTextBox->TabIndex = 4;
			this->xboxWEMTextBox->TextChanged += gcnew System::EventHandler(this, &MainForm::xboxWEMTextBox_TextChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(40, 141);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(201, 25);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Plugin Base Filename";
			// 
			// pluginComboBox
			// 
			this->pluginComboBox->DataSource = this->pluginEnumerator;
			this->pluginComboBox->Enabled = false;
			this->pluginComboBox->FormattingEnabled = true;
			this->pluginComboBox->Location = System::Drawing::Point(286, 141);
			this->pluginComboBox->MaxDropDownItems = 16;
			this->pluginComboBox->Name = L"pluginComboBox";
			this->pluginComboBox->Size = System::Drawing::Size(646, 32);
			this->pluginComboBox->TabIndex = 7;
			this->pluginComboBox->TextChanged += gcnew System::EventHandler(this, &MainForm::pluginComboBox_TextChanged);
			// 
			// dataSet1
			// 
			this->dataSet1->DataSetName = L"pluginDataSet";
			// 
			// auditListView
			// 
			this->auditListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) { this->columnHeader1 });
			this->auditListView->HideSelection = false;
			this->auditListView->Location = System::Drawing::Point(45, 186);
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
			this->columnHeader1->Width = 800;
			// 
			// achlistGroupBox
			// 
			this->achlistGroupBox->Controls->Add(this->importButton);
			this->achlistGroupBox->Controls->Add(this->generateButton);
			this->achlistGroupBox->Controls->Add(this->wavCheckBox);
			this->achlistGroupBox->Controls->Add(this->pscCheckBox);
			this->achlistGroupBox->ForeColor = System::Drawing::SystemColors::ControlText;
			this->achlistGroupBox->Location = System::Drawing::Point(45, 629);
			this->achlistGroupBox->Name = L"achlistGroupBox";
			this->achlistGroupBox->Size = System::Drawing::Size(471, 200);
			this->achlistGroupBox->TabIndex = 9;
			this->achlistGroupBox->TabStop = false;
			this->achlistGroupBox->Text = L"ACHLIST Generation";
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
			// fileWatcherGroupBox
			// 
			this->fileWatcherGroupBox->Controls->Add(this->stopButton);
			this->fileWatcherGroupBox->Controls->Add(this->startButton);
			this->fileWatcherGroupBox->Location = System::Drawing::Point(547, 629);
			this->fileWatcherGroupBox->Name = L"fileWatcherGroupBox";
			this->fileWatcherGroupBox->Size = System::Drawing::Size(385, 110);
			this->fileWatcherGroupBox->TabIndex = 10;
			this->fileWatcherGroupBox->TabStop = false;
			this->fileWatcherGroupBox->Text = L"File Watcher";
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
			this->startButton->Location = System::Drawing::Point(23, 36);
			this->startButton->Name = L"startButton";
			this->startButton->Size = System::Drawing::Size(157, 48);
			this->startButton->TabIndex = 4;
			this->startButton->Text = L"Start";
			this->startButton->UseVisualStyleBackColor = true;
			this->startButton->Click += gcnew System::EventHandler(this, &MainForm::startButton_Click);
			// 
			// quitButton
			// 
			this->quitButton->Location = System::Drawing::Point(752, 760);
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
			this->xboxWEMButton->Location = System::Drawing::Point(963, 102);
			this->xboxWEMButton->Name = L"xboxWEMButton";
			this->xboxWEMButton->Size = System::Drawing::Size(47, 39);
			this->xboxWEMButton->TabIndex = 5;
			this->xboxWEMButton->Text = L"...";
			this->xboxWEMButton->UseVisualStyleBackColor = true;
			this->xboxWEMButton->Click += gcnew System::EventHandler(this, &MainForm::xboxWEMButton_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(28, 28);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->helpToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1026, 38);
			this->menuStrip1->TabIndex = 12;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->exitToolStripMenuItem });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(62, 34);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::F4));
			this->exitToolStripMenuItem->Size = System::Drawing::Size(238, 40);
			this->exitToolStripMenuItem->Text = L"Exit";
			this->exitToolStripMenuItem->ToolTipText = L"Exit the Creation Kit Audit Tool";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::exitToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->aboutToolStripMenuItem });
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(74, 34);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::F1));
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(268, 40);
			this->aboutToolStripMenuItem->Text = L"About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::aboutToolStripMenuItem_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1026, 846);
			this->Controls->Add(this->xboxWEMButton);
			this->Controls->Add(this->quitButton);
			this->Controls->Add(this->fileWatcherGroupBox);
			this->Controls->Add(this->achlistGroupBox);
			this->Controls->Add(this->auditListView);
			this->Controls->Add(this->pluginComboBox);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->xboxWEMTextBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->starfieldFolderButton);
			this->Controls->Add(this->starfieldFolderTextBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->MinimumSize = System::Drawing::Size(1050, 910);
			this->Name = L"MainForm";
			this->Text = L"Starfield Creation Kit Audit Tool";
			this->Layout += gcnew System::Windows::Forms::LayoutEventHandler(this, &MainForm::MainForm_Layout);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fileSystemWatcher))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pluginEnumerator))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataSet1))->EndInit();
			this->achlistGroupBox->ResumeLayout(false);
			this->achlistGroupBox->PerformLayout();
			this->fileWatcherGroupBox->ResumeLayout(false);
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	//
	// Event handlers for the various controls
	//
	private: System::Void starfieldFolderButton_Click(System::Object^ sender, System::EventArgs^ e) {
		folderBrowser->Description = "Select the Starfield Installation Folder";
		folderBrowser->SelectedPath = starfieldFolderTextBox->Text;
		folderBrowser->ShowNewFolderButton = false;
		if (folderBrowser->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
			starfieldFolderTextBox->Text = folderBrowser->SelectedPath;
		}
	}
	private: System::Void xboxWEMButton_Click(System::Object^ sender, System::EventArgs^ e) {
		folderBrowser->Description = "Select the XBox Alternate WEM Folder";
		folderBrowser->SelectedPath = starfieldFolderTextBox->Text;
		folderBrowser->ShowNewFolderButton = true;
		if (folderBrowser->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
			String^ base = starfieldFolderTextBox->Text;
			String^ path = folderBrowser->SelectedPath;
			if (0 != String::Compare(base, 0, path, 0, base->Length, true)) {
				MessageBox::Show(
					L"XBox WEM Folder must reside within the Starfield Folder.",
					L"Invalid XBox WEM Folder",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
			}
			else {
				xboxWEMTextBox->Text = folderBrowser->SelectedPath;
			}
		}
	}
	private: System::Void startButton_Click(System::Object^ sender, System::EventArgs^ e) {
		startButton->Enabled = false;
		stopButton->Enabled = true;
		starfieldFolderButton->Enabled = false;
		xboxWEMButton->Enabled = false;
		pluginComboBox->Enabled = false;
		running = true;
	}
	private: System::Void stopButton_Click(System::Object^ sender, System::EventArgs^ e) {
		stopButton->Enabled = false;
		startButton->Enabled = true;
		starfieldFolderButton->Enabled = true;
		xboxWEMButton->Enabled = true;
		pluginComboBox->Enabled = true;
		running = false;
	}
	private: System::Void generateButton_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ xboxPrefix = L"Data\\.." + xboxWEMTextBox->Text->Substring(starfieldFolderTextBox->Text->Length) + L"\\";
		String^ espDirName = pluginComboBox->Text + L".esp";
		String^ esmDirName = pluginComboBox->Text + L".esm";
		Hashtable^ hmap = gcnew Hashtable();
		ArrayList^ xbList = gcnew ArrayList;
		ArrayList^ pcList = gcnew ArrayList;

		// Build out PC and XBox file lists.  First accumulate all the XBox WEM
		// files so that we can build our map of multi-platform WEM files.
		IEnumerator^ iter = auditListView->Items->GetEnumerator();
		while (iter->MoveNext()) {
			ListViewItem^ item = (ListViewItem^)iter->Current;
			String^ filename = item->Text;
			if (filename->StartsWith(xboxPrefix, StringComparison::InvariantCultureIgnoreCase)) {
				hmap->Add(filename->Substring(xboxPrefix->Length)->ToUpper(), filename);
				xbList->Add(espToEsmReplication(filename, espDirName, esmDirName));
			}
		}

		// Iterate through the list of files again, using the previously constructed
		// hashtable to prevent adding PC WEM files to the XBox list.
		iter = auditListView->Items->GetEnumerator();
		while (iter->MoveNext()) {
			ListViewItem^ item = (ListViewItem^)iter->Current;
			String^ filename = item->Text;

			// We've already processed the XBox WEM files, so skip them this time
			if (!filename->StartsWith(xboxPrefix, StringComparison::InvariantCultureIgnoreCase)) {
				// Replicate the file to the ESM directory if required
				filename = espToEsmReplication(filename, espDirName, esmDirName);

				// All files at this point are PC files
				pcList->Add(filename);

				// If this is not a PC WEM file, add it to the XBox list as well
				if (!hmap->ContainsKey(filename->ToUpper())) {
					xbList->Add(filename);
				}
			}
		}

		// Convert the lists to arrays for serialization
		System::Array^ pcFiles = pcList->ToArray(xboxPrefix->GetType());
		System::Array^ xbFiles = xbList->ToArray(xboxPrefix->GetType());

		DataContractJsonSerializer^ deser = gcnew DataContractJsonSerializer(pcFiles->GetType());
		String^ achlistFilename = userGameFolder + L"\\" + pluginComboBox->Text + L"-PC.achlist";
		System::IO::FileStream^ fh = nullptr;
		try {
			fh = File::Create(achlistFilename);
			deser->WriteObject(fh, pcFiles);
		}
		finally {
			if (nullptr != fh) {
				fh->Close();
			}
		}
		achlistFilename = userGameFolder + L"\\" + pluginComboBox->Text + L"-XB.achlist";
		fh = nullptr;
		try {
			fh = File::Create(achlistFilename);
			deser->WriteObject(fh, xbFiles);
		}
		finally {
			if (nullptr != fh) {
				fh->Close();
			}
		}
		MessageBox::Show(this,
			pluginComboBox->Text + 
			L"-PC.achlist and " + 
			pluginComboBox->Text + 
			L"-XB.achlist\nwere generated in\n" + 
			userGameFolder,
			L"ACHLIST Generation Complete",
			MessageBoxButtons::OK,
			MessageBoxIcon::Information);

	}
	private: System::Void quitButton_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void importButton_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void MainForm_Layout(System::Object^ sender, System::Windows::Forms::LayoutEventArgs^ e) {
		// If the last height/width are not yet initialized, do nothing
		if (0 > lastHeight || 0 > lastWidth) {
			return;
		}

		// Compute the change in the form's size
		int deltaHeight = this->Height - lastHeight;
		int deltaWidth = this->Width - lastWidth;

		// Move the components according to the size change
		if (0 != deltaHeight || 0 != deltaWidth) {
			// Suspend all layout processing until we change everything
			this->SuspendLayout();
			achlistGroupBox->SuspendLayout();
			fileWatcherGroupBox->SuspendLayout();

			// Move the various buttons to track the change-of-size
			MoveControl(achlistGroupBox, 0, deltaHeight);
			MoveControl(fileWatcherGroupBox, deltaWidth, deltaHeight);
			MoveControl(quitButton, deltaWidth, deltaHeight);
			MoveControl(starfieldFolderButton, deltaWidth, 0);
			MoveControl(xboxWEMButton, deltaWidth, 0);

			// Change the size of the text-based controls to track the change-of-size
			starfieldFolderTextBox->Width += deltaWidth;
			xboxWEMTextBox->Width += deltaWidth;
			pluginComboBox->Width += deltaWidth;
			auditListView->Width += deltaWidth;
			auditListView->Height += deltaHeight;

			// Resume all the normal layout processing now that we've made all out changes
			achlistGroupBox->ResumeLayout(false);
			achlistGroupBox->PerformLayout();
			fileWatcherGroupBox->ResumeLayout(false);
			fileWatcherGroupBox->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();
		}

		// Remember that last-seen frame dimensions
		lastHeight = this->Height;
		lastWidth = this->Width;
	}
	private: System::Void starfieldFolderTextBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		WriteSetting(registryNameStarfieldFolder, starfieldFolderTextBox->Text);
		starfieldDataFolder = starfieldFolderTextBox->Text + L"\\DATA\\";
		fileSystemWatcher->Path = starfieldFolderTextBox->Text;
		fileSystemWatcher->IncludeSubdirectories = true;
		xboxWEMButton->Enabled = true;
		if (0 != String::Compare(starfieldFolderTextBox->Text, 0, xboxWEMTextBox->Text, 0, Text->Length, true)) {
			xboxWEMTextBox->Text = L"";
		}
		else if (0 != pluginComboBox->Text->Length) {
			startButton->Enabled = true;
			importButton->Enabled = true;
			generateButton->Enabled = true;
		}
	}
	private: System::Void exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void aboutToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show(
			L"Monitors file activity within the Starfield Installation Tree to automated the generation of ACHLIST packing files.\n\n" +
			L"Generated ACHLIST files are stored in one's >Documents\\My Games\\Starfield\\CreationKitAuditTool< folder.\n\n" +
			L"GitHub: https://github.com/ebkarlson404/CreationKitAuditTool\n\n" +
			L"Version 0.9.0\n\n" +
			L"Copyright 2025",
			L"Creation Kit Audit Log Help",
			MessageBoxButtons::OK,
			MessageBoxIcon::Question);
	}
	private: System::Void xboxWEMTextBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		WriteSetting(registryNameXBoxWEMFolder, xboxWEMTextBox->Text);
		if (0 == xboxWEMTextBox->Text->Length) {
			pluginComboBox->Enabled = false;
			startButton->Enabled = false;
			importButton->Enabled = false;
			generateButton->Enabled = false;
		}
		else {
			starfieldXBoxDataFolder = xboxWEMTextBox->Text + L"\\DATA\\";
			pluginComboBox->Enabled = true;
			if (0 != pluginComboBox->Text->Length) {
				startButton->Enabled = true;
				importButton->Enabled = true;
				generateButton->Enabled = true;
			}
		}
	}
	private: System::Void pluginComboBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		auditListView->Items->Clear();
		if (0 == pluginComboBox->Text->Length) {
			startButton->Enabled = false;
			importButton->Enabled = false;
			generateButton->Enabled = false;
		}
		else if (0 != starfieldFolderTextBox->Text->Length &&
			0 != xboxWEMTextBox->Text->Length) {
			startButton->Enabled = true;
			importButton->Enabled = true;
			generateButton->Enabled = true;
			LoadManifest(pluginComboBox->Text);
		}
	}
	//
    // File activity reported by the FileSystemWatcher
	//
	private: System::Void fileSystemWatcher_Changed(System::Object^ sender, System::IO::FileSystemEventArgs^ e) {
		if (running) {
			if (shouldLog(e->FullPath, false)) {
				String^ rpath = relativePath(e->FullPath);
				if (nullptr == auditListView->FindItemWithText(rpath)) {
					auditListView->Items->Add(gcnew ListViewItem(rpath));
					WriteManifest(pluginComboBox->Text);
				}
			}
		}
	}
	private: System::Void fileSystemWatcher_Deleted(System::Object^ sender, System::IO::FileSystemEventArgs^ e) {
		if (running) {
			if (shouldLog(e->FullPath, true)) {
				auditListView->Items->Remove(auditListView->FindItemWithText(relativePath(e->FullPath)));
				WriteManifest(pluginComboBox->Text);
			}
		}
	}
	private: System::Void fileSystemWatcher_Created(System::Object^ sender, System::IO::FileSystemEventArgs^ e) {
		if (running) {
			if (shouldLog(e->FullPath, false)) {
				String^ rpath = relativePath(e->FullPath);
				if (nullptr == auditListView->FindItemWithText(rpath)) {
					auditListView->Items->Add(gcnew ListViewItem(rpath));
					WriteManifest(pluginComboBox->Text);
				}
			}
		}
	}
	private: System::Void fileSystemWatcher_Renamed(System::Object^ sender, System::IO::RenamedEventArgs^ e) {
		if (running) {
			if (shouldLog(e->OldFullPath, true)) {
				auditListView->Items->Remove(auditListView->FindItemWithText(relativePath(e->OldFullPath)));
				WriteManifest(pluginComboBox->Text);
			}
			if (shouldLog(e->FullPath, false)) {
				String^ rpath = relativePath(e->FullPath);
				if (nullptr == auditListView->FindItemWithText(rpath)) {
					auditListView->Items->Add(gcnew ListViewItem(rpath));
					WriteManifest(pluginComboBox->Text);
				}
			}
		}
	}
	//
	// Utility functions
	//
	private: bool shouldLog(String^ fullName, bool isDelete) {
		if (!isDelete) {
			try {
				FileAttributes attr = File::GetAttributes(fullName);
				if (attr.HasFlag(FileAttributes::Directory) || attr.HasFlag(FileAttributes::Hidden)) {
					return false;
				}
			}
			catch (System::Exception^) {
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

		// Ignore the ESP, ESM & TMP files.  Also the TEMP.WEM files that are generated by WWise.
		if (fullName->EndsWith(L".esm", StringComparison::InvariantCultureIgnoreCase) ||
			fullName->EndsWith(L".esp", StringComparison::InvariantCultureIgnoreCase) ||
			fullName->EndsWith(L".tmp", StringComparison::InvariantCultureIgnoreCase) ||
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

		// The WWise tool will process *all* WAV files anywhere in one's installation tree
		// irrespective of whether they are part of the current plugin or not.  Filter out
		// any files that appear to reside in a plugin-specific directory other than the
		// one currently selected.
		String^ upperName = fullName->ToUpper();
		String^ pluginDirName = L"\\" + pluginComboBox->Text->ToUpper() + L".ESP\\";
		if (upperName->Contains(L".ESP\\")) {
			return upperName->Contains(pluginDirName);
		}

		// If we see a directory name that ends in '.ESM' then WWise has found a WAV
		// file left in a Plugin.ESM directory, which cannot be part of the plugin
		// currently being operated upon by Creation Kit.
		if (upperName->Contains(L".ESM\\")) {
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
	private: System::Void MoveControl(Control^ control, int deltaX, int deltaY) {
		control->Left += deltaX;
		control->Top += deltaY;
	}
	private: System::Void WriteSetting(String^ name, String^ value) {

		try {
			RegistryKey^ key = Registry::CurrentUser->CreateSubKey(registryKey);
			key->SetValue(name, value);
			key->Close();
		}
		catch (Exception^) {
			// Ignore
		}
	}
    private: Object^ ReadSetting(String^ name) {
	   Object^ value = nullptr;
	   try {
		   RegistryKey^ key = Registry::CurrentUser->OpenSubKey(registryKey);
		   if (nullptr != key) {
			   value = key->GetValue(name);
		   }
	   }
	   catch (Exception^) {
		   // Ignore
	   }
	   return value;
    }
    private: System::Void LoadManifest(String^ plugin) {
		String^ manifestFile = userGameFolder + L"\\" + plugin + manifestFileExt;
		try {
			array<String^>^ lines = File::ReadAllLines(manifestFile);
			for (int i = 0; i < lines->Length; i++) {
				auditListView->Items->Add(gcnew ListViewItem(lines[i]));
			}
		} catch (Exception^ e) {
			MessageBox::Show(this,
				L"Error while reading " + manifestFile + L": " + e->Message,
				L"Manifest Read Error",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
		}
    }
	private: System::Void WriteManifest(String^ plugin) {
		String^ manifestFile = userGameFolder + L"\\" + plugin + manifestFileExt;
		IEnumerator^ iter = auditListView->Items->GetEnumerator();
		try {
			StreamWriter^ fh = nullptr;
			try {
				fh = File::CreateText(manifestFile);
				while (iter->MoveNext()) {
					ListViewItem^ item = (ListViewItem^)iter->Current;
					fh->WriteLine(item->Text);
				}
			}
			finally {
				if (nullptr != fh) {
					fh->Close();
				}
			}
		}
		catch (Exception^ e) {
			MessageBox::Show(this,
				L"Error while writing " + manifestFile + L": " + e->Message,
				L"Manifest Write Error",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
		}
	}
	private: String^ espToEsmReplication(String^ relFilename, String^ espDirName, String^ esmDirName) {
		String^ rootDir = starfieldFolderTextBox->Text + L"\\";
		int pos = relFilename->IndexOf(espDirName, StringComparison::InvariantCultureIgnoreCase);
		if (pos < 0) {
			return relFilename;
		}
		String^ newRelFilename = relFilename->Substring(0, pos) + esmDirName + relFilename->Substring(pos + espDirName->Length);
		String^ newDirName = rootDir + newRelFilename->Substring(0, newRelFilename->LastIndexOf(L"\\"));
		try {
			Directory::CreateDirectory(newDirName);
			File::Copy(rootDir + relFilename, rootDir + newRelFilename, true);
		}
		catch (Exception^ e) {
			MessageBox::Show(this,
				L"Error while replicating " +
				relFilename +
				L" to " +
				newRelFilename +
				L": " +
				e->Message,
				L"ESP to ESM Replication Failure",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
		}
		return newRelFilename;
	}
	};
}
