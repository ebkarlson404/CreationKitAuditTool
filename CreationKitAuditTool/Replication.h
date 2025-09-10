#pragma once

#include "StarfieldData.h"

namespace CreationKitAuditTool {

	class Replication
	{
	public: static System::Void MaybeReplicateFile(String^ fullname, bool ignoreIOException, IWin32Window^ caller) {
		EspToEsmReplication(StarfieldData::GetRelativeName(fullname), ignoreIOException, caller);
	}
	public: static bool MaybeDeleteReplicaFile(String^ fullname, IWin32Window^ caller) {
		// Ensure that the deleted file resides within one of our Data folders.
		String^ relativeName = StarfieldData::GetRelativeName(fullname);
		if (nullptr == relativeName) {
			return true;
		}

		// If the deleted files lies within an ESP directory, delete
		// the corresponding file in the corresponding ESM directory.
		String^ esmRelativeName = StarfieldData::EspToEsmNameTransform(relativeName);
		if (nullptr != esmRelativeName) {
			String^ esmFullName = StarfieldData::starfieldPrefix + esmRelativeName;
			try {
				if (File::Exists(esmFullName)) {
					File::Delete(esmFullName);
				}
			}
			catch (Exception^ e) {
				MessageBox::Show(caller,
					L"Error while deleting ESM replica file " +
					esmFullName +
					L": " +
					e->Message,
					L"ESM Replica Deletion Failure",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
				return false;
			}
		}

		// If the deleted file lies within the standard Starfield Data tree
		// delete its corresponding XBox replica, if there is one.
		String^ xboxFullname = StarfieldData::PCToXBoxNameTransform(fullname);
		if (nullptr != xboxFullname) {
			try {
				if (File::Exists(xboxFullname)) {
					File::Delete(xboxFullname);
				}
			}
			catch (Exception^ e) {
				MessageBox::Show(caller,
					L"Error while deleting XBox replica file " +
					xboxFullname +
					L": " +
					e->Message,
					L"XBox Replica Deletion Failure",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
				return false;
			}
		}
		return true;
	}
	public: static bool MaybeDeleteReplicaFolder(String^ fullname, IWin32Window^ caller) {
		// Ensure that the deleted folder resides within one of our Data folders
		String^ relativeName = StarfieldData::GetRelativeName(fullname);
		if (nullptr == relativeName) {
			return true;
		}

		// If the deleted folder lies within an ESP folder, delete the
		// corresponding folder under the corresponding ESM folder.
		String^ esmRelativeName = StarfieldData::EspToEsmNameTransform(relativeName);
		if (nullptr != esmRelativeName) {
			if (!Util::DeleteFolder(StarfieldData::starfieldPrefix + esmRelativeName, caller)) {
				return false;
			}
		}

		// If the deleted folder has been replicated into the XBox tree,
		// also delete the XBox replica folder.
		String^ xboxFullname = StarfieldData::PCToXBoxNameTransform(fullname);
		if (nullptr != xboxFullname) {
			if (!Util::DeleteFolder(xboxFullname, caller)) {
				return false;
			}
		}
		return true;
	}
	public: static String^ EspToEsmReplication(String^ espRelativeName, bool ignoreIOException, IWin32Window^ caller) {
		String^ esmRelativeName = StarfieldData::EspToEsmNameTransform(espRelativeName);
		if (nullptr == esmRelativeName) {
			return espRelativeName;
		}
		String^ esmDirectory = StarfieldData::starfieldPrefix + esmRelativeName->Substring(0, esmRelativeName->LastIndexOf(L"\\"));
		try {
			Directory::CreateDirectory(esmDirectory);
			File::Copy(StarfieldData::starfieldPrefix + espRelativeName, StarfieldData::starfieldPrefix + esmRelativeName, true);
		}
		catch (IOException^ e) {
			if (!ignoreIOException) {
				MessageBox::Show(caller,
					L"Error while replicating " +
					StarfieldData::starfieldPrefix + espRelativeName +
					L" to " +
					StarfieldData::starfieldPrefix + esmRelativeName +
					L": " +
					e->Message,
					L"ESP to ESM Replication Failure",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
			}
			return nullptr;
		}
		catch (Exception^ e) {
			MessageBox::Show(caller,
				L"Error while replicating " +
				StarfieldData::starfieldPrefix + espRelativeName +
				L" to " +
				StarfieldData::starfieldPrefix + esmRelativeName +
				L": " +
				e->Message,
				L"ESP to ESM Replication Failure",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
			return nullptr;
		}
		return esmRelativeName;
	}
	public: static bool MaybeRenameReplicaFiles(String^ oldFullName, String^ newFullName, IWin32Window^ caller) {
		// Renames should not change the folder name - verify that
		if (!Path::GetDirectoryName(oldFullName)->Equals(Path::GetDirectoryName(newFullName))) {
			MessageBox::Show(caller,
				L"File rename crosses directories, which should not be possible.  "
				L"Replication of rename skipped.",
				L"Rename Replication Assertion Failure",
				MessageBoxButtons::OK,
				MessageBoxIcon::Warning);
			return false;
		}

		// Get the relative names for the old and new files
		String^ oldRelativeName = StarfieldData::GetRelativeName(oldFullName);
		String^ newRelativeName = StarfieldData::GetRelativeName(newFullName);
		if (nullptr == oldRelativeName || nullptr == newRelativeName) {
			return true;
		}

		// If the folders lie within an ESP directory, rename
		// the corresponding folder in the corresponding ESM directory.
		String^ oldEsmRelativeName = StarfieldData::EspToEsmNameTransform(oldRelativeName);
		String^ newEsmRelativeName = StarfieldData::EspToEsmNameTransform(newRelativeName);
		if (nullptr != oldEsmRelativeName && nullptr != newEsmRelativeName) {
			String^ oldEsmFullName = StarfieldData::starfieldPrefix + oldEsmRelativeName;
			String^ newEsmFullName = StarfieldData::starfieldPrefix + newEsmRelativeName;
			try {
				if (File::Exists(oldEsmFullName)) {
					File::Move(oldEsmFullName, newEsmFullName);
				}
			}
			catch (Exception^ e) {
				MessageBox::Show(caller,
					L"Error while renaming ESM replica folders: " +
					e->Message,
					L"ESM Replica Rename Failure",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
				return false;
			}
		}

		// If the renamed folder lies within the standard Starfield Data tree
		// rename its corresponding XBox replica, if there is one.
		String^ oldXboxFullname = StarfieldData::PCToXBoxNameTransform(oldFullName);
		String^ newXBoxFullName = StarfieldData::PCToXBoxNameTransform(newFullName);
		if (nullptr != oldXboxFullname && nullptr != newXBoxFullName) {
			try {
				if (File::Exists(oldXboxFullname)) {
					File::Move(oldXboxFullname, newXBoxFullName);
				}
			}
			catch (Exception^ e) {
				MessageBox::Show(caller,
					L"Error while renaming XBox replica folders: " +
					e->Message,
					L"XBox Replica Deletion Failure",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
				return false;
			}
		}
		return true;
	}
	public: static bool MaybeRenameReplicasFolders(String^ oldFullName, String^ newFullName, IWin32Window^ caller) {
		// Get the relative names for the old and new files
		String^ oldRelativeName = StarfieldData::GetRelativeName(oldFullName);
		String^ newRelativeName = StarfieldData::GetRelativeName(newFullName);
		if (nullptr == oldRelativeName || nullptr == newRelativeName) {
			return true;
		}

		// If the files lie within an ESP directory, rename
		// the corresponding file in the corresponding ESM directory.
		String^ oldEsmRelativeName = StarfieldData::EspToEsmNameTransform(oldRelativeName);
		String^ newEsmRelativeName = StarfieldData::EspToEsmNameTransform(newRelativeName);
		if (nullptr != oldEsmRelativeName && nullptr != newEsmRelativeName) {
			String^ oldEsmFullName = StarfieldData::starfieldPrefix + oldEsmRelativeName;
			String^ newEsmFullName = StarfieldData::starfieldPrefix + newEsmRelativeName;
			try {
				if (Directory::Exists(oldEsmFullName)) {
					Directory::Move(oldEsmFullName, newEsmFullName);
				}
			}
			catch (Exception^ e) {
				MessageBox::Show(caller,
					L"Error while renaming ESM replica files: " +
					e->Message,
					L"ESM Replica Rename Failure",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
				return false;
			}
		}

		// If the renamed file lies within the standard Starfield Data tree
		// rename its corresponding XBox replica, if there is one.
		String^ oldXboxFullname = StarfieldData::PCToXBoxNameTransform(oldFullName);
		String^ newXBoxFullName = StarfieldData::PCToXBoxNameTransform(newFullName);
		if (nullptr != oldXboxFullname && nullptr != newXBoxFullName) {
			try {
				if (Directory::Exists(oldXboxFullname)) {
					Directory::Move(oldXboxFullname, newXBoxFullName);
				}
			}
			catch (Exception^ e) {
				MessageBox::Show(caller,
					L"Error while renaming XBox replica files: " +
					e->Message,
					L"XBox Replica Deletion Failure",
					MessageBoxButtons::OK,
					MessageBoxIcon::Error);
				return false;
			}
		}
		return true;
	}
    public: static bool ReplicateFolder(String^ source, String^ dest, String^ pattern, IWin32Window^ caller) {
		String^ sourceFile;
		try {
			Generic::IEnumerator<String^>^ iter =
				Directory::EnumerateFiles(source, pattern, SearchOption::AllDirectories)->GetEnumerator();
			while (iter->MoveNext()) {
				sourceFile = iter->Current;
				String^ sourceFolder = Path::GetDirectoryName(sourceFile);
				String^ destFolder = dest + sourceFolder->Substring(source->Length);
				Directory::CreateDirectory(destFolder);
				File::Copy(sourceFile, destFolder + L"\\" + Path::GetFileName(sourceFile));
			}
		}
		catch (Exception^ e) {
			MessageBox::Show(caller,
				L"Error replicating " + sourceFile + L": " + e->Message,
				L"Replication Error",
				MessageBoxButtons::OK,
				MessageBoxIcon::Error);
			return false;
		}
		return true;
	}
	};

}
