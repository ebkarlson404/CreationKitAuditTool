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

			// Populate the PlugIn Control with all known plugins
			PopluatePlugInChoices();
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
	protected: String^ starfieldBackupFolder;
	protected: String^ starfieldXBoxDataFolder;
	protected: int lastHeight = -1;
	protected: int lastWidth = -1;
	protected: static Color startButtonColor = Color::Lime;
	protected: static Color stopButtonColor = Color::Red;
	protected: static String^ registryKey = L"SOFTWARE\\GrizBane\\CreationKitAuditTool";
	protected: static String^ registryNameStarfieldFolder = L"StarfieldFolder";
	protected: static String^ registryNameXBoxWEMFolder = L"XBoxWEMFolder";
	protected: static String^ unboundPlugInName = L"<none>";
	protected: String^ previousPlugInName = L"<none>";
	protected: String^ userGameFolder;
	protected: static String^ manifestFileExt = L".manifest";
	protected: static String^ githubUrl = L"https://github.com/ebkarlson404/CreationKitAuditTool";
	protected: ListViewItem^ selectedAuditItem;

	protected:
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowser;
	private: System::Windows::Forms::TextBox^ starfieldFolderTextBox;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ starfieldFolderButton;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ xboxWEMTextBox;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ComboBox^ pluginComboBox;
	private: System::Windows::Forms::GroupBox^ auditGroupBox;
	private: System::Windows::Forms::ListView^ auditListView;
	private: System::Windows::Forms::CheckBox^ wavCheckBox;
	private: System::Windows::Forms::CheckBox^ pscCheckBox;
	private: System::Windows::Forms::Button^ stopButton;
	private: System::Windows::Forms::Button^ quitButton;
	private: System::Windows::Forms::Button^ xboxWEMButton;
	private: System::Windows::Forms::Button^ importButton;
	private: System::Windows::Forms::ColumnHeader^ columnHeader1;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ exitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ aboutToolStripMenuItem;
	private: System::Windows::Forms::BindingSource^ pluginEnumerator;
	private: System::Windows::Forms::ContextMenuStrip^ auditContextMenuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^ contextToolRemove;
	private: System::Windows::Forms::ToolTip^ toolTip;
	private: System::Windows::Forms::Button^ newPluginButton;
	private: System::Windows::Forms::OpenFileDialog^ findPluginDialog;
	private: System::Windows::Forms::Button^ addAuditFileButton;
	private: System::Windows::Forms::OpenFileDialog^ importAchlistDialog;
	private: System::Windows::Forms::OpenFileDialog^ addFileToAuditDialog;
	private: System::Windows::Forms::Button^ generateButton;
	private: System::Windows::Forms::Button^ startButton;
	private: System::Windows::Forms::ToolStripMenuItem^ gitHubToolStripMenuItem;
	private: System::Windows::Forms::Button^ clearButton;
	private: System::Windows::Forms::Button^ statusButton;


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
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
			this->auditListView = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->auditGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->statusButton = (gcnew System::Windows::Forms::Button());
			this->clearButton = (gcnew System::Windows::Forms::Button());
			this->startButton = (gcnew System::Windows::Forms::Button());
			this->importButton = (gcnew System::Windows::Forms::Button());
			this->stopButton = (gcnew System::Windows::Forms::Button());
			this->wavCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->pscCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->quitButton = (gcnew System::Windows::Forms::Button());
			this->xboxWEMButton = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gitHubToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->auditContextMenuStrip = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->contextToolRemove = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->newPluginButton = (gcnew System::Windows::Forms::Button());
			this->addAuditFileButton = (gcnew System::Windows::Forms::Button());
			this->generateButton = (gcnew System::Windows::Forms::Button());
			this->findPluginDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->importAchlistDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->addFileToAuditDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fileSystemWatcher))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pluginEnumerator))->BeginInit();
			this->auditGroupBox->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->auditContextMenuStrip->SuspendLayout();
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
			this->starfieldFolderTextBox->TabStop = false;
			this->starfieldFolderTextBox->TextChanged += gcnew System::EventHandler(this, &MainForm::starfieldFolderTextBox_TextChanged);
			// 
			// starfieldFolderButton
			// 
			this->starfieldFolderButton->Location = System::Drawing::Point(963, 63);
			this->starfieldFolderButton->Name = L"starfieldFolderButton";
			this->starfieldFolderButton->Size = System::Drawing::Size(47, 39);
			this->starfieldFolderButton->TabIndex = 2;
			this->starfieldFolderButton->Text = L"...";
			this->toolTip->SetToolTip(this->starfieldFolderButton, L"Select the installation folder for the Starfield executable");
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
			this->xboxWEMTextBox->TabStop = false;
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
			this->pluginComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->pluginComboBox->Enabled = false;
			this->pluginComboBox->FormattingEnabled = true;
			this->pluginComboBox->Location = System::Drawing::Point(286, 141);
			this->pluginComboBox->MaxDropDownItems = 16;
			this->pluginComboBox->Name = L"pluginComboBox";
			this->pluginComboBox->Size = System::Drawing::Size(646, 32);
			this->pluginComboBox->TabIndex = 7;
			this->toolTip->SetToolTip(this->pluginComboBox, L"Select which PlugIn to audit");
			this->pluginComboBox->TextChanged += gcnew System::EventHandler(this, &MainForm::pluginComboBox_TextChanged);
			// 
			// auditListView
			// 
			this->auditListView->BackColor = System::Drawing::SystemColors::Window;
			this->auditListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) { this->columnHeader1 });
			this->auditListView->HideSelection = false;
			this->auditListView->Location = System::Drawing::Point(45, 179);
			this->auditListView->MultiSelect = false;
			this->auditListView->Name = L"auditListView";
			this->auditListView->Size = System::Drawing::Size(887, 422);
			this->auditListView->Sorting = System::Windows::Forms::SortOrder::Ascending;
			this->auditListView->TabIndex = 9;
			this->auditListView->TabStop = false;
			this->toolTip->SetToolTip(this->auditListView, L"RIght click on a file to remove it from the audit log");
			this->auditListView->UseCompatibleStateImageBehavior = false;
			this->auditListView->View = System::Windows::Forms::View::Details;
			this->auditListView->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::auditListView_MouseClick);
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"Relative Filename";
			this->columnHeader1->Width = 800;
			// 
			// auditGroupBox
			// 
			this->auditGroupBox->BackColor = System::Drawing::SystemColors::Control;
			this->auditGroupBox->Controls->Add(this->statusButton);
			this->auditGroupBox->Controls->Add(this->clearButton);
			this->auditGroupBox->Controls->Add(this->startButton);
			this->auditGroupBox->Controls->Add(this->importButton);
			this->auditGroupBox->Controls->Add(this->stopButton);
			this->auditGroupBox->Controls->Add(this->wavCheckBox);
			this->auditGroupBox->Controls->Add(this->pscCheckBox);
			this->auditGroupBox->ForeColor = System::Drawing::SystemColors::ControlText;
			this->auditGroupBox->Location = System::Drawing::Point(45, 629);
			this->auditGroupBox->Name = L"auditGroupBox";
			this->auditGroupBox->Size = System::Drawing::Size(658, 168);
			this->auditGroupBox->TabIndex = 11;
			this->auditGroupBox->TabStop = false;
			this->auditGroupBox->Text = L"Audit Control";
			// 
			// statusButton
			// 
			this->statusButton->BackColor = System::Drawing::Color::Red;
			this->statusButton->Enabled = false;
			this->statusButton->Location = System::Drawing::Point(10, 98);
			this->statusButton->Name = L"statusButton";
			this->statusButton->Size = System::Drawing::Size(157, 48);
			this->statusButton->TabIndex = 6;
			this->statusButton->TabStop = false;
			this->statusButton->Text = L"Paused";
			this->toolTip->SetToolTip(this->statusButton, L"Start/Resume the audit behavior for this PlugIn");
			this->statusButton->UseVisualStyleBackColor = false;
			// 
			// clearButton
			// 
			this->clearButton->Location = System::Drawing::Point(299, 104);
			this->clearButton->Name = L"clearButton";
			this->clearButton->Size = System::Drawing::Size(157, 48);
			this->clearButton->TabIndex = 3;
			this->clearButton->Text = L"Clear";
			this->toolTip->SetToolTip(this->clearButton, L"Merge the contents of an existing ACHLIST file into this PlugIn\'s audit log");
			this->clearButton->UseVisualStyleBackColor = true;
			this->clearButton->Click += gcnew System::EventHandler(this, &MainForm::clearButton_Click);
			// 
			// startButton
			// 
			this->startButton->Enabled = false;
			this->startButton->Location = System::Drawing::Point(480, 28);
			this->startButton->Name = L"startButton";
			this->startButton->Size = System::Drawing::Size(157, 48);
			this->startButton->TabIndex = 4;
			this->startButton->Text = L"Start";
			this->toolTip->SetToolTip(this->startButton, L"Start/Resume the audit behavior for this PlugIn");
			this->startButton->UseVisualStyleBackColor = true;
			this->startButton->Click += gcnew System::EventHandler(this, &MainForm::startButton_Click);
			// 
			// importButton
			// 
			this->importButton->Enabled = false;
			this->importButton->Location = System::Drawing::Point(299, 28);
			this->importButton->Name = L"importButton";
			this->importButton->Size = System::Drawing::Size(157, 48);
			this->importButton->TabIndex = 2;
			this->importButton->Text = L"Import";
			this->toolTip->SetToolTip(this->importButton, L"Merge the contents of an existing ACHLIST file into this PlugIn\'s audit log");
			this->importButton->UseVisualStyleBackColor = true;
			this->importButton->Click += gcnew System::EventHandler(this, &MainForm::importButton_Click);
			// 
			// stopButton
			// 
			this->stopButton->Enabled = false;
			this->stopButton->Location = System::Drawing::Point(480, 104);
			this->stopButton->Name = L"stopButton";
			this->stopButton->Size = System::Drawing::Size(157, 48);
			this->stopButton->TabIndex = 5;
			this->stopButton->Text = L"Stop";
			this->toolTip->SetToolTip(this->stopButton, L"Stop/Pause the audit behavior for this PlugIn");
			this->stopButton->UseVisualStyleBackColor = true;
			this->stopButton->Click += gcnew System::EventHandler(this, &MainForm::stopButton_Click);
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
			this->toolTip->SetToolTip(this->wavCheckBox, L"Ignore any WAV files detected during an audit");
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
			this->toolTip->SetToolTip(this->pscCheckBox, L"Ignore an Papyrus Source Files detected during an audit");
			this->pscCheckBox->UseVisualStyleBackColor = true;
			// 
			// quitButton
			// 
			this->quitButton->Location = System::Drawing::Point(775, 733);
			this->quitButton->Name = L"quitButton";
			this->quitButton->Size = System::Drawing::Size(157, 48);
			this->quitButton->TabIndex = 13;
			this->quitButton->Text = L"Quit";
			this->toolTip->SetToolTip(this->quitButton, L"Exit the Audit Tool");
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
			this->toolTip->SetToolTip(this->xboxWEMButton, L"Select the root of the XBox WEM Folder");
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
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->gitHubToolStripMenuItem,
					this->aboutToolStripMenuItem
			});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(74, 34);
			this->helpToolStripMenuItem->Text = L"Help";
			// 
			// gitHubToolStripMenuItem
			// 
			this->gitHubToolStripMenuItem->Name = L"gitHubToolStripMenuItem";
			this->gitHubToolStripMenuItem->Size = System::Drawing::Size(268, 40);
			this->gitHubToolStripMenuItem->Text = L"GitHub";
			this->gitHubToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::gitHubToolStripMenuItem_Click);
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::F1));
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(268, 40);
			this->aboutToolStripMenuItem->Text = L"About";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::aboutToolStripMenuItem_Click);
			// 
			// auditContextMenuStrip
			// 
			this->auditContextMenuStrip->ImageScalingSize = System::Drawing::Size(28, 28);
			this->auditContextMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->contextToolRemove });
			this->auditContextMenuStrip->Name = L"auditContextMenuStrip";
			this->auditContextMenuStrip->Size = System::Drawing::Size(270, 40);
			// 
			// contextToolRemove
			// 
			this->contextToolRemove->Name = L"contextToolRemove";
			this->contextToolRemove->Size = System::Drawing::Size(269, 36);
			this->contextToolRemove->Text = L"Remove From Audit";
			this->contextToolRemove->Click += gcnew System::EventHandler(this, &MainForm::contextToolRemove_Click);
			// 
			// newPluginButton
			// 
			this->newPluginButton->Enabled = false;
			this->newPluginButton->Location = System::Drawing::Point(963, 141);
			this->newPluginButton->Name = L"newPluginButton";
			this->newPluginButton->Size = System::Drawing::Size(47, 39);
			this->newPluginButton->TabIndex = 8;
			this->newPluginButton->Text = L"+";
			this->toolTip->SetToolTip(this->newPluginButton, L"Add a new PlugIn to the repository of known PlugIns");
			this->newPluginButton->UseVisualStyleBackColor = true;
			this->newPluginButton->Click += gcnew System::EventHandler(this, &MainForm::newPluginButton_Click);
			// 
			// addAuditFileButton
			// 
			this->addAuditFileButton->Enabled = false;
			this->addAuditFileButton->Location = System::Drawing::Point(963, 370);
			this->addAuditFileButton->Name = L"addAuditFileButton";
			this->addAuditFileButton->Size = System::Drawing::Size(47, 39);
			this->addAuditFileButton->TabIndex = 10;
			this->addAuditFileButton->Text = L"+";
			this->toolTip->SetToolTip(this->addAuditFileButton, L"Manually add a file to the Audit Log");
			this->addAuditFileButton->UseVisualStyleBackColor = true;
			this->addAuditFileButton->Click += gcnew System::EventHandler(this, &MainForm::addAuditFileButton_Click);
			// 
			// generateButton
			// 
			this->generateButton->Enabled = false;
			this->generateButton->Location = System::Drawing::Point(775, 657);
			this->generateButton->Name = L"generateButton";
			this->generateButton->Size = System::Drawing::Size(157, 48);
			this->generateButton->TabIndex = 12;
			this->generateButton->Text = L"Generate";
			this->toolTip->SetToolTip(this->generateButton, L"Replicates files from *.ESP folders to *.ESM folders and then generate the PC and"
				L" XBox ACHLIST files from the current audit log");
			this->generateButton->UseVisualStyleBackColor = true;
			this->generateButton->Click += gcnew System::EventHandler(this, &MainForm::generateButton_Click);
			// 
			// findPluginDialog
			// 
			this->findPluginDialog->DefaultExt = L"esp";
			this->findPluginDialog->Filter = L"PlugIn files|*.esp";
			this->findPluginDialog->ReadOnlyChecked = true;
			this->findPluginDialog->Title = L"Select PlugIn to add to the Audit Tool";
			// 
			// importAchlistDialog
			// 
			this->importAchlistDialog->DefaultExt = L"achlist";
			this->importAchlistDialog->Filter = L"ACHLIST Files|*.achlist";
			this->importAchlistDialog->ReadOnlyChecked = true;
			this->importAchlistDialog->Title = L"Select ACHLIST File for Import";
			// 
			// addFileToAuditDialog
			// 
			this->addFileToAuditDialog->Filter = resources->GetString(L"addFileToAuditDialog.Filter");
			this->addFileToAuditDialog->Multiselect = true;
			this->addFileToAuditDialog->ReadOnlyChecked = true;
			this->addFileToAuditDialog->Title = L"Select a File to add to the Audit Log";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1026, 816);
			this->Controls->Add(this->generateButton);
			this->Controls->Add(this->addAuditFileButton);
			this->Controls->Add(this->newPluginButton);
			this->Controls->Add(this->xboxWEMButton);
			this->Controls->Add(this->quitButton);
			this->Controls->Add(this->auditGroupBox);
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
			this->MinimumSize = System::Drawing::Size(1050, 880);
			this->Name = L"MainForm";
			this->Text = L"Starfield Creation Kit Audit Tool";
			this->Layout += gcnew System::Windows::Forms::LayoutEventHandler(this, &MainForm::MainForm_Layout);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fileSystemWatcher))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pluginEnumerator))->EndInit();
			this->auditGroupBox->ResumeLayout(false);
			this->auditGroupBox->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->auditContextMenuStrip->ResumeLayout(false);
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
			String^ path = folderBrowser->SelectedPath;
			if (!FileResidesWithinStarfieldFolder(path)) {
				MessageBox::Show(
					L"XBox WEM Folder must reside within the Starfield Folder.",
					L"Invalid XBox WEM Folder",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
			}
			else {
				xboxWEMTextBox->Text = path;
			}
		}
	}
	private: System::Void startButton_Click(System::Object^ sender, System::EventArgs^ e) {
		statusButton->BackColor = startButtonColor;
		statusButton->Text = L"Running";
		startButton->Enabled = false;
		stopButton->Enabled = true;
		starfieldFolderButton->Enabled = false;
		xboxWEMButton->Enabled = false;
		pluginComboBox->Enabled = false;
		newPluginButton->Enabled = false;
		running = true;
	}
	private: System::Void stopButton_Click(System::Object^ sender, System::EventArgs^ e) {
		statusButton->BackColor = stopButtonColor;
		statusButton->Text = L"Paused";
		stopButton->Enabled = false;
		startButton->Enabled = true;
		starfieldFolderButton->Enabled = true;
		xboxWEMButton->Enabled = true;
		pluginComboBox->Enabled = true;
		newPluginButton->Enabled = true;
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
				xbList->Add(EspToEsmReplication(filename, espDirName, esmDirName));
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
				filename = EspToEsmReplication(filename, espDirName, esmDirName);

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

		// Write the arrays out to the ACHLIST files
		WriteArrayToJsonFile(pcFiles, userGameFolder + L"\\" + pluginComboBox->Text + L"-PC.achlist");
		WriteArrayToJsonFile(xbFiles, userGameFolder + L"\\" + pluginComboBox->Text + L"-XB.achlist");

		// Tell the user what was done
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
	private: System::Void clearButton_Click(System::Object^ sender, System::EventArgs^ e) {
		// Clear the audit log and update the plugin's manifest
		auditListView->Items->Clear();
		WriteManifest(pluginComboBox->Text);
	}
	private: System::Void importButton_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ esmDirName = L"\\" + pluginComboBox->Text + L".esm\\";
		String^ espDirName = L"\\" + pluginComboBox->Text + L".esp\\";
		if (importAchlistDialog->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
			// Set the folder for the import file as the initial folder for the next time
			String^ importFile = importAchlistDialog->FileName;
			importAchlistDialog->InitialDirectory = Directory::GetParent(importFile)->FullName;

			// Read the ACHLIST file and add all files to the audit log
			System::Array^ files = ReadArrayFromJsonFile(importFile);
			for (int i = 0; i < files->Length; i++) {
				String^ filename = (String^)files->GetValue(i);
				
				// Since the foreign ACHLIST file may have been created for ESM
				// distribution, ensure that we transform any references to
				// directories name MyMod.ESM to MyMod.ESP.
				int pos = filename->IndexOf(esmDirName, StringComparison::InvariantCultureIgnoreCase);
				if (pos >= 0) {
					filename = filename->Substring(0, pos) + espDirName + filename->Substring(pos + esmDirName->Length);
				}

				// Add the file to the audit log if it is not already present
				if (!AuditFileAlreadyPresent(filename)) {
					auditListView->Items->Add(gcnew ListViewItem(filename));
				}
			}
			WriteManifest(pluginComboBox->Text);
		}
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
			auditGroupBox->SuspendLayout();

			// Move the various buttons to track the change-of-size
			MoveControl(auditGroupBox, 0, deltaHeight);
			MoveControl(newPluginButton, deltaWidth, 0);
			MoveControl(generateButton, deltaWidth, deltaHeight);
			MoveControl(quitButton, deltaWidth, deltaHeight);
			MoveControl(starfieldFolderButton, deltaWidth, 0);
			MoveControl(xboxWEMButton, deltaWidth, 0);
			addAuditFileButton->Left += deltaWidth;
			addAuditFileButton->Top = auditListView->Top + ((auditListView->Height - addAuditFileButton->Height) / 2);

			// Change the size of the text-based controls to track the change-of-size
			starfieldFolderTextBox->Width += deltaWidth;
			xboxWEMTextBox->Width += deltaWidth;
			pluginComboBox->Width += deltaWidth;
			auditListView->Width += deltaWidth;
			auditListView->Height += deltaHeight;

			// Resume all the normal layout processing now that we've made all out changes
			auditGroupBox->ResumeLayout(false);
			auditGroupBox->PerformLayout();
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
		starfieldBackupFolder = starfieldDataFolder + L"\\BACKUP\\";
		fileSystemWatcher->Path = starfieldFolderTextBox->Text;
		fileSystemWatcher->IncludeSubdirectories = true;
		findPluginDialog->InitialDirectory = starfieldDataFolder;
		importAchlistDialog->InitialDirectory = starfieldFolderTextBox->Text;
		addFileToAuditDialog->InitialDirectory = starfieldDataFolder;
		xboxWEMButton->Enabled = true;
		if (!FileResidesWithinStarfieldFolder(xboxWEMTextBox->Text)) {
			xboxWEMTextBox->Text = L"";
		}
		else {
			startButton->Enabled = true;
			if (!pluginComboBox->Text->Equals(unboundPlugInName)) {
				importButton->Enabled = true;
				addAuditFileButton->Enabled = true;
				generateButton->Enabled = true;
			}
		}
	}
	private: System::Void exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void gitHubToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Diagnostics::Process^ proc = gcnew System::Diagnostics::Process();
		proc->Start(githubUrl);
	}
	private: System::Void aboutToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show(
			L"Monitors file activity within the Starfield Installation Tree to automated the generation of ACHLIST packing files.\n\n" +
			L"Provides automatic replication of files from *.ESP folders to *.ESM folders during ACHLIST generation.\n\n" +
			L"Generates platform-specific ACHLIST files for packaging PC and XBox WEM files.\n\n" +
			L"Generated ACHLIST files are stored in one's >Documents\\My Games\\Starfield\\CreationKitAuditTool< folder.\n\n" +
			L"GitHub: " + githubUrl + L"\n\n" +
			L"Version 0.9.2\n\n" +
			L"Copyright 2025, Eric Karlson\n\n" +
			L"Distrbuted under the terms of the Apache License version 2.0, January 2004",
			L"Creation Kit Audit Log Help",
			MessageBoxButtons::OK,
			MessageBoxIcon::Question);
	}
	private: System::Void xboxWEMTextBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		WriteSetting(registryNameXBoxWEMFolder, xboxWEMTextBox->Text);
		if (0 == xboxWEMTextBox->Text->Length) {
			pluginComboBox->Enabled = false;
			newPluginButton->Enabled = false;
			startButton->Enabled = false;
			importButton->Enabled = false;
			addAuditFileButton->Enabled = false;
			generateButton->Enabled = false;
		}
		else {
			starfieldXBoxDataFolder = xboxWEMTextBox->Text + L"\\DATA\\";
			pluginComboBox->Enabled = true;
			newPluginButton->Enabled = true;
			startButton->Enabled = true;
			if (!pluginComboBox->Text->Equals(unboundPlugInName)) {
				importButton->Enabled = true;
				addAuditFileButton->Enabled = true;
				generateButton->Enabled = true;
			}
		}
	}
	private: System::Void pluginComboBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		// If the current value in the control is an empty string, this is
		// an interim condition caused by reloading the choice list - ignore
		String^ currentPlugin = pluginComboBox->Text;
		if (currentPlugin->Length == 0) {
			return;
		}

		// Clear the audit log unless we were not bound to a specific plugin before
		bool preserveAudit = previousPlugInName->Equals(unboundPlugInName);
		if (!preserveAudit) {
			auditListView->Items->Clear();
		}

		// Toggle the state on the various buttons depending on whether we are
		// now bound to a specific plugin
		if (currentPlugin->Equals(unboundPlugInName)) {
			importButton->Enabled = false;
			generateButton->Enabled = false;
			addAuditFileButton->Enabled = false;
			generateButton->Enabled = false;
		}
		else if (0 != starfieldFolderTextBox->Text->Length &&
			0 != xboxWEMTextBox->Text->Length) {
			startButton->Enabled = true;
			importButton->Enabled = true;
			addAuditFileButton->Enabled = true;
			generateButton->Enabled = true;
			LoadManifest(currentPlugin);
			if (preserveAudit) {
				WriteManifest(currentPlugin);
			}
		}

		// Record the new plugin binding
		previousPlugInName = currentPlugin;
	}
	private: System::Void auditListView_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Right)
		{
			selectedAuditItem = auditListView->GetItemAt(e->X, e->Y);
			if (nullptr != selectedAuditItem) {
				auditContextMenuStrip->Show(Cursor->Position);
			}
		}
	}
	private: System::Void contextToolRemove_Click(System::Object^ sender, System::EventArgs^ e) {
		if (nullptr != selectedAuditItem) {
			auditListView->Items->Remove(selectedAuditItem);
			selectedAuditItem = nullptr;
			WriteManifest(pluginComboBox->Text);
		}
	}
	private: System::Void newPluginButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (Windows::Forms::DialogResult::OK == findPluginDialog->ShowDialog(this)) {
			// Get the name of the plugin, create its manifest file if needed,
			// re-popluate the choices in the pluginComboBox control and then
			// set this plugin as the active project.
			String^ pluginName = findPluginDialog->SafeFileName->Substring(0, findPluginDialog->SafeFileName->Length - 4);
			if (RegisterPlugInIfNeeded(pluginName)) {
				PopluatePlugInChoices();
				pluginComboBox->Text = pluginName;
			}
		}
	}
	private: System::Void addAuditFileButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (addFileToAuditDialog->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
			String^ lastFilename;
			String^ skippedFiles = L"";
			String^ separator = L"";
			array<String^>^ filenames = addFileToAuditDialog->FileNames;
			for (int i = 0; i < filenames->Length; i++) {
				String^ filename = filenames[i];

				// Silently skip any folders or hidden files.
				// Skip and report any files not within the Starfield or XBox Data folders.
				if (IsDirectoryOrHiddenOrDeleted(filename)) {
					// Silent ignore
				}
				else if (!FileResidesWithinEitherDataFolder(filename)) {
					skippedFiles = skippedFiles + separator + filename;
					separator = L"\n";
				}
				else if (!FileRelatedToPlugIn(filename, pluginComboBox->Text)) {
					skippedFiles = skippedFiles + separator + filename;
					separator = L"\n";
				}
				else {
					// Add the new file to the audit log if it is not already present.
					String^ rname = RelativePath(filename);
					if (!AuditFileAlreadyPresent(rname)) {
						auditListView->Items->Add(gcnew ListViewItem(rname));
						lastFilename = filename;
					}
				}

				// If we selected at least one file, remember that file's folder
				// as the initial directory for the next 'add' operation.
				// Note that when multiple files are selected, they must all
				// be from the same directory.
				if (nullptr != lastFilename) {
					addFileToAuditDialog->InitialDirectory = Directory::GetParent(lastFilename)->FullName;
				}
			}

			// Report any skipped files
			if (skippedFiles->Length > 0) {
				MessageBox::Show(
					L"The following files were not added to the audit log because they do not reside within either the Starfield Data or Starfield XBox Data folders or they are not related to the current plugin:\n" +
					skippedFiles,
					L"Invalid File Selections",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);

			}
		}
	}
	//
    // File activity reported by the FileSystemWatcher
	//
	private: System::Void fileSystemWatcher_Changed(System::Object^ sender, System::IO::FileSystemEventArgs^ e) {
		if (running) {
			if (ShouldLog(e->FullPath, false)) {
				String^ rpath = RelativePath(e->FullPath);
				if (nullptr == auditListView->FindItemWithText(rpath)) {
					auditListView->Items->Add(gcnew ListViewItem(rpath));
					WriteManifest(pluginComboBox->Text);
				}
			}
		}
	}
	private: System::Void fileSystemWatcher_Deleted(System::Object^ sender, System::IO::FileSystemEventArgs^ e) {
		if (running) {
			if (ShouldLog(e->FullPath, true)) {
				auditListView->Items->Remove(auditListView->FindItemWithText(RelativePath(e->FullPath)));
				WriteManifest(pluginComboBox->Text);
			}
		}
	}
	private: System::Void fileSystemWatcher_Created(System::Object^ sender, System::IO::FileSystemEventArgs^ e) {
		if (running) {
			if (ShouldLog(e->FullPath, false)) {
				String^ rpath = RelativePath(e->FullPath);
				if (nullptr == auditListView->FindItemWithText(rpath)) {
					auditListView->Items->Add(gcnew ListViewItem(rpath));
					WriteManifest(pluginComboBox->Text);
				}
			}
		}
	}
	private: System::Void fileSystemWatcher_Renamed(System::Object^ sender, System::IO::RenamedEventArgs^ e) {
		if (running) {
			if (ShouldLog(e->OldFullPath, true)) {
				auditListView->Items->Remove(auditListView->FindItemWithText(RelativePath(e->OldFullPath)));
				WriteManifest(pluginComboBox->Text);
			}
			if (ShouldLog(e->FullPath, false)) {
				String^ rpath = RelativePath(e->FullPath);
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
	private: System::Void WriteArrayToJsonFile(System::Array^ strings, String^ filename) {
		DataContractJsonSerializer^ deser = gcnew DataContractJsonSerializer(strings->GetType());
		try {
			System::IO::FileStream^ fh = nullptr;
			try {
				fh = File::Create(filename);
				deser->WriteObject(fh, strings);
			}
			finally {
				if (nullptr != fh) {
					fh->Close();
				}
			}
		}
		catch (Exception^ e) {
			MessageBox::Show(L"Error creating " + filename + L": " + e->Message,
				L"File Creation Error",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
		}
	}
	private: System::Array^ ReadArrayFromJsonFile(String^ filename) {
		// Some contortions to force the type data needed for the JSON Serializer
		ArrayList^ typedArray = gcnew ArrayList(0);
		System::Array^ strings = typedArray->ToArray(filename->GetType());

		// Construct the serializer and read the data
		DataContractJsonSerializer^ deser = gcnew DataContractJsonSerializer(strings->GetType());
		try {
			System::IO::FileStream^ fh = nullptr;
			try {
				fh = File::OpenRead(filename);
				strings = cli::safe_cast<System::Array^>(deser->ReadObject(fh));
			}
			finally {
				if (nullptr != fh) {
					fh->Close();
				}
			}
		}
		catch (Exception^ e) {
			MessageBox::Show(L"Error creating " + filename + L": " + e->Message,
				L"File Creation Error",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
		}
		return strings;
	}
	private: bool IsDirectoryOrHiddenOrDeleted(String^ fullname) {
		FileAttributes attr;
		try {
			FileAttributes attr = File::GetAttributes(fullname);
		}
		catch (System::Exception^) {
			// Assume that the file was deleted.
			return true;
		}
		return attr.HasFlag(FileAttributes::Directory) || attr.HasFlag(FileAttributes::Hidden);
	}
	private: bool FileRelatedToPlugIn(String^ fullname, String^ plugin) {
		// Force the filename to upper case as there is no case-insensitive version
		// of String::Contains()
		String^ upperName = fullname->ToUpper();

		// If there is a directory that ends with '.ESM' then the file
		// cannot be related to a plugin ESP file.
		if (upperName->Contains(L".ESM\\")) {
			return false;
		}

		// If there is a directory that ends with '.ESP' that does not
		// correspond to this plugin, then it is related to some other plugin.
		if (upperName->Contains(L".ESP\\") &&
			!upperName->Contains(L"\\" + plugin->ToUpper() + L".ESP\\")) {
			return false;
		}

		// Otherwise this file is related specifically to this plug,
		// or it is not specific to any given plugin
		return true;
	}
	private: bool ShouldLog(String^ fullName, bool isDelete) {
		if (!isDelete) {
			if (IsDirectoryOrHiddenOrDeleted(fullName)) {
				return false;
			}
		}

		// Ignore any file not under the Starfield Data or Starfield XBox folders
		if (!FileResidesWithinEitherDataFolder(fullName)) {
			return false;
		}

		// Ignore the ESP, ESM, ACHLIST & TMP files.
		// Also the TEMP.WEM files that are generated by WWise.
		// And anything inside of Starfield's Data\Backup folder.
		if (fullName->EndsWith(L".esm", StringComparison::InvariantCultureIgnoreCase) ||
			fullName->EndsWith(L".esp", StringComparison::InvariantCultureIgnoreCase) ||
			fullName->EndsWith(L".achlist", StringComparison::InvariantCultureIgnoreCase) ||
			fullName->EndsWith(L".tmp", StringComparison::InvariantCultureIgnoreCase) ||
			fullName->EndsWith(L"\\Temp.wem", StringComparison::InvariantCultureIgnoreCase) ||
			fullName->StartsWith(starfieldBackupFolder, StringComparison::InvariantCultureIgnoreCase)) {
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
		return FileRelatedToPlugIn(fullName, pluginComboBox->Text);
	}
	private: String^ RelativePath(String^ fullname) {
		// If the file resides in the Starfield XBox Alternate Data folder, we have to construct
		// the special relative path that will resolve properly when the Creation Kit processes
		// the ARCHLIST file.
		if (FileResidesWithinXBoxDataFolder(fullname)) {
			return L"Data\\..\\" + fullname->Substring(starfieldFolderTextBox->Text->Length + 1);
		}

		// A normal Starfield Data file, just compute a simple relative path
		return fullname->Substring(starfieldFolderTextBox->Text->Length + 1);
	}
	private: bool FileResidesWithinStarfieldFolder(String^ fullFilename) {
		String^ starfieldFolder = starfieldFolderTextBox->Text + L"\\";
		return starfieldFolder->Length < fullFilename->Length &&
			0 == String::Compare(starfieldFolder, 0, fullFilename, 0, starfieldFolder->Length, true);
	}
	private: bool FileResidesWithinEitherDataFolder(String^ fullFilename) {
		return FileResidesWithinStarfieldDataFolder(fullFilename) ||
			   FileResidesWithinXBoxDataFolder(fullFilename);
	}
	private: bool FileResidesWithinStarfieldDataFolder(String^ fullFilename) {
		return starfieldDataFolder->Length < fullFilename->Length &&
			0 == String::Compare(starfieldDataFolder, 0, fullFilename, 0, starfieldDataFolder->Length, true);
	}
	private: bool FileResidesWithinXBoxDataFolder(String^ fullFilename) {
		return starfieldXBoxDataFolder->Length < fullFilename->Length &&
			0 == String::Compare(starfieldXBoxDataFolder, 0, fullFilename, 0, starfieldXBoxDataFolder->Length, true);
	}
	private: bool AuditFileAlreadyPresent(String^ relativeFilename) {
		IEnumerator^ iter = auditListView->Items->GetEnumerator();
		while (iter->MoveNext()) {
			if (0 == String::Compare(relativeFilename, (cli::safe_cast<ListViewItem^>(iter->Current))->Text, true)) {
				return true;
			}
		}
		return false;
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
	private: bool RegisterPlugInIfNeeded(String^ plugin) {
		String^ manifestFile = userGameFolder + L"\\" + plugin + manifestFileExt;
		try {
			StreamWriter^ fh = nullptr;
			try {
				fh = File::AppendText(manifestFile);
			}
			finally {
				if (nullptr != fh) {
					fh->Close();
				}
			}
		}
		catch (Exception^ e) {
			MessageBox::Show(L"Unable to create manifest file " + manifestFile + ": " + e->Message,
				L"Manifest File Creation Error",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
			return false;
		}
		return true;
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
		// If we are not bound to a specific plugin, do not write a manifest
		if (!plugin->Equals(unboundPlugInName)) {
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
	}
	private: String^ EspToEsmReplication(String^ relFilename, String^ espDirName, String^ esmDirName) {
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
	private: System::Void PopluatePlugInChoices() {
		// Remember the current setting of the PlugIn Control
		String^ currentPlugIn = pluginComboBox->Text;
		bool restoreOriginalChoice = false;

		// Reset the list of choices
		pluginComboBox->Items->Clear();

		// Add the invariant <none> choice
		pluginComboBox->Items->Add(unboundPlugInName);

		IEnumerable^ enumeration = Directory::EnumerateFiles(userGameFolder, L"*" + manifestFileExt);
		IEnumerator^ iter = enumeration->GetEnumerator();
		while (iter->MoveNext()) {
			String^ filename = (cli::safe_cast<String^>(iter->Current))->Substring(userGameFolder->Length + 1);
			filename = filename->Substring(0, filename->Length - manifestFileExt->Length);
			if (currentPlugIn->Equals(filename)) {
				restoreOriginalChoice = true;
			}
			pluginComboBox->Items->Add(filename);
		}

		// Initialize/restore the selected item
		pluginComboBox->Text = restoreOriginalChoice ? currentPlugIn : unboundPlugInName;
	}
};
}
