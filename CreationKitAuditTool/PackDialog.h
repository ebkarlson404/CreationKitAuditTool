#pragma once

#include "ArchiveDialog.h"
#include "LanguageDialog.h"
#include "PackingTask.h"
#include "Replication.h"
#include "StarfieldData.h"

namespace CreationKitAuditTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for PackForm
	/// </summary>
	public ref class PackDialog : public System::Windows::Forms::Form
	{
	public:
		PackDialog(void)
		{
			InitializeComponent();
			languageListView->AutoResizeColumns(ColumnHeaderAutoResizeStyle::ColumnContent);

			// Build the map of ISO699 language codes to combo box strings
			if (LanguageMap->Count == 0) {
				LanguageMap->Add(L"zhhans", L"Chinese (simplified) - zhhans");
				LanguageMap->Add(L"en", L"English - en");
				LanguageMap->Add(L"fr", L"French - fr");
				LanguageMap->Add(L"de", L"German - de");
				LanguageMap->Add(L"it", L"Italian - it");
				LanguageMap->Add(L"ja", L"Japanese - ja");
				LanguageMap->Add(L"pl", L"Polish - pl");
				LanguageMap->Add(L"ptbr", L"Portugese (Brazil) - ptbr");
				LanguageMap->Add(L"es", L"Spanish (Spain) - es");
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~PackDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	protected:

	private: System::Windows::Forms::GroupBox^ pluginTypeGroupBox;
	private: System::Windows::Forms::RadioButton^ voiceOnlyRadioButton;
	private: System::Windows::Forms::RadioButton^ textOnlyRadioButton;
	private: System::Windows::Forms::RadioButton^ nonlocalizedRadioButton;
	private: System::Windows::Forms::Button^ doneButton;
	private: System::Windows::Forms::Button^ packButton;
	private: System::Windows::Forms::RadioButton^ bothRadioButton;
	private: System::Windows::Forms::ContextMenuStrip^ contextMenuStrip;
	private: System::Windows::Forms::ToolStrip^ toolStrip;
	private: System::Windows::Forms::ToolTip^ toolTip;
	private: System::Windows::Forms::GroupBox^ voiceLocalizationGroupBox;
	private: System::Windows::Forms::Button^ setPrimaryButton;

	private: System::Windows::Forms::Button^ stageButton;

	private: System::ComponentModel::IContainer^ components;

	protected:

	private: String^ plugin;
	private: ListView^ auditLog;
	private: bool hasTextLocalization;
	private: bool hasVoiceLocalization;
	private: String^ primaryLanguage;
	public: static String^ primaryLanguageMarker = L".plang";
	public: static String^ secondaryLanguageMarker = L".slang";
	private: LanguageDialog^ languageDialog = gcnew LanguageDialog;
	private: ArchiveDialog^ archiveDialog = gcnew ArchiveDialog;
	private: String^ espPluginFolder;
	private: String^ espPluginRelativePrefix;



	private: System::Windows::Forms::ListView^ languageListView;
	private: System::Windows::Forms::ColumnHeader^ supportedHeader;
	private: System::Windows::Forms::ColumnHeader^ nameHeader;
	private: System::Windows::Forms::Label^ label2;

	public:
	protected: static Dictionary<String^, String^>^ LanguageMap =
		gcnew Dictionary<String^, String^>;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::ListViewItem^ listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {
				L"zhhans",
					L"Chinese (simplified)"
			}, -1));
			System::Windows::Forms::ListViewItem^ listViewItem2 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {
				L"en",
					L"English"
			}, -1));
			System::Windows::Forms::ListViewItem^ listViewItem3 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {
				L"fr",
					L"French"
			}, -1));
			System::Windows::Forms::ListViewItem^ listViewItem4 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {
				L"de",
					L"German"
			}, -1));
			System::Windows::Forms::ListViewItem^ listViewItem5 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {
				L"it",
					L"Italian"
			}, -1));
			System::Windows::Forms::ListViewItem^ listViewItem6 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {
				L"ja",
					L"Japanese"
			}, -1));
			System::Windows::Forms::ListViewItem^ listViewItem7 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {
				L"pl",
					L"Polish"
			}, -1));
			System::Windows::Forms::ListViewItem^ listViewItem8 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {
				L"ptbr",
					L"Portugese (Brazil)"
			}, -1));
			System::Windows::Forms::ListViewItem^ listViewItem9 = (gcnew System::Windows::Forms::ListViewItem(gcnew cli::array< System::String^  >(2) {
				L"es",
					L"Spanish (Spain)"
			}, -1));
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(PackDialog::typeid));
			this->pluginTypeGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->bothRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->voiceOnlyRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->textOnlyRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->nonlocalizedRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->doneButton = (gcnew System::Windows::Forms::Button());
			this->packButton = (gcnew System::Windows::Forms::Button());
			this->toolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->setPrimaryButton = (gcnew System::Windows::Forms::Button());
			this->stageButton = (gcnew System::Windows::Forms::Button());
			this->languageListView = (gcnew System::Windows::Forms::ListView());
			this->supportedHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->nameHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->voiceLocalizationGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pluginTypeGroupBox->SuspendLayout();
			this->voiceLocalizationGroupBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// pluginTypeGroupBox
			// 
			this->pluginTypeGroupBox->Controls->Add(this->bothRadioButton);
			this->pluginTypeGroupBox->Controls->Add(this->voiceOnlyRadioButton);
			this->pluginTypeGroupBox->Controls->Add(this->textOnlyRadioButton);
			this->pluginTypeGroupBox->Controls->Add(this->nonlocalizedRadioButton);
			this->pluginTypeGroupBox->Location = System::Drawing::Point(13, 13);
			this->pluginTypeGroupBox->Name = L"pluginTypeGroupBox";
			this->pluginTypeGroupBox->Size = System::Drawing::Size(351, 206);
			this->pluginTypeGroupBox->TabIndex = 0;
			this->pluginTypeGroupBox->TabStop = false;
			this->pluginTypeGroupBox->Text = L"Plugin Type";
			// 
			// bothRadioButton
			// 
			this->bothRadioButton->AutoSize = true;
			this->bothRadioButton->Location = System::Drawing::Point(30, 153);
			this->bothRadioButton->Name = L"bothRadioButton";
			this->bothRadioButton->Size = System::Drawing::Size(277, 29);
			this->bothRadioButton->TabIndex = 3;
			this->bothRadioButton->TabStop = true;
			this->bothRadioButton->Text = L"Text and Voice Localization";
			this->toolTip->SetToolTip(this->bothRadioButton, L"Plugin has both textual and voice localization");
			this->bothRadioButton->UseVisualStyleBackColor = true;
			// 
			// voiceOnlyRadioButton
			// 
			this->voiceOnlyRadioButton->AutoSize = true;
			this->voiceOnlyRadioButton->Location = System::Drawing::Point(30, 118);
			this->voiceOnlyRadioButton->Name = L"voiceOnlyRadioButton";
			this->voiceOnlyRadioButton->Size = System::Drawing::Size(241, 29);
			this->voiceOnlyRadioButton->TabIndex = 2;
			this->voiceOnlyRadioButton->TabStop = true;
			this->voiceOnlyRadioButton->Text = L"Voice Localization Only";
			this->toolTip->SetToolTip(this->voiceOnlyRadioButton, L"Plugin has only voice localization");
			this->voiceOnlyRadioButton->UseVisualStyleBackColor = true;
			// 
			// textOnlyRadioButton
			// 
			this->textOnlyRadioButton->AutoSize = true;
			this->textOnlyRadioButton->Location = System::Drawing::Point(30, 83);
			this->textOnlyRadioButton->Name = L"textOnlyRadioButton";
			this->textOnlyRadioButton->Size = System::Drawing::Size(230, 29);
			this->textOnlyRadioButton->TabIndex = 1;
			this->textOnlyRadioButton->TabStop = true;
			this->textOnlyRadioButton->Text = L"Text Localization Only";
			this->toolTip->SetToolTip(this->textOnlyRadioButton, L"Plugin has only textual localization");
			this->textOnlyRadioButton->UseVisualStyleBackColor = true;
			// 
			// nonlocalizedRadioButton
			// 
			this->nonlocalizedRadioButton->AutoSize = true;
			this->nonlocalizedRadioButton->Location = System::Drawing::Point(30, 48);
			this->nonlocalizedRadioButton->Name = L"nonlocalizedRadioButton";
			this->nonlocalizedRadioButton->Size = System::Drawing::Size(163, 29);
			this->nonlocalizedRadioButton->TabIndex = 0;
			this->nonlocalizedRadioButton->TabStop = true;
			this->nonlocalizedRadioButton->Text = L"Non-Localized";
			this->toolTip->SetToolTip(this->nonlocalizedRadioButton, L"Plugin has no localization");
			this->nonlocalizedRadioButton->UseVisualStyleBackColor = true;
			// 
			// doneButton
			// 
			this->doneButton->Location = System::Drawing::Point(388, 778);
			this->doneButton->Name = L"doneButton";
			this->doneButton->Size = System::Drawing::Size(153, 59);
			this->doneButton->TabIndex = 1;
			this->doneButton->Text = L"&Done";
			this->toolTip->SetToolTip(this->doneButton, L"Close this dialog");
			this->doneButton->UseVisualStyleBackColor = true;
			this->doneButton->Click += gcnew System::EventHandler(this, &PackDialog::doneButton_Click);
			// 
			// packButton
			// 
			this->packButton->Location = System::Drawing::Point(13, 778);
			this->packButton->Name = L"packButton";
			this->packButton->Size = System::Drawing::Size(153, 59);
			this->packButton->TabIndex = 2;
			this->packButton->Text = L"&Pack";
			this->toolTip->SetToolTip(this->packButton, L"Stage all Localized WEM Files and then pack all required BA2 archive files");
			this->packButton->UseVisualStyleBackColor = true;
			this->packButton->Click += gcnew System::EventHandler(this, &PackDialog::packButton_Click);
			// 
			// setPrimaryButton
			// 
			this->setPrimaryButton->Location = System::Drawing::Point(21, 465);
			this->setPrimaryButton->Name = L"setPrimaryButton";
			this->setPrimaryButton->Size = System::Drawing::Size(224, 54);
			this->setPrimaryButton->TabIndex = 2;
			this->setPrimaryButton->Text = L"Set &Primary Language";
			this->toolTip->SetToolTip(this->setPrimaryButton, L"Mark the PlugIn for Voice Localization and set the Primary Language");
			this->setPrimaryButton->UseVisualStyleBackColor = true;
			this->setPrimaryButton->Click += gcnew System::EventHandler(this, &PackDialog::setPrimaryButton_Click);
			// 
			// stageButton
			// 
			this->stageButton->Location = System::Drawing::Point(282, 465);
			this->stageButton->Name = L"stageButton";
			this->stageButton->Size = System::Drawing::Size(224, 54);
			this->stageButton->TabIndex = 3;
			this->stageButton->Text = L"&Stage WEM Files";
			this->toolTip->SetToolTip(this->stageButton, L"Stage WEM files to the Localization Staging Tree");
			this->stageButton->UseVisualStyleBackColor = true;
			this->stageButton->Click += gcnew System::EventHandler(this, &PackDialog::stageButton_Click);
			// 
			// languageListView
			// 
			this->languageListView->CheckBoxes = true;
			this->languageListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {
				this->supportedHeader,
					this->nameHeader
			});
			this->languageListView->HideSelection = false;
			listViewItem1->StateImageIndex = 0;
			listViewItem2->StateImageIndex = 0;
			listViewItem3->StateImageIndex = 0;
			listViewItem4->StateImageIndex = 0;
			listViewItem5->StateImageIndex = 0;
			listViewItem6->StateImageIndex = 0;
			listViewItem7->StateImageIndex = 0;
			listViewItem8->StateImageIndex = 0;
			listViewItem9->StateImageIndex = 0;
			this->languageListView->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(9) {
				listViewItem1, listViewItem2,
					listViewItem3, listViewItem4, listViewItem5, listViewItem6, listViewItem7, listViewItem8, listViewItem9
			});
			this->languageListView->Location = System::Drawing::Point(21, 68);
			this->languageListView->Name = L"languageListView";
			this->languageListView->Size = System::Drawing::Size(485, 364);
			this->languageListView->TabIndex = 1;
			this->toolTip->SetToolTip(this->languageListView, L"Indicate which languages are supported.  The highlighted language is the Primary "
				L"Language for the PlugIn and cannot be changed.");
			this->languageListView->UseCompatibleStateImageBehavior = false;
			this->languageListView->View = System::Windows::Forms::View::Details;
			this->languageListView->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &PackDialog::languageListView_ItemCheck);
			// 
			// supportedHeader
			// 
			this->supportedHeader->Text = L"Supported";
			this->supportedHeader->Width = 100;
			// 
			// nameHeader
			// 
			this->nameHeader->Text = L"Name";
			this->nameHeader->Width = 140;
			// 
			// voiceLocalizationGroupBox
			// 
			this->voiceLocalizationGroupBox->Controls->Add(this->label2);
			this->voiceLocalizationGroupBox->Controls->Add(this->languageListView);
			this->voiceLocalizationGroupBox->Controls->Add(this->stageButton);
			this->voiceLocalizationGroupBox->Controls->Add(this->setPrimaryButton);
			this->voiceLocalizationGroupBox->Location = System::Drawing::Point(13, 225);
			this->voiceLocalizationGroupBox->Name = L"voiceLocalizationGroupBox";
			this->voiceLocalizationGroupBox->Size = System::Drawing::Size(528, 537);
			this->voiceLocalizationGroupBox->TabIndex = 3;
			this->voiceLocalizationGroupBox->TabStop = false;
			this->voiceLocalizationGroupBox->Text = L"Voice Localization";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(16, 40);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(206, 25);
			this->label2->TabIndex = 0;
			this->label2->Text = L"Supported Languages";
			// 
			// PackDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(584, 934);
			this->ControlBox = false;
			this->Controls->Add(this->voiceLocalizationGroupBox);
			this->Controls->Add(this->packButton);
			this->Controls->Add(this->doneButton);
			this->Controls->Add(this->pluginTypeGroupBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(590, 940);
			this->Name = L"PackDialog";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Localization and Packing";
			this->pluginTypeGroupBox->ResumeLayout(false);
			this->pluginTypeGroupBox->PerformLayout();
			this->voiceLocalizationGroupBox->ResumeLayout(false);
			this->voiceLocalizationGroupBox->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

	//
	// Event Handlers
	//
	private: System::Void doneButton_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void setPrimaryButton_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			if (languageDialog->Run(this)) {
				if (CreateMarkerFile(primaryLanguage + primaryLanguageMarker)) {
					primaryLanguage = languageDialog->Language;
					hasVoiceLocalization = true;
					setPrimaryButton->Enabled = false;
					stageButton->Enabled = true;
					InitializePluginRadioButtons();
					InitializeLanguageList();
				}
			}
		}
		catch (Exception^) {
			// This should never happen - silently swallow anything that gets through
		}
	}
	private: System::Void stageButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (StageLocalizedWEMFiles()) {
			MessageBox::Show(
				this,
				L"Localized Voice Files staged to the " +
				StarfieldData::localizationFolder +
				L" directory tree.",
				L"Staging Confirmation",
				MessageBoxButtons::OK,
				MessageBoxIcon::Information);
		}
		else {
			MessageBox::Show(
				this,
				L"Staging of localized Voice Files failed.",
				L"Staging Failure",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
		}
	}
	private: System::Void packButton_Click(System::Object^ sender, System::EventArgs^ e) {
		// Start by staging the files from the ESP folders to the Localization tree
		if (!StageLocalizedWEMFiles()) {
			MessageBox::Show(
				this,
				L"Staging operation failed - packaging abort.",
				L"Pack Operation Failure",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
			return;
		}

		// Now compute and execute all the packing tasks which will also replicate
		// files from ESP folders to their corresponding ESM folders.
		ComputeAndExecutePackingTasks();
	}
	private: System::Void languageListView_ItemCheck(System::Object^ sender, System::Windows::Forms::ItemCheckEventArgs^ e) {
		ListViewItem^ item = languageListView->Items[e->Index];
		if (nullptr != item->Tag) {
			e->NewValue = CheckState::Checked;
			item->Focused = false;
		}
		else if (e->CurrentValue == CheckState::Checked) {
			if (!RemoveMarkerFile(item->Text + secondaryLanguageMarker)) {
				e->NewValue = CheckState::Checked;
			}
		}
		else if (!CreateMarkerFile(item->Text + secondaryLanguageMarker)) {
			e->NewValue = CheckState::Unchecked;
		}
	}
	//
    // Utility methods
    //
	public: System::Void Initialize(String^ plugin, ListView^ auditLog) {
		this->Text = plugin + L": Localization and Packing";
		this->plugin = plugin;
		this->auditLog = auditLog;
		this->primaryLanguage = nullptr;
		this->espPluginFolder = StarfieldData::starfieldVoicePrefix + plugin + L".esp";
		this->espPluginRelativePrefix = StarfieldData::GetRelativeName(espPluginFolder) + L"\\";

		// Force creation of the ESP folder if we don't have one already
		Directory::CreateDirectory(espPluginFolder);

		// Does this plugin have any string translation files?
		Generic::IEnumerator<String^>^ iter =
			Directory::EnumerateFiles(StarfieldData::starfieldDataPrefix + L"Strings",
				plugin + L"*.*")->GetEnumerator();
		hasTextLocalization = iter->MoveNext();

		// Does this plugin have a voice localization marker?
		// Search for a <lang>.plang marker file
		iter = Directory::EnumerateFiles(espPluginFolder, L"*" + primaryLanguageMarker)->GetEnumerator();
		hasVoiceLocalization = iter->MoveNext();
		if (hasVoiceLocalization) {
			primaryLanguage = Path::GetFileNameWithoutExtension(iter->Current);
		}

		// Set the proper radio button
		InitializePluginRadioButtons();

		// Set the state of the voice localization buttons
		setPrimaryButton->Enabled = !hasVoiceLocalization;
		stageButton->Enabled = hasVoiceLocalization;

		// Set the active language
		InitializeLanguageList();
	}
	private: System::Void InitializePluginRadioButtons() {
		if (hasVoiceLocalization) {
			nonlocalizedRadioButton->Enabled = false;
			textOnlyRadioButton->Enabled = false;
			bothRadioButton->Enabled = true;
			bothRadioButton->Checked = hasTextLocalization;
			voiceOnlyRadioButton->Enabled = true;
			voiceOnlyRadioButton->Checked = !hasTextLocalization;
		}
		else {
			voiceOnlyRadioButton->Enabled = false;
			bothRadioButton->Enabled = false;
			textOnlyRadioButton->Enabled = true;
			textOnlyRadioButton->Checked = hasTextLocalization;
			nonlocalizedRadioButton->Enabled = true;
			nonlocalizedRadioButton->Checked = !hasTextLocalization;
		}
	}
	private: System::Void InitializeLanguageList() {
		Collections::IEnumerator^ iter;
		if (nullptr == primaryLanguage) {
			languageListView->Enabled = false;
			for (iter = languageListView->Items->GetEnumerator(); iter->MoveNext();	) {
				ListViewItem^ item = cli::safe_cast<ListViewItem^>(iter->Current);
				item->Tag = nullptr;
				item->ToolTipText = nullptr;
				item->Checked = false;
				item->BackColor = languageListView->BackColor;
			}
		}
		else {
			languageListView->Enabled = true;
			ListViewItem^ primary = languageListView->FindItemWithText(primaryLanguage);
			if (nullptr != primary) {
				primary->Tag = L"tag";
				primary->Checked = true;
				primary->BackColor = Color::LightGreen;
			}
			for (iter = languageListView->Items->GetEnumerator(); iter->MoveNext(); ) {
				ListViewItem^ item = cli::safe_cast<ListViewItem^>(iter->Current);
				if (item != primary) {
					item->Tag = nullptr;
					item->Checked = File::Exists(espPluginFolder + L"\\" + item->Text + secondaryLanguageMarker);
					item->BackColor = languageListView->BackColor;
				}
			}
		}
	}
	/**
	* Find and stage all localized voice files in the current audit log
	* @returns true if everything worked, false otherwise
	*/
	private: bool StageLocalizedWEMFiles() {
		try {
			Collections::IEnumerator^ iter = languageListView->Items->GetEnumerator();
			while (iter->MoveNext()) {
				ListViewItem^ item = cli::safe_cast<ListViewItem^>(iter->Current);
				if (item->Checked) {
					StageWEMFilesForLanguage(item->Text, nullptr != item->Tag);
				}
			}
		}
		catch (AbortException^) {
			// User abort - fall through
		}
		catch (Exception^ e) {
			MessageBox::Show(
				this,
				L"Stage operation failed: " + e->Message,
				L"Stage Operation Failure",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
			return false;
		}
		return true;
	}
	/**
	* Finds and stages all voice files in the current audit log localized
	* for a given language.
	* @param lang - The language to stage
	* @param isPrimaryLang - Indicates whether the language is the 'Primary Language'
	* for the plugin
	* @throws AbortException if something went wrong and the user choose to abort
	* the operation
	*/
	private: System::Void StageWEMFilesForLanguage(String^ lang, bool isPrimaryLang) {
		// Find all WEM files in the audit log
		// For each such file, find the localized file and replicate it
		// into the Localization Working directory tree.
		Collections::IEnumerator^ iter = auditLog->Items->GetEnumerator();
		while (iter->MoveNext()) {
			ListViewItem^ item = cli::safe_cast<ListViewItem^>(iter->Current);
			if (Util::HasPrefix(item->Text, espPluginRelativePrefix) &&
				Util::HasSuffix(item->Text, L".WEM")) {

				// Get the localized vesion of the base file
				String^ localizedName = LocalizeWEMFilename(item->Text, lang, isPrimaryLang);

				// Stage the PC version of the WEM file
				StageLocalizedWEMFile(localizedName, lang, false);

				// Stage the XBox version of the WEM file
				StageLocalizedWEMFile(
					StarfieldData::starfieldXBoxRelativePrefix + localizedName, lang, true);
			}
		}
	}
	/**
	* Stages a localized file in the plugin's ESP folder to the language-appropriate
	* location in the Localized Staging directory tree.
	* @param espRelativeName - The relative name of the file in the ESP folder
	* @param lang - The language to use for staging
	* @param isXBox - Indicates that the file is for the XBox platform
	* @throw AbortException if something goes wrong and the user chooses to
	* abort the operation
	*/
	private: System::Void StageLocalizedWEMFile(String^ espRelativeName, String^ lang, bool isXBox) {
		Forms::DialogResult status = Forms::DialogResult::Retry;
		while (status == Forms::DialogResult::Retry) {
			String^ targetName = espToLocalEsmNameTransform(espRelativeName, lang, isXBox);
			try {
				Directory::CreateDirectory(Path::GetDirectoryName(targetName));
				File::Copy(StarfieldData::starfieldPrefix + espRelativeName, targetName, true);
				status = Forms::DialogResult::OK;
			}
			catch (Exception^ e) {
				status = MessageBox::Show(
					this,
					L"Unable to stage localized WEM file " + espRelativeName +	L" to " +
					lang + L" staging area : " + e->Message,
					L"Staging Failure",
					MessageBoxButtons::AbortRetryIgnore,
					MessageBoxIcon::Error);
				if (status == Forms::DialogResult::Abort) {
					throw gcnew AbortException(L"User aborted staging operation", e);
				}
			}
		}
	}
	private: String^ DelocalizeWEMFilename(String^ basename) {
		int pos = basename->IndexOf(L"_");
		return (0 > pos) ?
			basename :
			basename->Substring(0, pos) + Path::GetExtension(basename);
	}
	private: String^ LocalizeWEMFilename(String^ filename, String^ lang, bool isPrimary) {
		return isPrimary ?
			filename :
			Path::GetDirectoryName(filename) + L"\\" + Path::GetFileNameWithoutExtension(filename) +
			L"_" + lang + Path::GetExtension(filename);
	}
	/**
	* Converts relative name of a file that resides within this plugin's ESP folder
	* to its corresponding Localization Staged name.
	* @param espRelativeName - The name of the file to be transformed
	* @param lang - The language to use for staging
	* @param isXBox - Indicates if this should be staged to the XBox tree
	* @return The full name to use for staging the file to the localization tree
	*/
	private: String^ espToLocalEsmNameTransform(String^ relativeName, String^ lang, bool isXBox) {
		String^ filename =
			DelocalizeWEMFilename(Path::GetFileNameWithoutExtension(relativeName)) +
			Path::GetExtension(relativeName);
		int pos = relativeName->IndexOf(L"\\" + plugin + L".esp\\", StringComparison::InvariantCultureIgnoreCase);
		String^ espRelativePath = Path::GetDirectoryName(relativeName->Substring(pos + plugin->Length + 6));
		String^ localizedEsmPrefix =
			StarfieldData::localizationPrefix + (isXBox ? L"XBOX\\" : L"") +
			lang + L"\\Data\\Sound\\Voice\\" + plugin + L".esm\\";
		return localizedEsmPrefix + espRelativePath + L"\\" + filename;
	}
	/**
	* Adds the indicated marker file to the plugin's ESP folder.
	* @param name - The name of the marker file
	* @return true if the marker was added, false otherwise
	*/
	private: bool CreateMarkerFile(String^ name) {
		String^ fullname = espPluginFolder + L"\\" + name;
		Forms::DialogResult status = Forms::DialogResult::Retry;
		while (status == Forms::DialogResult::Retry) {
			try {
				File::WriteAllText(fullname, L"Marker file created by CreationKitAuditTool");
				status = Forms::DialogResult::OK;
			}
			catch (Exception^ e) {
				status = MessageBox::Show(
					this,
					L"Failed to create marker file " + fullname + L": " + e->Message,
					L"Marker File Creation Error",
					MessageBoxButtons::AbortRetryIgnore,
					MessageBoxIcon::Error);
				if (status == Forms::DialogResult::Abort) {
					return false;
				}
			}
		}
		return status == Forms::DialogResult::OK;
    }
	/**
	* Removes the indicated marker file from the plugin's ESP folder.
	* @param name - The name of the marker file
	* @return true if the marker was removed, false otherwise
	*/
	private: bool RemoveMarkerFile(String^ name) {
		String^ fullname = espPluginFolder + L"\\" + name;
		Forms::DialogResult status = Forms::DialogResult::Retry;
		while (status == Forms::DialogResult::Retry) {
			try {
				File::Delete(fullname);
				status = Forms::DialogResult::OK;
			}
			catch (FileNotFoundException^) {
				// Apparently the marker file is already gone
				status = Forms::DialogResult::OK;
			}
			catch (Exception^ e) {
				status = MessageBox::Show(
					this,
					L"Failed to delete marker file " + fullname + L": " + e->Message,
					L"Marker File Removal Error",
					MessageBoxButtons::AbortRetryIgnore,
					MessageBoxIcon::Error);
				if (status == Forms::DialogResult::Abort) {
					return false;
				}
			}
		}
		return status == Forms::DialogResult::OK;
	}
	/**
	* Checks to see if the file is part of the localization metadata that is
	* used to track plugin localization.
	* @param relativeName - The relative name of the file to check
	* @return true if the file is part of the localization metadata, false otherwise
	*/
	public: static bool isLocalizationMetadata(String^ relativeName) {
		// Check for the language markers
		return Util::HasSuffix(relativeName, L".PLANG") || Util::HasSuffix(relativeName, L".SLANG");
	}
	/**
	* Checks to see if a file is part of the localization system.  Primarilly
	* used by the audit log to exclude localized files from the manifest.
	* @param espRelativeName - The data-relative name of the file to check
	* @returns true if it is part of the localization system, false otherwise
	*/
	public: static bool isLocalizationFile(String^ relativeName) {
		// Check for localization metadata files
		// Check to see if the file resides within some ESP/ESM folder
		// and has a known "_<lang>" annotation on the filename
		if (isLocalizationMetadata(relativeName)) {
			return true;
		}
		if (!Util::HasSuffix(relativeName, L".WEM")) {
			return false;
		}
		if (0 > relativeName->IndexOf(L".ESP\\", StringComparison::InvariantCultureIgnoreCase)) {
			return false;
		}
		if (0 > relativeName->IndexOf(L".ESM\\", StringComparison::InvariantCultureIgnoreCase)) {
			return false;
		}
		Dictionary<String^,String^>::Enumerator iter = LanguageMap->GetEnumerator();
		while (iter.MoveNext()) {
			if (Util::HasSuffix(relativeName, L"_" + iter.Current.Key + L".WEM")) {
				return true;
			}
		}
		return false;
	}
	private: System::Void ComputeAndExecutePackingTasks() {
		// Construct PackingTasks for all possible BA2 archives that might be created
		PackingTask^ mainPC = gcnew PackingTask(false, false, gcnew List<String^>(), plugin + L" - Main.ba2");
		PackingTask^ mainXB = gcnew PackingTask(false, true, gcnew List<String^>(), plugin + L" - Main_xbox.ba2");
		PackingTask^ texturesPC = gcnew PackingTask(true, false, gcnew List<String^>(), plugin + L" - Textures.ba2");
		PackingTask^ texturesXB = gcnew PackingTask(true, true, gcnew List<String^>(), plugin + L" - Textures_xbox.ba2");
		Dictionary<String^, PackingTask^>^ voicesPC = gcnew Dictionary<String^, PackingTask^>();
		Dictionary<String^, PackingTask^>^ voicesXB = gcnew Dictionary<String^, PackingTask^>();

		try {
			// Iterate through all files in the audit log sort them into the appropriate
			// PackingTask.  For each discovered PC also pack the corresponding XBox file.
			Collections::IEnumerator^ iter = auditLog->Items->GetEnumerator();
			while (iter->MoveNext()) {
				ListViewItem^ item = safe_cast<ListViewItem^>(iter->Current);
				ReplicateAndCollateFile(item->Text, mainPC, mainXB, texturesPC, texturesXB, voicesPC, voicesXB);
			}

			// Now that we've marshalled the file lists for all BA2 archive files,
			// run the Archive2.exe tool to generate the files.
			archiveDialog->Run(plugin, mainPC, mainXB, texturesPC, texturesXB, voicesPC, voicesXB, this);
		}
		catch (AbortException^) {
			MessageBox::Show(
				this,
				L"Packing operation aborted at user's request.",
				L"Packing Operation Aborted",
				MessageBoxButtons::OK,
				MessageBoxIcon::Warning);
		}
	}
	/**
	* Given the relative name of a file in the plugin's ESP folder, replicate
	* that file, any XBox derivations of the file and all localized variants of
	* that file, to their corresponding ESM folders and then add the replicated
	* files to the appropriate PackingTasks.
	* @param espRelativeName - The relative name of the ESP data file
	* @param mainPC - The PackingTask for the Main PC archive
	* @param mainXB - The PackingTask for the Main XBox archive
	* @param texturesPC - The PackingTask for the Textures PC archive
	* @param texturesXB - The PackingTask for the Textures XBox archive
	* @param voicesPC - A Dictionary containing all known localized PC PackingTasks
	* @param voicesXB - A Dictionary containing all known localized XBox PackingTasks
	* @return true if everything worked, false if there were failures but the user
	* choose to ignore them
	* @throws AbortException if there were failures and the user choose to abort
	* the operation
	*/
	private: bool ReplicateAndCollateFile(
		String^ espRelativeName,
		PackingTask^ mainPC,
		PackingTask^ mainXB,
		PackingTask^ texturesPC,
		PackingTask^ texturesXB,
		Dictionary<String^, PackingTask^>^ voicesPC,
		Dictionary<String^, PackingTask^>^ voicesXB) {

		// Replicate to the ESM folder if needed
		String^ esmRelativeName = Replication::EspToEsmReplication(espRelativeName, this);
		if (nullptr == esmRelativeName) {
			return false;
		}

		// Add the file to the appropriate PackingTasks
		if (Util::HasSuffix(esmRelativeName, L".DDS")) {
			texturesPC->Files->Add(esmRelativeName);
			String^ xbEsmRelativeName = GetXBoxEsmRelativeName(espRelativeName);
			if (nullptr == xbEsmRelativeName) {
				return false;
			}
			texturesXB->Files->Add(xbEsmRelativeName);
		}
		else if (Util::HasSuffix(esmRelativeName, L".WEM")) {
			if (hasVoiceLocalization) {
				PackLocalizedWEMFiles(espRelativeName, voicesPC, voicesXB);
			}
			else {
				mainPC->Files->Add(esmRelativeName);
				String^ xbEsmRelativeName = GetXBoxEsmRelativeName(espRelativeName);
				if (nullptr == xbEsmRelativeName) {
					return false;
				}
				mainXB->Files->Add(xbEsmRelativeName);
			}
		}
		else {
			mainPC->Files->Add(esmRelativeName);
			mainXB->Files->Add(esmRelativeName);
		}
		return true;
	}
	/**
	* Given the ESP-Relative name of a PC-encoded WEM file, find the corresponding
	* XBox derived WEM file, replicate that file to the XBox ESM folder and
	* return the name of the XBox ESM-Relative WEM file.
	* @param pcEspRelativeName - The ESP-Relative name of the PC-encoded WEM file
	* @return The ESM-Relative name of the XBox-encoded WEM file or nullptr if
	* the replication failed and the user choose to ignore the problem
	* @throws AbortException - If the user aborted the replication
	*/
	private: String^ GetXBoxEsmRelativeName(String^ pcEspRelativeName) {
		String^ xbEspRelativeName = StarfieldData::starfieldXBoxRelativePrefix + pcEspRelativeName;
		return Replication::EspToEsmReplication(xbEspRelativeName, this);
	}
	/**
	* Given a 'native-language' WEM file, add the 'native-language' WEM and all
	* localized variants to the appropriate PackingTasks.
	* @param espRelativeName - The ESP-Relative name of the 'native-language' WEM file
	* @param voicesPC - A Dictionary containing all known localized PC PackingTask's
	* @param voicesXB - A Dictionary containing all known localized XBox PackingTask's
	*/
	private: System::Void PackLocalizedWEMFiles(
		String^ espRelativeName,
		Dictionary<String^, PackingTask^>^ voicesPC,
		Dictionary<String^, PackingTask^>^ voicesXB) {

		// Find every localized set of voice files and pack them into their
		// individual packing tasks
		Collections::IEnumerator^ iter = languageListView->Items->GetEnumerator();
		while (iter->MoveNext()) {
			ListViewItem^ item = cli::safe_cast<ListViewItem^>(iter->Current);
			if (item->Checked) {
				PackLanguageWEMFile(espRelativeName, item->Text, false, voicesPC);
				PackLanguageWEMFile(espRelativeName, item->Text, true, voicesXB);
			}
		}
	}
	/**
	* Adds a localized WEM file to the appropriate PackingTask
	* @param espRelativeName - The ESP-relative name of the WEM file
	* @param lang - The language used in the WEM file
	* @param isXBox - Indicates whether the WEM file is formatted for XBox
	* @param voiceTasks - A Dictionary of all known language-specific PackingTask's
	*/
	private: System::Void PackLanguageWEMFile(
		String^ espRelativeName,
		String^ lang,
		bool isXBox,
		Dictionary<String^, PackingTask^>^ voiceTasks) {

		// Find/Create the PackingTask
		if (!voiceTasks->ContainsKey(lang)) {
			voiceTasks->Add(lang, gcnew PackingTask(isXBox, plugin, lang));
		}
		PackingTask^ task = voiceTasks[lang];

		// Map the name to the staged copy of the localized file
		String^ stagedName = espToLocalEsmNameTransform(espRelativeName, lang, isXBox);

		// Generate a data-relative name for the staged file and append the PackingTask
		String^ localRelativeName =
			L"Data\\..\\" +
			StarfieldData::localizationPrefix->Substring(StarfieldData::starfieldPrefix->Length) +
			stagedName->Substring(StarfieldData::localizationPrefix->Length);
		task->Files->Add(localRelativeName);
	}
};
}
