#pragma once

#include "ReplicationEvent.h"

namespace CreationKitAuditTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;

	/// <summary>
	/// Summary for ReplicationLogDialog
	/// </summary>
	public ref class ReplicationLogDialog : public System::Windows::Forms::Form
	{
	public:
		ReplicationLogDialog(void)
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
		~ReplicationLogDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: int lastHeight = -1;
	private: int lastWidth = -1;

	private: System::Windows::Forms::ListView^ logListView;
	protected:
	private: System::Windows::Forms::ColumnHeader^ timeHeader;
	private: System::Windows::Forms::ColumnHeader^ operationHeader;
	private: System::Windows::Forms::ColumnHeader^ fileHeader;
	private: System::Windows::Forms::ColumnHeader^ renameHeader;
	private: System::Windows::Forms::ColumnHeader^ targetHeader;
	private: System::Windows::Forms::Button^ clipboardButton;
	private: System::Windows::Forms::Button^ doneButton;
	private: System::Windows::Forms::ToolTip^ toolTip;
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
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ReplicationLogDialog::typeid));
			this->logListView = (gcnew System::Windows::Forms::ListView());
			this->timeHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->operationHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->fileHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->renameHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->targetHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->clipboardButton = (gcnew System::Windows::Forms::Button());
			this->doneButton = (gcnew System::Windows::Forms::Button());
			this->toolTip = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->SuspendLayout();
			// 
			// logListView
			// 
			this->logListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(5) {
				this->timeHeader, this->operationHeader,
					this->fileHeader, this->renameHeader, this->targetHeader
			});
			this->logListView->FullRowSelect = true;
			this->logListView->HideSelection = false;
			this->logListView->Location = System::Drawing::Point(8, 10);
			this->logListView->Name = L"logListView";
			this->logListView->Size = System::Drawing::Size(976, 609);
			this->logListView->TabIndex = 0;
			this->logListView->UseCompatibleStateImageBehavior = false;
			this->logListView->View = System::Windows::Forms::View::Details;
			// 
			// timeHeader
			// 
			this->timeHeader->Text = L"Timestamp";
			// 
			// operationHeader
			// 
			this->operationHeader->Text = L"Operation";
			// 
			// fileHeader
			// 
			this->fileHeader->Text = L"File";
			// 
			// renameHeader
			// 
			this->renameHeader->Text = L"New Name";
			// 
			// targetHeader
			// 
			this->targetHeader->Text = L"Target File";
			// 
			// clipboardButton
			// 
			this->clipboardButton->Location = System::Drawing::Point(8, 642);
			this->clipboardButton->Name = L"clipboardButton";
			this->clipboardButton->Size = System::Drawing::Size(193, 48);
			this->clipboardButton->TabIndex = 1;
			this->clipboardButton->Text = L"&Copy to Clipboard";
			this->toolTip->SetToolTip(this->clipboardButton, L"Copies the Replication Log to the Clipboard as tab-delimited text");
			this->clipboardButton->UseVisualStyleBackColor = true;
			this->clipboardButton->Click += gcnew System::EventHandler(this, &ReplicationLogDialog::clipboardButton_Click);
			// 
			// doneButton
			// 
			this->doneButton->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->doneButton->Location = System::Drawing::Point(791, 642);
			this->doneButton->Name = L"doneButton";
			this->doneButton->Size = System::Drawing::Size(193, 48);
			this->doneButton->TabIndex = 2;
			this->doneButton->Text = L"&Done";
			this->toolTip->SetToolTip(this->doneButton, L"Closes the dialog window");
			this->doneButton->UseVisualStyleBackColor = true;
			this->doneButton->Click += gcnew System::EventHandler(this, &ReplicationLogDialog::doneButton_Click);
			// 
			// ReplicationLogDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->doneButton;
			this->ClientSize = System::Drawing::Size(996, 741);
			this->ControlBox = false;
			this->Controls->Add(this->doneButton);
			this->Controls->Add(this->clipboardButton);
			this->Controls->Add(this->logListView);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(1020, 765);
			this->Name = L"ReplicationLogDialog";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Replication Log - Last 1,000";
			this->Layout += gcnew System::Windows::Forms::LayoutEventHandler(this, &ReplicationLogDialog::ReplicationLogDialog_Layout);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void clipboardButton_Click(System::Object^ sender, System::EventArgs^ e) {
		StringBuilder builder;
		Collections::IEnumerator^ iter = logListView->Items->GetEnumerator();
		while (iter->MoveNext()) {
			ListViewItem^ item = cli::safe_cast<ListViewItem^>(iter->Current);
			auto values = item->SubItems;
			String^ delim = L"";
			for (int i = 0; i < values->Count; i++) {
				builder.Append(delim);
				builder.Append(values[i]->Text);
				delim = L"\t";
			}
			builder.AppendLine();
		}
		String^ str = builder.ToString();
		if (nullptr == str || str == System::String::Empty) {
			Clipboard::Clear();
		}
		else {
			Clipboard::SetText(str);
		}
		MessageBox::Show(
			this,
			L"Replication Log copied to the system clipboard.",
			L"Action Confirmation",
			MessageBoxButtons::OK,
			MessageBoxIcon::Information);
	}
	private: System::Void doneButton_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void ReplicationLogDialog_Layout(System::Object^ sender, System::Windows::Forms::LayoutEventArgs^ e) {
		if (WindowState == FormWindowState::Minimized) {
			return;
		}
		if (-1 == lastHeight || -1 == lastWidth) {
			return;
		}

		int deltaHeight = this->Height - lastHeight;
		int deltaWidth = this->Width - lastWidth;

		logListView->Width += deltaWidth;
		logListView->Height += deltaHeight;
		clipboardButton->Top += deltaHeight;
		doneButton->Top += deltaHeight;
		doneButton->Left += deltaWidth;

		lastHeight = this->Height;
		lastWidth = this->Width;
	}
	public: Windows::Forms::DialogResult Run(Generic::List<ReplicationEvent^>^ log, IWin32Window^ parent) {
		logListView->Items->Clear();
		Generic::List<ReplicationEvent^>::Enumerator iter = log->GetEnumerator();
		while (iter.MoveNext()) {
			ReplicationEvent^ event = iter.Current;
			logListView->Items->Add(gcnew ListViewItem(gcnew array<String^>(5) {
					event->Timestamp.ToShortDateString() + L" " + event->Timestamp.ToShortTimeString(),
					event->Operation,
					event->Filename,
					event->NewFilename,
					event->Target
			}));
		}
		logListView->AutoResizeColumns(
			0 == log->Count ? ColumnHeaderAutoResizeStyle::HeaderSize : ColumnHeaderAutoResizeStyle::ColumnContent);
		return this->ShowDialog(parent);
	}
};
}
