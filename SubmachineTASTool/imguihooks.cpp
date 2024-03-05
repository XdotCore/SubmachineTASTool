#include <windows.h>
#include <filesystem>
#include <iostream>
#include <d3d11.h>
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "dxvtables.h"
#include "ImGUIHooks.h"
#include "hooking.h"
#include "tas.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool showImGui = true;
HWND window = nullptr;
bool isImGuiSetUp = false;

bool usingD3d11 = false;
ID3D11Device* device11 = nullptr;
ID3D11DeviceContext* context = nullptr;
ID3D11RenderTargetView* renderTargetView = nullptr;

WNDPROC TrueWndProc;
LRESULT FakeWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (!isImGuiSetUp)
        return TrueWndProc(hWnd, msg, wParam, lParam);

    if (!showImGui && msg == WM_SETCURSOR) {
        // Keep game chosen cursor if imgui isn't showing
        bool trueResult = TrueWndProc(hWnd, msg, wParam, lParam);
        HCURSOR cursor = GetCursor();
        bool result = ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
        SetCursor(cursor);
        if (result)
            return true;
        else
            return trueResult;
    } else if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
        return true;

    static ImGuiIO& io = ImGui::GetIO();
    if (io.WantCaptureMouse)
        return DefWindowProc(hWnd, msg, wParam, lParam);

    return TrueWndProc(hWnd, msg, wParam, lParam);
}

CreateWindowExWFunc RealCreateWindowExW = CreateWindowExW;
CreateWindowExWFunc FakeCreateWindowExW = [](DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) {
    HWND result = RealCreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);

    wchar_t className[256];
    GetClassName(result, className, 256);
    if (wcscmp(className, L"YYGameMakerYY") == 0) {
        window = result;

        TrueWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)FakeWndProc);
    }

    return result;
};

void PlatformIndependentImGuiSetup() {
    IMGUI_CHECKVERSION();
    ImGuiContext* ctx = ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui::StyleColorsDark();

    if (!std::filesystem::exists("SubmachineTASTool/"))
        std::filesystem::create_directory("SubmachineTASTool/");
    io.IniFilename = "SubmachineTASTool/imgui.ini";
}

void DrawImGui() {
    ImGui::NewFrame();

    showImGui = DrawTASGui();

    if (showImGui)
        ImGui::ShowDemoWindow();

    ImGui::EndFrame();
    ImGui::Render();
}

void CreateRenderTarget(IDXGISwapChain* swapChain) {
    ID3D11Texture2D* backBuffer = nullptr;
    swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    device11->CreateRenderTargetView(backBuffer, NULL, &renderTargetView);
    backBuffer->Release();
}

void CleanupRenderTarget() {
    if (renderTargetView) {
        renderTargetView->Release();
        renderTargetView = nullptr;
    }
}

IDXGISwapChain_PresentFunc RealIDXGISwapChain_Present;
IDXGISwapChain_PresentFunc FakeIDXGISwapChain_Present = [](IDXGISwapChain* This, UINT SyncInterval, UINT Flags) {
    if (!isImGuiSetUp) {
        CreateRenderTarget(This);
        isImGuiSetUp = true;
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();

    DrawImGui();

    context->OMSetRenderTargets(1, &renderTargetView, NULL);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    return RealIDXGISwapChain_Present(This, SyncInterval, Flags);
};

// render target view needs to be gone when the game tries to resize the window, as is said in the ms docs
IDXGISwapChain_ResizeBuffersFunc RealIDXGISwapChain_ResizeBuffers;
IDXGISwapChain_ResizeBuffersFunc FakeIDXGISwapChain_ResizeBuffers = [](IDXGISwapChain* This, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags) {
    CleanupRenderTarget();
    HRESULT result = RealIDXGISwapChain_ResizeBuffers(This, BufferCount, Width, Height, NewFormat, SwapChainFlags);
    CreateRenderTarget(This);
    return result;
};

PFN_D3D11_CREATE_DEVICE RealD3D11CreateDevice;
PFN_D3D11_CREATE_DEVICE FakeD3D11CreateDevice = [](IDXGIAdapter* pAdapter, D3D_DRIVER_TYPE DriverType, HMODULE Software, UINT Flags, CONST D3D_FEATURE_LEVEL* pFeatureLevels, UINT FeatureLevels, UINT SDKVersion, ID3D11Device** ppDevice, D3D_FEATURE_LEVEL* pFeatureLevel, ID3D11DeviceContext** ppImmediateContext) {
    HRESULT result = RealD3D11CreateDevice(pAdapter, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion, ppDevice, pFeatureLevel, ppImmediateContext);

    IDXGIFactory1* dummyFactory = nullptr;
    if (FAILED(CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&dummyFactory))) {
        MessageBox(NULL, L"Failed to get dx11 factory1.", L"Failed", MB_OK);
        return result;
    }

    DXGI_SWAP_CHAIN_DESC dummyDesc;
    ZeroMemory(&dummyDesc, sizeof(dummyDesc));
    // This is the minimum needed to be set for it to work
    dummyDesc.BufferCount = 1;
    dummyDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    dummyDesc.OutputWindow = window;
    dummyDesc.SampleDesc.Count = 1;
    dummyDesc.Windowed = true;

    IDXGISwapChain* dummySwapChain = nullptr;

    if (FAILED(dummyFactory->CreateSwapChain(*ppDevice, &dummyDesc, &dummySwapChain))) {
        MessageBox(NULL, L"Failed to get dx11 swapchain.", L"Failed", MB_OK);
        return result;
    }

    RealIDXGISwapChain_Present = (IDXGISwapChain_PresentFunc)vtblPresent(dummySwapChain);
    RealIDXGISwapChain_ResizeBuffers = (IDXGISwapChain_ResizeBuffersFunc)vtblResizeBuffers(dummySwapChain);

    BeginHooking();
    AttachHook("IDXGISwapChain.Present", &RealIDXGISwapChain_Present, FakeIDXGISwapChain_Present);
    AttachHook("IDXGISwapChain.ResizeBuffers", &RealIDXGISwapChain_ResizeBuffers, FakeIDXGISwapChain_ResizeBuffers);
    CommitHooking();

    dummySwapChain->Release();

    PlatformIndependentImGuiSetup();
    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(*ppDevice, *ppImmediateContext);

    device11 = *ppDevice;
    context = *ppImmediateContext;

    return result;
};

void AttachImGuiHooks() {
    BeginHooking();
    AttachHook("CreateWindowExW", &RealCreateWindowExW, FakeCreateWindowExW);

    HMODULE d3d11 = GetModuleHandle(L"d3d11.dll");
    usingD3d11 = d3d11;
    RealD3D11CreateDevice = (PFN_D3D11_CREATE_DEVICE)GetProcAddress(d3d11, "D3D11CreateDevice");
    AttachHook("D3D11CreateDevice", &RealD3D11CreateDevice, FakeD3D11CreateDevice);

    CommitHooking();
}

void DetachImGuiHooks() {
    BeginHooking();
    DetachHook("CreateWindowExW", &RealCreateWindowExW, FakeCreateWindowExW);

    DetachHook("D3D11CreateDevice", &RealD3D11CreateDevice, FakeD3D11CreateDevice);
    DetachHook("IDXGISwapChain.Present", &RealIDXGISwapChain_Present, FakeIDXGISwapChain_Present);
    DetachHook("IDXGISwapChain.ResizeBuffers", &RealIDXGISwapChain_ResizeBuffers, FakeIDXGISwapChain_ResizeBuffers);

    CommitHooking();

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}