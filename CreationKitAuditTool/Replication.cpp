#include "AuditFilterDialog.h"
#include "Replication.h"
#include "PackDialog.h"
#include "StarfieldData.h"

namespace CreationKitAuditTool {

	System::Void Replication::AppendReplicationLog(String^ target) {
		replicationLog->Add(currentEvent->CopyWithTarget(target));
		if (replicationLog->Count > replicationLogSize) {
			replicationLog->RemoveAt(0);
		}
	}
	bool Replication::MaybeReplicateFile(String^ fullname, String^ plugin) {
		String^ relativeName = StarfieldData::GetRelativeName(fullname);
		if (nullptr == relativeName) {
			return false;
		}

		// If this plugin is configured for localized voice support
		// See if this is a voice WEM file that should be staged
		String^ stagedFilename = PackDialog::MaybeStageLocalizedWEMFile(fullname, plugin);
		if (nullptr != stagedFilename) {
			AppendReplicationLog(stagedFilename);
		}

		// Check to see if this file should be replicated as part of the ESP->ESM pattern
		if (!ShouldReplicate(fullname, plugin)) {
			return false;
		}

		try {
			String^ esmRelativeName = EspToEsmReplication(relativeName, nullptr);
			if (nullptr != esmRelativeName && !relativeName->Equals(esmRelativeName)) {
				AppendReplicationLog(esmRelativeName);
			}
		}
		catch (Exception^) {
			// Swallow any exceptions
			return false;
		}
		return true;
	}
	System::Void Replication::MaybeDeleteReplicaFile(String^ fullname, String^ plugin) {
		// Ensure that the deleted file resides within one of our Data folders.
		String^ relativeName = StarfieldData::GetRelativeName(fullname);
		if (nullptr == relativeName) {
			return;
		}

		// Check to see if this is a localized WEM file that should be destaged
		String^ stagedFileName = PackDialog::MaybeDeleteStagesLocalizedWEMFile(fullname, plugin);
		if (nullptr != stagedFileName) {
			AppendReplicationLog(stagedFileName);
		}

		// Check that this is a file that would have been replicated to begin with
		if (!ShouldReplicate(fullname, plugin)) {
			return;
		}

		// If the deleted files lies within an ESP directory, delete
		// the corresponding file in the corresponding ESM directory.
		String^ esmRelativeName = StarfieldData::EspToEsmNameTransform(relativeName);
		if (nullptr != esmRelativeName) {
			String^ esmFullName = StarfieldData::starfieldPrefix + esmRelativeName;
			try {
				if (File::Exists(esmFullName)) {
					File::Delete(esmFullName);
					AppendReplicationLog(esmRelativeName);
				}
			}
			catch (Exception^) {
				// Swallow any exceptions and continue
			}

			// If the deleted file lies within the standard Starfield Data tree
			// delete its corresponding XBox transform, if there is one.
			String^ xboxFullname = StarfieldData::PCToXBoxNameTransform(fullname);
			if (nullptr != xboxFullname) {
				try {
					if (File::Exists(xboxFullname)) {
						File::Delete(xboxFullname);
						AppendReplicationLog(StarfieldData::GetRelativeName(xboxFullname));
					}
				}
				catch (Exception^) {
					// Swallow any exceptions and continue
				}
			}
		}
	}
	System::Void Replication::MaybeDeleteReplicaFolder(String^ fullname) {
		// Ensure that the deleted folder resides within one of our Data folders
		String^ relativeName = StarfieldData::GetRelativeName(fullname);
		if (nullptr == relativeName) {
			return;
		}

		// If the deleted folder lies within an ESP folder, delete the
		// corresponding folder under the corresponding ESM folder.
		String^ esmRelativeName = StarfieldData::EspToEsmNameTransform(relativeName);
		if (nullptr != esmRelativeName) {
			if (Util::DeleteFolder(StarfieldData::starfieldPrefix + esmRelativeName, nullptr)) {
				AppendReplicationLog(esmRelativeName);
			}

			// If the deleted folder has been replicated into the XBox tree,
			// also delete the XBox replica folder.
			String^ xboxFullname = StarfieldData::PCToXBoxNameTransform(fullname);
			if (nullptr != xboxFullname) {
				if (Util::DeleteFolder(xboxFullname, nullptr)) {
					AppendReplicationLog(StarfieldData::GetRelativeName(xboxFullname));
				}
			}
		}
	}
	bool Replication::MaybeRenameReplicaFiles(String^ oldFullName, String^ newFullName, String^ plugin) {
		// Renames should not change the folder name - verify that
		if (!Path::GetDirectoryName(oldFullName)->Equals(Path::GetDirectoryName(newFullName))) {
			return false;
		}

		// Get the relative names for the old and new files.
		// Both must reside within one of the Data directory trees.
		String^ oldRelativeName = StarfieldData::GetRelativeName(oldFullName);
		String^ newRelativeName = StarfieldData::GetRelativeName(newFullName);
		if (nullptr == oldRelativeName || nullptr == newRelativeName) {
			return false;
		}

		// Check to see whether the renamed file is a localized WEM file that
		// should be restaged under the new name
		array<String^>^ names = PackDialog::MaybeRenamedStagedLocalizedWEMFile(
			oldFullName, newFullName, plugin);
		if (nullptr != names) {
			if (names->GetLength(0) == 1) {
				AppendReplicationLog(names[0]->Substring(StarfieldData::starfieldPrefix->Length));
			}
			else {
				// If we get here, then the renamed WEM file had a different
				// language tag, which means we have to model this as a
				// DELETE followed by a CREATE
				String^ originalOperation = currentEvent->Operation;
				String^ originalNewName = currentEvent->NewFilename;
				String^ originalFilename = currentEvent->Filename;
				currentEvent->NewFilename = String::Empty;
				currentEvent->Operation = L"DELETE";
				AppendReplicationLog(names[0]->Substring(StarfieldData::starfieldPrefix->Length));
				currentEvent->Operation = L"CREATE";
				currentEvent->Filename = StarfieldData::GetRelativeName(newFullName);
				AppendReplicationLog(names[1]->Substring(StarfieldData::starfieldPrefix->Length));
				currentEvent->Operation = originalOperation;
				currentEvent->Filename = originalFilename;
				currentEvent->NewFilename = originalNewName;
			}
		}

		// Check that the original file was one that would have been replicated
		if (!ShouldReplicate(oldFullName, plugin)) {
			return false;
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
					AppendReplicationLog(oldEsmRelativeName);
				}
			}
			catch (Exception^) {
				return false;
			}

