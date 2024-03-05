#include <iostream>
#include <filesystem>
#include "file.h"

std::wstring GetFile(IFileDialog* dialog, std::wstring title, COMDLG_FILTERSPEC* filter, int filterCount, int defaultFilter) {
    HRESULT hr = dialog->SetTitle(title.c_str());
    if (FAILED(hr)) {
        std::cout << "Failed to set file dialog title for file dialog" << std::endl;
        return L"";
    }

    IShellItem* path;
    hr = SHCreateItemFromParsingName(std::filesystem::current_path().wstring().c_str(), NULL, IID_IShellItem, (void**)&path);
    if (FAILED(hr)) {
        std::cout << "Failed to get current directory" << std::endl;
        return L"";
    }

    hr = dialog->SetDefaultFolder(path);
    if (FAILED(hr)) {
        std::cout << "Failed to set folder for file dialog" << std::endl;
        return L"";
    }
    
    hr = dialog->SetFileTypes(filterCount, filter);
    if (FAILED(hr)) {
        std::cout << "Failed to set file dialog filter" << std::endl;
        return L"";
    }

    hr = dialog->SetFileTypeIndex(defaultFilter + 1);
    if (FAILED(hr)) {
        std::cout << "Failed to set default file type for file dialog" << std::endl;
        return L"";
    }

    hr = dialog->Show(NULL);
    if (FAILED(hr)) {
        std::cout << "File dialog canceled" << std::endl;
        return L"";
    }

    IShellItem* dialogResult;
    hr = dialog->GetResult(&dialogResult);
    if (FAILED(hr)) {
        std::cout << "Failed to get file dialog result" << std::endl;
        return L"";
    }

    wchar_t* filePath;
    dialogResult->GetDisplayName(SIGDN_FILESYSPATH, &filePath);
    if (FAILED(hr)) {
        std::cout << "Failed to get file path" << std::endl;
        return L"";
    }

    dialogResult->Release();

    return filePath;
}

std::wstring GetSaveFile(std::wstring title, COMDLG_FILTERSPEC* filter, int filterCount, int defaultFilter = 0) {
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(hr)) {
        std::cout << "Failed to save input because failed to init COM library" << std::endl;
        return L"";
    }

    IFileSaveDialog* dialog;
    hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL, IID_IFileSaveDialog, (void**)&dialog);
    if (FAILED(hr)) {
        std::cout << "Failed to save input because failed to create file dialog" << std::endl;
        return L"";
    }

    std::wstring filePath = GetFile(dialog, title, filter, filterCount, defaultFilter);

    dialog->Release();
    CoUninitialize();

    return filePath;
}

std::wstring GetOpenFile(std::wstring title, COMDLG_FILTERSPEC* filter, int filterCount, int defaultFilter = 0) {
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (FAILED(hr)) {
        std::cout << "Failed to open input because failed to init COM library" << std::endl;
        return L"";
    }

    IFileOpenDialog* dialog;
    hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, (void**)&dialog);
    if (FAILED(hr)) {
        std::cout << "Failed to open input because failed to create file dialog" << std::endl;
        return L"";
    }

    std::wstring filePath = GetFile(dialog, title, filter, filterCount, defaultFilter);

    dialog->Release();
    CoUninitialize();

    return filePath;
}