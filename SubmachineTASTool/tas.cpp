#include <windows.h>
#include <shobjidl.h> 
#include <fstream>
#include <iostream>
#include <format>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include "detours/detours.h"
#include "imgui.h"
#include "hooking.h"
#include "tas.h"
#include "input.h"
#include "file.h"

bool showGui = true;
bool showWindowsCursor = false;

bool recording = false;
std::vector<FrameInput> inputRecording;
std::vector<unsigned int> inputRandomSeeds;

bool playing = false;
int frame = 0;
int seedIndex = 0;

bool frameStepping = false;
bool stepFrame = false;
bool stepNextFrame = false;

void ChangedShowWindowsCursor() {
    *hCursor = showWindowsCursor ? LoadCursor(NULL, IDC_ARROW) : NULL;
    SetCursor(*hCursor);
}

void ChangedRecording() {
    playing = false;

    if (recording) {
        inputRecording.clear();
        inputRandomSeeds.clear();
        std::cout << "Recording input..." << std::endl;
    }
    else
        std::cout << "Stop recording input..." << std::endl;
}

void ChangedPlaying() {
    recording = false;

    if (playing) {
        frame = 0;
        seedIndex = 0;
        std::cout << "Playing input..." << std::endl;
    }
    else
        std::cout << "Stop playing input..." << std::endl;
}

void SaveInput() {
    COMDLG_FILTERSPEC filter[2] = {};
    filter[0].pszSpec = L"*.*";
    filter[0].pszName = L"Any *.*";
    filter[1].pszSpec = L"*.tas";
    filter[1].pszName = L"TAS input *.tas";
    std::wstring saveFileName = GetSaveFile(L"Save Input", filter, 2, 1);
    if (saveFileName.empty())
        return;

    std::ofstream saveFile;
    saveFile.open(saveFileName, std::ios::out | std::ios::trunc);

    saveFile << "randomSeeds" << '\n';
    for (int i = 0; i < inputRandomSeeds.size(); i++)
        saveFile << inputRandomSeeds[i] << '\n';
    saveFile << "end" << '\n';

    saveFile << "recording" << '\n';
    for (int i = 0; i < inputRecording.size(); i++) {
        saveFile << "frame" << '\n';
        saveFile << inputRecording[i].Serialize();
        saveFile << "end" << '\n';
    }
    saveFile << "end" << '\n';

    saveFile.close();
}

void LoadInput() {
    COMDLG_FILTERSPEC filter[2] = {};
    filter[0].pszSpec = L"*.*";
    filter[0].pszName = L"Any *.*";
    filter[1].pszSpec = L"*.tas";
    filter[1].pszName = L"TAS input *.tas";
    std::wstring loadFileName = GetOpenFile(L"Load Input", filter, 2, 1);
    if (loadFileName.empty())
        return;

    std::ifstream loadFile;
    loadFile.open(loadFileName, std::ios::in);

    inputRandomSeeds.clear();
    inputRecording.clear();

    std::string line;
    while (std::getline(loadFile, line, '\n')) {
        if (line == "randomSeeds") {
            while (std::getline(loadFile, line, '\n')) {
                if (line == "end")
                    break;

                inputRandomSeeds.push_back(std::stoi(line));
            }
        }
        else if (line == "recording") {
            while (std::getline(loadFile, line, '\n')) {
                if (line == "end")
                    break;

                if (line == "frame") {
                    FrameInput frame = {};
                    frame.Unserialize(loadFile);

                    inputRecording.push_back(frame);
                }
            }
        }
    }
}

void ChangedFrameStepping() {
    if (frameStepping)
        stepFrame = false;
}

// TODO: not have the locations hardcoded
DoIOFunc RealDoIO = (DoIOFunc)(0x1AEFD0);
DoUpdateFunc RealDoUpdate = (DoUpdateFunc)(0x1AE2C0);
DoDrawFunc RealDoDraw = (DoDrawFunc)(0x1AE970);
GMLFunc Real_randomise = (GMLFunc)(0x22EDB0);
GMLFunc random_set_seed = (GMLFunc)(0x22ED10);

