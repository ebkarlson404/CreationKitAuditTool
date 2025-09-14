#pragma once

#include "ReplicationEvent.h"

using namespace System::Collections;
using namespace Windows::Forms;

namespace CreationKitAuditTool {

	ref class Replication
	{
	public: static ReplicationEvent^ currentEvent = gcnew ReplicationEvent;
	private: static int replicationLogSize = 1000;
	public: static Generic::List<ReplicationEvent^>^ replicationLog = gcnew Generic::List<ReplicationEvent^>;

	private: static System::Void AppendReplicationLog(String^ target);
	/**
	* Used by the background continuous replication logic to replicate
	* a newly discovered file if it should be replicated.
	* @param fullname - The full name of the file to process
	* @param plugin - The name of the current plugin
	*/
	public: static bool MaybeReplicateFile(String^ fullname, String^ plugin);
	/**
	* Given the name of a deleted file, check to see if there are any
	* ESP->ESM replicas of the deleted file.  If so, delete the
	* replicas.
	* @param fullname - The full name of the deleted file
	* @param plugin - The name of the current plugin
	*/
	public: static System::Void MaybeDeleteReplicaFile(String^ fullname, String^ plugin);
	/**
	* Given the name of a delete folder, check to see if there are any
	* ESP->ESM replicas of the deleted folder.  If so, delete the replcas.
	* @param fullname - The full name of the deleted folder
	*/
	public: static System::Void MaybeDeleteReplicaFolder(String^ fullname);
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
	public: static String^ EspToEsmReplication(String^ espRelativeName, IWin32Window^ caller);
	/**
	* Replicate the rename of a source file onto any replicas of the file.
	* If the ESM replica of the file does not exist, this is a noop.
	* @param oldFullName - The original name of the object
	* @param newFullName - The new name of the object
	* @param plugin - The name of the current plugin
	* @returns true if the operation did something, false if not
	*/
	public: static bool MaybeRenameReplicaFiles(String^ oldFullName, String^ newFullName, String^ plugin);	/**
	* Given a renamed folder, apply the same renaming to any replicas of the folder.
	* @param oldFullName - The original full name of the folder
	* @param newFullName - The new full name of the folder
	* @returns true if all something was done, false otherwise
	*/
	public: static bool MaybeRenameReplicasFolders(String^ oldFullName, String^ newFullName);
	/**
	* Checks to see whether a given file is a candidate for ESP->ESM replication.
	* @param fullname - The full name of the file to check
	* @param plugin - The name of the current plugin
	* @return true if the file is an ESP->ESM replication candidate, false otherwise
	*/
	public: static bool ShouldReplicate(String^ fullname, String^ plugin);
	};

}
