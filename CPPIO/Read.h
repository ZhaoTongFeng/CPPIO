#pragma once
#include <iostream>
#include <string>
#include <fstream>


std::string GetString(const char* fileName) {
    std::string res = "";
    std::ifstream ifs(fileName);
    if (!ifs) {
        std::cout << fileName << "文件打开失败\n";
        return res;
    }
    //std::codecvt_utf8<char, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < char, 0x10ffff, std::consume_header >;
    //ifs.imbue(std::locale(ifs.getloc(), codecvtToUnicode));
    //***********************************************************
    ifs >> res;
    
    std::cout << "Read " << ifs.gcount() << " characters\nContent:" << res << "\n";
    return res;
}

//读取UTF-8
#include <codecvt>
std::wstring GetWString(const char* fileName)
{
    std::wstring wst = L"";
    std::wifstream wif(fileName);
    if (!wif) {
        std::cout << fileName << "文件打开失败\n";
        return wst;
    }
    //***********************************************************
    //wifstream的解码格式
    std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
    wif.imbue(std::locale(wif.getloc(), codecvtToUnicode));
    wif >> wst;
    //设置wcout的解码格式
    std::wcout.imbue(std::locale("chs"));
    std::wcout << L"Read " << wst.size() << L" characters\nContent:" << wst << L"\n";
    return wst;
}


//手动分配
char* GetChars(const char* fileName) {
    //打开文件（输入|文件指针置于末尾）
    std::ifstream ifs(fileName,
        std::ifstream::in  | std::ifstream::ate
    );
    if (!ifs) {
        std::cout << fileName << "文件打开失败\n"; 
        return NULL;
    }
    std::ifstream::pos_type size = ifs.tellg();
    ifs.seekg(0, ifs.beg);
    //***********************************************************
    //申请数组缓冲区
    char* buffer = new char[static_cast<size_t>(size)+1];
    //读取到数组
    ifs.read(buffer, static_cast<size_t>(size));
    buffer[static_cast<size_t>(size)] = 0;
    std::cout << "Read " << ifs.gcount() << " characters\nContent:" << buffer << "\n";
    ifs.close();
    //释放或者返回字符串
    //delete[] buffer;
    //buffer = nullptr;
    return buffer;
}


//vector
#include <vector>
char* GetCharsV(const char* fileName) {
    //打开文件（输入|文件指针置于末尾）
    std::ifstream ifs(fileName,
        std::ifstream::in | std::ifstream::ate
    );
    if (!ifs) {
        std::cout << fileName << "文件打开失败\n";
        return NULL;
    }
    //获取文件大小
    std::ifstream::pos_type size = ifs.tellg();
    //文件指针重置到首位
    ifs.seekg(0, ifs.beg);
    //***********************************************************
    //申请vector缓冲区
    std::vector<char> vec(static_cast<size_t>(size) + 1);

    //读取到vector
    ifs.read(vec.data(), static_cast<size_t>(size));
    std::cout << "Read " << ifs.gcount() << " characters\nContent:" << vec.data() << "\n";
    //std::cout << "Read " << vec.size() << " characters\nContent:" << vec.data() << "\n";

    ifs.close();
    //释放或者返回字符串
    //不能直接将vec的数据拷贝给char*，因为在函数作用域结束之后，vec里的char都会跟着vec释放。
    //res = vec.data();
    char* res = new char[vec.size() + 1];
    strncpy_s(res, vec.size(), vec.data(), vec.size());
    res[vec.size()] = 0;
    return res;
}




