#pragma once
#include "AchList.h"
#include "AuditFilterDialog.h"
#include "FileType.h"
#include "PackDialog.h"
#include "Replication.h"
#include "ReplicationLogDialog.h"
#include "StarfieldData.h"

namespace CreationKitAuditTool {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Microsoft::Win32;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			Util::Initialize();

			// Record initial window size
			lastHeight = this->Height;
			lastWidth = this->Width;

			// Reload the last parameter values for the Starfield Folder and XBox WEM Folder
			Object^ value = Util::ReadStringSetting(registryKey, registryNameStarfieldFolder);
			if (nullptr != value) {
				starfieldFolderTextBox->Text = cli::safe_cast<String^>(value);
			}
			value = Util::ReadStringSetting(registryKey, registryNameXBoxWEMFolder);
			if (nullptr != value && xboxRootFolderTextBox->Enabled) {
				xboxRootFolderTextBox->Text = cli::safe_cast<String^>(value);
			}
			value = Util::ReadStringSetting(registryKey, registryLocalizationFolder);
			if (nullptr != value && localizationFolderTextBox->Enabled) {
				localizationFolderTextBox->Text = cli::safe_cast<String^>(value);
			}

			// Generate the name of the folder that Creation Kit Audit Tool will
			// use for storing manifests and generated ARCHLIST files
			String^ docFolder = System::Environment::GetFolderPath(System::Environment::SpecialFolder::MyDocuments);
			userGameFolder = docFolder + L"\\My Games\\Starfield\\CreationKitAuditTool";
			userGamePrefix = Util::PathToPrefix(userGameFolder);
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
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowser;
	private: System::Windows::Forms::TextBox^ starfieldFolderTextBox;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ starfieldFolderButton;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ xboxRootFolderTextBox;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::ComboBox^ pluginComboBox;
	private: System::Windows::Forms::GroupBox^ auditGroupBox;
	private: System::Windows::Forms::ListView^ auditListView;
	private: System::Windows::Forms::Button^ stopButton;
	private: System::Windows::Forms::Button^ packButton;
	private: System::Windows::Forms::Button^ xboxWEMButton;
	private: System::Windows::Forms::Button^ importButton;
	private: System::Windows::Forms::ColumnHeader^ columnHeader1;
	private: System::Windows::Forms::MenuStrip^ mainMenuStrip;
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
	private: System::Windows::Forms::ToolStripMenuItem^ auditFiltersToolStripMenuItem;
	private: System::Windows::Forms::CheckBox^ replicationCheckBox;
	private: System::Windows::Forms::ToolStripMenuItem^ continuousReplicationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ wWiseConfigurationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ auditProcessAndFilteringToolStripMenuItem;
	private: System::Windows::Forms::NotifyIcon^ notifyIcon;
	private: System::Windows::Forms::ContextMenuStrip^ notifyContextMenuStrip;
	private: System::Windows::Forms::ToolStripMenuItem^ notifyToolStripShowItem;
	private: System::Windows::Forms::ToolStripMenuItem^ notifyToolStripExitItem;
	private: System::Windows::Forms::ToolStripMenuItem^ notifyToolStripResumeItem;
	private: System::Windows::Forms::ToolStripMenuItem^ notifyToolStripPauseItem;
	private: System::Windows::Forms::ToolStripMenuItem^ localizationToolStripMenuItem;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Button^ localizationButton;
	private: System::Windows::Forms::TextBox^ localizationFolderTextBox;

	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
	protected: bool running = false;
	protected: bool notificationExit = false;
	protected: int lastHeight = -1;
	protected: int lastWidth = -1;
	protected: static Color statusRunningColor = Color::Lime;
	protected: static Color runningTextColor = Color::Black;
	protected: static Color statusPausedColor = Color::Red;
	protected: static Color pausedTextColor = Color::White;
	protected: static String^ registryKey = L"SOFTWARE\\GrizBane\\CreationKitAuditTool";
	protected: static String^ registryNameStarfieldFolder = L"StarfieldFolder";
	protected: static String^ registryNameXBoxWEMFolder = L"XBoxWEMFolder";
	protected: static String^ registryNameContinuousReplication = L"ContinuousReplication";
	protected: static String^ registryLocalizationFolder = L"LocalizationRootFolder";
	protected: static String^ autodetectPluginName = L"<autodetect>";
	protected: String^ previousPlugInName = L"<autodetect>";
	protected: String^ userGameFolder;
	protected: String^ userGamePrefix;
	protected: static String^ manifestFileExt = L".manifest";
	protected: static String^ githubUrl = L"https://github.com/ebkarlson404/CreationKitAuditTool";
	protected: ListViewItem^ selectedAuditItem;
	protected: ReplicationLogDialog^ replicationLogDialog = gcnew ReplicationLogDialog();
	private: System::Windows::Forms::Button^ clipboardButton;
	private: System::Windows::Forms::Button^ viewLogButton;

protected:
	protected: PackDialog^ packDialog = gcnew PackDialog();
	protected:

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
			this->xboxRootFolderTextBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->pluginComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->pluginEnumerator = (gcnew System::Windows::Forms::BindingSource(this->components));
			this->auditListView = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->auditGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->replicationCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->statusButton = (gcnew System::Windows::Forms::Button());
			this->clearButton = (gcnew System::Windows::Forms::Button());
			this->startButton = (gcnew System::Windows::Forms::Button());
			this->importButton = (gcnew System::Windows::Forms::Button());
			this->stopButton = (gcnew System::Windows::Forms::Button());
			this->packButton = (gcnew System::Windows::Forms::Button());
			this->xboxWEMButton = (gcnew System::Windows::Forms::Button());
			this->mainMenuStrip = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->auditFiltersToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->auditProcessAndFilteringToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->continuousReplicationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->wWiseConfigurationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->localizationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->gitHubToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->auditContextMenuStrip = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->contextToolRemove = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->newPluginButton = (gcnew System::Windows::Forms::Button());
			this->addAuditFileButton = (gcnew System::Windows::Forms::Button());
			this->generateButton = (gcnew System::Windows::Forms::Button());
			this->localizationButton = (gcnew System::Windows::Forms::Button());
			this->clipboardButton = (gcnew System::Windows::Forms::Button());
			this->findPluginDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->importAchlistDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->addFileToAuditDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->notifyIcon = (gcnew System::Windows::Forms::NotifyIcon(this->components));
			this->notifyContextMenuStrip = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->notifyToolStripShowItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->notifyToolStripResumeItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->notifyToolStripPauseItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->notifyToolStripExitItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->localizationFolderTextBox = (gcnew System::Windows::Forms::TextBox());
			this->viewLogButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fileSystemWatcher))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pluginEnumerator))->BeginInit();
			this->auditGroupBox->SuspendLayout();
			this->mainMenuStrip->SuspendLayout();
			this->auditContextMenuStrip->SuspendLayout();
			this->notifyContextMenuStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// fileSystemWatcher
			// 
			this->fileSystemWatcher->EnableRaisingEvents = true;
			this->fileSystemWatcher->IncludeSubdirectories = true;
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
			this->starfieldFolderButton->Location = System::Drawing::Point(963, 60);
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
			this->label2->Location = System::Drawing::Point(40, 103);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(174, 25);
			this->label2->TabIndex = 3;
			this->label2->Text = L"XBOX Root Folder";
			// 
			// xboxRootFolderTextBox
			// 
			this->xboxRootFolderTextBox->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->xboxRootFolderTextBox->Location = System::Drawing::Point(286, 103);
			this->xboxRootFolderTextBox->Name = L"xboxRootFolderTextBox";
			this->xboxRootFolderTextBox->ReadOnly = true;
			this->xboxRootFolderTextBox->Size = System::Drawing::Size(646, 29);
			this->xboxRootFolderTextBox->TabIndex = 4;
			this->xboxRootFolderTextBox->TabStop = false;
			this->xboxRootFolderTextBox->TextChanged += gcnew System::EventHandler(this, &MainForm::xboxRootFolderTextBox_TextChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(40, 183);
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
			this->pluginComboBox->Location = System::Drawing::Point(286, 183);
			this->pluginComboBox->MaxDropDownItems = 16;
			this->pluginComboBox->Name = L"pluginComboBox";
			this->pluginComboBox->Size = System::Drawing::Size(646, 32);
			this->pluginComboBox->TabIndex = 8;
			this->toolTip->SetToolTip(this->pluginComboBox, L"Select which PlugIn to audit");
			this->pluginComboBox->TextChanged += gcnew System::EventHandler(this, &MainForm::pluginComboBox_TextChanged);
			// 
			// auditListView
			// 
			this->auditListView->BackColor = System::Drawing::SystemColors::Window;
			this->auditListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) { this->columnHeader1 });
			this->auditListView->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::None;
			this->auditListView->HideSelection = false;
			this->auditListView->Location = System::Drawing::Point(45, 221);
			this->auditListView->MultiSelect = false;
			this->auditListView->Name = L"auditListView";
			this->auditListView->Size = System::Drawing::Size(887, 422);
			this->auditListView->Sorting = System::Windows::Forms::SortOrder::Ascending;
			this->auditListView->TabIndex = 10;
			this->auditListView->TabStop = false;
			this->toolTip->SetToolTip(this->auditListView, L"RIght click on a file to remove it from the audit log");
			this->auditListView->UseCompatibleStateImageBehavior = false;
			this->auditListView->View = System::Windows::Forms::View::Details;
			this->auditListView->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::auditListView_MouseClick);
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"Audit Log";
			this->columnHeader1->Width = 879;
			// 
			// auditGroupBox
			// 
			this->auditGroupBox->BackColor = System::Drawing::SystemColors::Control;
			this->auditGroupBox->Controls->Add(this->viewLogButton);
			this->auditGroupBox->Controls->Add(this->replicationCheckBox);
			this->auditGroupBox->Controls->Add(this->statusButton);
			this->auditGroupBox->Controls->Add(this->clearButton);
			this->auditGroupBox->Controls->Add(this->startButton);
			this->auditGroupBox->Controls->Add(this->importButton);
			this->auditGroupBox->Controls->Add(this->stopButton);
			this->auditGroupBox->ForeColor = System::Drawing::SystemColors::ControlText;
			this->auditGroupBox->Location = System::Drawing::Point(45, 671);
			this->auditGroupBox->Name = L"auditGroupBox";
			this->auditGroupBox->Size = System::Drawing::Size(612, 212);
			this->auditGroupBox->TabIndex = 12;
			this->auditGroupBox->TabStop = false;
			this->auditGroupBox->Text = L"Audit Control";
			// 
			// replicationCheckBox
			// 
			this->replicationCheckBox->AutoSize = true;
			this->replicationCheckBox->Enabled = false;
			this->replicationCheckBox->Location = System::Drawing::Point(22, 163);
			this->replicationCheckBox->Name = L"replicationCheckBox";
			this->replicationCheckBox->Size = System::Drawing::Size(238, 29);
			this->replicationCheckBox->TabIndex = 5;
			this->replicationCheckBox->Text = L"Continuous Replication";
			this->toolTip->SetToolTip(this->replicationCheckBox, L"Immediately replicate files from ESP to ESM folders as changes are discovered");
			this->replicationCheckBox->UseVisualStyleBackColor = true;
			this->replicationCheckBox->CheckedChanged += gcnew System::EventHandler(this, &MainForm::replicationCheckBox_CheckedChanged);
			// 
			// statusButton
			// 
			this->statusButton->BackColor = System::Drawing::Color::Red;
			this->statusButton->ForeColor = System::Drawing::Color::White;
			this->statusButton->Location = System::Drawing::Point(22, 28);
			this->statusButton->Name = L"statusButton";
			this->statusButton->Size = System::Drawing::Size(157, 48);
			this->statusButton->TabIndex = 0;
			this->statusButton->TabStop = false;
			this->statusButton->Text = L"Paused";
			this->statusButton->UseVisualStyleBackColor = false;
			this->statusButton->Click += gcnew System::EventHandler(this, &MainForm::statusButton_Click);
			// 
			// clearButton
			// 
			this->clearButton->Location = System::Drawing::Point(434, 91);
			this->clearButton->Name = L"clearButton";
			this->clearButton->Size = System::Drawing::Size(157, 48);
			this->clearButton->TabIndex = 4;
			this->clearButton->Text = L"C&lear";
			this->toolTip->SetToolTip(this->clearButton, L"Merge the contents of an existing ACHLIST file into this PlugIn\'s audit log");
			this->clearButton->UseVisualStyleBackColor = true;
			this->clearButton->Click += gcnew System::EventHandler(this, &MainForm::clearButton_Click);
			// 
			// startButton
			// 
			this->startButton->Enabled = false;
			this->startButton->Location = System::Drawing::Point(271, 28);
			this->startButton->Name = L"startButton";
			this->startButton->Size = System::Drawing::Size(157, 48);
			this->startButton->TabIndex = 1;
			this->startButton->Text = L"&Start";
			this->toolTip->SetToolTip(this->startButton, L"Start/Resume the audit behavior for this PlugIn");
			this->startButton->UseVisualStyleBackColor = true;
			this->startButton->Click += gcnew System::EventHandler(this, &MainForm::startButton_Click);
			// 
			// importButton
			// 
			this->importButton->Enabled = false;
			this->importButton->Location = System::Drawing::Point(271, 91);
			this->importButton->Name = L"importButton";
			this->importButton->Size = System::Drawing::Size(157, 48);
			this->importButton->TabIndex = 3;
			this->importButton->Text = L"&Import";
			this->toolTip->SetToolTip(this->importButton, L"Merge the contents of an existing ACHLIST file into this PlugIn\'s audit log");
			this->importButton->UseVisualStyleBackColor = true;
			this->importButton->Click += gcnew System::EventHandler(this, &MainForm::importButton_Click);
			// 
			// stopButton
			// 
			this->stopButton->Enabled = false;
			this->stopButton->Location = System::Drawing::Point(434, 28);
			this->stopButton->Name = L"stopButton";
			this->stopButton->Size = System::Drawing::Size(157, 48);
			this->stopButton->TabIndex = 2;
			this->stopButton->Text = L"&Stop";
			this->toolTip->SetToolTip(this->stopButton, L"Stop/Pause the audit behavior for this PlugIn");
			this->stopButton->UseVisualStyleBackColor = true;
			this->stopButton->Click += gcnew System::EventHandler(this, &MainForm::stopButton_Click);
			// 
			// packButton
			// 
			this->packButton->Enabled = false;
			this->packButton->Location = System::Drawing::Point(710, 762);
			this->packButton->Name = L"packButton";
			this->packButton->Size = System::Drawing::Size(222, 48);
			this->packButton->TabIndex = 14;
			this->packButton->Text = L"Localize and &Pack";
			this->toolTip->SetToolTip(this->packButton, L"Pack files from the Audit Log into BA2 Archive Files");
			this->packButton->UseVisualStyleBackColor = true;
			this->packButton->Click += gcnew System::EventHandler(this, &MainForm::packButton_Click);
			// 
			// xboxWEMButton
			// 
			this->xboxWEMButton->Enabled = false;
			this->xboxWEMButton->Location = System::Drawing::Point(963, 100);
			this->xboxWEMButton->Name = L"xboxWEMButton";
			this->xboxWEMButton->Size = System::Drawing::Size(47, 39);
			this->xboxWEMButton->TabIndex = 5;
			this->xboxWEMButton->Text = L"...";
			this->toolTip->SetToolTip(this->xboxWEMButton, L"Select the root of the XBox Alternate Path");
			this->xboxWEMButton->UseVisualStyleBackColor = true;
			this->xboxWEMButton->Click += gcnew System::EventHandler(this, &MainForm::xboxWEMButton_Click);
			// 
			// mainMenuStrip
			// 
			this->mainMenuStrip->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
			this->mainMenuStrip->ImageScalingSize = System::Drawing::Size(28, 28);
			this->mainMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->fileToolStripMenuItem,
					this->helpToolStripMenuItem
			});
			this->mainMenuStrip->Location = System::Drawing::Point(0, 0);
			this->mainMenuStrip->Name = L"mainMenuStrip";
			this->mainMenuStrip->Size = System::Drawing::Size(1026, 38);
			this->mainMenuStrip->TabIndex = 12;
			this->mainMenuStrip->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->auditFiltersToolStripMenuItem,
					this->exitToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(62, 34);
			this->fileToolStripMenuItem->Text = L"&File";
			// 
			// auditFiltersToolStripMenuItem
			// 
			this->auditFiltersToolStripMenuItem->Name = L"auditFiltersToolStripMenuItem";
			this->auditFiltersToolStripMenuItem->Size = System::Drawing::Size(241, 40);
			this->auditFiltersToolStripMenuItem->Text = L"&Audit Filters";
			this->auditFiltersToolStripMenuItem->ToolTipText = L"File extensions excluded from discovery in the audit log";
			this->auditFiltersToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::auditFiltersToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::F4));
			this->exitToolStripMenuItem->Size = System::Drawing::Size(241, 40);
			this->exitToolStripMenuItem->Text = L"E&xit";
			this->exitToolStripMenuItem->ToolTipText = L"Exit the Creation Kit Audit Tool";
			this->exitToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::exitToolStripMenuItem_Click);
			// 
			// helpToolStripMenuItem
			// 
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->auditProcessAndFilteringToolStripMenuItem,
					this->continuousReplicationToolStripMenuItem, this->wWiseConfigurationToolStripMenuItem, this->localizationToolStripMenuItem,
					this->gitHubToolStripMenuItem, this->aboutToolStripMenuItem
			});
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			this->helpToolStripMenuItem->Size = System::Drawing::Size(74, 34);
			this->helpToolStripMenuItem->Text = L"&Help";
			// 
			// auditProcessAndFilteringToolStripMenuItem
			// 
			this->auditProcessAndFilteringToolStripMenuItem->Name = L"auditProcessAndFilteringToolStripMenuItem";
			this->auditProcessAndFilteringToolStripMenuItem->Size = System::Drawing::Size(378, 40);
			this->auditProcessAndFilteringToolStripMenuItem->Text = L"A&udit Process and Filtering";
			this->auditProcessAndFilteringToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::auditProcessAndFilteringToolStripMenuItem_Click);
			// 
			// continuousReplicationToolStripMenuItem
			// 
			this->continuousReplicationToolStripMenuItem->Name = L"continuousReplicationToolStripMenuItem";
			this->continuousReplicationToolStripMenuItem->Size = System::Drawing::Size(378, 40);
			this->continuousReplicationToolStripMenuItem->Text = L"&Continuous Replication";
			this->continuousReplicationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::continuousReplicationToolStripMenuItem_Click);
			// 
			// wWiseConfigurationToolStripMenuItem
			// 
			this->wWiseConfigurationToolStripMenuItem->Name = L"wWiseConfigurationToolStripMenuItem";
			this->wWiseConfigurationToolStripMenuItem->Size = System::Drawing::Size(378, 40);
			this->wWiseConfigurationToolStripMenuItem->Text = L"&WWise Configuration";
			this->wWiseConfigurationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::wWiseConfigurationToolStripMenuItem_Click);
			// 
			// localizationToolStripMenuItem
			// 
			this->localizationToolStripMenuItem->Name = L"localizationToolStripMenuItem";
			this->localizationToolStripMenuItem->Size = System::Drawing::Size(378, 40);
			this->localizationToolStripMenuItem->Text = L"&Localization Support";
			this->localizationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::localizationToolStripMenuItem_Click);
			// 
			// gitHubToolStripMenuItem
			// 
			this->gitHubToolStripMenuItem->Name = L"gitHubToolStripMenuItem";
			this->gitHubToolStripMenuItem->Size = System::Drawing::Size(378, 40);
			this->gitHubToolStripMenuItem->Text = L"&GitHub";
			this->gitHubToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::gitHubToolStripMenuItem_Click);
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Control | System::Windows::Forms::Keys::F1));
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(378, 40);
			this->aboutToolStripMenuItem->Text = L"&About";
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
			this->newPluginButton->Location = System::Drawing::Point(963, 180);
			this->newPluginButton->Name = L"newPluginButton";
			this->newPluginButton->Size = System::Drawing::Size(47, 39);
			this->newPluginButton->TabIndex = 9;
			this->newPluginButton->Text = L"+";
			this->toolTip->SetToolTip(this->newPluginButton, L"Add a new PlugIn to the repository of known PlugIns");
			this->newPluginButton->UseVisualStyleBackColor = true;
			this->newPluginButton->Click += gcnew System::EventHandler(this, &MainForm::newPluginButton_Click);
			// 
			// addAuditFileButton
			// 
			this->addAuditFileButton->Enabled = false;
			this->addAuditFileButton->Location = System::Drawing::Point(963, 412);
			this->addAuditFileButton->Name = L"addAuditFileButton";
			this->addAuditFileButton->Size = System::Drawing::Size(47, 39);
			this->addAuditFileButton->TabIndex = 11;
			this->addAuditFileButton->Text = L"+";
			this->toolTip->SetToolTip(this->addAuditFileButton, L"Manually add a file to the Audit Log");
			this->addAuditFileButton->UseVisualStyleBackColor = true;
			this->addAuditFileButton->Click += gcnew System::EventHandler(this, &MainForm::addAuditFileButton_Click);
			// 
			// generateButton
			// 
			this->generateButton->Enabled = false;
			this->generateButton->Location = System::Drawing::Point(710, 823);
			this->generateButton->Name = L"generateButton";
			this->generateButton->Size = System::Drawing::Size(222, 48);
			this->generateButton->TabIndex = 15;
			this->generateButton->Text = L"&Generate ACHLIST";
			this->toolTip->SetToolTip(this->generateButton, L"Replicates files from *.ESP folders to *.ESM folders and then generate the PC and"
				L" XBox ACHLIST files from the current audit log");
			this->generateButton->UseVisualStyleBackColor = true;
			this->generateButton->Click += gcnew System::EventHandler(this, &MainForm::generateButton_Click);
			// 
			// localizationButton
			// 
			this->localizationButton->Enabled = false;
			this->localizationButton->Location = System::Drawing::Point(963, 140);
			this->localizationButton->Name = L"localizationButton";
			this->localizationButton->Size = System::Drawing::Size(47, 39);
			this->localizationButton->TabIndex = 7;
			this->localizationButton->Text = L"...";
			this->toolTip->SetToolTip(this->localizationButton, L"The root of the Localization Staging Folder");
			this->localizationButton->UseVisualStyleBackColor = true;
			this->localizationButton->Click += gcnew System::EventHandler(this, &MainForm::localizationButton_Click);
			// 
			// clipboardButton
			// 
			this->clipboardButton->Location = System::Drawing::Point(710, 649);
			this->clipboardButton->Name = L"clipboardButton";
			this->clipboardButton->Size = System::Drawing::Size(222, 48);
			this->clipboardButton->TabIndex = 13;
			this->clipboardButton->Text = L"Copy to Clip&board";
			this->toolTip->SetToolTip(this->clipboardButton, L"Pack files from the Audit Log into BA2 Archive Files");
			this->clipboardButton->UseVisualStyleBackColor = true;
			this->clipboardButton->Click += gcnew System::EventHandler(this, &MainForm::clipboardButton_Click);
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
			// notifyIcon
			// 
			this->notifyIcon->ContextMenuStrip = this->notifyContextMenuStrip;
			this->notifyIcon->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"notifyIcon.Icon")));
			this->notifyIcon->Text = L"Creation Kit Audit Tool - paused";
			this->notifyIcon->Visible = true;
			this->notifyIcon->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::notifyIcon_MouseClick);
			// 
			// notifyContextMenuStrip
			// 
			this->notifyContextMenuStrip->ImageScalingSize = System::Drawing::Size(28, 28);
			this->notifyContextMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->notifyToolStripShowItem,
					this->notifyToolStripResumeItem, this->notifyToolStripPauseItem, this->notifyToolStripExitItem
			});
			this->notifyContextMenuStrip->Name = L"notifyContextMenuStrip";
			this->notifyContextMenuStrip->Size = System::Drawing::Size(163, 148);
			// 
			// notifyToolStripShowItem
			// 
			this->notifyToolStripShowItem->Name = L"notifyToolStripShowItem";
			this->notifyToolStripShowItem->Size = System::Drawing::Size(162, 36);
			this->notifyToolStripShowItem->Text = L"&Show UI";
			this->notifyToolStripShowItem->Click += gcnew System::EventHandler(this, &MainForm::notifyToolStripShowItem_Click);
			// 
			// notifyToolStripResumeItem
			// 
			this->notifyToolStripResumeItem->Name = L"notifyToolStripResumeItem";
			this->notifyToolStripResumeItem->Size = System::Drawing::Size(162, 36);
			this->notifyToolStripResumeItem->Text = L"&Resume";
			this->notifyToolStripResumeItem->Click += gcnew System::EventHandler(this, &MainForm::notifyToolStripResumeItem_Click);
			// 
			// notifyToolStripPauseItem
			// 
			this->notifyToolStripPauseItem->Enabled = false;
			this->notifyToolStripPauseItem->Name = L"notifyToolStripPauseItem";
			this->notifyToolStripPauseItem->Size = System::Drawing::Size(162, 36);
			this->notifyToolStripPauseItem->Text = L"&Pause";
			this->notifyToolStripPauseItem->Click += gcnew System::EventHandler(this, &MainForm::notifyToolStripPauseItem_Click);
			// 
			// notifyToolStripExitItem
			// 
			this->notifyToolStripExitItem->Name = L"notifyToolStripExitItem";
			this->notifyToolStripExitItem->Size = System::Drawing::Size(162, 36);
			this->notifyToolStripExitItem->Text = L"E&xit";
			this->notifyToolStripExitItem->Click += gcnew System::EventHandler(this, &MainForm::notifyToolStripExitItem_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(40, 143);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(220, 25);
			this->label4->TabIndex = 14;
			this->label4->Text = L"Localization Root Folder";
			// 
			// localizationFolderTextBox
			// 
			this->localizationFolderTextBox->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->localizationFolderTextBox->Location = System::Drawing::Point(286, 143);
			this->localizationFolderTextBox->Name = L"localizationFolderTextBox";
			this->localizationFolderTextBox->ReadOnly = true;
			this->localizationFolderTextBox->Size = System::Drawing::Size(646, 29);
			this->localizationFolderTextBox->TabIndex = 6;
			this->localizationFolderTextBox->TabStop = false;
			this->localizationFolderTextBox->TextChanged += gcnew System::EventHandler(this, &MainForm::localizationFolderTextBox_TextChanged);
			// 
			// viewLogButton
			// 
			this->viewLogButton->Location = System::Drawing::Point(271, 152);
			this->viewLogButton->Name = L"viewLogButton";
			this->viewLogButton->Size = System::Drawing::Size(157, 48);
			this->viewLogButton->TabIndex = 6;
			this->viewLogButton->Text = L"&View Log";
			this->toolTip->SetToolTip(this->viewLogButton, L"Merge the contents of an existing ACHLIST file into this PlugIn\'s audit log");
			this->viewLogButton->UseVisualStyleBackColor = true;
			this->viewLogButton->Click += gcnew System::EventHandler(this, &MainForm::viewLogButton_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1026, 901);
			this->Controls->Add(this->clipboardButton);
			this->Controls->Add(this->localizationButton);
			this->Controls->Add(this->localizationFolderTextBox);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->generateButton);
			this->Controls->Add(this->addAuditFileButton);
			this->Controls->Add(this->newPluginButton);
			this->Controls->Add(this->xboxWEMButton);
			this->Controls->Add(this->packButton);
			this->Controls->Add(this->auditGroupBox);
			this->Controls->Add(this->auditListView);
			this->Controls->Add(this->pluginComboBox);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->xboxRootFolderTextBox);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->starfieldFolderButton);
			this->Controls->Add(this->starfieldFolderTextBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->mainMenuStrip);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->mainMenuStrip;
			this->MinimumSize = System::Drawing::Size(1050, 965);
			this->Name = L"MainForm";
			this->Text = L"Starfield Creation Kit Audit Tool";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->Layout += gcnew System::Windows::Forms::LayoutEventHandler(this, &MainForm::MainForm_Layout);
			this->Resize += gcnew System::EventHandler(this, &MainForm::MainForm_Resize);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->fileSystemWatcher))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pluginEnumerator))->EndInit();
			this->auditGroupBox->ResumeLayout(false);
			this->auditGroupBox->PerformLayout();
			this->mainMenuStrip->ResumeLayout(false);
			this->mainMenuStrip->PerformLayout();
			this->auditContextMenuStrip->ResumeLayout(false);
			this->notifyContextMenuStrip->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	//
	// Event handlers for the various controls
	//
	private: System::Void MainForm_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
		// Only close the application if one chooses the 'Exit' option from the
		// context menu on the notification icon.
		if (!notificationExit) {
			this->Hide();
			e->Cancel = true;
		}
	}
	private: System::Void notifyIcon_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		// On a left-click, show the UI
		// On a right-click, show the context menu
		if (System::Windows::Forms::MouseButtons::Left == e->Button) {
			this->Show();
		}
	}
	private: System::Void notifyToolStripShowItem_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Show();
	}
	private: System::Void notifyToolStripResumeItem_Click(System::Object^ sender, System::EventArgs^ e) {
		startButton_Click(sender, e);
	}
	private: System::Void notifyToolStripPauseItem_Click(System::Object^ sender, System::EventArgs^ e) {
		stopButton_Click(sender, e);
	}
	private: System::Void notifyToolStripExitItem_Click(System::Object^ sender, System::EventArgs^ e) {
		this->notificationExit = true;
		this->Close();
	}
	private: System::Void starfieldFolderButton_Click(System::Object^ sender, System::EventArgs^ e) {
		folderBrowser->Description = "Select the Starfield Installation Folder";
		folderBrowser->SelectedPath = starfieldFolderTextBox->Text;
		folderBrowser->ShowNewFolderButton = false;
		if (folderBrowser->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
			starfieldFolderTextBox->Text = folderBrowser->SelectedPath;
		}
	}
	private: System::Void xboxWEMButton_Click(System::Object^ sender, System::EventArgs^ e) {
		folderBrowser->Description = "Select the XBox Alternate Folder";
		folderBrowser->SelectedPath = starfieldFolderTextBox->Text;
		folderBrowser->ShowNewFolderButton = true;
		if (folderBrowser->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
			String^ path = folderBrowser->SelectedPath;
			if (!StarfieldData::FileResidesWithinStarfieldFolder(path)) {
				MessageBox::Show( this,
					L"XBox Folder must reside within the Starfield Folder.",
					L"Invalid XBox Folder",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
			}
			else {
				xboxRootFolderTextBox->Text = path;
			}
		}
	}
	private: System::Void localizationButton_Click(System::Object^ sender, System::EventArgs^ e) {
		folderBrowser->Description = "Select the Localization Folder";
		folderBrowser->SelectedPath = starfieldFolderTextBox->Text;
		folderBrowser->ShowNewFolderButton = true;
		if (folderBrowser->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
			String^ path = folderBrowser->SelectedPath;
			if (!StarfieldData::FileResidesWithinStarfieldFolder(path)) {
				MessageBox::Show( this,
					L"Localization Folder must reside within the Starfield Folder.",
					L"Invalid Localization Folder",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
			}
			else {
				localizationFolderTextBox->Text = path;
			}
		}
	}
	private: System::Void startButton_Click(System::Object^ sender, System::EventArgs^ e) {
		statusButton->BackColor = statusRunningColor;
		statusButton->ForeColor = runningTextColor;
		statusButton->Text = L"Running";
		startButton->Enabled = false;
		stopButton->Enabled = true;
		starfieldFolderButton->Enabled = false;
		xboxWEMButton->Enabled = false;
		pluginComboBox->Enabled = false;
		newPluginButton->Enabled = false;
		if (IsAutodetectMode()) {
			replicationCheckBox->Enabled = false;
			replicationCheckBox->Checked = false;
		}
		else {
			replicationCheckBox->Checked = Util::ReadBooleanSetting(registryKey, registryNameContinuousReplication, false);
			replicationCheckBox->Enabled = true;
		}
		notifyToolStripPauseItem->Enabled = true;
		notifyToolStripResumeItem->Enabled = false;
		running = true;
		UpdateNotifyIcon();
	}
	private: System::Void stopButton_Click(System::Object^ sender, System::EventArgs^ e) {
		statusButton->BackColor = statusPausedColor;
		statusButton->ForeColor = pausedTextColor;
		statusButton->Text = L"Paused";
		stopButton->Enabled = false;
		startButton->Enabled = true;
		starfieldFolderButton->Enabled = true;
		xboxWEMButton->Enabled = true;
		pluginComboBox->Enabled = true;
		newPluginButton->Enabled = true;
		replicationCheckBox->Enabled = false;
		replicationCheckBox->Checked = false;
		notifyToolStripPauseItem->Enabled = false;
		notifyToolStripResumeItem->Enabled = true;
		running = false;
		UpdateNotifyIcon();
	}
    private: System::Void statusButton_Click(System::Object^ sender, System::EventArgs^ e) {
		// Toggle the run state
		if (running) {
			stopButton_Click(sender, e);
		}
		else {
			startButton_Click(sender, e);
		}
    }
	private: System::Void clipboardButton_Click(System::Object^ sender, System::EventArgs^ e) {
		StringBuilder builder;
		Collections::IEnumerator^ iter = auditListView->Items->GetEnumerator();
		while (iter->MoveNext()) {
			ListViewItem^ item = cli::safe_cast<ListViewItem^>(iter->Current);
			builder.AppendLine(item->Text);
		}
		String^ str = builder.ToString();
		if (nullptr == str || System::String::Empty == str) {
			Clipboard::Clear();
		}
		else {
			Clipboard::SetText(str);
		}
		MessageBox::Show(
			this,
			L"Audit Log copied to the system clipboard.",
			L"Action Confirmation",
			MessageBoxButtons::OK,
			MessageBoxIcon::Information);
	}
	private: System::Void generateButton_Click(System::Object^ sender, System::EventArgs^ e) {
		List<String^>^ xbFullList = gcnew List<String^>;
		List<String^>^ xbVoiceList = gcnew List<String^>;
		List<String^>^ xbNonVoiceList = gcnew List<String^>;
		List<String^>^ pcFullList = gcnew List<String^>;
		List<String^>^ pcVoiceList = gcnew List<String^>;
		List<String^>^ pcNonVoiceList = gcnew List<String^>;

		// Iterate through the audit log to find the primary copies of all
		// files in the manifest.  For WEM and DDS files, also find their
		// XBox versions in the Starfield XBox alternate directory tree.
		Collections::IEnumerator^ iter = auditListView->Items->GetEnumerator();
		while (iter->MoveNext()) {
			// Replicate the file to the ESM directory if required
			ListViewItem^ item = cli::safe_cast<ListViewItem^>(iter->Current);
			String^ relativeName = Replication::EspToEsmReplication(item->Text, this);
			if (nullptr == relativeName) {
				return;
			}

			// Marshall the file into the correct PC packing lists
			pcFullList->Add(relativeName);
			if (Util::HasPrefix(relativeName, StarfieldData::starfieldRelativeVoicePrefix) &&
				Util::HasSuffix(relativeName, L".WEM")) {
				pcVoiceList->Add(relativeName);
			}
			else {
				pcNonVoiceList->Add(relativeName);
			}

			// If this is a platform-specific file format, go find the XBox
			// version of the file.  Otherwise it is a platform-neutral file
			// which should be added to teh XBox non-voice manifest
			if (Util::HasSuffix(relativeName, L".WEM")) {
				String^ xboxRelativeName = PCEspToXBoxEsmReplication(item->Text);
				if (nullptr == xboxRelativeName) {
					return;
				}
				xbFullList->Add(xboxRelativeName);
				xbVoiceList->Add(xboxRelativeName);
			} else if (Util::HasSuffix(relativeName, L".DDS")) {
				String^ xboxRelativeName = PCEspToXBoxEsmReplication(item->Text);
				if (nullptr == xboxRelativeName) {
					return;
				}
				xbFullList->Add(xboxRelativeName);
				xbNonVoiceList->Add(xboxRelativeName);
			}
			else {
				xbFullList->Add(relativeName);
				xbNonVoiceList->Add(relativeName);
			}
		}

		// Write the arrays out to the FULL ACHLIST files
		array<String^>^ pcFiles = pcFullList->ToArray();
		array<String^>^ xbFiles = xbFullList->ToArray();
		AchList::WriteArrayToJsonFile(pcFiles, userGamePrefix + pluginComboBox->Text + L"-PC.achlist", this);
		AchList::WriteArrayToJsonFile(xbFiles, userGamePrefix + pluginComboBox->Text + L"-XB.achlist", this);

		// Write the arrays out to the VOICE ACHLIST files
		//pcFiles = pcVoiceList->ToArray();
		//xbFiles = xbVoiceList->ToArray();
		//AchList::WriteArrayToJsonFile(pcFiles, userGamePrefix + pluginComboBox->Text + L"-VOICE-PC.achlist", this);
		//AchList::WriteArrayToJsonFile(xbFiles, userGamePrefix + pluginComboBox->Text + L"-VOICE-XB.achlist", this);

		// Write the arrays out to the NONVOICE ACHLIST files
		//pcFiles = pcNonVoiceList->ToArray();
		//xbFiles = xbNonVoiceList->ToArray();
		//AchList::WriteArrayToJsonFile(pcFiles, userGamePrefix + pluginComboBox->Text + L"-NONVOICE-PC.achlist", this);
		//AchList::WriteArrayToJsonFile(xbFiles, userGamePrefix + pluginComboBox->Text + L"-NONVOICE-XB.achlist", this);

		// Tell the user what was done
		MessageBox::Show(this,
			L"Generated the following ACLIST files in " +
			userGameFolder + L"\n\n * " +
			pluginComboBox->Text + L"-PC.achlist\n * " + 
			//pluginComboBox->Text + L"-VOICE-PC.achlist\n * " +
			//pluginComboBox->Text + L"-NONVOICE-PC.achlist\n * " +
			pluginComboBox->Text + L"-XB.achlist",
			//pluginComboBox->Text + L"-XB.achlist\n * " +
			//pluginComboBox->Text + L"-VOICE-XB.achlist\n * " +
			//pluginComboBox->Text + L"-NONVOICE-XB.achlist"
			L"ACHLIST Generation Complete",
			MessageBoxButtons::OK,
			MessageBoxIcon::Information);

	}
	private: String^ PCEspToXBoxEsmReplication(String^ pcEspRelativePath) {
		String^ xBoxEspRelativeName = StarfieldData::starfieldXBoxRelativePrefix + pcEspRelativePath;
		return Replication::EspToEsmReplication(xBoxEspRelativeName, this);
	}
	private: System::Void packButton_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			packDialog->Initialize(pluginComboBox->Text, auditListView);
			packDialog->ShowDialog(this);
		}
		catch (Exception^ e) {
			MessageBox::Show(
				this,
				L"Pack operation failed: " + e->Message,
				L"Pack Operation Failure",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
		}
	}
	private: System::Void replicationCheckBox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (replicationCheckBox->Enabled) {
			Util::WriteSetting(registryKey, registryNameContinuousReplication, replicationCheckBox->Checked);
		}
	}
	private: System::Void clearButton_Click(System::Object^ sender, System::EventArgs^ e) {
		// Clear the audit log and update the plugin's manifest
		if (MessageBox::Show(this,
			L"Do you want to clear the audit log?",
			L"CLear Audit Confirmation",
			MessageBoxButtons::OKCancel,
			MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::OK) {
				auditListView->Items->Clear();
				WriteManifest(pluginComboBox->Text);
		}
	}
	private: System::Void importButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (importAchlistDialog->ShowDialog(this) == System::Windows::Forms::DialogResult::OK) {
			// Set the folder for the import file as the initial folder for the next time
			String^ importFile = importAchlistDialog->FileName;
			importAchlistDialog->InitialDirectory = Directory::GetParent(importFile)->FullName;

			// Read the ACHLIST file and add all files to the audit log
			array<String^>^ files = AchList::ReadArrayFromJsonFile(importFile, this);
			if (nullptr == files) {
				return;
			}
			for (int i = 0; i < files->Length; i++) {
				String^ filename = files[i];
				
				// Since the foreign ACHLIST file may have been created for ESM
				// distribution, ensure that we transform any references to
				// directories name MyMod.ESM to MyMod.ESP.
				int pos = filename->IndexOf(StarfieldData::esmDirName, StringComparison::InvariantCultureIgnoreCase);
				if (pos >= 0) {
					filename = filename->Substring(0, pos) + StarfieldData::espDirName + filename->Substring(pos + StarfieldData::esmDirName->Length);
				}

				// Add the file to the audit log if it is not already present and not
				// a direct reference to an XBox files
				if (!Util::HasPrefix(filename, StarfieldData::starfieldXBoxRelativePrefix) &&
					!AuditFileAlreadyPresent(filename)) {
					auditListView->Items->Add(gcnew ListViewItem(filename));
					auditListView->AutoResizeColumns(ColumnHeaderAutoResizeStyle::ColumnContent);
				}
			}
			WriteManifest(pluginComboBox->Text);
		}
	}
	private: System::Void viewLogButton_Click(System::Object^ sender, System::EventArgs^ e) {
		replicationLogDialog->Run(Replication::replicationLog, this);
	}
	private: System::Void MainForm_Resize(System::Object^ sender, System::EventArgs^ e) {
		if (this->WindowState == FormWindowState::Minimized) {
			this->Hide();
		}
	}
	private: System::Void MainForm_Layout(System::Object^ sender, System::Windows::Forms::LayoutEventArgs^ e) {
		if (0 > lastHeight || 0 > lastWidth) {
			return;
		}

		// If we are minimizing the window, do not change the layout
		if (this->WindowState == FormWindowState::Minimized) {
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
			MoveControl(clipboardButton, deltaWidth, deltaHeight);
			MoveControl(generateButton, deltaWidth, deltaHeight);
			MoveControl(packButton, deltaWidth, deltaHeight);
			MoveControl(starfieldFolderButton, deltaWidth, 0);
			MoveControl(xboxWEMButton, deltaWidth, 0);
			MoveControl(localizationButton, deltaWidth, 0);
			addAuditFileButton->Left += deltaWidth;
			addAuditFileButton->Top = auditListView->Top + ((auditListView->Height - addAuditFileButton->Height) / 2);

			// Change the size of the text-based controls to track the change-of-size
			starfieldFolderTextBox->Width += deltaWidth;
			xboxRootFolderTextBox->Width += deltaWidth;
			localizationFolderTextBox->Width += deltaWidth;
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
		Util::WriteSetting(registryKey, registryNameStarfieldFolder, starfieldFolderTextBox->Text);
		StarfieldData::starfieldFolder = starfieldFolderTextBox->Text;
		StarfieldData::starfieldPrefix = Util::PathToPrefix(StarfieldData::starfieldFolder);
		StarfieldData::starfieldDataFolder = StarfieldData::starfieldPrefix + L"DATA";
		StarfieldData::starfieldDataPrefix = Util::PathToPrefix(StarfieldData::starfieldDataFolder);
		StarfieldData::starfieldVoicePrefix = StarfieldData::starfieldDataPrefix + L"Sound\\Voice\\";
		StarfieldData::starfieldBackupPrefix = StarfieldData::starfieldDataPrefix + L"BACKUP\\";
		fileSystemWatcher->BeginInit();
		fileSystemWatcher->Path = StarfieldData::starfieldFolder;
		fileSystemWatcher->EndInit();
		findPluginDialog->InitialDirectory = StarfieldData::starfieldDataFolder;
		importAchlistDialog->InitialDirectory = starfieldFolderTextBox->Text;
		addFileToAuditDialog->InitialDirectory = StarfieldData::starfieldDataFolder;
		xboxWEMButton->Enabled = true;
		localizationButton->Enabled = true;
		if (!StarfieldData::FileResidesWithinStarfieldFolder(localizationFolderTextBox->Text)) {
			localizationFolderTextBox->Text = L"";
		}
		if (!StarfieldData::FileResidesWithinStarfieldFolder(xboxRootFolderTextBox->Text)) {
			xboxRootFolderTextBox->Text = L"";
		}
		else {
			startButton->Enabled = true;
			if (!pluginComboBox->Text->Equals(autodetectPluginName)) {
				importButton->Enabled = true;
				addAuditFileButton->Enabled = true;
				generateButton->Enabled = true;
				packButton->Enabled = true;
			}
		}
	}
	private: System::Void xboxRootFolderTextBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		String^ xbFolder = xboxRootFolderTextBox->Text;
		Util::WriteSetting(registryKey, registryNameXBoxWEMFolder, xbFolder);
		if (0 == xbFolder->Length) {
			pluginComboBox->Enabled = false;
			newPluginButton->Enabled = false;
			startButton->Enabled = false;
			importButton->Enabled = false;
			addAuditFileButton->Enabled = false;
			generateButton->Enabled = false;
			packButton->Enabled = false;
		}
		else {
			StarfieldData::starfieldXBoxDataFolder = xbFolder + L"\\DATA";
			StarfieldData::starfieldXBoxRelativePrefix =
				L"Data\\.." +
				Util::PathToPrefix(xbFolder->Substring(starfieldFolderTextBox->Text->Length));
			StarfieldData::starfieldXBoxDataPrefix =
				Util::PathToPrefix(StarfieldData::starfieldXBoxDataFolder);
			StarfieldData::starfieldXBoxRelativeVoicePrefix =
				StarfieldData::starfieldXBoxRelativePrefix + L"Data\\Sound\\Voice\\";
			pluginComboBox->Enabled = true;
			newPluginButton->Enabled = true;
			startButton->Enabled = true;
			if (!pluginComboBox->Text->Equals(autodetectPluginName)) {
				importButton->Enabled = true;
				addAuditFileButton->Enabled = true;
				generateButton->Enabled = true;
				packButton->Enabled = true;
			}
		}
	}
	private: System::Void localizationFolderTextBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		Util::WriteSetting(registryKey, registryLocalizationFolder, localizationFolderTextBox->Text);
		StarfieldData::localizationFolder = localizationFolderTextBox->Text;
		StarfieldData::localizationPrefix = Util::PathToPrefix(StarfieldData::localizationFolder);
		StarfieldData::localizationRelativePrefix = L"Data\\.." +
			StarfieldData::localizationPrefix->Substring(StarfieldData::starfieldPrefix->Length - 1);
	}
	private: System::Void pluginComboBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
		// If the current value in the control is an empty string, this is
		// an interim condition caused by reloading the choice list - ignore
		String^ newPlugin = pluginComboBox->Text;
		if (newPlugin->Length == 0) {
			// This can happen when regenerating the set of choices for the plugin control
			return;
		}

		// Clear the audit log unless we were not bound to a specific plugin before
		bool preserveAudit = previousPlugInName->Equals(autodetectPluginName);
		if (!preserveAudit) {
			auditListView->Items->Clear();
		}

		// Toggle the state on the various buttons depending on whether we are
		// now bound to a specific plugin
		if (newPlugin->Equals(autodetectPluginName)) {
			// Deactivate the other audit control buttons
			importButton->Enabled = false;
			generateButton->Enabled = false;
			packButton->Enabled = false;
			addAuditFileButton->Enabled = false;
			replicationCheckBox->Enabled = false;
			replicationCheckBox->Checked = false;

			// Clear the ESP and ESM directory names
			StarfieldData::espDirName = nullptr;
			StarfieldData::esmDirName = nullptr;
		}
		else {
			// Activate the other audit control buttons
			startButton->Enabled = !running;
			importButton->Enabled = true;
			addAuditFileButton->Enabled = true;
			generateButton->Enabled = true;
			packButton->Enabled = true;
			replicationCheckBox->Checked = running &&
				Util::ReadBooleanSetting(registryKey, registryNameContinuousReplication, false);
			replicationCheckBox->Enabled = running;

			// Generate the names for the MyMod.ESP and MyMod.ESM directories
			StarfieldData::espDirName = L"\\" + newPlugin + L".esp\\";
			StarfieldData::esmDirName = L"\\" + newPlugin + L".esm\\";

			// Load/Update the current manifest for this plugin
			LoadManifest(newPlugin);
			if (preserveAudit) {
				WriteManifest(newPlugin);
			}
		}

		// Update the text on the Notify Icon
		UpdateNotifyIcon();

		// Record the new plugin binding
		previousPlugInName = newPlugin;
	}
	private: System::Void auditFiltersToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		AuditFilterDialog::singleton->ShowDialog(this);
    }
	private: System::Void exitToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void auditProcessAndFilteringToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show(this,
			L"This tool works by using the native Windows APIs to receive notifications " +
			L"anytime that a file is created, altered, renamed or deleted anywhere in the Starfield " +
			L"directory tree.  The tool uses these notifications to keep an audit log of all changes " +
			L"made by the Creation Kit as part of working on one's plugin.  This audit log is then " +
			L"used as a manifest of all files that must be packed into the BA2 archives that one " +
			L"distributes with one's plugin.\n\nAs it turns out, the Creation Kit does create " +
			L"some files that would not normally be packaged with one's plugin.  Consequently, " +
			L"this audit tool uses a set of suffix-filters to ignore files that Creation Kit " +
			L"creates that should not be part of the plugin's distribution package.  One can " +
			L"customize the set of filters by using 'File | Audit Filter' from the menu bar.\n\n" +
			L"Note that one can suspend and resume the audit process by using the 'Start' and 'Stop' " +
			L"buttons in the 'Audit Control' group in the lower left corner of the UI.\n\n" +
			L"One can also manually add files to the audit log by using the '+' button to the " +
			L"right of the audit log list.  Manually adding files to the audit log bypasses " +
			L"the normal filtering logic and will always be added.\n\nOne can remove files from " +
			L"the audit log by right-clicking on the errant file and then clicking on the " +
			L"'Remove from Audit' operation.  Note that even if a file is manually removed " +
			L"from the audit log, if Creation Kit touches that file again, it will be " +
			L"relogged.",
			L"Audit Process and Filters",
			MessageBoxButtons::OK,
			MessageBoxIcon::Information);
	}
	private: System::Void continuousReplicationToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show(this,
			L"Every time that one generates or regenerates the ACHLIST packing files " +
			L"for a plugin, the tool will also replicate all files found in the plugin's ESP " +
			L"directories to the corresponding ESM directories.  However this synchronization of files " +
			L"only occurs when one clicks on the 'Generate' button.  If one has made changes to " +
			L"the plugin since the last time that the ACHLIST files were generated, the ESM directories " +
			L"may become out-of-date.\n\nThe Continuous Replication option will cause the audit " +
			L"process to replicate files into the ESM directories as soon as a change is detected.  " +
			L"This will ensure that the ESM directories are kept in sync with the ESP directories " +
			L"irrespective of whether one regenerates the ACHLIST files.\n\nNote that continuous " +
			L"replication only happens while the audit process is running.  If one pauses the " +
			L"audit process, the continuous replication will also be paused.",
			L"What is Continuous Replication",
			MessageBoxButtons::OK,
			MessageBoxIcon::Information);
	}
	private: System::Void wWiseConfigurationToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show(this,
			L"In order to generate platform-specific ACHLIST files, one must configure " +
			L"WWise in the CreationKitCustom.ini file to generate *both* PC and XBox WEM files " +
			L"simultaneously, placing the XBox WEM files in an alternate directory structure.\n\n"
			L"One can provide a suitable configuration for WWise by ensuring that the [Audio] " +
			L"section of the CreationKitCustom.ini file " +
			L"has the following settings:\n\n[Audio]\nbProcessAudioForPC = 1\nbProcessAudioForXB = 1\n" +
			L"sPathToVoiceOutputPC =\nsPathToVoiceOutputXB = XBOX\\Data\\Sound\\Voice\n" +
			L"sPathToSoundBankOutputPC =\nsPathToSoundBankOutputXB = XBOX\\Data\\Sound\\SoundBanks\n" +
			L"bLogWwiseConversationOutput = 1\nsPathToWwiseProj = Tools\\wwise\\Starfield\\Starfield.wproj\n\n" +
			L"Once WWise has been configured, one should configure the 'XBox WEM Folder' property " +
			L"of the audit tool to point at the root of the XBox Alternate folder.  Using the " +
			L"WWise configuration shown above, this would be your Starfield Installation folder " +
			L"followed by '\\XBOX'.",
			L"WWise Configuration",
			MessageBoxButtons::OK,
			MessageBoxIcon::Information);
	}
	private: System::Void localizationToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show(this,
			L"Plugins that have been localized have two special " +
			L"characteristics: String Translation Files and Localized Voice Files\n\n" +
			L"The String Translation Files are generated using the CreationKit.exe tool and are " +
			L"packaged as a collection of language-specific files stored in the Data\\Strings folder. " +
			L"Please refer to Bethesda's Verified Creators Wiki for specifics of the process.\n\n" +
			L"If one's localized plugin has localized voice files, one needs a place to persist " +
			L"the WEM files that were recorded in alternate languages and these language-specific " +
			L"WEM files must be packed in BA2 archives that use the following naming scheme: " +
			L"'<mod> - Voices_<lang>.ba2' where " +
			L"<lang> is one of the ISO 639 language codes - e.g. 'en', 'it', 'fr', 'de'.\n\n" +
			L"The localized WEM files should be stored in the same folder where the 'native' " +
			L"WEM files reside.  They should have the same numeric name, but have a '_<lang>' " +
			L"suffix to indicate the language for the file.  For example, if there was a 'native' " +
			L"WEM file named '123456.wem' then the French version of that file would be named " +
			L"'123456_fr.wem'.  Once the localized WEM files are stored on disk, the Creation Kit " +
			L"Audit Tool provides a mechanism to pack them into the properly named 'Voices_<lang>' BA2 " +
			L"archive files.\n\nNote that as of version 1.15.222 of the Starfield Creation Kit " +
			L"the Starfield Creation Kit does not provide a mechanism for shipping the " +
			L"language - specific voice BA2 files with a plugin.  Users would have " +
			L"acquire the localized voice files from some other source and then drop them into their " +
			L"Starfield\\Data folder manually.  One can publish plugins with localized voice resources " +
			L"on Nexus.",
			L"Localization Support",
			MessageBoxButtons::OK,
			MessageBoxIcon::Information);
	}
	private: System::Void gitHubToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		System::Diagnostics::Process^ proc = gcnew System::Diagnostics::Process();
		proc->Start(githubUrl);
	}
	private: System::Void aboutToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		MessageBox::Show( this,
			L"Monitors file activity within the Starfield Installation Tree to automated the generation of ACHLIST packing files.\n\n" +
			L"Provides automatic replication of files from *.ESP folders to *.ESM folders during ACHLIST generation.\n\n" +
			L"Generates platform-specific ACHLIST files for packaging PC and XBox WEM files.\n\n" +
			L"Generated ACHLIST files are stored in one's >Documents\\My Games\\Starfield\\CreationKitAuditTool< folder.\n\n" +
			L"GitHub: " + githubUrl + L"\n\n" +
			L"Version 2.1.1\n\n" +
			L"Copyright 2025, Eric Karlson\n\n" +
			L"Distrbuted under the terms of the Apache License version 2.0, January 2004",
			L"Creation Kit Audit Log Help",
			MessageBoxButtons::OK,
			MessageBoxIcon::Information);
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
			String^ plugin = findPluginDialog->SafeFileName->Substring(0, findPluginDialog->SafeFileName->Length - 4);
			if (RegisterPlugInIfNeeded(plugin)) {
				PopluatePlugInChoices();
				pluginComboBox->Text = plugin;
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

				// Silently skip anything that is not a normal file.
				// Skip and report any files not within the Starfield or XBox Data folders.
				// Skip and report any file that resides within a plugin folder
				// that is not related to the current plugin.
				if (NORMAL_FILE != Util::ClassifyFile(filename)) {
					// Silent ignore
				}
				else if (!StarfieldData::FileResidesWithinAnyDataFolder(filename)) {
					skippedFiles = skippedFiles + separator + filename;
					separator = L"\n";
				}
				else if (!StarfieldData::FileRelatedToPlugIn(filename, pluginComboBox->Text)) {
					skippedFiles = skippedFiles + separator + filename;
					separator = L"\n";
				}
				else {
					// Add the new file to the audit log if it is not already present.
					String^ rname = StarfieldData::GetRelativeName(filename);
					if (!AuditFileAlreadyPresent(rname)) {
						auditListView->Items->Add(gcnew ListViewItem(rname));
						auditListView->AutoResizeColumns(ColumnHeaderAutoResizeStyle::ColumnContent);
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
				MessageBox::Show( this,
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
			FileType ft = Util::ClassifyFile(e->FullPath);
			if (NORMAL_FILE == ft) {
				String^ relativeName = StarfieldData::GetRelativeName(e->FullPath);
				if (nullptr != relativeName) {
					Replication::currentEvent->Stamp(L"CHANGED", relativeName);
					HandleFileCreation(e->FullPath);
				}
			}
		}
	}
	private: System::Void fileSystemWatcher_Deleted(System::Object^ sender, System::IO::FileSystemEventArgs^ e) {
		if (running) {
			String^ relativeName = StarfieldData::GetRelativeName(e->FullPath);
			if (nullptr != relativeName) {
				Replication::currentEvent->Stamp(L"DELETE", relativeName);

				// Since we cannot tell at this point whether the deleted object was a file
				// or a directory, we try both possibilities for deleting potential replicas
				// of the orginal object.
				// Both of these routines perform checking to see whether the replicated
				// object is a directory or file, so we can call both of them without
				// knowing ahead of time which one is correct.
				// Both of these functions will also handle removing the object from
				// the audit log.
				HandleFileDeletion(e->FullPath);
				HandleFolderDeletion(e->FullPath);
			}
		}
	}
	private: System::Void fileSystemWatcher_Created(System::Object^ sender, System::IO::FileSystemEventArgs^ e) {
		if (running) {
			String^ relativeName = StarfieldData::GetRelativeName(e->FullPath);
			if (nullptr != relativeName) {
				Replication::currentEvent->Stamp(L"CREATED", relativeName);
				FileType ft = Util::ClassifyFile(e->FullPath);
				if (NORMAL_FILE == ft) {
					HandleFileCreation(e->FullPath);
				}
				else if (DIRECTORY == ft) {
					HandleFolderCreation(e->FullPath);
				}
			}
		}
	}
	private: System::Void fileSystemWatcher_Renamed(System::Object^ sender, System::IO::RenamedEventArgs^ e) {
		if (running) {
			String^ oldRelativeName = StarfieldData::GetRelativeName(e->OldFullPath);
			String^ newRelativeName = StarfieldData::GetRelativeName(e->FullPath);
			if (nullptr != oldRelativeName && nullptr != newRelativeName) {
				Replication::currentEvent->Stamp(L"RENAME", oldRelativeName, newRelativeName);
				FileType ft = Util::ClassifyFile(e->FullPath);
				if (NORMAL_FILE == ft) {
					HandleRenamedFile(e->OldFullPath, e->FullPath);
				}
				else if (DIRECTORY == ft) {
					HandleRenamedFolder(e->OldFullPath, e->FullPath);
				}
				else {
					// The renamed object is gone or unknown, so all we know is that the
					// original object is gone.  Treat this as a DELETE action on the
					// original, unknown, object.
					HandleFileDeletion(e->OldFullPath);
					HandleFolderDeletion(e->OldFullPath);
				}
			}
		}
	}
	//
	// Utility functions
	//
    private: System::Void UpdateNotifyIcon() {
		notifyIcon->Text = "Creation Kit Audit Tool - " + (running ? "running" : "paused");
    }
	private: ListViewItem^ FindListViewItem(ListView^ listview, String^ text, bool prefixSearch) {
		return (listview->Items->Count == 0) ?
			nullptr :
			listview->FindItemWithText(text, true, 0, prefixSearch);
	}
	private: System::Void AutoBindPlugin(String^ fullname) {
		// Extract the base plugin name
		String^ plugin = fullname->Substring(StarfieldData::starfieldDataPrefix->Length,
			fullname->Length - StarfieldData::starfieldDataPrefix->Length - 4);

		// Register and switch to the autodetected plugin
		if (RegisterPlugInIfNeeded(plugin)) {
			PopluatePlugInChoices();
			pluginComboBox->Text = plugin;
		}
	}
	private: bool IsAutodetectMode() {
		return autodetectPluginName->Equals(pluginComboBox->Text);
	}
	private: System::Void HandleFileCreation(String^ fullname) {
		if (replicationCheckBox->Checked) {
			Replication::MaybeReplicateFile(fullname, pluginComboBox->Text);
		}
		if (StarfieldData::IsESPFile(fullname) && IsAutodetectMode()) {
			AutoBindPlugin(fullname);
		}
		if (ShouldLog(fullname)) {
			String^ rpath = StarfieldData::GetRelativeName(fullname);
			if (nullptr == FindListViewItem(auditListView, rpath, false)) {
				auditListView->Items->Add(gcnew ListViewItem(rpath));
				auditListView->AutoResizeColumns(ColumnHeaderAutoResizeStyle::ColumnContent);
				WriteManifest(pluginComboBox->Text);
			}
		}
	}
	/**
	* Walk the directory tree of a given folder and report any files as
	* being "created" for the purposes of continuous replication and
	* audit logging.
	* This is necessary because when a folder is moved, nothing is reported
	* to the FileSystemWatcher about contents of the moved folder coming
	* along for the ride, so we have to rediscover anything contained
	* within the moved folder.
	* @param fullname - The full name of the folder to "rediscover"
	*/
	private: System::Void RediscoverFolderContents(String^ fullname) {
		// Emulate a CREATE operation on all files that reside within this
		// directory tree.  In cases where one has moved a folder there are
		// no notifications about the items that move with the folder, so
		// we have to walk the tree to discover them.
		Generic::IEnumerator<String^>^ iter =
			Directory::EnumerateFiles(fullname, L"*.*", SearchOption::AllDirectories)->GetEnumerator();
		while (iter->MoveNext()) {
			HandleFileCreation(iter->Current);
		}
	}
	private: System::Void HandleFolderCreation(String^ fullname) {
		if (replicationCheckBox->Checked) {
			RediscoverFolderContents(fullname);
		}
	}
	private: System::Void HandleFolderDeletion(String^ fullname) {
		String^ relativeName = StarfieldData::GetRelativeName(fullname);
		if (nullptr == relativeName) {
			// Folder is not in one of the Data folders - ignore
			return;
		}

		// Replicate the folder deletion, if needed
		if (replicationCheckBox->Checked) {
			Replication::MaybeDeleteReplicaFolder(fullname);
		}

		// Now remove all audit logs whose directory matches the one being deleted
		bool manifestAltered = false;
		String^ relativePrefix = Util::PathToPrefix(relativeName);
		ListViewItem^ item = FindListViewItem(auditListView, relativePrefix, true);
		while (nullptr != item) {
			auditListView->Items->Remove(item);
			manifestAltered = true;
			item = FindListViewItem(auditListView, relativePrefix, true);
		}

		if (manifestAltered) {
			WriteManifest(pluginComboBox->Text);
		}
	}
	private: System::Void HandleFileDeletion(String^ fullname) {
		String^ relativeName = StarfieldData::GetRelativeName(fullname);
		if (nullptr == relativeName) {
			// File does not reside in one of the Data folders - ignore
			return;
		}
		if (replicationCheckBox->Checked) {
			Replication::MaybeDeleteReplicaFile(fullname, pluginComboBox->Text);
		}
		ListViewItem^ item = FindListViewItem(auditListView, relativeName, false);
		if (nullptr != item) {
			auditListView->Items->Remove(item);
			WriteManifest(pluginComboBox->Text);
		}
	}
	private: System::Void HandleRenamedFile(String^ oldFullName, String^ newFullName) {
		String^ relativeName = StarfieldData::GetRelativeName(oldFullName);
		if (nullptr == relativeName) {
			// File does not reside in one of the Data folders - ignore
			return;
		}

		// Replicate the rename, if needed
		if (replicationCheckBox->Checked) {
			Replication::MaybeRenameReplicaFiles(oldFullName, newFullName, pluginComboBox->Text);
		}

		// Remove audit logs for the old filename
		bool manifestAltered = false;
		ListViewItem^ item = FindListViewItem(auditListView, relativeName, false);
		if (nullptr != item) {
			auditListView->Items->Remove(item);
			manifestAltered = true;
		}

		// Add audit logs for the new filename
		if (ShouldLog(newFullName)) {
			relativeName = StarfieldData::GetRelativeName(newFullName);
			if (nullptr == FindListViewItem(auditListView, relativeName, false)) {
				auditListView->Items->Add(gcnew ListViewItem(relativeName));
				auditListView->AutoResizeColumns(ColumnHeaderAutoResizeStyle::ColumnContent);
				manifestAltered = true;
			}
		}

		if (manifestAltered) {
			WriteManifest(pluginComboBox->Text);
		}
	}
	private: System::Void HandleRenamedFolder(String^ oldFullName, String^ newFullName) {
		String^ oldRelativeName = StarfieldData::GetRelativeName(oldFullName);
		if (nullptr == oldRelativeName) {
			// Folder does not reside in one of the Data folders - ignore
			return;
		}

		// Replicate the rename, if needed
		if (replicationCheckBox->Checked) {
			Replication::MaybeRenameReplicasFolders(oldFullName, newFullName);
		}
		
		// Find and remove all audit logs for files that reside in the oldFullName.
		// Save all such items so that we can reinstroduce them when the newFullName.
		Generic::List<String^>^ oldNames = gcnew Generic::List<String^>();
		ListViewItem^ item = FindListViewItem(auditListView, oldRelativeName, true);
		while (nullptr != item) {
			oldNames->Add(item->Text);
			auditListView->Items->Remove(item);
			item = FindListViewItem(auditListView, oldRelativeName, true);
		}

		// Now add all the audit logs back, but replacing the old folder
		// name with the new one.
		String^ newRelativeName = StarfieldData::GetRelativeName(newFullName);
		Generic::IEnumerator<String^>^ iter = oldNames->GetEnumerator();
		while (iter->MoveNext()) {
			String^ newAuditName = newRelativeName + iter->Current->Substring(oldRelativeName->Length);
			auditListView->Items->Add(gcnew ListViewItem(newAuditName));
			auditListView->AutoResizeColumns(ColumnHeaderAutoResizeStyle::ColumnContent);
		}
	}
	/**
	* Determines whether a given file should be added to the audit log.
	* @param fullname - The full name of the file in question
	* @return true if the file should be added to the audit log, false otherwise
	*/
	private: bool ShouldLog(String^ fullname) {
		if (NORMAL_FILE != Util::ClassifyFile(fullname)) {
			return false;
		}

		// Ignore any file not under the Starfield Data folders
		if (!StarfieldData::FileResidesWithinStarfieldDataFolder(fullname)) {
			return false;
		}

		// Ignore files whose extensions are in the configured audit filter list
		array<String^>^ filters = AuditFilterDialog::singleton->GetFilters();
		for (int i = 0; i < filters->Length; i++) {
			if (Util::HasSuffix(fullname, filters[i])) {
				return false;
			}
		}

		// Also the WISE.DAT & TEMP.WEM files that are generated by WWise.
		// Ignore the MOTDImage as it could have been changed by something else.
		// And anything inside of Starfield's Data\Backup folder.
		if (Util::HasSuffix(fullname, L"\\TEMP.WEM") ||
			Util::HasSuffix(fullname, L"\\WWISE.DAT") ||
			Util::HasSuffix(fullname, L"\\MOTDIMAGE.PNG") ||
			Util::HasPrefix(fullname, StarfieldData::starfieldBackupPrefix)) {
			return false;
		}

		// Ignore any files related to voice localization - only the
		// 'native-language' files are recorded in the audit log
		if (PackDialog::isLocalizationFile(fullname)) {
			return false;
		}

		// The WWise tool will process *all* WAV files anywhere in one's installation tree
		// irrespective of whether they are part of the current plugin or not.  Filter out
		// any files that appear to reside in a plugin-specific directory other than the
		// one currently selected.
		return StarfieldData::FileRelatedToPlugIn(fullname, pluginComboBox->Text);
	}
	/**
	* Checks to see if a given relative file name is already in the audit log
	* @param relativeName - The relative name of the file to check
	* @return true if the file is already in the audit log, false otherwise
	*/
	private: bool AuditFileAlreadyPresent(String^ relativeName) {
		Collections::IEnumerator^ iter = auditListView->Items->GetEnumerator();
		while (iter->MoveNext()) {
			if (0 == String::Compare(relativeName, (cli::safe_cast<ListViewItem^>(iter->Current))->Text, true)) {
				return true;
			}
		}
		return false;
	}
	/**
	* Moves a control in its parent window
	* @param control - The control to move
	* @param deltaX - The amount to move left-right
	* @param deltaY - The amount to move up-down
	*/
	private: System::Void MoveControl(Control^ control, int deltaX, int deltaY) {
		control->Left += deltaX;
		control->Top += deltaY;
	}
	/**
	* Creates an empty manifest file for the indicated plugin, if it does not
	* already have a manifest file.
	* @param plugin - The plugin to register
	* @return true if everything worked, false otherwise
	*/
	private: bool RegisterPlugInIfNeeded(String^ plugin) {
		String^ manifestFile = userGamePrefix + plugin + manifestFileExt;
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
			MessageBox::Show(this,
				L"Unable to create manifest file " + manifestFile + L": " + e->Message,
				L"Manifest File Creation Error",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
			return false;
		}
		return true;
	}
	/**
	* Reads the manifest file for a given plugin and uses it to repopulate
	* the audit log.
	* @param plugin - The plugin whose manifest should be read
	*/
    private: System::Void LoadManifest(String^ plugin) {
		String^ manifestFile = userGamePrefix + plugin + manifestFileExt;
		try {
			array<String^>^ lines = File::ReadAllLines(manifestFile);
			for (int i = 0; i < lines->Length; i++) {
				// Older versions tried to track both the PC and XBox files
				// separately. In the new version, the XBox files are
				// implied by the PC files and are not explicitly tracked
				// in the manifest.  So we have to filter out any obsolete
				// audit logs related to XBox files.
				if (!Util::HasPrefix(lines[i], StarfieldData::starfieldXBoxRelativePrefix)) {
					auditListView->Items->Add(gcnew ListViewItem(lines[i]));
				}
			}
			auditListView->AutoResizeColumns(ColumnHeaderAutoResizeStyle::ColumnContent);
		} catch (Exception^ e) {
			MessageBox::Show(this,
				L"Error while reading " + manifestFile + L": " + e->Message,
				L"Manifest Read Error",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
		}
    }
	/**
	* Writes the current audit log to the manifest file for the indicated plugin.
	* @param plugin - The plugin whose manifest file should written
	*/
	private: System::Void WriteManifest(String^ plugin) {
		// If we are not bound to a specific plugin, do not write a manifest
		if (!plugin->Equals(autodetectPluginName)) {
			String^ manifestFile = userGamePrefix + plugin + manifestFileExt;
			Collections::IEnumerator^ iter = auditListView->Items->GetEnumerator();
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
	/**
	* Generate a list of all plugins that have manifest files in the
	* Documents\My Games\Starfield\CreationKitAuditTool folder and
	* use it to repopulate the pluginComboBox.
	*/
	private: System::Void PopluatePlugInChoices() {
		try {
			// Remember the current setting of the PlugIn Control
			String^ currentPlugIn = pluginComboBox->Text;
			bool restoreOriginalChoice = false;

			// Reset the list of choices
			pluginComboBox->Items->Clear();

			// Add the invariant <none> choice
			pluginComboBox->Items->Add(autodetectPluginName);

			Generic::IEnumerable<String^>^ enumeration = Directory::EnumerateFiles(userGameFolder, L"*" + manifestFileExt);
			Generic::IEnumerator<String^>^ iter = enumeration->GetEnumerator();
			while (iter->MoveNext()) {
				String^ filename = iter->Current->Substring(userGamePrefix->Length);
				String^ plugin = filename->Substring(0, filename->Length - manifestFileExt->Length);
				if (currentPlugIn->Equals(plugin)) {
					restoreOriginalChoice = true;
				}
				pluginComboBox->Items->Add(plugin);
			}

			// Initialize/restore the selected item
			pluginComboBox->Text = restoreOriginalChoice ? currentPlugIn : autodetectPluginName;
		}
		catch (Exception^ e) {
			MessageBox::Show(
				this,
				L"Failed to retrieve plugin manifest from the " +
				userGameFolder +
				L" folder: " +
				e->Message,
				L"Plugin Manifest Failure",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
		}
	}
};
}