			// If the renamed folder lies within the standard Starfield Data tree
			// rename its corresponding XBox replica, if there is one.
			String^ oldXboxFullname = StarfieldData::PCToXBoxNameTransform(oldFullName);
			String^ newXBoxFullName = StarfieldData::PCToXBoxNameTransform(newFullName);
			if (nullptr != oldXboxFullname && nullptr != newXBoxFullName) {
				try {
					if (File::Exists(oldXboxFullname)) {
						File::Move(oldXboxFullname, newXBoxFullName);
						AppendReplicationLog(StarfieldData::GetRelativeName(oldXboxFullname));
					}
				}
				catch (Exception^) {
					return false;
				}
			}
		}
		return true;
	}
	bool Replication::MaybeRenameReplicasFolders(String^ oldFullName, String^ newFullName) {
		// Get the relative names for the old and new files
		String^ oldRelativeName = StarfieldData::GetRelativeName(oldFullName);
		String^ newRelativeName = StarfieldData::GetRelativeName(newFullName);
		if (nullptr == oldRelativeName || nullptr == newRelativeName) {
			return false;
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
					AppendReplicationLog(oldEsmRelativeName);
				}
			}
			catch (Exception^) {
				return false;
			}

			// If the renamed file lies within the standard Starfield Data tree
			// rename its corresponding XBox replica, if there is one.
			String^ oldXboxFullname = StarfieldData::PCToXBoxNameTransform(oldFullName);
			String^ newXBoxFullName = StarfieldData::PCToXBoxNameTransform(newFullName);
			if (nullptr != oldXboxFullname && nullptr != newXBoxFullName) {
				try {
					if (Directory::Exists(oldXboxFullname)) {
						Directory::Move(oldXboxFullname, newXBoxFullName);
						AppendReplicationLog(StarfieldData::GetRelativeName(oldXboxFullname));
					}
				}
				catch (Exception^) {
					return false;
				}
			}
		}
		return true;
	}
	String^ Replication::EspToEsmReplication(String^ espRelativeName, IWin32Window^ caller) {
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
	bool Replication::ShouldReplicate(String^ fullname, String^ plugin) {
		if (NORMAL_FILE != Util::ClassifyFile(fullname)) {
			return false;
		}

		// Ignore any file not under the Starfield Data or Starfield XBox folders,
		// excluding the Data\Backup folder
		if (!StarfieldData::FileResidesWithinAnyDataFolder(fullname) ||
			Util::HasPrefix(fullname, StarfieldData::starfieldBackupPrefix)) {
			return false;
		}

		// Ignore files whose extensions are in the configured audit filter list
		ListView::ListViewItemCollection^ filters = AuditFilterDialog::singleton->GetAuditFilters();
		for (int i = 0; i < filters->Count; i++) {
			if (Util::HasSuffix(fullname, filters[i]->Text)) {
				return false;
			}
		}

		// Also the WISE.DAT & TEMP.WEM files that are generated by WWise.
		// Ignore the MOTDImage as it could have been changed by something else.
		// And anything inside of Starfield's Data\Backup folder.
		if (Util::HasSuffix(fullname, L"\\TEMP.WEM") ||
			Util::HasSuffix(fullname, L"\\WWISE.DAT") ||
			Util::HasSuffix(fullname, L"\\MOTDIMAGE.PNG")) {
			return false;
		}

		// Ignore any metadata files related to voice localization
		if (PackDialog::isLocalizationFile(fullname)) {
			return false;
		}

		// Filter out any files that appear to reside in a plugin-specific directory
		// other than the one currently selected.
		return StarfieldData::FileRelatedToPlugIn(fullname, plugin);
	}

}
