#pragma once

#include "ccode.h"

namespace GM {

	struct CScript {
		int (**_vptr$CScript)(void);
		CCode* m_Code;
		YYGMLFunc* m_Functions;
		CInstance* m_StaticObject;
		union CScriptUnion {
			const char* m_Script;
			int m_CompiledIndex;
		} script;
		const char* m_Name;
		int m_Offset;
	};

}
