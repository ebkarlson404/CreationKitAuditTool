#pragma once

using namespace System;
using namespace System::Collections;

namespace CreationKitAuditTool {

	public ref class PackingTask
	{
	/**
	* Constructor specific for creating Localized Voice Archives
	*/
	public: PackingTask(bool isXBoxArchive, String^ plugin, String^ lang) {
		this->Format = L"General";
		this->Compression = isXBoxArchive ? L"XBox" : L"Default";
		this->Files = gcnew Generic::List<String^>;
		this->ArchiveName = plugin + L" - Voices_" + lang + (isXBoxArchive ? L"_xbox.ba2" : L".ba2");
	}
	public: PackingTask(
		bool isTextureArchive,
		bool isXBoxArchive,
		Generic::List<String^>^ files,
		String^ archiveName) {
		if (isTextureArchive) {
			this->Format = isXBoxArchive ? L"XBoxDDS" : L"DDS";
		}
		else {
			this->Format = L"General";
		}
		this->Compression = isXBoxArchive ? L"XBox" : L"Default";
		this->Files = files;
		this->ArchiveName = archiveName;
	}
	protected: ~PackingTask() {}

	public: String^ Format;
	public: String^ Compression;
	public: Generic::List<String^>^ Files;
	public: String^ ArchiveName;
	};

}
