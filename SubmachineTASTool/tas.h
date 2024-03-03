#pragma once

#include "rvalue.h"

typedef void(__cdecl* VoidFunc)();
typedef double(__cdecl* DoubleFunc)();
typedef void(__cdecl* GMLFunc)(RValue* result, void* self, void* other, int argCount, RValue* args);

void AttachHooks();
void DetachHooks();

bool DrawTASGui();