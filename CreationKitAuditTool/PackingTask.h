#pragma once

#include "ArchiveType.h"

using namespace System;
using namespace System::Collections;

namespace CreationKitAuditTool {

	public ref class PackingTask
	{
	/**
	* Generalized constructor
	* @param spec - The type of spec to pack
	* @param plugin - The name of the plugin we are packing
	*/
	public: PackingTask(ArchiveType^ spec,String^ plugin) :
		Format(spec->Format),
		Compression(spec->Compression),
		Files(gcnew Generic::List<String^>),
		ArchiveName(spec->GetArchiveName(plugin)) {}
	protected: ~PackingTask() {}

	public: String^ Format;
	public: String^ Compression;
	public: Generic::List<String^>^ Files;
	public: String^ ArchiveName;
	};
}
