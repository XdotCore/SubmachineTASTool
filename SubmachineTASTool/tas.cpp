#include <windows.h>
#include <fstream>
#include <iostream>
#include <format>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#include <sstream>
#include "imgui.h"
#include "hooking.h"
#include "tas.h"
#include "input.h"
#include "file.h"
#include "GameMaker/ccode.h"
#include "GameMaker/croom.h"
#include "GameMaker/gmflowfuncs.h"
#include "GameMaker/gmbuiltinfuncs.h"

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
    *GM::hCursor = showWindowsCursor ? LoadCursor(NULL, IDC_ARROW) : NULL;
    SetCursor(*GM::hCursor);
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

void ToggledFrameStepping() {
    if (frameStepping)
        stepFrame = false;
}

GM::VoidFunc FakeMainLoop = []() {
    GM::MainLoop();
};

GM::VoidFunc FakeDoStep = []() {
    GM::DoStep();
};

GM::VoidFunc FakeDoIO = []() {
    GM::DoIO();
    if (GM::isKeyPressed[GM::VirtualKey::vk_f1]) {
        showGui = !showGui;
    }
    else if (GM::isKeyPressed[GM::VirtualKey::vk_f2]) {
        showWindowsCursor = !showWindowsCursor;
        ChangedShowWindowsCursor();
    }
    else if (GM::isKeyPressed[GM::VirtualKey::vk_f5]) {
        recording = !recording;
        ChangedRecording();
    }
    else if (GM::isKeyPressed[GM::VirtualKey::vk_f6]) {
        playing = !playing;
        ChangedPlaying();
    }
    else if (GM::isKeyPressed[GM::VirtualKey::vk_f7]) {
        SaveInput();
    }
    else if (GM::isKeyPressed[GM::VirtualKey::vk_f8]) {
        LoadInput();
    }
    else if (GM::isKeyPressed[GM::VirtualKey::vk_f9]) {
        frameStepping = !frameStepping;
        ToggledFrameStepping();
    }
    else if (GM::isKeyPressed[GM::VirtualKey::vk_f10]) {
        stepNextFrame = true;
    }
    else if (frameStepping) {
        if (stepNextFrame) {
            stepNextFrame = false;
            stepFrame = true;
        }
        else if (!stepFrame) {
            if (std::any_of(GM::isKeyPressed, &GM::isKeyPressed[255], [](bool key) { return key; }) ||
                std::any_of(GM::isMouseButtonPressed, &GM::isMouseButtonPressed[4], [](bool key) { return key; }))
                stepFrame = true;
        }
        else
            stepFrame = false;
    }

    if (frameStepping && !stepFrame)
        return;

    if (recording) {
        FrameInput frameInput = {};

        memcpy_s(frameInput.isKeyPressed, 256, GM::isKeyPressed, 256);
        memcpy_s(frameInput.isKeyReleased, 256, GM::isKeyReleased, 256);
        memcpy_s(frameInput.isKeyDown, 256, GM::isKeyDown, 256);
        memcpy_s(frameInput.isMouseButtonPressed, 5, GM::isMouseButtonPressed, 5);
        memcpy_s(frameInput.isMouseButtonReleased, 5, GM::isMouseButtonReleased, 5);
        memcpy_s(frameInput.isMouseButtonDown, 5, GM::isMouseButtonDown, 5);

        frameInput.mouseX = *GM::mouseX;
        frameInput.mouseY = *GM::mouseY;

        inputRecording.push_back(frameInput);
    }
    else if (playing) {
        if (frame >= inputRecording.size()) {
            playing = false;
            std::cout << "Stop playing input..." << std::endl;
        }
        else {
            FrameInput frameInput = inputRecording[frame++];

            memcpy_s(GM::isKeyPressed, 256, frameInput.isKeyPressed, 256);
            memcpy_s(GM::isKeyReleased, 256, frameInput.isKeyReleased, 256);
            memcpy_s(GM::isKeyDown, 256, frameInput.isKeyDown, 256);
            memcpy_s(GM::isMouseButtonPressed, 5, frameInput.isMouseButtonPressed, 5);
            memcpy_s(GM::isMouseButtonReleased, 5, frameInput.isMouseButtonReleased, 5);
            memcpy_s(GM::isMouseButtonDown, 5, frameInput.isMouseButtonDown, 5);

            *GM::mouseX = frameInput.mouseX;
            *GM::mouseY = frameInput.mouseY;
        }
    }
};

