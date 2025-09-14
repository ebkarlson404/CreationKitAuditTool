#pragma once

namespace CreationKitAuditTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;
	using namespace System::IO;

	/// <summary>
	/// Summary for ArchiveErrorDialog
	/// </summary>
	public ref class ArchiveErrorDialog : public System::Windows::Forms::Form
	{
	public:
		ArchiveErrorDialog(void)
		{
			InitializeComponent();

			// Snapshot the current window size
			lastHeight = this->Height;
			lastWidth = this->Width;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ArchiveErrorDialog()
		{
			if (components)
			{
				delete components;
			}
		}

	private: int lastHeight = -1;
	private: int lastWidth = -1;
	private: String^ ArchiveName;
	private: System::Windows::Forms::ListView^ outputListView;
	private: System::Windows::Forms::Button^ clipboardButton;


	protected:

	private: System::Windows::Forms::Button^ keepButton;
	private: System::Windows::Forms::Button^ discardButton;
	private: System::Windows::Forms::Label^ label;
	private: System::Windows::Forms::ColumnHeader^ lineHeader;


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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ArchiveErrorDialog::typeid));
			this->outputListView = (gcnew System::Windows::Forms::ListView());
			this->lineHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->clipboardButton = (gcnew System::Windows::Forms::Button());
			this->keepButton = (gcnew System::Windows::Forms::Button());
			this->discardButton = (gcnew System::Windows::Forms::Button());
			this->label = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// outputListView
			// 
			this->outputListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) { this->lineHeader });
			this->outputListView->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::None;
			this->outputListView->HideSelection = false;
			this->outputListView->Location = System::Drawing::Point(10, 58);
			this->outputListView->Name = L"outputListView";
			this->outputListView->ShowGroups = false;
			this->outputListView->Size = System::Drawing::Size(845, 510);
			this->outputListView->TabIndex = 0;
			this->outputListView->UseCompatibleStateImageBehavior = false;
			this->outputListView->View = System::Windows::Forms::View::Details;
			// 
			// lineHeader
			// 
			this->lineHeader->Text = L"Line";
			this->lineHeader->Width = 841;
			// 
			// clipboardButton
			// 
			this->clipboardButton->Location = System::Drawing::Point(10, 593);
			this->clipboardButton->Name = L"clipboardButton";
			this->clipboardButton->Size = System::Drawing::Size(188, 46);
			this->clipboardButton->TabIndex = 1;
			this->clipboardButton->Text = L"&Copy to Clipboard";
			this->clipboardButton->UseVisualStyleBackColor = true;
			this->clipboardButton->Click += gcnew System::EventHandler(this, &ArchiveErrorDialog::clipboardButton_Click);
			// 
			// keepButton
			// 
			this->keepButton->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->keepButton->Location = System::Drawing::Point(428, 593);
			this->keepButton->Name = L"keepButton";
			this->keepButton->Size = System::Drawing::Size(188, 46);
			this->keepButton->TabIndex = 2;
			this->keepButton->Text = L"&Keep Archive";
			this->keepButton->UseVisualStyleBackColor = true;
			this->keepButton->Click += gcnew System::EventHandler(this, &ArchiveErrorDialog::keepButton_Click);
			// 
			// discardButton
			// 
			this->discardButton->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->discardButton->Location = System::Drawing::Point(666, 593);
			this->discardButton->Name = L"discardButton";
			this->discardButton->Size = System::Drawing::Size(188, 46);
			this->discardButton->TabIndex = 3;
			this->discardButton->Text = L"&Discard Archive";
			this->discardButton->UseVisualStyleBackColor = true;
			this->discardButton->Click += gcnew System::EventHandler(this, &ArchiveErrorDialog::discardButton_Click);
			// 
			// label
			// 
			this->label->AutoSize = true;
			this->label->Location = System::Drawing::Point(85, 16);
			this->label->Name = L"label";
			this->label->Size = System::Drawing::Size(636, 25);
			this->label->TabIndex = 4;
			this->label->Text = L"Errors were reported during archive packing - archive may be incomplete";
			// 
			// ArchiveErrorDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(866, 661);
			this->ControlBox = false;
			this->Controls->Add(this->label);
			this->Controls->Add(this->discardButton);
			this->Controls->Add(this->keepButton);
			this->Controls->Add(this->clipboardButton);
			this->Controls->Add(this->outputListView);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(890, 725);
			this->Name = L"ArchiveErrorDialog";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Archive Packing Error";
			this->Layout += gcnew System::Windows::Forms::LayoutEventHandler(this, &ArchiveErrorDialog::ArchiveErrorDialog_Layout);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void clipboardButton_Click(System::Object^ sender, System::EventArgs^ e) {
		StringBuilder builder;
		Collections::IEnumerator^ iter = outputListView->Items->GetEnumerator();
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
			L"Archive Log copied to the system clipboard.",
			L"Action Confirmation",
			MessageBoxButtons::OK,
			MessageBoxIcon::Information);
	}
	private: System::Void keepButton_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void discardButton_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			File::Delete(this->ArchiveName);
		}
		catch (Exception^) {
			// Ignore
		}
		this->Close();
	}
	private: System::Void ArchiveErrorDialog_Layout(System::Object^ sender, System::Windows::Forms::LayoutEventArgs^ e) {
		// Do nothing if we are minimized
		if (this->WindowState == FormWindowState::Minimized) {
			return;
		}

		// If we've not recorded the previous window size yet, do nothing
		if (lastHeight == -1 || lastWidth == -1) {
			return;
		}

		// Compute the change in size and use it to move/resize components
		int deltaHeight = Height - lastHeight;
		int deltaWidth = Width - lastWidth;

		outputListView->Width += deltaWidth;
		outputListView->Height += deltaHeight;
		label->Left = outputListView->Left + (outputListView->Width - label->Width) / 2;
	    clipboardButton->Top += deltaHeight;
		keepButton->Top += deltaHeight;
		keepButton->Left += deltaWidth;
		discardButton->Top += deltaHeight;
		discardButton->Left += deltaWidth;

		// Record the new window size
		lastHeight = Height;
		lastWidth = Width;
	}
	public: Windows::Forms::DialogResult Run(
		String^ archiveName, Generic::List<String^>^ output, IWin32Window^ parent) {
		this->ArchiveName = archiveName;
		this->Text = Path::GetFileName(archiveName) + L": Archive Creation Failure";
		outputListView->Items->Clear();
		Generic::List<String^>::Enumerator iter = output->GetEnumerator();
		while (iter.MoveNext()) {
			outputListView->Items->Add(iter.Current);
		}
		outputListView->AutoResizeColumns(ColumnHeaderAutoResizeStyle::ColumnContent);
		return this->ShowDialog(parent);
	}
};
}