DoUpdateFunc FakeDoIO = []() {
    RealDoIO();
    if (isKeyPressed[VirtualKey::vk_f3]) {
        showGui = !showGui;
    }
    else if (isKeyPressed[VirtualKey::vk_f4]) {
        showWindowsCursor = !showWindowsCursor;
        ChangedShowWindowsCursor();
    }
    else if (isKeyPressed[VirtualKey::vk_f5]) {
        recording = !recording;
        ChangedRecording();
    }
    else if (isKeyPressed[VirtualKey::vk_f6]) {
        playing = !playing;
        ChangedPlaying();
    }
    else if (isKeyPressed[VirtualKey::vk_f7]) {
        SaveInput();
    }
    else if (isKeyPressed[VirtualKey::vk_f8]) {
        LoadInput();
    }
    else if (isKeyPressed[VirtualKey::vk_f9]) {
        frameStepping = !frameStepping;
        ChangedFrameStepping();
    }
    else if (isKeyPressed[VirtualKey::vk_f10]) {
        stepNextFrame = true;
    }
    else if (frameStepping) {
        if (stepNextFrame) {
            stepNextFrame = false;
            stepFrame = true;
        }
        else if (!stepFrame) {
            if (std::any_of(isKeyPressed, &isKeyPressed[255], [](bool key) { return key; }) ||
                std::any_of(isMouseButtonPressed, &isMouseButtonPressed[4], [](bool key) { return key; }))
                stepFrame = true;
        }
        else
            stepFrame = false;
    }

    if (frameStepping && !stepFrame)
        return;

    if (recording) {
        FrameInput frameInput = {};

        memcpy_s(frameInput.isKeyPressed, 256, isKeyPressed, 256);
        memcpy_s(frameInput.isKeyReleased, 256, isKeyReleased, 256);
        memcpy_s(frameInput.isKeyDown, 256, isKeyDown, 256);
        memcpy_s(frameInput.isMouseButtonPressed, 5, isMouseButtonPressed, 5);
        memcpy_s(frameInput.isMouseButtonReleased, 5, isMouseButtonReleased, 5);
        memcpy_s(frameInput.isMouseButtonDown, 5, isMouseButtonDown, 5);

        frameInput.mouse_x = *mouse_x;
        frameInput.mouse_y = *mouse_y;

        inputRecording.push_back(frameInput);
    }
    else if (playing) {
        if (frame >= inputRecording.size()) {
            playing = false;
            std::cout << "Stop playing input..." << std::endl;
        }
        else {
            FrameInput frameInput = inputRecording[frame++];

            memcpy_s(isKeyPressed, 256, frameInput.isKeyPressed, 256);
            memcpy_s(isKeyReleased, 256, frameInput.isKeyReleased, 256);
            memcpy_s(isKeyDown, 256, frameInput.isKeyDown, 256);
            memcpy_s(isMouseButtonPressed, 5, frameInput.isMouseButtonPressed, 5);
            memcpy_s(isMouseButtonReleased, 5, frameInput.isMouseButtonReleased, 5);
            memcpy_s(isMouseButtonDown, 5, frameInput.isMouseButtonDown, 5);

            *mouse_x = frameInput.mouse_x;
            *mouse_y = frameInput.mouse_y;
        }
    }
};

DoUpdateFunc FakeDoUpdate = []() {
    if (frameStepping && !stepFrame)
        return;

    RealDoUpdate();
};

DoDrawFunc FakeDoDraw = []() {
    if (frameStepping && !stepFrame)
        return;

    RealDoDraw();
};

GMLFunc Fake_randomise = [](RValue* result, void* self, void* other, int argCount, RValue* args) {
    if (recording) {
        Real_randomise(result, self, other, argCount, args);
        unsigned int seed = (unsigned int)result->value.val;
        std::cout << "recording seed: " << seed << std::endl;
        std::cout << "recording seed: " << result->value.val << std::endl;
        std::cout << "recording seed: " << result->value.v32 << std::endl;
        std::cout << "recording seed: " << result->value.v64 << std::endl;
        inputRandomSeeds.push_back(seed);
    }
    else if (playing) {
        if (seedIndex >= inputRandomSeeds.size()) {
            playing = false;
            std::cout << "Stop playing input..." << std::endl;
        }
        else {
            unsigned int seed = inputRandomSeeds[seedIndex++];
            std::cout << "playing seed: " << seed << std::endl;
            RValue _result = {};
            RValue _args = {};
            _args.kind = ValueType::Real;
            _args.value.val = (double)seed;
            random_set_seed(&_result, nullptr, nullptr, 1, &_args);
            result->kind = ValueType::Real;
            result->value.val = (double)seed;
        }
    }
    else
        Real_randomise(result, self, other, argCount, args);
};

