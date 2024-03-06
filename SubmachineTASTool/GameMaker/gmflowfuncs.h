#pragma once

namespace GM {

	typedef void(__cdecl* VoidFunc)();
	typedef double(__cdecl* DoubleFunc)();

	extern VoidFunc MainLoop;
	// In MainLoop
	extern VoidFunc DoStep;
	//In DoStep
	extern VoidFunc DoIO;
	extern VoidFunc DoUpdate;
	extern VoidFunc DoDraw;

}