GM::VoidFunc FakeDoUpdate = []() {
    if (frameStepping && !stepFrame)
        return;

    GM::DoUpdate();
};

GM::VoidFunc FakeDoDraw = []() {
    if (frameStepping && !stepFrame)
        return;

    GM::DoDraw();
};

GM::BuiltinFunc Fake_randomise = [](GM::RValue* result, GM::CInstance* self, GM::CInstance* other, int argCount, GM::RValue* args) {
    if (recording) {
        GM::randomise(result, self, other, argCount, args);
        unsigned int seed = (unsigned int)result->value.val;
        inputRandomSeeds.push_back(seed);
    }
    else if (playing) {
        if (seedIndex >= inputRandomSeeds.size()) {
            playing = false;
        }
        else {
            unsigned int seed = inputRandomSeeds[seedIndex++];
            GM::RValue _result = {};
            GM::RValue _args = {};
            _args.kind = GM::ValueType::Real;
            _args.value.val = (double)seed;
            GM::random_set_seed(&_result, nullptr, nullptr, 1, &_args);
            result->kind = GM::ValueType::Real;
            result->value.val = (double)seed;
        }
    }
    else
        GM::randomise(result, self, other, argCount, args);
};

void AttachHooks() {

    BeginHooking();
    AttachGameHook("MainLoop", &GM::MainLoop, FakeMainLoop);
    AttachGameHook("DoStep", &GM::DoStep, FakeDoStep);
    AttachGameHook("DoIO", &GM::DoIO, FakeDoIO);
    AttachGameHook("DoUpdate", &GM::DoUpdate, FakeDoUpdate);
    AttachGameHook("DoDraw", &GM::DoDraw, FakeDoDraw);
    AttachGameHook("randomise", &GM::randomise, Fake_randomise);
    CommitHooking();

    AttachGameNoHook("hCursor", &GM::hCursor);
    AttachGameNoHook("isKeyReleased", &GM::isKeyReleased);
    AttachGameNoHook("isKeyPressed", &GM::isKeyPressed);
    AttachGameNoHook("isKeyDown", &GM::isKeyDown);
    AttachGameNoHook("isMouseButtonReleased", &GM::isMouseButtonReleased);
    AttachGameNoHook("isMouseButtonPressed", &GM::isMouseButtonPressed);
    AttachGameNoHook("isMouseButtonDown", &GM::isMouseButtonDown);
    AttachGameNoHook("mouseX", &GM::mouseX);
    AttachGameNoHook("mouseY", &GM::mouseY);
    AttachGameNoHook("currentRoom", &GM::currentRoom);
    AttachGameNoHook("random_set_seed", &GM::random_set_seed);
}

void DetachHooks() {
    BeginHooking();
    DetachHook("DoIO", &GM::DoIO, FakeDoIO);
    DetachHook("DoUpdate", &GM::DoUpdate, FakeDoUpdate);
    DetachHook("DoDraw", &GM::DoDraw, FakeDoDraw);
    DetachHook("randomise", &GM::randomise, Fake_randomise);
    CommitHooking();
}

bool DrawTASGui() {
    if (!showGui)
        return showGui;

    ImGui::Begin("TAS (F1)", &showGui, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

    if (ImGui::Checkbox("Show windows cursor", &showWindowsCursor))
        ChangedShowWindowsCursor();
    ImGui::SameLine();
    ImGui::TextDisabled("(F2)");
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
        ToggledFrameStepping();
    ImGui::TableNextColumn();
    ImGui::TextDisabled("(F9)");

    ImGui::TableNextColumn();
    if (ImGui::Button("Step frame"))
        stepNextFrame = true;
    ImGui::TableNextColumn();
    ImGui::TextDisabled("(F10)");

    ImGui::EndTable();
    ImGui::NewLine();

    ImGui::Text("Current Room: %s", (*GM::currentRoom)->m_Name);
    ImGui::Text("Mouse: x %d, y %d", *GM::mouseX, *GM::mouseY);

    ImGui::End();
    return showGui;
}
