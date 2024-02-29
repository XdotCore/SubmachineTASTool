#pragma once

#include <windows.h>
#include <shobjidl.h>
#include <string>

std::wstring GetSaveFile(std::wstring title, COMDLG_FILTERSPEC* filter, int filterCount, int defaultFilter);
std::wstring GetOpenFile(std::wstring title, COMDLG_FILTERSPEC* filter, int filterCount, int defaultFilter);
