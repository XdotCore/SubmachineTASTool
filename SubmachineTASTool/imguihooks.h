#pragma once

#include <d3d11.h>

typedef HWND(__stdcall* CreateWindowExWFunc)(DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
typedef HRESULT(__stdcall* IDXGISwapChain_PresentFunc) (IDXGISwapChain*, UINT, UINT);
typedef HRESULT(__stdcall* IDXGISwapChain_ResizeBuffersFunc)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

void AttachImGuiHooks();
void DetachImGuiHooks();