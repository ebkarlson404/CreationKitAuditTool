#pragma once

#include "PackingTask.h"
#include "Replication.h"
#include "StarfieldData.h"

namespace CreationKitAuditTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
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
			//
			//TODO: Add the constructor code here
			//
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
	private: System::Windows::Forms::Button^ bootstrapButton;
	private: System::Windows::Forms::Button^ stageButton;
	private: System::Windows::Forms::Button^ unstageButton;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::ComboBox^ languageComboBox;

	private: System::ComponentModel::IContainer^ components;

	protected:

	private: String^ defaultLanguage = L"English - en";
	private: String^ plugin;
	private: ListView^ auditLog;
	private: bool hasTextLocalization;
	private: bool hasVoiceLocalization;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pluginTypeGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->bothRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->voiceOnlyRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->textOnlyRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->nonlocalizedRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->doneButton = (gcnew System::Windows::Forms::Button());
			this->packButton = (gcnew System::Windows::Forms::Button());
			this->toolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->bootstrapButton = (gcnew System::Windows::Forms::Button());
			this->stageButton = (gcnew System::Windows::Forms::Button());
			this->unstageButton = (gcnew System::Windows::Forms::Button());
			this->languageComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->voiceLocalizationGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
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
			this->doneButton->Location = System::Drawing::Point(388, 485);
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
			this->packButton->Location = System::Drawing::Point(13, 485);
			this->packButton->Name = L"packButton";
			this->packButton->Size = System::Drawing::Size(153, 59);
			this->packButton->TabIndex = 2;
			this->packButton->Text = L"&Pack";
			this->toolTip->SetToolTip(this->packButton, L"lktasfn");
			this->packButton->UseVisualStyleBackColor = true;
			this->packButton->Click += gcnew System::EventHandler(this, &PackDialog::packButton_Click);
			// 
			// bootstrapButton
			// 
			this->bootstrapButton->Location = System::Drawing::Point(30, 82);
			this->bootstrapButton->Name = L"bootstrapButton";
			this->bootstrapButton->Size = System::Drawing::Size(146, 93);
			this->bootstrapButton->TabIndex = 1;
			this->bootstrapButton->Text = L"&Bootstrap";
			this->toolTip->SetToolTip(this->bootstrapButton, L"Initialize Voice Localization with a copy of the unlocalized voice files");
			this->bootstrapButton->UseVisualStyleBackColor = true;
			this->bootstrapButton->Click += gcnew System::EventHandler(this, &PackDialog::bootstrapButton_Click);
			// 
			// stageButton
			// 
			this->stageButton->Location = System::Drawing::Point(195, 82);
			this->stageButton->Name = L"stageButton";
			this->stageButton->Size = System::Drawing::Size(146, 93);
			this->stageButton->TabIndex = 2;
			this->stageButton->Text = L"&Stage WAV Files";
			this->toolTip->SetToolTip(this->stageButton, L"Stage WAV files from the Active Language Folder to the Starfield\\Data folder for "
				L"processing via WWise");
			this->stageButton->UseVisualStyleBackColor = true;
			this->stageButton->Click += gcnew System::EventHandler(this, &PackDialog::stageButton_Click_1);
			// 
			// unstageButton
			// 
			this->unstageButton->Location = System::Drawing::Point(361, 82);
			this->unstageButton->Name = L"unstageButton";
			this->unstageButton->Size = System::Drawing::Size(146, 93);
			this->unstageButton->TabIndex = 2;
			this->unstageButton->Text = L"&Unstage WEM Files";
			this->toolTip->SetToolTip(this->unstageButton, L"Copy WEM files from the Starfield\\Data folders to the current Language Folder");
			this->unstageButton->UseVisualStyleBackColor = true;
			this->unstageButton->Click += gcnew System::EventHandler(this, &PackDialog::unstageButton_Click);
			// 
			// languageComboBox
			// 
			this->languageComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->languageComboBox->FormattingEnabled = true;
			this->languageComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
				L"Chinese (Simplified) - zhhans", L"English - en",
					L"French - fr", L"German - de", L"Italian - it", L"Japanese - ja", L"Polish - pl", L"Portugese (Brazil) - ptbr", L"Spanish (Spain) - es"
			});
			this->languageComboBox->Location = System::Drawing::Point(225, 39);
			this->languageComboBox->Name = L"languageComboBox";
			this->languageComboBox->Size = System::Drawing::Size(282, 32);
			this->languageComboBox->TabIndex = 0;
			this->toolTip->SetToolTip(this->languageComboBox, L"Sets the language to use for Voice Localization actions");
			// 
			// voiceLocalizationGroupBox
			// 
			this->voiceLocalizationGroupBox->Controls->Add(this->languageComboBox);
			this->voiceLocalizationGroupBox->Controls->Add(this->label1);
			this->voiceLocalizationGroupBox->Controls->Add(this->unstageButton);
			this->voiceLocalizationGroupBox->Controls->Add(this->stageButton);
			this->voiceLocalizationGroupBox->Controls->Add(this->bootstrapButton);
			this->voiceLocalizationGroupBox->Location = System::Drawing::Point(13, 249);
			this->voiceLocalizationGroupBox->Name = L"voiceLocalizationGroupBox";
			this->voiceLocalizationGroupBox->Size = System::Drawing::Size(528, 192);
			this->voiceLocalizationGroupBox->TabIndex = 3;
			this->voiceLocalizationGroupBox->TabStop = false;
			this->voiceLocalizationGroupBox->Text = L"Voice Localization";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(32, 39);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(186, 25);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Language Selection";
			// 
			// PackDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(580, 604);
			this->ControlBox = false;
			this->Controls->Add(this->voiceLocalizationGroupBox);
			this->Controls->Add(this->packButton);
			this->Controls->Add(this->doneButton);
			this->Controls->Add(this->pluginTypeGroupBox);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(586, 610);
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
	private: System::Void bootstrapButton_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void stageButton_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void unstageButton_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void packButton_Click(System::Object^ sender, System::EventArgs^ e) {
		// Construct PackingTasks for all possible BA2 archives that might be created
		PackingTask^ mainPC = gcnew PackingTask(false, false, gcnew List<String^>(), plugin + L" - Main.ba2");
		PackingTask^ mainXB = gcnew PackingTask(false, true, gcnew List<String^>(), plugin + L" - Main_xbox.ba2");
		PackingTask^ texturesPC = gcnew PackingTask(true, false, gcnew List<String^>(), plugin + L" - Textures.ba2");
		PackingTask^ texturesXB = gcnew PackingTask(true, true, gcnew List<String^>(), plugin + L" - Textures_xbox.ba2");
		Dictionary<String^, PackingTask^>^ voicesPC = gcnew Dictionary<String^, PackingTask^>();
		Dictionary<String^, PackingTask^>^ voicesXB = gcnew Dictionary<String^, PackingTask^>();

		// Iterate through all files in the audit log sort them into the appropriate
		// PackingTask.  Start by marshalling all the XBox files then do a second
		// pass to find all PC and platform-neutral files.
		Dictionary<String^,bool>^ xbMap = gcnew Dictionary<String^,bool>();
		Collections::IEnumerator^ iter = auditLog->Items->GetEnumerator();
		while (iter->MoveNext()) {
			ListViewItem^ item = safe_cast<ListViewItem^>(iter->Current);
			if (Util::HasPrefix(item->Text, StarfieldData::starfieldXBoxRelativePrefix)) {
				// XBox-specific file
				xbMap->Add(item->Text->Substring(StarfieldData::starfieldXBoxRelativePrefix->Length)->ToUpper(), true);
				// Replicate to ESM folder
				String^ esmRelativeName = Replication::EspToEsmReplication(item->Text, false, this);
				// Classify as texture or non-texture
				// Classify as voice or non-voice if we have voice localization
				if (Util::HasSuffix(esmRelativeName, L".DDS")) {
					texturesXB->Files->Add(esmRelativeName);
				}
				else if (hasVoiceLocalization &&
					Util::HasPrefix(esmRelativeName, StarfieldData::starfieldXBoxRelativeVoicePrefix) &&
					Util::HasSuffix(esmRelativeName, L".WEM")) {
					if (!PackageLocalizedVoiceFile(esmRelativeName, true, voicesXB)) {
						return;
					}
				}
				else {
					mainXB->Files->Add(esmRelativeName);
				}
			}
		}

		// Now iterate through the audit log again to find the PC-specific
		// and platform-neutral files
		iter = auditLog->Items->GetEnumerator();
		while (iter->MoveNext()) {
			ListViewItem^ item = safe_cast<ListViewItem^>(iter->Current);
			if (!Util::HasPrefix(item->Text, StarfieldData::starfieldXBoxRelativePrefix)) {
				// Check to see if there is an XBox version of this file
				bool platformNeutral = !xbMap->ContainsKey(item->Text->ToUpper());
				// Replicate from ESP to ESM folder
				String^ esmRelativeName = Replication::EspToEsmReplication(item->Text, false, this);
				// Classify as txture or non-texture
				// Classify as voice or non-voice if the plugin has voice localization
				if (Util::HasSuffix(esmRelativeName, L".DDS")) {
					texturesPC->Files->Add(esmRelativeName);
					if (platformNeutral && AbortPacking(item->Text, L"Texture")) {
						return;
					}
				}
				else if (hasVoiceLocalization &&
					Util::HasPrefix(esmRelativeName, StarfieldData::starfieldRelativeVoicePrefix) &&
					Util::HasSuffix(esmRelativeName, L".WEM")) {
					if (!PackageLocalizedVoiceFile(esmRelativeName, false, voicesPC)) {
						return;
					}
				}
				else {
					mainPC->Files->Add(esmRelativeName);
					if (platformNeutral &&
						Util::HasSuffix(esmRelativeName, L".WEM") &&
						AbortPacking(item->Text, L"WEM")) {
							return;
					}
				}
			}
		}

		// Now that we've marshalled the file lists for all BA2 archive files,
		// run the Archive2.exe tool to generate the files.
		// TODO
		//archiveDialog->Run(plugin, mainPC, mainXB, texturesPC, texturesXB, voicesPC, voicesXB);
	}

	//
    // Utility methods
    //
	public: System::Void Initialize(String^ plugin, ListView^ auditLog) {
		this->Text = plugin + L": Localization and Packing";
		this->plugin = plugin;
		this->auditLog = auditLog;

		// Does this plugin have any string translation files?
		Generic::IEnumerator<String^>^ iter =
			Directory::EnumerateFiles(StarfieldData::starfieldDataPrefix + L"Strings",
				plugin + L"*.*")->GetEnumerator();
		hasTextLocalization = iter->MoveNext();

		// Does this plugin have any voice localization folders?
		String^ language;
		Generic::IEnumerator<String^>^ languageIter =
			Directory::EnumerateDirectories(StarfieldData::localizationFolder)->GetEnumerator();
		hasVoiceLocalization = false;
		while (languageIter->MoveNext() && !hasVoiceLocalization) {
			hasVoiceLocalization = Directory::Exists(languageIter->Current + L"\\Data\\Sound\\Voice\\" + plugin + L".esp");
			language = Path::GetFileName(languageIter->Current);
		}

		// Set the proper radio button
		if (hasVoiceLocalization) {
			bothRadioButton->Checked = hasTextLocalization;
			voiceOnlyRadioButton->Checked = !hasTextLocalization;
		}
		else {
			textOnlyRadioButton->Checked = hasTextLocalization;;
			nonlocalizedRadioButton->Checked = !hasTextLocalization;
		}

		// Set the state of the voice localization buttons
		bootstrapButton->Enabled = !hasVoiceLocalization;
		stageButton->Enabled = hasVoiceLocalization;
		unstageButton->Enabled = hasVoiceLocalization;

		// Set the active language
		if (nullptr == language) {
			languageComboBox->Text = defaultLanguage;
		}
		else {
			bool found = false;
			Collections::IEnumerator^ items = languageComboBox->Items->GetEnumerator();
			while (items->MoveNext() && !found) {
				String^ text = safe_cast<String^>(items->Current);
				if (text->EndsWith(L" - " + language)) {
					languageComboBox->Text = text;
					found = true;
				}
			}
			if (!found) {
				languageComboBox->Text = defaultLanguage;
			}
		}
	}
    private: bool PackageLocalizedVoiceFile(
		String^ esmRelativeName,
		bool xbox,
		Dictionary<String^,PackingTask^>^ packingJobs) {
		// Iterate through all language folders checking for localized forms
		// of the indicated voice file.  For each such file that is found,
		// replicate it to the corresponding ESM folder and add it
		// to the PackingTask for that language.
		Generic::IEnumerator<String^>^ langIter =
			Directory::EnumerateDirectories(StarfieldData::localizationFolder)->GetEnumerator();
		while (langIter->MoveNext()) {
			String^ lang = Path::GetFileName(langIter->Current);
			String^ espPath = langIter->Current +
				(xbox ? L"\\XBox\\" : L"\\Win\\") +
				L"Data\\Sound\\Voice\\" +
				plugin +
				L".esp";
			if (Directory::Exists(espPath)) {
				// Bootstrap the PackingTask if we do not have one already
				PackingTask^ task = packingJobs[lang];
				if (nullptr == task) {
					task = gcnew PackingTask(
						false,
						xbox,
						gcnew List<String^>(), 
						plugin + L" - Voices_" + lang + (xbox ? L"_xbox.ba2" : L".ba2"));
					packingJobs->Add(lang, task);
				}
				// TODO
			}
		}
		return true;
	}
	private: bool AbortPacking(String^ relativeName, String^ filetype) {
		return Windows::Forms::DialogResult::Cancel ==
			MessageBox::Show(this,
				L"PC " +
				filetype +
				L"file discovered with no corresponding XBox version: " +
				relativeName +
				L"XBox packaging is likely incomplete.\n\nPress CANCEL to abort " +
				L"archive packing, or OK to ignore.",
				L"Incomplete XBox Manifest",
				MessageBoxButtons::OKCancel,
				MessageBoxIcon::Question);
	}
};
}
