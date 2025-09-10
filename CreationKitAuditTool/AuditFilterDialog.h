#pragma once

namespace CreationKitAuditTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Summary for AuditFilterDialog
	/// </summary>
	public ref class AuditFilterDialog : public System::Windows::Forms::Form
	{
	public:
		AuditFilterDialog(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			lastHeight = this->Height;
			lastWidth = this->Width;

			customFiltersFilename =	System::Environment::GetFolderPath(
				System::Environment::SpecialFolder::MyDocuments) +
				L"\\My Games\\Starfield\\CreationKitAuditTool\\CustomFilters.txt";;
			InitFilterList();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~AuditFilterDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	protected: int lastHeight = -1;
	protected: int lastWidth = -1;
	protected: ListViewItem^ selectedFilterItem;
	protected: String^ customFiltersFilename;
	private: System::Windows::Forms::ContextMenuStrip^ auditFilterContextMenuStrip;
	protected:
	private: System::Windows::Forms::Button^ okButton;
	private: System::Windows::Forms::Button^ addFilterButton;
	private: System::Windows::Forms::Label^ auditListLabel;
	private: System::Windows::Forms::ListView^ auditFiltersListView;
	private: System::Windows::Forms::ColumnHeader^ filterColumnHeader;
	private: System::Windows::Forms::ToolTip^ auditFilterToolTip;
	private: System::Windows::Forms::Label^ newFilterLabel;
	private: System::Windows::Forms::TextBox^ newFilterTextBox;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripRemoveMenuItem;


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
			System::Windows::Forms::ListViewItem^ listViewItem1 = (gcnew System::Windows::Forms::ListViewItem(L".achlist"));
			System::Windows::Forms::ListViewItem^ listViewItem2 = (gcnew System::Windows::Forms::ListViewItem(L".ba2"));
			System::Windows::Forms::ListViewItem^ listViewItem3 = (gcnew System::Windows::Forms::ListViewItem(L".esm"));
			System::Windows::Forms::ListViewItem^ listViewItem4 = (gcnew System::Windows::Forms::ListViewItem(L".esp"));
			System::Windows::Forms::ListViewItem^ listViewItem5 = (gcnew System::Windows::Forms::ListViewItem(L".pas"));
			System::Windows::Forms::ListViewItem^ listViewItem6 = (gcnew System::Windows::Forms::ListViewItem(L".psc"));
			System::Windows::Forms::ListViewItem^ listViewItem7 = (gcnew System::Windows::Forms::ListViewItem(L".tmp"));
			System::Windows::Forms::ListViewItem^ listViewItem8 = (gcnew System::Windows::Forms::ListViewItem(L".wav"));
			this->auditFilterContextMenuStrip = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->toolStripRemoveMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->okButton = (gcnew System::Windows::Forms::Button());
			this->addFilterButton = (gcnew System::Windows::Forms::Button());
			this->auditListLabel = (gcnew System::Windows::Forms::Label());
			this->auditFiltersListView = (gcnew System::Windows::Forms::ListView());
			this->filterColumnHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->auditFilterToolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->newFilterTextBox = (gcnew System::Windows::Forms::TextBox());
			this->newFilterLabel = (gcnew System::Windows::Forms::Label());
			this->auditFilterContextMenuStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// auditFilterContextMenuStrip
			// 
			this->auditFilterContextMenuStrip->ImageScalingSize = System::Drawing::Size(28, 28);
			this->auditFilterContextMenuStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripRemoveMenuItem });
			this->auditFilterContextMenuStrip->Name = L"auditFilterContextMenuStrip";
			this->auditFilterContextMenuStrip->Size = System::Drawing::Size(209, 40);
			// 
			// toolStripRemoveMenuItem
			// 
			this->toolStripRemoveMenuItem->Name = L"toolStripRemoveMenuItem";
			this->toolStripRemoveMenuItem->Size = System::Drawing::Size(208, 36);
			this->toolStripRemoveMenuItem->Text = L"Remove filter";
			this->toolStripRemoveMenuItem->Click += gcnew System::EventHandler(this, &AuditFilterDialog::toolStripRemoveMenuItem_Click);
			// 
			// okButton
			// 
			this->okButton->Location = System::Drawing::Point(156, 586);
			this->okButton->Name = L"okButton";
			this->okButton->Size = System::Drawing::Size(157, 48);
			this->okButton->TabIndex = 5;
			this->okButton->Text = L"OK";
			this->auditFilterToolTip->SetToolTip(this->okButton, L"Close the Audit Filter Dialog");
			this->okButton->UseVisualStyleBackColor = true;
			this->okButton->Click += gcnew System::EventHandler(this, &AuditFilterDialog::okButton_Click);
			// 
			// addFilterButton
			// 
			this->addFilterButton->Location = System::Drawing::Point(266, 529);
			this->addFilterButton->Name = L"addFilterButton";
			this->addFilterButton->Size = System::Drawing::Size(47, 39);
			this->addFilterButton->TabIndex = 4;
			this->addFilterButton->Text = L"+";
			this->auditFilterToolTip->SetToolTip(this->addFilterButton, L"Add the file suffix as a new Audit Filter");
			this->addFilterButton->UseVisualStyleBackColor = true;
			this->addFilterButton->Click += gcnew System::EventHandler(this, &AuditFilterDialog::addFilterButton_Click);
			// 
			// auditListLabel
			// 
			this->auditListLabel->AutoSize = true;
			this->auditListLabel->Location = System::Drawing::Point(12, 22);
			this->auditListLabel->Name = L"auditListLabel";
			this->auditListLabel->Size = System::Drawing::Size(114, 25);
			this->auditListLabel->TabIndex = 0;
			this->auditListLabel->Text = L"Audit Filters";
			// 
			// auditFiltersListView
			// 
			this->auditFiltersListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(1) { this->filterColumnHeader });
			this->auditFiltersListView->HideSelection = false;
			this->auditFiltersListView->Items->AddRange(gcnew cli::array< System::Windows::Forms::ListViewItem^  >(8) {
				listViewItem1,
					listViewItem2, listViewItem3, listViewItem4, listViewItem5, listViewItem6, listViewItem7, listViewItem8
			});
			this->auditFiltersListView->Location = System::Drawing::Point(17, 62);
			this->auditFiltersListView->MultiSelect = false;
			this->auditFiltersListView->Name = L"auditFiltersListView";
			this->auditFiltersListView->Size = System::Drawing::Size(296, 417);
			this->auditFiltersListView->Sorting = System::Windows::Forms::SortOrder::Ascending;
			this->auditFiltersListView->TabIndex = 1;
			this->auditFilterToolTip->SetToolTip(this->auditFiltersListView, L"Right click to remove an audit filter");
			this->auditFiltersListView->UseCompatibleStateImageBehavior = false;
			this->auditFiltersListView->View = System::Windows::Forms::View::Details;
			this->auditFiltersListView->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &AuditFilterDialog::auditFiltersListView_MouseClick);
			// 
			// filterColumnHeader
			// 
			this->filterColumnHeader->Text = L"Filter";
			this->filterColumnHeader->Width = 286;
			// 
			// newFilterTextBox
			// 
			this->newFilterTextBox->Location = System::Drawing::Point(17, 533);
			this->newFilterTextBox->Name = L"newFilterTextBox";
			this->newFilterTextBox->Size = System::Drawing::Size(225, 29);
			this->newFilterTextBox->TabIndex = 3;
			this->auditFilterToolTip->SetToolTip(this->newFilterTextBox, L"Enter a new file suffix");
			this->newFilterTextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &AuditFilterDialog::newFilterTextBox_KeyPress);
			// 
			// newFilterLabel
			// 
			this->newFilterLabel->AutoSize = true;
			this->newFilterLabel->Location = System::Drawing::Point(12, 497);
			this->newFilterLabel->Name = L"newFilterLabel";
			this->newFilterLabel->Size = System::Drawing::Size(98, 25);
			this->newFilterLabel->TabIndex = 2;
			this->newFilterLabel->Text = L"New Filter";
			// 
			// AuditFilterDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(336, 686);
			this->ContextMenuStrip = this->auditFilterContextMenuStrip;
			this->ControlBox = false;
			this->Controls->Add(this->newFilterTextBox);
			this->Controls->Add(this->newFilterLabel);
			this->Controls->Add(this->auditFiltersListView);
			this->Controls->Add(this->auditListLabel);
			this->Controls->Add(this->addFilterButton);
			this->Controls->Add(this->okButton);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->MinimumSize = System::Drawing::Size(360, 710);
			this->Name = L"AuditFilterDialog";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Manage Audit Filters";
			this->Layout += gcnew System::Windows::Forms::LayoutEventHandler(this, &AuditFilterDialog::AuditFilterDialog_Layout);
			this->auditFilterContextMenuStrip->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void AuditFilterDialog_Layout(System::Object^ sender, System::Windows::Forms::LayoutEventArgs^ e) {
		if (0 > lastHeight || 0 > lastWidth) {
			return;
		}

		this->SuspendLayout();

		int deltaHeight = this->Height - lastHeight;
		int deltaWidth = this->Width - lastWidth;

		auditFiltersListView->Height += deltaHeight;
		auditFiltersListView->Width += deltaWidth;
		MoveControl(newFilterTextBox, 0, deltaHeight);
		MoveControl(newFilterLabel, 0, deltaHeight);
		newFilterTextBox->Width += deltaWidth;
		MoveControl(addFilterButton, deltaWidth, deltaHeight);
		MoveControl(okButton, deltaWidth, deltaHeight);

		lastHeight = this->Height;
		lastWidth = this->Width;

		this->ResumeLayout(false);
		this->PerformLayout();
	}
	private: System::Void auditFiltersListView_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Right)
		{
			selectedFilterItem = auditFiltersListView->GetItemAt(e->X, e->Y);
			if (nullptr != selectedFilterItem) {
				auditFilterContextMenuStrip->Show(Cursor->Position);
			}
		}
	}
	private: System::Void toolStripRemoveMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (nullptr != selectedFilterItem) {
			auditFiltersListView->Items->Remove(selectedFilterItem);
			selectedFilterItem = nullptr;
			WriteFilterFile();
		}
	}
	private: System::Void newFilterTextBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (e->KeyChar == (wchar_t)Keys::Enter) {
			AddNewFilter(newFilterTextBox->Text);
		}
	}
	private: System::Void addFilterButton_Click(System::Object^ sender, System::EventArgs^ e) {
		AddNewFilter(newFilterTextBox->Text);
	}
	private: System::Void okButton_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Hide();
	}
	private: System::Void MoveControl(Control^ control, int deltaX, int deltaY) {
		control->Left += deltaX;
		control->Top += deltaY;
	}
	private: System::Void AddNewFilter(String^ newFilter) {
		if (newFilter->Length != 0 && !AuditFilterAlreadyPresent(newFilter)) {
			auditFiltersListView->Items->Add(gcnew ListViewItem(newFilter));
			WriteFilterFile();
		}
		newFilterTextBox->Text = L"";
	}
	private: bool AuditFilterAlreadyPresent(String^ filter) {
		IEnumerator^ iter = auditFiltersListView->Items->GetEnumerator();
		while (iter->MoveNext()) {
			if (0 == String::Compare(filter, (cli::safe_cast<ListViewItem^>(iter->Current))->Text, true)) {
				return true;
			}
		}
		return false;
	}
	private: System::Void InitFilterList() {
		try {
			array<String^>^ filters = File::ReadAllLines(customFiltersFilename);
			auditFiltersListView->Items->Clear();
			for (int i = 0; i < filters->Length; i++) {
				auditFiltersListView->Items->Add(gcnew ListViewItem(filters[i]));
			}
		}
		catch (Exception^) {
			// Assume any exceptions were caused by a missing file - ignore
		}
	}
	private: System::Void WriteFilterFile() {
		try {
			StreamWriter^ fh = nullptr;
			try {
				fh = File::CreateText(customFiltersFilename);
				IEnumerator^ iter = auditFiltersListView->Items->GetEnumerator();
				while (iter->MoveNext()) {
					fh->WriteLine((cli::safe_cast<ListViewItem^>(iter->Current))->Text);
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
				L"Error while writing " + customFiltersFilename + L": " + e->Message,
				L"Custom Filter File Error",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
		}
	}
	public: ListView::ListViewItemCollection^ GetAuditFilters() {
		return auditFiltersListView->Items;
	}
};
}
