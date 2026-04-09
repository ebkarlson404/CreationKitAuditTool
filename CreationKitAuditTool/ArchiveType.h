#pragma once
#include "ArchiveTarget.h"

using namespace System;

namespace CreationKitAuditTool {

	public ref class ArchiveType
	{
    /**
	* Shortcut constructor for a localized voice archive.
	* @param target - The target platform for the archive
	* @param language - The ISO 699 language code for the localized voices
	*/
	public: ArchiveType(ArchiveTarget target, String^ language) :
		ArchiveType(target, L"General", L"None", L" - Voices_" + language) {}
	/**
	* Generalized constructor
	* @param target - The target platform for the archive
	* @param format - The format to use for the archive: General|DDS|XBoxDDS
	* @param compresion - The compression to use for the archive: None|Default|XBox|LZ4
	* @param suffix - The suffix string to use for the archive file
	*/
	public: ArchiveType(ArchiveTarget target, String^ format, String^ compression, String^ suffix) :
		Target(target),
		Format(format),
		Compression(compression),
		Suffix(suffix) {}
	protected: ~ArchiveType() {}

	private: ArchiveTarget Target;
	public: String^ Format;
	public: String^ Compression;
	private: String^ Suffix;

	public: static ArchiveType^ PC_MAIN =
		gcnew ArchiveType(TARGET_PC, L"General", L"None", L" - Main");
	public: static ArchiveType^ PC_TEXTURE =
		gcnew ArchiveType(TARGET_PC, L"DDS", L"Default", L" - Textures");
	public: static ArchiveType^ PS5_MAIN =
		gcnew ArchiveType(TARGET_PS5, L"General", L"None", L" - Main");
	public: static ArchiveType^ PS5_TEXTURE =
		gcnew ArchiveType(TARGET_PS5, L"DDS", L"Default", L" - Textures");
	public: static ArchiveType^ XBOX_MAIN =
		gcnew ArchiveType(TARGET_XBOX, L"General", L"None", L" - Main");
	public: static ArchiveType^ XBOX_TEXTURE =
		gcnew ArchiveType(TARGET_XBOX, L"XBoxDDS", L"Default", L" - Textures");

	private: String^ GetArchiveSuffix() {
		switch (Target) {
		case TARGET_PC: return L"";
		case TARGET_PS5: return L"_ps";
		case TARGET_XBOX: return L"_xbox";
		}
		throw gcnew Exception(L"Unimplemented ArchiveType");
	}
	public: String^ GetArchiveName(String^ plugin) {
		return plugin + this->Suffix + GetArchiveSuffix() + L".ba2";
	}
	};

}
