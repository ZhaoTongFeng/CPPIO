#pragma once
#include <iostream>
#include <string>
//1.引入库文件
#include <fstream>
#include <vector>
#include <stdio.h>

//需要导入window.h文件,Linux上面还需要其它解决办法
#include< windows.h >
#pragma warning(disable : 4996)


const std::wstring s2ws(const std::string& s) {
    std::locale old_loc = std::locale::global(std::locale(""));

    const char* src_str = s.c_str();
    const size_t buffer_size = s.size() + 1;
    wchar_t* dst_wstr = new wchar_t[buffer_size];
    wmemset(dst_wstr, 0, buffer_size);
    mbstowcs(dst_wstr, src_str, buffer_size);

    std::wstring result = dst_wstr;
    delete[] dst_wstr;
    std::locale::global(old_loc);
    return result;
}

std::string to_utf8(const wchar_t* buffer, int len)
{
    int nChars = ::WideCharToMultiByte(
        CP_UTF8,
        0,
        buffer,
        len,
        NULL,
        0,
        NULL,
        NULL);
    if (nChars == 0)return "";

    std::string newbuffer;
    newbuffer.resize(nChars);
    ::WideCharToMultiByte(
        CP_UTF8,
        0,
        buffer,
        len,
        const_cast<char*>(newbuffer.c_str()),
        nChars,
        NULL,
        NULL);

    return newbuffer;
}

std::string to_utf8(const std::wstring& str)
{
    return to_utf8(str.c_str(), (int)str.size());
}

