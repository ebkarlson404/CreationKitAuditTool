#pragma once

using namespace System;

namespace CreationKitAuditTool {

	public ref class ArchiveType
	{
	/**
	* Shortcut constructor for a localized voice archive.
	* @param isXBox - true if this is an XBox archive, false otherwise
	* @param language - The ISO 699 language code for the localized voices
	*/
	public: ArchiveType(bool isXBox, String^ language) :
		ArchiveType(isXBox, L"General", L"None", L" - Voices_" + language) {}
	/**
	* Generalized constructor
	* @param isXBox - true if this is an XBox archive, false otherwise
	* @param format - The format to use for the archive: General|DDS|XBoxDDS
	* @param compresion - The compression to use for the archive: None|Default|XBox|LZ4
	* @param suffix - The suffix string to use for the archive file
	*/
	public: ArchiveType(bool isXBox, String^ format, String^ compression, String^ suffix) :
		IsXBox(isXBox),
		Format(format),
		Compression(compression),
		Suffix(suffix) {}
	protected: ~ArchiveType() {}

	private: bool IsXBox;
	public: String^ Format;
	public: String^ Compression;
	private: String^ Suffix;

	public: static ArchiveType^ PC_MAIN =
		gcnew ArchiveType(false, L"General", L"None", L" - Main");
	public: static ArchiveType^ PC_TEXTURE =
		gcnew ArchiveType(true, L"DDS", L"Default", L" - Textures");
	public: static ArchiveType^ XBOX_MAIN =
		gcnew ArchiveType(true, L"General", L"None", L" - Main");
	public: static ArchiveType^ XBOX_TEXTURE =
		gcnew ArchiveType(true, L"XBoxDDS", L"Default", L" - Textures");

	public: String^ GetArchiveName(String^ plugin) {
		return plugin + this->Suffix + (this->IsXBox ? L"_xbox.ba2" : L".ba2");
	}
	};

}
