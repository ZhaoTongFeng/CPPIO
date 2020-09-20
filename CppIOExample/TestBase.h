#pragma once
#include "BaseIO.h"
using namespace MBaseIO;

void BaseTest() {
    //文件
    const char* truncFileName = "./file/truncFile.txt";
    const char* appFileName = "./file/appFile.txt";
    const char* writeUTF8FileName = "./file/write-utf8.txt";

    //内容
    const char* content = "abcdefgh";
    const wchar_t* UTF8Content = L"abcd1234\n厄萨斯厄薩斯Атрокс";

    //写入测试
    for (int i = 0; i < 2; i++) {
        OverwriteContent(truncFileName, content);
        AppendContent(appFileName, content);
    }
    OverwriteUTF8(writeUTF8FileName, UTF8Content);

    //读取测试
    char* p1 = GetChars(truncFileName);
    char* p2 = GetCharsV(appFileName);
    wchar_t* p3 = GetWChars(writeUTF8FileName);
    wchar_t* p4 = GetWCharsV(writeUTF8FileName);
    
    //窄字符方式读取宽字符
    char* p5 = GetChars(writeUTF8FileName);
    char* p6 = GetCharsV(writeUTF8FileName);

    //释放空间
    delete[] p2;
    delete[] p4;
    delete[] p1;
    delete[] p3;
}