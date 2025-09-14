#pragma once

#include "FileType.h"

using namespace System;
using namespace System::IO;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace Microsoft::Win32;

namespace CreationKitAuditTool {

	ref class Util
	{
	private: static String^ recycleBin;

	public: static Int32 zero = Int32(0);

	public: static System::Void Initialize() {
		// Compute name of the Windows recycle bin
		// Ideally we should use something like GetFolderPath to find this path, except that
		// it doesn't include support for the Recycle Bin folder.  So I am hard-coding the
		// standard Windows naming scheme here until I can find an API to look it up.
		recycleBin = L"$RECYCLE.BIN\\" + System::Security::Principal::WindowsIdentity::GetCurrent()->User->Value;
	}
	public: static System::Void WriteSetting(String^ registryKey, String^ name, String^ value) {
		try {
			RegistryKey^ key = Registry::CurrentUser->CreateSubKey(registryKey);
			key->SetValue(name, value);
			key->Close();
		}
		catch (Exception^) {
			// Ignore
		}
	}
	public: static System::Void WriteSetting(String^ registryKey, String^ name, bool value) {
		try {
			RegistryKey^ key = Registry::CurrentUser->CreateSubKey(registryKey);
			key->SetValue(name, value ? 1 : 0, RegistryValueKind::DWord);
			key->Close();
		}
		catch (Exception^) {
			// Ignore
		}
	}
	public: static String^ ReadStringSetting(String^ registryKey, String^ name) {
		Object^ value = nullptr;
		try {
			RegistryKey^ key = Registry::CurrentUser->OpenSubKey(registryKey);
			if (nullptr != key) {
				value = key->GetValue(name);
				key->Close();
			}
		}
		catch (Exception^) {
			// Ignore
		}
		return (value == nullptr) ? nullptr : cli::safe_cast<String^>(value);
	}
	public: static bool ReadBooleanSetting(String^ registryKey, String^ name, bool defaultValue) {
		Object^ value = nullptr;
		try {
			RegistryKey^ key = Registry::CurrentUser->OpenSubKey(registryKey);
			if (nullptr != key) {
				value = key->GetValue(name);
				key->Close();
			}
		}
		catch (Exception^) {
			// Ignore
		}
		if (nullptr == value) {
			return defaultValue;
		}
		return (value == nullptr) ? defaultValue : !value->Equals(Util::zero);
	}
	public: static bool HasPrefix(String^ filename, String^ prefix) {
		return filename->StartsWith(prefix, StringComparison::InvariantCultureIgnoreCase);
	}
	public: static bool HasSuffix(String^ filename, String^ suffix) {
		return filename->EndsWith(suffix, StringComparison::InvariantCultureIgnoreCase);
	}
	public: static bool HasSubstring(String^ filename, String^ substring) {
		return 0 <= filename->IndexOf(substring, StringComparison::InvariantCultureIgnoreCase);
	}
	public: static FileType ClassifyFile(String^ fullname) {
		FileAttributes attr;
		try {
			attr = File::GetAttributes(fullname);
		}
		catch (FileNotFoundException^) {
			return DELETED;
		}
		catch (DirectoryNotFoundException^) {
			return DELETED;
		}
		catch (System::Exception^) {
			// Unknown problem getting the file's attributes
			return UNKNOWN;
		}
		if (attr.HasFlag(FileAttributes::Directory)) {
			return DIRECTORY;
		}
		if (attr.HasFlag(FileAttributes::System)) {
			return SYSTEM_FILE;
		}
		if (attr.HasFlag(FileAttributes::Hidden)) {
			return HIDDEN_FILE;
		}
		if (attr.HasFlag(FileAttributes::Temporary)) {
			return TEMPORARY_FILE;
		}
		return NORMAL_FILE;
	}
	/**
	* Deletes an entire directory tree.  If possible, the folder will simply
	* be moved into the recycle bin.  If that is not possible, then a full,
	* recursive tree delete is performed.
	* @param fullname - The full name of the folder to delete
	* @param caller - The window to use for displaying MessageBoxes, or
	* nullptr if errors should be silently swallowed.
	* @returns true if the folder was deleted, false the operation failed,
	* the folder does not exist or the name does not refer to a folder
	*/
	public: static bool DeleteFolder(String^ fullname, IWin32Window^ caller) {
		// Nothing to do if the directory does not exist
		if (!Directory::Exists(fullname)) {
			return false;
		}

		// First try to move the folder directly into the Recycling Bin
		try {
			String^ recycleFolder = Path::GetPathRoot(fullname) + recycleBin;
			if (Directory::Exists(recycleFolder)) {
				String^ target = recycleFolder + L"\\" + Path::GetFileName(fullname);
				Directory::Move(fullname, target);
				return true;
			}
		}
		catch (Exception^) {
			// Ignore as there may be some reason that the folder cannot be
			// moved directory into the recycle bin.
		}

		// Something didn't work - fallback to a brute force recursive delete
		return Util::RecursiveDeleteFolder(fullname, caller);
	}
	/**
	* Performs a recursive delete on an entire directory tree.
	* @param fullname - The full name of the folder to delete
	* @param caller - The window to use for showing MessageBoxes, or nullptr
	* to silently swallow any errors
	* @returns true if the folder was deleted, false if the operation failed, the
	* folder doesn't exist or the name does not refer to a folder
	*/
	private: static bool RecursiveDeleteFolder(String^ fullname, IWin32Window^ caller) {
		// Nothing to do if the directory does not exist
		if (!Directory::Exists(fullname)) {
			return false;
		}

		try {
			// Recursive brute-force deletion of everything in the directory and
			// then the directory itself.  Has a potential race-condition if other
			// processes are creating files into the same directory tree.
			Generic::IEnumerator<String^>^ iter = Directory::EnumerateDirectories(fullname)->GetEnumerator();
			while (iter->MoveNext()) {
				RecursiveDeleteFolder(iter->Current, caller);
			}
			iter = Directory::EnumerateFiles(fullname)->GetEnumerator();
			while (iter->MoveNext()) {
				File::Delete(iter->Current);
			}
			Directory::Delete(fullname);
		}
		catch (Exception^ e) {
			MessageBox::Show(caller,
				L"Error during recursive delete of folder " +
				fullname +
				L": " +
				e->Message,
				L"Recursive Folder Deletion Failure",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
			return false;
		}
		return true;
	}
	};

}

