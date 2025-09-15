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
		this->Compression = L"None";
		this->Files = gcnew Generic::List<String^>;
		this->ArchiveName =
			plugin +
			L" - Voices_" +
			lang +
			(isXBoxArchive ? L"_xbox.ba2" : L".ba2");
		this->IsAppendTask = false;
	}
	/**
	* Constructor specific to creating Main or Textures Archives
	*/
	public: PackingTask(
		bool isTextureArchive,
		bool isXBoxArchive,
		Generic::List<String^>^ files,
		String^ plugin) {
		this->Format = isTextureArchive ? (isXBoxArchive ? L"XBoxDDS" : L"DDS") : L"General";
		this->Compression = isTextureArchive ? L"Default" : L"None";
		this->Files = files;
		this->ArchiveName =
			plugin +
			(isTextureArchive ? L" - Textures" : L" - Main") +
			(isXBoxArchive ? L"_xbox.ba2" : L".ba2");
		this->IsAppendTask = false;
	}
	protected: ~PackingTask() {}

	public: String^ Format;
	public: String^ Compression;
	public: Generic::List<String^>^ Files;
	public: String^ ArchiveName;
	public: bool IsAppendTask;
	};
}
