#pragma once

#include "AbortException.h"
#include "StarfieldData.h"

namespace CreationKitAuditTool {

	class Replication
	{
	/**
	* Used by the background continuous replication logic to replicate
	* a newly discovered file if it should be replicated.
	* @param fullname - The full name of the file to process
	*/
	public: static System::Void MaybeReplicateFile(String^ fullname) {
		try {
			String^ relativeName = StarfieldData::GetRelativeName(fullname);
			if (nullptr != relativeName) {
				EspToEsmReplication(relativeName, nullptr);
			}
		}
		catch (Exception^) {
			// Swallow any exceptions
		}
	}
	/**
	* Given the name of a deleted file, check to see if there are any
	* ESP->ESM replicas of the deleted file.  If so, delete the
	* replicas.
	* @param fullname - The full name of the deleted file
	*/
	public: static System::Void MaybeDeleteReplicaFile(String^ fullname) {
		// Ensure that the deleted file resides within one of our Data folders.
		String^ relativeName = StarfieldData::GetRelativeName(fullname);
		if (nullptr == relativeName) {
			return;
		}

		// If the deleted files lies within an ESP directory, delete
		// the corresponding file in the corresponding ESM directory.
		String^ esmRelativeName = StarfieldData::EspToEsmNameTransform(relativeName);
		if (nullptr != esmRelativeName) {
			String^ esmFullName = StarfieldData::starfieldPrefix + esmRelativeName;
			try {
				File::Delete(esmFullName);
			}
			catch (Exception^) {
				// Swallow any exceptions and continue
			}
		}

		// If the deleted file lies within the standard Starfield Data tree
		// delete its corresponding XBox transform, if there is one.
		String^ xboxFullname = StarfieldData::PCToXBoxNameTransform(fullname);
		if (nullptr != xboxFullname) {
			try {
				File::Delete(xboxFullname);
			}
			catch (Exception^) {
				// Swallow any exceptions and continue
			}
		}
	}
	public: static System::Void MaybeDeleteReplicaFolder(String^ fullname) {
		// Ensure that the deleted folder resides within one of our Data folders
		String^ relativeName = StarfieldData::GetRelativeName(fullname);
		if (nullptr == relativeName) {
			return;
		}

		// If the deleted folder lies within an ESP folder, delete the
		// corresponding folder under the corresponding ESM folder.
		String^ esmRelativeName = StarfieldData::EspToEsmNameTransform(relativeName);
		if (nullptr != esmRelativeName) {
			Util::DeleteFolder(StarfieldData::starfieldPrefix + esmRelativeName, nullptr);
		}

		// If the deleted folder has been replicated into the XBox tree,
		// also delete the XBox replica folder.
		String^ xboxFullname = StarfieldData::PCToXBoxNameTransform(fullname);
		if (nullptr != xboxFullname) {
			Util::DeleteFolder(xboxFullname, nullptr);
		}
	}
    /**
	* Replicates the file from ESP to ESM folders, if applicable, and returns the
	* name of the file that should be used for archive packing.
	* @param espRelativeName The relative name of a file that may reside in an ESP folder
	* @param ignoreDoesNotExist Ignore errors if espRelativeName does not exist
	* @param caller The window to use for displaying error message boxes or nullptr
	* if errors should be silently ignored
	* @returns The name of the file to use for archive packing or nullptr if the operation
	* fails
	* @throws AbortException - User requested abort action
	*/
	public: static String^ EspToEsmReplication(String^ espRelativeName, IWin32Window^ caller) {
		String^ esmRelativeName = StarfieldData::EspToEsmNameTransform(espRelativeName);
		if (nullptr == esmRelativeName) {
			return espRelativeName;
		}
		String^ esmDirectory = StarfieldData::starfieldPrefix + esmRelativeName->Substring(0, esmRelativeName->LastIndexOf(L"\\"));
		DialogResult status = DialogResult::Retry;
		while (status == DialogResult::Retry) {
			try {
				Directory::CreateDirectory(esmDirectory);
				File::Copy(StarfieldData::starfieldPrefix + espRelativeName, StarfieldData::starfieldPrefix + esmRelativeName, true);
				status = DialogResult::OK;
			}
			catch (Exception^ e) {
				if (nullptr != caller) {
					status = MessageBox::Show(
						caller,
						L"Error while replicating " +
						StarfieldData::starfieldPrefix + espRelativeName +
						L" to " +
						StarfieldData::starfieldPrefix + esmRelativeName +
						L": " +
						e->Message,
						L"ESP to ESM Replication Failure",
						MessageBoxButtons::AbortRetryIgnore,
						MessageBoxIcon::Error);
				}
				else {
					status = DialogResult::Ignore;
				}
				if (status == DialogResult::Abort) {
					throw gcnew AbortException(L"User requested abort", e);
				}
			}
		}
		return (status == DialogResult::OK) ? esmRelativeName : nullptr;
	}
	/**
	* Replicate the rename of a source file onto any replicas of the file.
	* If the ESM replica of the file does not exist, this is a noop.
	* @param oldFullName - The original name of the object
	* @param newFullName - The new name of the object
	* @returns true if the operation worked, false if not
	*/
	public: static bool MaybeRenameReplicaFiles(String^ oldFullName, String^ newFullName) {
		// Renames should not change the folder name - verify that
		if (!Path::GetDirectoryName(oldFullName)->Equals(Path::GetDirectoryName(newFullName))) {
			return false;
		}

		// Get the relative names for the old and new files.
		// Both must reside within one of the Data directory trees.
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
			catch (Exception^) {
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
			catch (Exception^) {
				return false;
			}
		}
		return true;
	}
	/**
	* Given a renamed folder, apply the same renaming to any replicas of the folder.
	* @param oldFullName - The original full name of the folder
	* @param newFullName - The new full name of the folder
	* @returns true if all replicas were renamed, false otherwise
	*/
	public: static bool MaybeRenameReplicasFolders(String^ oldFullName, String^ newFullName) {
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
			catch (Exception^) {
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
			catch (Exception^) {
				return false;
			}
		}
		return true;
	}
	};

}
