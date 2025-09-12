#pragma once
using namespace System;

namespace CreationKitAuditTool {

    ref class AbortException : public Exception
    {
        public: AbortException(String^ reason, Exception^ cause) : Exception(reason, cause) {
        }

        protected: ~AbortException() {
        }
    };

}
