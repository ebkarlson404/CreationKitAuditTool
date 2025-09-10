#pragma once
#include "Util.h"

using namespace System;

namespace CreationKitAuditTool {

	public ref class StarfieldData
	{
	public: static String^ starfieldPrefix;
	public: static String^ starfieldDataFolder;
	public: static String^ starfieldDataPrefix;
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

	public: static bool IsESPFile(String^ fullname) {
		return Util::HasSuffix(fullname, L".ESP") && Util::HasPrefix(fullname, starfieldDataPrefix);
	}
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
	public: static bool FileResidesWithinStarfieldFolder(String^ fullFilename) {
		return Util::HasPrefix(fullFilename, StarfieldData::starfieldPrefix);
	}
	public: static bool FileResidesWithinStarfieldDataFolder(String^ fullFilename) {
		return Util::HasPrefix(fullFilename, StarfieldData::starfieldDataPrefix);
	}
	public: static bool FileResidesWithinXBoxDataFolder(String^ fullFilename) {
		return Util::HasPrefix(fullFilename, StarfieldData::starfieldXBoxDataPrefix);
	}
	public: static bool FileResidesWithinEitherDataFolder(String^ fullFilename) {
		return FileResidesWithinStarfieldDataFolder(fullFilename) ||
			FileResidesWithinXBoxDataFolder(fullFilename);
	}
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
	public: static String^ PCToXBoxNameTransform(String^ fullname) {
		if (!Util::HasPrefix(fullname, starfieldDataPrefix)) {
			return nullptr;
		}
		return starfieldXBoxDataPrefix + fullname->Substring(starfieldDataPrefix->Length);
	}
	public: static bool FileRelatedToPlugIn(String^ fullname, String^ plugin) {
		return fullname->ToUpper()->Contains(L"\\" + plugin->ToUpper() + L".ESP\\");
	}

	};

}

