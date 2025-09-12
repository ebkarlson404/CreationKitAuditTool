#pragma once
#include "Util.h"

using namespace System;

namespace CreationKitAuditTool {

	public ref class StarfieldData
	{
	public: static String^ starfieldFolder;
	public: static String^ starfieldPrefix;
	public: static String^ starfieldDataFolder;
	public: static String^ starfieldDataPrefix;
	public: static String^ starfieldVoicePrefix;
	public: static String^ starfieldRelativeVoicePrefix = L"Data\\Sound\\Voice\\";
	public: static String^ starfieldBackupPrefix;
	public: static String^ starfieldXBoxDataFolder;
	public: static String^ starfieldXBoxRelativePrefix;
	public: static String^ starfieldXBoxDataPrefix;
	public: static String^ starfieldXBoxRelativeVoicePrefix;
	public: static String^ espDirName = nullptr;
	public: static String^ esmDirName = nullptr;
	public: static String^ localizationFolder;
	public: static String^ localizationPrefix;
	public: static String^ localizationRelativePrefix;
	/**
	* Checks whether a file is a plugin's ESP file
	* @param fullname - The full name of the file to check
	* @returns true if the file is a plugin ESP file, false otherwise
	*/
	public: static bool IsESPFile(String^ fullname) {
		return Util::HasSuffix(fullname, L".ESP") && Util::HasPrefix(fullname, starfieldDataPrefix);
	}
    /**
	* Returns the name of a file relative to one of the Starfield Data folders.
	* @param fullname - The full name of the file
	* @returns The Data-relative name of the file, or nullptr if the file does not
	* reside within one of the Starfield Data folders
	*/
	public: static String^ GetRelativeName(String^ fullname) {
		// If the file resides in the Starfield XBox Alternate Data folder, we have to construct
		// the special relative path that will resolve properly when the Creation Kit processes
		// the ARCHLIST file.
		if (FileResidesWithinXBoxDataFolder(fullname)) {
			return L"Data\\..\\" + fullname->Substring(starfieldPrefix->Length);
		}

		// For a normal Starfield Data file, just compute a simple relative path
		if (FileResidesWithinStarfieldDataFolder(fullname)) {
			return fullname->Substring(starfieldPrefix->Length);
		}

		// Anything else is not within one of our Data folders, so there is no relative name
		return nullptr;
	}
	public: static bool FileResidesWithinStarfieldFolder(String^ fullname) {
		return Util::HasPrefix(fullname, StarfieldData::starfieldPrefix);
	}
	public: static bool FileResidesWithinStarfieldDataFolder(String^ fullname) {
		return Util::HasPrefix(fullname, StarfieldData::starfieldDataPrefix);
	}
	public: static bool FileResidesWithinXBoxDataFolder(String^ fullname) {
		return Util::HasPrefix(fullname, StarfieldData::starfieldXBoxDataPrefix);
	}
	public: static bool FileResidesWithinAnyDataFolder(String^ fullname) {
		return FileResidesWithinStarfieldDataFolder(fullname) ||
			FileResidesWithinXBoxDataFolder(fullname);
	}
	/**
	* Transforms the name of a file that resides within a <mod>.esp folder
	* to the corresponding file in the <mod>.esm folder.
	* @param relativeName - The data-relative name of the file
	* @returns The data-relative name of the corresponding ESM file, or
	* nullptr if the file does not reside within an ESP folder.
	*/
	public: static String^ EspToEsmNameTransform(String^ relativeName) {
		if (espDirName == nullptr) {
			return nullptr;
		}
		int pos = relativeName->IndexOf(espDirName, StringComparison::InvariantCultureIgnoreCase);
		if (pos < 0) {
			return nullptr;
		}
		return relativeName->Substring(0, pos) + esmDirName + relativeName->Substring(pos + espDirName->Length);
	}
	/**
	* Transforms the name of a file that resides in the Starfield\Data tree
	* to its corresponding file in the XBox Data tree.
	* @param fullname - The name of the file in the Starfield\Data tree
	* @returns The name of the corresponding XBox Data file, or nullptr if
	* the file does not reside in the Starfield\Data tree.
	*/
	public: static String^ PCToXBoxNameTransform(String^ fullname) {
		if (!Util::HasPrefix(fullname, starfieldDataPrefix)) {
			return nullptr;
		}
		return starfieldXBoxDataPrefix + fullname->Substring(starfieldDataPrefix->Length);
	}
	/**
	* Checks to see if a file resides within some ESP folder related to a given plugin.
	* @param fullname - The name of the file to check
	* @param plugin - The base name of the plugin
	* @return true if the file resides within a ESP folder related to the plugin,
	* false otherwise
	*/
	public: static bool FileRelatedToPlugIn(String^ fullname, String^ plugin) {
		return fullname->ToUpper()->Contains(L"\\" + plugin->ToUpper() + L".ESP\\");
	}

	};

}

