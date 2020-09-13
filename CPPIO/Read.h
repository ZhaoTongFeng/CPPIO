#pragma once
#include <iostream>
#include <fstream>

void ReadV1(char* fileName) {
    std::ifstream ifstreamfile(fileName,
        std::ifstream::in
    );
    if (!ifstreamfile) {
        std::cout << "文件打开失败";
        return;
    }
    char c;
    while (ifstreamfile.good())
    {
        c = ifstreamfile.get();
        std::cout << c;
    }
    ifstreamfile.close();
    return;
}

//方法一：vector
#include <vector>
char* ReadV2(char* fileName) {
    //打开文件（输入|二进制|文件指针置于末尾）
    std::ifstream ifstreamfile(fileName,
        std::ifstream::in | std::ifstream::ate
    );
    if (!ifstreamfile) {
        std::cout << "文件打开失败"; 
        return NULL;
    }
    //获取文件大小
    std::ifstream::pos_type size = ifstreamfile.tellg();
    //文件指针重置到首位
    ifstreamfile.seekg(0, ifstreamfile.beg);
    //***********************************************************
    //申请vector缓冲区
    std::vector<char> vec(static_cast<size_t>(size) + 1);
    
    //读取到vector
    ifstreamfile.read(vec.data(), static_cast<size_t>(size));
    std::cout << "Read " << ifstreamfile.gcount() << " characters\nContent:" << vec.data() << "\n";
    
    ifstreamfile.close();
    //释放或者返回字符串
    //不能直接将vec的数据拷贝给char*，因为在函数作用域结束之后，vec里的char都会跟着vec释放。
    //res = vec.data();
    char* res = new char[vec.size()+1];
    strncpy_s(res, vec.size(),vec.data(), vec.size());
    res[vec.size()] = 0;
    return res;
}

//方法二：动态分配
char* ReadV3(char* fileName) {
    //打开文件（输入|二进制|文件指针置于末尾）
    std::ifstream ifstreamfile(fileName,
        std::ifstream::in  | std::ifstream::ate
    );
    if (!ifstreamfile) {
        std::cout << "文件打开失败"; 
        return NULL;
    }
    std::ifstream::pos_type size = ifstreamfile.tellg();
    ifstreamfile.seekg(0, ifstreamfile.beg);
    //***********************************************************
    //申请数组缓冲区
    char* buffer = new char[static_cast<size_t>(size)+1];
    //读取到数组
    ifstreamfile.read(buffer, static_cast<size_t>(size));
    buffer[static_cast<size_t>(size)] = 0;
    std::cout << "Read " << ifstreamfile.gcount() << " characters\nContent:" << buffer << "\n";
    ifstreamfile.close();
    //释放或者返回字符串
    //delete[] buffer;
    //buffer = nullptr;
    return buffer;
}




//读取UTF-8
#include<locale>
#include <codecvt>
wchar_t* ReadUTF8(char* fileName) 
{
    std::wifstream wif(fileName,
        std::ifstream::in | std::ifstream::ate
    );
    if (!wif) {
        std::cout << "文件打开失败";
        return NULL;
    }
    std::ifstream::pos_type size = wif.tellg();
    wif.seekg(0, wif.beg);
    //***********************************************************
    //解码器
    //https://www.cnblogs.com/cthon/p/9340808.html
    std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
    wif.imbue(std::locale(wif.getloc(), codecvtToUnicode));

    wchar_t* buffer = new wchar_t[static_cast<size_t>(size) + 1];
    wif.read(buffer, static_cast<size_t>(size));
    buffer[static_cast<size_t>(size)] = 0;
    std::wcout << "Read " << wif.gcount() << " characters\nContent:" << buffer << "\n";
    wif.close();
    return buffer;
}