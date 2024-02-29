#pragma once

#include <string>
#include <iomanip>

static void PrintAddress(std::string name, intptr_t ptr) {
    std::cout << name << ": 0x" << std::uppercase << std::setfill('0') << std::setw(8) << std::hex << ptr << std::endl;
}

template<typename T>
static void AttachHook(std::string name, T* real, T fake) {
    PrintAddress(std::format("Attached {}", name).c_str(), *(intptr_t*)real);
    DetourAttach((void**)real, fake);
}

template<typename T>
static void DetachHook(std::string name, T* real, T fake) {
    PrintAddress(std::format("Detached {}", name).c_str(), *(intptr_t*)real);
    DetourDetach((void**)real, fake);
}

template<typename T>
static void AttachGameHook(std::string name, T* real, T fake) {
    static intptr_t gameStart = (intptr_t)GetModuleHandle(NULL);

    *(intptr_t*)real += gameStart;
    AttachHook(name, real, fake);
}

template<typename T>
static void AttachGameNoHook(std::string name, T* ptr) {
    static intptr_t gameStart = (intptr_t)GetModuleHandle(NULL);

    PrintAddress(std::format("Attached (No Hook) {}", name).c_str(), *(intptr_t*)ptr += gameStart);
}
