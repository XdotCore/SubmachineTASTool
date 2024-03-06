#include "gmflowfuncs.h"

namespace GM {

	VoidFunc MainLoop = (VoidFunc)(0x1AF8B0);
	// In MainLoop
	VoidFunc DoStep = (VoidFunc)(0x1AF190);
	//In DoStep
	VoidFunc DoIO = (VoidFunc)(0x1AEFD0);
	VoidFunc DoUpdate = (VoidFunc)(0x1AE2C0);
	VoidFunc DoDraw = (VoidFunc)(0x1AE970);

}