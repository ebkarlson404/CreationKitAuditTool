#pragma once

#include "ArchiveErrorDialog.h"
#include "PackingTask.h"
#include "StarfieldData.h"

namespace CreationKitAuditTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Diagnostics;
	using namespace System::IO;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading::Tasks;

	/// <summary>
	/// Summary for ArchiveDialog
	/// </summary>
	public ref class ArchiveDialog : public System::Windows::Forms::Form
	{
	public:
		ArchiveDialog(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			progressBarDelegate = gcnew Func<ArchiveDialog^,Object^>(ArchiveDialog::BumpProgress);
			selfArgs = gcnew array<Object^>(1) { this };
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ArchiveDialog()
		{
			if (components)
			{
				delete components;
			}
		}
	private: static String^ archiveToolPath = L"Tools\\Archive2\\Archive2.exe";
	private: Generic::Queue<PackingTask^>^ workQueue = gcnew Generic::Queue<PackingTask^>;
	private: Generic::List<String^>^ archiveOutput = gcnew Generic::List<String^>;
	private: ArchiveErrorDialog^ archiveErrorDialog = gcnew ArchiveErrorDialog;
	private: String^ lastArchiveName;
	private: Delegate^ progressBarDelegate;
	private: array<Object^>^ selfArgs;
	private: bool allowCheckMarks = false;

	private: System::Windows::Forms::ProgressBar^ progressBar;
	protected:
	private: System::Windows::Forms::ListView^ filesListView;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ okButton;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::ColumnHeader^ statusHeader;
	private: System::Windows::Forms::ColumnHeader^ archiveHeader;
	private: System::ComponentModel::BackgroundWorker^ backgroundWorker;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(ArchiveDialog::typeid));
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->filesListView = (gcnew System::Windows::Forms::ListView());
			this->statusHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->archiveHeader = (gcnew System::Windows::Forms::ColumnHeader());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->okButton = (gcnew System::Windows::Forms::Button());
			this->backgroundWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->SuspendLayout();
			// 
			// progressBar
			// 
			this->progressBar->Location = System::Drawing::Point(19, 411);
			this->progressBar->MarqueeAnimationSpeed = 10;
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(732, 44);
			this->progressBar->Step = 1;
			this->progressBar->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			this->progressBar->TabIndex = 2;
			// 
			// filesListView
			// 
			this->filesListView->CheckBoxes = true;
			this->filesListView->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {
				this->statusHeader,
					this->archiveHeader
			});
			this->filesListView->FullRowSelect = true;
			this->filesListView->HeaderStyle = System::Windows::Forms::ColumnHeaderStyle::Nonclickable;
			this->filesListView->HideSelection = false;
			this->filesListView->Location = System::Drawing::Point(19, 75);
			this->filesListView->Name = L"filesListView";
			this->filesListView->Size = System::Drawing::Size(732, 314);
			this->filesListView->TabIndex = 1;
			this->filesListView->UseCompatibleStateImageBehavior = false;
			this->filesListView->View = System::Windows::Forms::View::Details;
			this->filesListView->ItemCheck += gcnew System::Windows::Forms::ItemCheckEventHandler(this, &ArchiveDialog::filesListView_ItemCheck);
			// 
			// statusHeader
			// 
			this->statusHeader->Text = L"Status";
			this->statusHeader->Width = 80;
			// 
			// archiveHeader
			// 
			this->archiveHeader->Text = L"Archive";
			this->archiveHeader->Width = 300;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(317, 34);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(124, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Archive Files";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// okButton
			// 
			this->okButton->Enabled = false;
			this->okButton->Location = System::Drawing::Point(607, 475);
			this->okButton->Name = L"okButton";
			this->okButton->Size = System::Drawing::Size(144, 52);
			this->okButton->TabIndex = 3;
			this->okButton->Text = L"&OK";
			this->okButton->UseVisualStyleBackColor = true;
			this->okButton->Click += gcnew System::EventHandler(this, &ArchiveDialog::okButton_Click);
			// 
			// backgroundWorker
			// 
			this->backgroundWorker->WorkerReportsProgress = true;
			this->backgroundWorker->WorkerSupportsCancellation = true;
			this->backgroundWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &ArchiveDialog::backgroundWorker_DoWork);
			this->backgroundWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &ArchiveDialog::backgroundWorker_RunWorkerCompleted);
			// 
			// ArchiveDialog
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(11, 24);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(766, 546);
			this->ControlBox = false;
			this->Controls->Add(this->okButton);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->filesListView);
			this->Controls->Add(this->progressBar);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(790, 610);
			this->Name = L"ArchiveDialog";
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Archive Progress";
			this->Load += gcnew System::EventHandler(this, &ArchiveDialog::ArchiveDialog_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void filesListView_ItemCheck(System::Object^ sender, System::Windows::Forms::ItemCheckEventArgs^ e) {
		ListViewItem^ item = filesListView->Items[e->Index];
		if (!allowCheckMarks) {
			e->NewValue = item->Checked ? CheckState::Checked : CheckState::Unchecked;
		}
		item->Focused = false;
	}
	private: System::Void okButton_Click(System::Object^ sender, System::EventArgs^ e) {
		this->Close();
	}
	private: System::Void ArchiveDialog_Load(System::Object^ sender, System::EventArgs^ e) {
		// Start the background process now that the window is visible
		if (workQueue->Count > 0) {
			StartNextPackingTask();
		}
		else {
			okButton->Enabled = true;
		}
	}
	private: System::Void process_OutputDataReceived(System::Object^ sender, System::Diagnostics::DataReceivedEventArgs^ e) {
		if (nullptr != e->Data) {
			archiveOutput->Add(e->Data);
			if (Util::HasPrefix(e->Data, L"Adding \"")) {
				progressBar->Invoke(progressBarDelegate, selfArgs);
			}
		}
	}
	private: System::Void process_ErrorDataReceived(System::Object^ sender, System::Diagnostics::DataReceivedEventArgs^ e) {
		if (nullptr != e->Data) {
			archiveOutput->Add(e->Data);
			if (Util::HasPrefix(e->Data, L"Skipped non-existing file \"")) {
				progressBar->Invoke(progressBarDelegate, selfArgs);
			}
		}
	}
	private: System::Void backgroundWorker_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) {
		// Reset the capture buffer for the Archive2 output
		archiveOutput->Clear();

		// Get the PackingTask to execute
		PackingTask^ task = cli::safe_cast<PackingTask^>(e->Argument);
		lastArchiveName = StarfieldData::starfieldPrefix + L"Data\\" + task->ArchiveName;

		// Generate a temp file to hold the manifest
		String^ manifestFilename = Path::GetTempFileName();
		File::AppendAllLines(manifestFilename, task->Files);

		// Compute the arguments to the Archive2 tool
		String^ args =
			L"-c=\"Data\\" + task->ArchiveName + L"\"" +
			L" -s=\"" + manifestFilename + L"\"" +
			L" -f=" + task->Format +
			L" -compression=" + task->Compression;

		// Marshall the start info for the archive tool
		ProcessStartInfo^ startInfo = gcnew ProcessStartInfo;
		startInfo->Arguments = args;
		startInfo->CreateNoWindow = true;
		startInfo->FileName = StarfieldData::starfieldPrefix + archiveToolPath;
		startInfo->RedirectStandardError = true;
		startInfo->RedirectStandardOutput = true;
		startInfo->UseShellExecute = false;
		startInfo->WindowStyle = ProcessWindowStyle::Hidden;
		startInfo->WorkingDirectory = StarfieldData::starfieldFolder;

		// Run the archive tool
		Process^ proc = Process::Start(startInfo);

		// Setup to consume the stdout and stderr from the archive tool
		proc->OutputDataReceived += gcnew System::Diagnostics::DataReceivedEventHandler(this, &ArchiveDialog::process_OutputDataReceived);
		proc->ErrorDataReceived += gcnew System::Diagnostics::DataReceivedEventHandler(this, &ArchiveDialog::process_ErrorDataReceived);
		proc->BeginOutputReadLine();
		proc->BeginErrorReadLine();

		// Wait for the archive to complete
		proc->WaitForExit();

		// Grab the exit code
		e->Result = gcnew Int32(proc->ExitCode);

		// Clean the temp file
		try {
			File::Delete(manifestFilename);
		}
		catch (Exception^) {
			// Ignore errors cleaning up the temp file
		}
	}
	private: System::Void backgroundWorker_RunWorkerCompleted(System::Object^ sender, System::ComponentModel::RunWorkerCompletedEventArgs^ e) {

		// Check the status box on the last archive file
		ListViewItem^ item = filesListView->Items[filesListView->Items->Count - 1];
		allowCheckMarks = true;
		item->Checked = true;
		allowCheckMarks = false;

		// See whether the last archive worked or not
		if (e->Cancelled) {
			// Cancel isn't support at this time
		}
		else if (nullptr != e->Error) {
			MessageBox::Show(
				this,
				L"Internal error encountered during packing: " + e->Error->Message,
				L"Pack Operation Aborted",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
		}
		else if (!(cli::safe_cast<Int32^>(e->Result))->Equals(Util::zero)) {
			if (Windows::Forms::DialogResult::Cancel == archiveErrorDialog->Run(lastArchiveName, archiveOutput, this)) {
				item->BackColor = Color::Red;
			}
			else {
				item->BackColor = Color::Yellow;
			}
		}

		// Queue up the next task, if there is one
		if (workQueue->Count > 0) {
			StartNextPackingTask();
		}
		else {
			okButton->Enabled = true;
		}
	}
	private: System::Void StartNextPackingTask() {
		PackingTask^ task = workQueue->Dequeue();
		progressBar->Value = 0;
		progressBar->Maximum = task->Files->Count;
			filesListView->Items->Add(
				gcnew ListViewItem(gcnew cli::array<System::String^>(2) {
				L"", task->ArchiveName
			}));
			filesListView->AutoResizeColumn(1, ColumnHeaderAutoResizeStyle::ColumnContent);
		backgroundWorker->RunWorkerAsync(task);
	}
	private: static Object^ BumpProgress(ArchiveDialog^ dialog) {
		dialog->progressBar->PerformStep();
		return Util::zero;
	}
	public: System::Void Run(
		String^ plugin,
		PackingTask^ mainPC,
		PackingTask^ mainXB,
		PackingTask^ texturesPC,
		PackingTask^ texturesXB,
		Dictionary<String^,PackingTask^>^ voicesPC,
		Dictionary<String^,PackingTask^>^ voicesXB,
		IWin32Window^ parent) {

		// Save all the parameter data
		this->Text = plugin + L": Archive Creation";

		// Build out work queue
		workQueue->Clear();
		if (mainPC->Files->Count > 0) {
			this->workQueue->Enqueue(mainPC);
		}
		if (mainXB->Files->Count > 0) {
			this->workQueue->Enqueue(mainXB);
		}
		if (texturesPC->Files->Count > 0) {
			this->workQueue->Enqueue(texturesPC);
		}
		if (texturesXB->Files->Count > 0) {
			this->workQueue->Enqueue(texturesXB);
		}
		Dictionary<String^, PackingTask^>::Enumerator iter = voicesPC->GetEnumerator();
		while (iter.MoveNext()) {
			this->workQueue->Enqueue(iter.Current.Value);
		}
		iter = voicesXB->GetEnumerator();
		while (iter.MoveNext()) {
			this->workQueue->Enqueue(iter.Current.Value);
		}

		// Reset the controls
		this->filesListView->Items->Clear();
		this->filesListView->AutoResizeColumns(ColumnHeaderAutoResizeStyle::HeaderSize);
		this->progressBar->Value = 0;
		this->okButton->Enabled = false;

		// Show the modal window and wait for everything to finish
		this->ShowDialog(parent);
	}
};
}
