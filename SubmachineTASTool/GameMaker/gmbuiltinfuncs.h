#pragma once

#include "rvalue.h"

// Gamemaker builtin funcs
namespace GM {

	typedef void(__cdecl* BuiltinFunc)(RValue* result, CInstance* self, CInstance* other, int argCount, RValue* args);

	extern BuiltinFunc randomise;
	extern BuiltinFunc random_set_seed;

}
