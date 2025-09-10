#pragma once

namespace CreationKitAuditTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
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
	private: System::Windows::Forms::GroupBox^ pluginTypeGroupBox;
	protected:
	private: System::Windows::Forms::RadioButton^ bothRadioButton;
	private: System::Windows::Forms::RadioButton^ textOnlyRadioButton;
	private: System::Windows::Forms::RadioButton^ nonlocalizedRadioButton;
	private: System::Windows::Forms::Button^ doneButton;

	protected:

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
			this->pluginTypeGroupBox = (gcnew System::Windows::Forms::GroupBox());
			this->bothRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->textOnlyRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->nonlocalizedRadioButton = (gcnew System::Windows::Forms::RadioButton());
			this->doneButton = (gcnew System::Windows::Forms::Button());
			this->pluginTypeGroupBox->SuspendLayout();
			this->SuspendLayout();
			// 
			// pluginTypeGroupBox
			// 
			this->pluginTypeGroupBox->Controls->Add(this->bothRadioButton);
			this->pluginTypeGroupBox->Controls->Add(this->textOnlyRadioButton);
			this->pluginTypeGroupBox->Controls->Add(this->nonlocalizedRadioButton);
			this->pluginTypeGroupBox->Location = System::Drawing::Point(13, 13);
			this->pluginTypeGroupBox->Name = L"pluginTypeGroupBox";
			this->pluginTypeGroupBox->Size = System::Drawing::Size(351, 166);
			this->pluginTypeGroupBox->TabIndex = 0;
			this->pluginTypeGroupBox->TabStop = false;
			this->pluginTypeGroupBox->Text = L"Plugin Type";
			// 
			// bothRadioButton
			// 
			this->bothRadioButton->AutoSize = true;
			this->bothRadioButton->Location = System::Drawing::Point(30, 118);
			this->bothRadioButton->Name = L"bothRadioButton";
			this->bothRadioButton->Size = System::Drawing::Size(300, 29);
			this->bothRadioButton->TabIndex = 2;
			this->bothRadioButton->TabStop = true;
			this->bothRadioButton->Text = L"Text and/or Voice Localization";
			this->bothRadioButton->UseVisualStyleBackColor = true;
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
			this->nonlocalizedRadioButton->UseVisualStyleBackColor = true;
			// 
			// doneButton
			// 
			this->doneButton->Location = System::Drawing::Point(558, 485);
			this->doneButton->Name = L"doneButton";
			this->doneButton->Size = System::Drawing::Size(153, 59);
			this->doneButton->TabIndex = 1;
			this->doneButton->Text = L"&Done";
			this->doneButton->UseVisualStyleBackColor = true;
			this->doneButton->Click += gcnew System::EventHandler(this, &PackDialog::doneButton_Click);
			// 
			// PackDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(749, 575);
			this->ControlBox = false;
			this->Controls->Add(this->doneButton);
			this->Controls->Add(this->pluginTypeGroupBox);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"PackDialog";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Localization and Packing";
			this->pluginTypeGroupBox->ResumeLayout(false);
			this->pluginTypeGroupBox->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void doneButton_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
};
}
