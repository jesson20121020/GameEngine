#include "FileUtils-Win.h"
#define UNICODE
#include <Shlobj.h>
#include <iostream>


static std::wstring StringUtf8ToWideChar(const std::string& strUtf8)
{
    std::wstring ret;
    if (!strUtf8.empty())
    {
        int nNum = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, nullptr, 0);
        if (nNum)
        {
            WCHAR* wideCharString = new WCHAR[nNum + 1];
            wideCharString[0] = 0;

            nNum = MultiByteToWideChar(CP_UTF8, 0, strUtf8.c_str(), -1, wideCharString, nNum + 1);

            ret = wideCharString;
            delete[] wideCharString;
        }
        else
        {
            std::cout << "Wrong convert to WideChar code:0x%x" << GetLastError() << std::endl;
        }
    }
    return ret;
}

FileUtilsWin::FileUtilsWin() {

}

FileUtils* FileUtils::getInstance()
{
    if (s_sharedFileUtils == nullptr)
    {
        s_sharedFileUtils = new FileUtilsWin();
    }
    return s_sharedFileUtils;
}

bool FileUtilsWin::isAbsolutePath(const std::string& strPath) const
{
    if ((strPath.length() > 2
        && ((strPath[0] >= 'a' && strPath[0] <= 'z') || (strPath[0] >= 'A' && strPath[0] <= 'Z'))
        && strPath[1] == ':') || (strPath[0] == '/' && strPath[1] == '/'))
    {
        return true;
    }
    return false;
}
long FileUtilsWin::getFileSize(const std::string& filePath)
{
    WIN32_FILE_ATTRIBUTE_DATA fad;
    if (!GetFileAttributesEx(StringUtf8ToWideChar(filePath).c_str(), GetFileExInfoStandard, &fad))
    {
        return 0; // error condition, could call GetLastError to find out more
    }
    LARGE_INTEGER size;
    size.HighPart = fad.nFileSizeHigh;
    size.LowPart = fad.nFileSizeLow;
    return (long)size.QuadPart;
}

bool FileUtilsWin::isFileExistInternal(const std::string& strFilePath) const
{
    if (strFilePath.empty())
    {
        return false;
    }
    std::string strPath = strFilePath;
    DWORD attr = GetFileAttributesW(StringUtf8ToWideChar(strPath).c_str());
    if (attr == INVALID_FILE_ATTRIBUTES || (attr & FILE_ATTRIBUTE_DIRECTORY))
        return false;   //  not a file
    return true;
}

std::string FileUtilsWin::convertToPlatformPath(const std::string& filePath) const
{
    std::string path = filePath;
    for (int i = 0; i < path.size(); i++) {
        if (path[i] == '/') {
            path[i] = '\\';
        }
    }
    return path;
}