#pragma once

#include "rvalue.h"

typedef void(__cdecl* DoIOFunc)();
typedef void(__cdecl* DoUpdateFunc)();
typedef void(__cdecl* DoDrawFunc)();
typedef void(__cdecl* GMLFunc)(RValue* result, void* self, void* other, int argCount, RValue* args);

void AttachHooks();
void DetachHooks();

bool DrawTASGui();