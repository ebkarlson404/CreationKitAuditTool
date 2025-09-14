#pragma once

using namespace System;

namespace CreationKitAuditTool {

	public ref class ReplicationEvent
	{
	public: ReplicationEvent() {
		this->Operation = L"";
		this->Filename = L"";
		this->NewFilename = L"";
		this->Target = L"";
	}
	public: ReplicationEvent(ReplicationEvent^ other) {
		this->Timestamp = other->Timestamp;
		this->Operation = other->Operation;
		this->Filename = other->Filename;
		this->NewFilename = other->NewFilename;
		this->Target = other->Target;
	}

	public: System::Void Stamp(String^ operation, String^ filename) {
		this->Timestamp = DateTime::Now;
		this->Operation = operation;
		this->Filename = filename;
		this->NewFilename = L"";
		this->Target = L"";
	}
	public: System::Void Stamp(String^ operation, String^ newFilename, String^ oldFilename) {
		this->Timestamp = DateTime::Now;
		this->Operation = operation;
		this->Filename = newFilename;
		this->NewFilename = oldFilename;
		this->Target = L"";
	}
	public: ReplicationEvent^ CopyWithTarget(String^ target) {
		ReplicationEvent^ copy = gcnew ReplicationEvent(this);
		copy->Target = target;
		return copy;
	}

	public: DateTime Timestamp;
	public: String^ Operation;
	public: String^ Filename;
	public: String^ NewFilename;
	public: String^ Target;
	};

}
