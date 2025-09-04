#include "clipboard.h"
#include <windows.h>
#include <string>

static std::wstring utf8ToUtf16(const std::string &utf8) {
    if (utf8.empty()) return L"";
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(),
                                          (int)utf8.size(), NULL, 0);
    std::wstring wstr(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), (int)utf8.size(),
                        &wstr[0], size_needed);
    return wstr;
}

static std::string utf16ToUtf8(const std::wstring &utf16) {
    if (utf16.empty()) return "";
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(),
                                          (int)utf16.size(), NULL, 0, NULL, NULL);
    std::string str(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), (int)utf16.size(),
                        &str[0], size_needed, NULL, NULL);
    return str;
}

std::string Clipboard::get() {
    if (!OpenClipboard(NULL))
        return "";

    HANDLE hData = GetClipboardData(CF_UNICODETEXT);
    if (hData == NULL) {
        CloseClipboard();
        return "";
    }

    wchar_t *pszText = static_cast<wchar_t *>(GlobalLock(hData));
    if (pszText == NULL) {
        CloseClipboard();
        return "";
    }

    std::wstring wtext(pszText);
    GlobalUnlock(hData);
    CloseClipboard();

    return utf16ToUtf8(wtext);
}

void Clipboard::set(const std::string &text) {
    if (!OpenClipboard(NULL))
        return;

    EmptyClipboard();

    std::wstring wtext = utf8ToUtf16(text);
    size_t sizeInBytes = (wtext.size() + 1) * sizeof(wchar_t);

    HGLOBAL hGlob = GlobalAlloc(GMEM_MOVEABLE, sizeInBytes);
    if (hGlob == NULL) {
        CloseClipboard();
        return;
    }

    memcpy(GlobalLock(hGlob), wtext.c_str(), sizeInBytes);
    GlobalUnlock(hGlob);

    SetClipboardData(CF_UNICODETEXT, hGlob);
    CloseClipboard();
}
