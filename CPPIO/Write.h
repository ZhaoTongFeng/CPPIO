#pragma once
#include <iostream>
#include <string>
//1.引入库文件
#include <fstream>

bool OverwriteContent(const char* fileName, const char* content) {
    //2.打开文件

    //打开文件方法一
    std::ofstream truncfile(fileName,
        std::ofstream::out |
        std::ofstream::trunc    //模式：重写
    );

    //打开文件方法二
    //std::ofstream truncfile;
    //truncfile.open("truncFile.txt", 
    //    std::ofstream::out | 
    //    std::ofstream::trunc    //模式：重写
    //);


    //检测文件是否打开成功
    if (!truncfile.is_open()) {
        std::cout << "Open truncFile fail";
        return false;
    }
    truncfile.write(content, std::strlen(content));

    //4.关闭
    truncfile.close();
    return true;
}

bool AppendContent(const char* fileName,const char* content) {
    std::ofstream appfile(fileName,
        std::ofstream::out |
        std::ofstream::app      //模式：追加
    );
    if (!appfile) {
        std::cout << "Open appfile fail";
        return false;
    }
    appfile.write(content, std::strlen(content));

    appfile.close();
    return true;
}

//读取UTF8文件
#include<locale>
#include <codecvt>
bool OverwriteUTF8(const char* fileName, const wchar_t* content) {
    std::wofstream wof(fileName,
        std::ofstream::out |
        std::ofstream::trunc
    );
    if (!wof.is_open()) {
        std::cout << "Open truncFile fail";
        return false;
    }

    std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
    wof.imbue(std::locale(wof.getloc(), codecvtToUnicode));
    
    wof.write(content, std::wcslen(content));
    wof.close();
    return true;
}


void WriteV2() {
    std::ofstream ostreamFile("ostreamFile.txt",
        std::ofstream::out | std::ofstream::trunc
    );
    ostreamFile << 1;
    ostreamFile.put(97);
    //truncfile.swap(appfile);
    std::cout << "tellp:" << ostreamFile.tellp();
    ostreamFile.seekp(1);
    ostreamFile << 3;

    ostreamFile.close();
}