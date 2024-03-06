#pragma once

#include "rvalue.h"
#include "cinstance.fwd.h"
#include "rtoken.h"

namespace GM {

	typedef void(__cdecl* PFUNC_YYGML)(CInstance* self, CInstance* other);
	typedef RValue* (__cdecl* PFUNC_YYGMLScript)(CInstance* self, CInstance* other, RValue* result, int argCount, RValue** args);
	typedef void(__cdecl* PFUNC_RAW)();

	struct YYGMLFunc {
		const char* m_Name;
		union YYGMLFuncUnion {
			PFUNC_YYGMLScript m_ScriptFunction;
			PFUNC_YYGML m_CodeFunction;
			PFUNC_RAW m_RawFunction;
		} func;
		void* m_FunctionVariables;
	};

	struct CCode {
		int (**_vptr$CCode)(void);
		CCode* m_Next;
		int m_Kind;
		int m_Compiled;
		const char* m_Str;
		RToken m_Token;
		RValue m_Value;
		void* m_VmInstance;
		void* m_VmDebugInfo;
		char* m_Code;
		const char* m_Name;
		int m_CodeIndex;
		YYGMLFunc* m_Functions;
		bool m_Watch;
		int m_Offset;
		int m_LocalsCount;
		int m_ArgsCount;
		int m_Flags;
		YYObjectBase* m_Prototype;
	};

}
