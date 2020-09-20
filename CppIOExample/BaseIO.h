#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <codecvt> //用于转码和解码
using namespace std;

namespace MBaseIO {
    //***************************************************************
    //Read                                                          *
    //***************************************************************
    //获取窄字符串（以char*为缓冲）
    char* GetChars(const char* fileName) {
        cout << "\nMBaseIO::GetChars:\n";
        char* buffer = nullptr;
        //打开文件（输入|文件指针置于末尾）
        std::ifstream ifs(fileName,std::ios::in | std::ios::ate);
        if (!ifs) {
            cout << fileName << "文件打开失败\n";
            return buffer;
        }
        //获取文件大小
        size_t size = static_cast<size_t>(ifs.tellg());
        //文件指针重置到首位
        ifs.seekg(0, ifs.beg);

        //Array buffer
        buffer = new char[size+1];
        ifs.read(buffer, size);
        buffer[size] = 0;
        ifs.close();

        cout << "gcount:" << ifs.gcount() << "\t";
        cout << "size:" << size << "\t\t";
        cout << "strlen: " << strlen(buffer) << endl;
        cout << buffer << endl;
        return buffer;
    }

    //获取窄字符串（以vector为缓冲）
    char* GetCharsV(const char* fileName) {
        cout << "\nMBaseIO::GetCharsV:\n";
        char* res = nullptr;
        std::ifstream ifs(fileName,
            std::ifstream::in | std::ios::ate 
        );
        if (!ifs) {
            cout << fileName << "文件打开失败\n";
            return NULL;
        }
        size_t size = static_cast<size_t>(ifs.tellg());
        ifs.seekg(0, ifs.beg);
        //申请vector缓冲区
        std::vector<char> vec(size + 1, 0);
        ifs.read(vec.data(), size);
        ifs.close();

        //不能直接将vec的数据拷贝给char*，因为在函数作用域结束之后，没有用new创建的vector里的char都会跟着vector释放。
        //res = vec.data();
        res = new char[vec.size()];
        strncpy_s(res, vec.size(), vec.data(), vec.size());

        cout << "gcount:" << ifs.gcount() << "\t";
        cout << "size:" << size << "\t\t";
        cout << "strlen:" << strlen(res) << "\t";
        cout << "vec.size(): " << vec.size() << endl;
        cout << res << endl;
        return res;
    }

    //获取宽字符串（以wchar_t*为缓冲）
    wchar_t* GetWChars(const char* fileName) {
        cout << "\nMBaseIO::GetWChars:\n";
        
        wchar_t* buffer = nullptr;
        std::wifstream ifs(fileName,
            std::wifstream::in | std::wifstream::ate
        );
        if (!ifs) {
            cout << fileName << "文件打开失败\n";
            return buffer;
        }
        //需要设置解码方式
        std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
        ifs.imbue(std::locale(ifs.getloc(), codecvtToUnicode));

        //这里测量出来的size并不是wchar_t的数量，而是以char为单位的数量，
        size_t size = static_cast<size_t>(ifs.tellg());
        ifs.seekg(0, ifs.beg);

        //必须要将数组进行初始化，否则会导致后面的wcout无法输出
        buffer = new wchar_t[size + 1];
        wmemset(buffer, 0, size + 1);
        ifs.read(buffer, size);
        ifs.close();

        size_t realSize = wcslen(buffer);
        if (realSize == 0) {
            return nullptr;
        }
        
        cout << "gcount:" << ifs.gcount() << "\t";
        cout << "size:" << size << "\t\t";
        cout << "realSize:" << realSize << "\t";
        cout << "wcslen(buffer):" << wcslen(buffer) << "\t";

        //如果实际大小比之前分配的空间小，则缩小分配的空间
        if (realSize < size) {
            realSize++;
            wchar_t* res = new wchar_t[realSize];
            wmemmove(res, buffer, realSize);
            delete[] buffer;

            cout << "wcslen(res): " << wcslen(res) << endl;
            wcout << res << endl;
            return res;
        }
        else {
            wcout << buffer << endl;
            return buffer;
        }
    }

    //获取宽字符串（以vector为缓冲）
    wchar_t* GetWCharsV(const char* fileName) {
        cout << "\nMBaseIO::GetWCharsV:\n";
        std::wifstream ifs(fileName,
            std::wifstream::in | std::wifstream::ate 
        );
        if (!ifs) {
            cout << fileName << "文件打开失败\n";
            return NULL;
        }
        std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
        ifs.imbue(std::locale(ifs.getloc(), codecvtToUnicode));

        size_t size = static_cast<size_t>(ifs.tellg());
        ifs.seekg(0, ifs.beg);

        std::vector<wchar_t> vec(size + 1,0);
        ifs.read(vec.data(), size);
        ifs.close();

        //vector to wchar_t*
        wchar_t* res = new wchar_t[vec.size()];
        wcscpy_s(res, vec.size(), vec.data());

        cout << "gcount:" << ifs.gcount() << "\t";
        cout << "size:" << size << "\t\t";
        cout << "wcslen: " << wcslen(res) << "\t";
        cout << "vec.size(): " << vec.size() << endl;
        wcout << res << endl;
        return res;
    }

    //***************************************************************
    //Write                                                         *
    //***************************************************************
    //覆盖写入
    bool OverWriteFile(const char* fileName, const char* content) {
        cout << "\nMBaseIO::OverWriteFile:\n";
        //打开文件
        std::ofstream truncfile(fileName,
            std::ios::out |
            std::ios::trunc    //模式：重写
        );
        if (!truncfile.is_open()) {
            cout << fileName << " Open fail" << endl;
            return false;
        }
        //写入
        truncfile.write(content, std::strlen(content));
        //关闭
        truncfile.close();
        cout << "strlen(content):" << strlen(content) << endl;
        return true;
    }
    //追加写入
    bool AppendFile(const char* fileName, const char* content) {
        cout << "\nMBaseIO::AppendFile:\n";
        std::ofstream appfile(fileName,
            std::ios::out |
            std::ios::app      //模式：追加
        );
        if (!appfile) {
            cout << fileName << " Open fail" << endl;
            return false;
        }
        appfile.write(content, std::strlen(content));
        appfile.close();
        cout << "strlen(content):" << strlen(content) << endl;
        return true;
    }

    //覆盖写入UTF8
    bool OverWriteUTF8(const char* fileName, const wchar_t* content) {
        cout << "\nMBaseIO::OverWriteUTF8:\n";
        std::wofstream wof;
        wof.open(fileName, 
            std::ios::out | std::ios::trunc
        );
        if (!wof.is_open()) {
            cout << fileName << "Open fail" << endl;
            return false;
        }
        std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
        wof.imbue(std::locale(wof.getloc(), codecvtToUnicode));
        wof.write(content, wcslen(content));
        wof.close();
        
        cout << "wcslen(content):"<<wcslen(content) << endl;
        return true;
    }
}