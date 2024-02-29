#define CINTERFACE
#include <dxgi.h>
#include "DXVtables.h"

void* vtblPresent(IDXGISwapChain* swapChain) {
	return swapChain->lpVtbl->Present;
}

void* vtblResizeBuffers(IDXGISwapChain* swapChain) {
	return swapChain->lpVtbl->ResizeBuffers;
}