void AttachHooks() {
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    AttachGameHook("DoIO", &RealDoIO, FakeDoIO);
    AttachGameHook("DoUpdate", &RealDoUpdate, FakeDoUpdate);
    AttachGameHook("DoDraw", &RealDoDraw, FakeDoDraw);
    AttachGameHook("randomise", &Real_randomise, Fake_randomise);
    DetourTransactionCommit();

    AttachGameNoHook("hCursor", &hCursor);
    AttachGameNoHook("isKeyReleased", &isKeyReleased);
    AttachGameNoHook("isKeyPressed", &isKeyPressed);
    AttachGameNoHook("isKeyDown", &isKeyDown);
    AttachGameNoHook("isMouseButtonReleased", &isMouseButtonReleased);
    AttachGameNoHook("isMouseButtonPressed", &isMouseButtonPressed);
    AttachGameNoHook("isMouseButtonDown", &isMouseButtonDown);
    AttachGameNoHook("mouse_x", &mouse_x);
    AttachGameNoHook("mouse_y", &mouse_y);
    AttachGameNoHook("random_set_seed", &random_set_seed);
}

void DetachHooks() {
    DetourTransactionBegin();
    DetourUpdateThread(GetCurrentThread());
    DetachHook("DoIO", &RealDoIO, FakeDoIO);
    DetachHook("DoUpdate", &RealDoUpdate, FakeDoUpdate);
    DetachHook("DoDraw", &RealDoDraw, FakeDoDraw);
    DetachHook("randomise", &Real_randomise, Fake_randomise);
    DetourTransactionCommit();
}

bool DrawTASGui() {
    if (!showGui)
        return showGui;

    ImGui::SetNextWindowSize(ImVec2(0, 0), ImGuiCond_Once);
    ImGui::Begin("TAS (F3)", &showGui);

    if (ImGui::Checkbox("Show windows cursor", &showWindowsCursor))
        ChangedShowWindowsCursor();
    ImGui::SameLine();
    ImGui::TextDisabled("(F4)");
    ImGui::NewLine();

    if (!ImGui::BeginTable("Controls", 4, ImGuiTableFlags_SizingFixedFit))
        return showGui;

    ImGui::TableNextColumn();
    if (ImGui::Checkbox("Recording", &recording))
        ChangedRecording();
    ImGui::TableNextColumn();
    ImGui::TextDisabled("(F5)");

    ImGui::TableNextColumn();
    if (ImGui::Checkbox("Playing", &playing))
        ChangedPlaying();
    ImGui::TableNextColumn();
    ImGui::TextDisabled("(F6)");

    ImGui::TableNextColumn();
    if (ImGui::Button("Save input"))
        SaveInput();
    ImGui::TableNextColumn();
    ImGui::TextDisabled("(F7)");

    ImGui::TableNextColumn();
    if (ImGui::Button("Load input"))
        LoadInput();
    ImGui::TableNextColumn();
    ImGui::TextDisabled("(F8)");

    ImGui::TableNextColumn();
    ImGui::NewLine();
    ImGui::TableNextRow();

    ImGui::TableNextColumn();
    if (ImGui::Checkbox("Frame stepping", &frameStepping))
        ChangedFrameStepping();
    ImGui::TableNextColumn();
    ImGui::TextDisabled("(F9)");

    ImGui::TableNextColumn();
    if (ImGui::Button("Step frame"))
        stepNextFrame = true;
    ImGui::TableNextColumn();
    ImGui::TextDisabled("(F10)");

    ImGui::EndTable();

    ImGui::End();
    return showGui;
}
