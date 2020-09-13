#pragma once
#include "Write.h"
#include "Read.h"




void WriteTest() {
    char writeFileName[] = "file/read.txt";
    char truncFileName[] = "file/truncFile.txt";
    char appFileName[] = "file/appFile.txt";
    char content[] = "Content";

    for (int i = 0; i < 2; i++) {
        OverwriteContent(truncFileName, content);
        AppendContent(appFileName, content);
    }
}

void ReadTest() {
    char readFileName[] = "file/read.txt";
    //ReadV1(fileName);
    ReadV2(readFileName);
    ReadV3(readFileName);
}



void UTF8Test() {
    std::locale china("chs");   //use china character
    std::wcin.imbue(china);     //use locale object
    std::wcout.imbue(china);

    char fileName[] = "file/utf8.txt";
    wchar_t text[] = L"一二三四五";

    OverwriteUTF8(fileName, text);

    wchar_t* res = ReadUTF8(fileName);
    if (res) {
        std::wcout << "字符：" << res << "\n";
    }
}