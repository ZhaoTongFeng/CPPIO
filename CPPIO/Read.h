#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <codecvt>//用于转码和解码



//读文本文件用String，二进制情况使用GetXXXV
class MFileReader {
public:
    //***************************************************************
    //用窄字符保存                                                  *
    //***************************************************************
    //916,1007
    static char* GetChars(const char* fileName) {
        char* buffer = nullptr;
        //打开文件（输入|文件指针置于末尾）
        std::ifstream ifs(fileName,
            std::ifstream::in | std::ifstream::ate | std::ifstream::binary
        );
        if (!ifs) {
            std::cout << fileName << "文件打开失败\n";
            return buffer;
        }
        //获取文件大小
        size_t size = static_cast<size_t>(ifs.tellg());
        //文件指针重置到首位
        ifs.seekg(0, ifs.beg);

        //Array buffer
        buffer = new char[size + 1];
        ifs.read(buffer, size);
        buffer[size] = 0;
        ifs.close();
        
        std::cout << "gcount:" << ifs.gcount() << "\n";
        std::cout << "arr.len: " << strlen(buffer) << " \nContent:" << buffer << "\n";
        return buffer;
    }
    //916,1008
    static char* GetCharsV(const char* fileName) {
        std::ifstream ifs(fileName,
            std::ifstream::in | std::ifstream::ate
        );
        if (!ifs) {
            std::cout << fileName << "文件打开失败\n";
            return NULL;
        }
        size_t size = static_cast<size_t>(ifs.tellg());
        ifs.seekg(0, ifs.beg);
        //申请vector缓冲区
        std::vector<char> vec(size+1);
        ifs.read(vec.data(), size);
        ifs.close();

        //释放或者返回字符串
        //不能直接将vec的数据拷贝给char*，因为在函数作用域结束之后，没有用new创建的vector里的char都会跟着vector释放。
        //res = vec.data();
        char* res = new char[vec.size()];
        strncpy_s(res, vec.size(), vec.data(), vec.size());

        std::cout << "gcount:" << ifs.gcount() << "\n";
        std::cout << "vec.size: " << vec.size() << " \nContent:" << vec.data() << "\n";
        return res;
    }
    //operator >> 适用于读取文本数据
    //使用这种方法打开UTF8的文件，不仅会出现乱码的错误，String.size()的返回值返回的也不是字数，而是文件的空间大小
    static std::string GetString(const char* fileName) {
        std::string res = "";
        std::ifstream ifs(fileName);
        if (!ifs) {
            std::cout << fileName << "文件打开失败\n";
            return res;
        }
        while (ifs) {
            ifs >> res;
        }
        
        ifs.close();

        std::cout << "gcount:" << ifs.gcount() << "\n";
        std::cout << "str.size:" << res.size() << " \nContent:" << res << "\n";
        return res;
    }
    //***************************************************************
    //用宽字符保存                                                  *
    //***************************************************************
    //296，339
    static wchar_t* GetWChars(const char* fileName) {
        wchar_t* res = nullptr;
        std::wifstream ifs(fileName,
            std::wifstream::in | std::wifstream::ate | std::ifstream::binary
        );
        if (!ifs) {
            std::cout << fileName << "文件打开失败\n";
            return res;
        }
        //需要设置解码方式
        std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
        ifs.imbue(std::locale(ifs.getloc(), codecvtToUnicode));

        size_t size = static_cast<size_t>(ifs.tellg());
        ifs.seekg(0, ifs.beg);

        res = new wchar_t[size];
        ifs.read(res, size);
        ifs.close();

        std::wcout << "gcount:" << ifs.gcount() << "\n";
        std::wcout << "arr.len: " << wcslen(res) << " \nContent:" << res << "\n";
        return res;
    }
    //296，325
    //文件大小是325，这种方法能正确分配大小。
    static wchar_t* GetWCharsV(const char* fileName) {
        std::wifstream ifs(fileName,
            std::wifstream::in | std::wifstream::ate
        );
        if (!ifs) {
            std::cout << fileName << "文件打开失败\n";
            return NULL;
        }
        std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
        ifs.imbue(std::locale(ifs.getloc(), codecvtToUnicode));
        
        size_t size = static_cast<size_t>(ifs.tellg());
        ifs.seekg(0, ifs.beg);

        std::vector<wchar_t> vec(size);
        ifs.read(vec.data(), size);
        ifs.close();

        //vector to wchar_t*
        wchar_t* res = new wchar_t[vec.size()];
        wcscpy_s(res, vec.size(), vec.data());

        std::wcout << "gcount:" << ifs.gcount() << "\n";
        std::wcout << "vec.size: " << vec.size() << " \nContent:" << vec.data() << "\n";
        return res;
    }

    //如果是读取文本文件，使用这种方式更方便，而且wstring.size()返回的就是字符串的个数
    static std::wstring GetWString(const char* fileName) {
        std::wstring res = L"";
        std::wifstream ifs(fileName);
        if (!ifs) {
            std::cout << fileName << "文件打开失败\n";
            return res;
        }
        std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
        ifs.imbue(std::locale(ifs.getloc(), codecvtToUnicode));

        while (ifs)
        {
            ifs >> res;
        }
        
        ifs.close();

        std::wcout << L"gcount:" << ifs.gcount() << L"\n";
        std::wcout << L"wstr.size:" << res.size() << L" \nContent:" << res << L"\n";
        return res;
    }
};