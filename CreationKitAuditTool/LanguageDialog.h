#pragma once

namespace CreationKitAuditTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for LanguageDialog
	/// </summary>
	public ref class LanguageDialog : public System::Windows::Forms::Form
	{
	public:
		LanguageDialog(void)
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
		~LanguageDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::ComboBox^ languageComboBox;
	private: System::Windows::Forms::Button^ cancelButton;
	private: System::Windows::Forms::Button^ okButton;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	public: String^ Language;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(LanguageDialog::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->languageComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->cancelButton = (gcnew System::Windows::Forms::Button());
			this->okButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(20, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(541, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Which Language was used for your non-localized voice files\?";
			// 
			// languageComboBox
			// 
			this->languageComboBox->DropDownStyle = System::Windows::Forms::ComboBoxStyle::DropDownList;
			this->languageComboBox->FormattingEnabled = true;
			this->languageComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(9) {
				L"Chinese (simplified) - zhhans", L"English - en",
					L"French - fr", L"German - de", L"Italian - it", L"Japanese - ja", L"Polish - pl", L"Portugese (Brazil) - ptbr", L"Spanish (Spain) - es"
			});
			this->languageComboBox->Location = System::Drawing::Point(25, 62);
			this->languageComboBox->Name = L"languageComboBox";
			this->languageComboBox->Size = System::Drawing::Size(536, 32);
			this->languageComboBox->TabIndex = 1;
			// 
			// cancelButton
			// 
			this->cancelButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->cancelButton->Location = System::Drawing::Point(30, 136);
			this->cancelButton->Name = L"cancelButton";
			this->cancelButton->Size = System::Drawing::Size(146, 54);
			this->cancelButton->TabIndex = 2;
			this->cancelButton->Text = L"&Cancel";
			this->cancelButton->UseVisualStyleBackColor = true;
			this->cancelButton->Click += gcnew System::EventHandler(this, &LanguageDialog::cancelButton_Click);
			// 
			// okButton
			// 
			this->okButton->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->okButton->Location = System::Drawing::Point(415, 136);
			this->okButton->Name = L"okButton";
			this->okButton->Size = System::Drawing::Size(146, 54);
			this->okButton->TabIndex = 3;
			this->okButton->Text = L"&OK";
			this->okButton->UseVisualStyleBackColor = true;
			this->okButton->Click += gcnew System::EventHandler(this, &LanguageDialog::okButton_Click);
			// 
			// LanguageDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(591, 216);
			this->ControlBox = false;
			this->Controls->Add(this->okButton);
			this->Controls->Add(this->cancelButton);
			this->Controls->Add(this->languageComboBox);
			this->Controls->Add(this->label1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(615, 280);
			this->Name = L"LanguageDialog";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Select a Language";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void cancelButton_Click(System::Object^ sender, System::EventArgs^ e) {
		Language = nullptr;
		this->Close();
	}
	private: System::Void okButton_Click(System::Object^ sender, System::EventArgs^ e) {
		int pos = languageComboBox->Text->IndexOf(L"-");
		Language = languageComboBox->Text->Substring(pos + 2);
		this->Close();
	}
    public: bool Run(IWin32Window^ parent) {
		languageComboBox->Text = L"English - en";
		ShowDialog(parent);
		return Language != nullptr;
	}
};
}
