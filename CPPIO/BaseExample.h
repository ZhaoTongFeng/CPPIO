#pragma once
#include "Write.h"
#include "Read.h"

void ReadTest() {
    char fileName[] = "./file/read.txt";
    GetString(fileName);
    GetChars(fileName);
    GetCharsV(fileName);
    GetWString(fileName);
}


void WriteTest() {
    char truncFileName[] = "./file/truncFile.txt";
    char appFileName[] = "./file/appFile.txt";
    char content[] = "abcd1234∂Ú»¯Àπ∂ÚÀ_Àπß°ß‰ß‚ß‡ß‹ß„";

    for (int i = 0; i < 2; i++) {
        OverwriteContent(truncFileName, content);
        AppendContent(appFileName, content);
    }

    char utf8File[] = "./file/utf8.txt";
    wchar_t text[] = L"abcd1234∂Ú»¯Àπ∂ÚÀ_Àπß°ß‰ß‚ß‡ß‹ß„";
    OverwriteUTF8(utf8File, text);


    std::wstring res = GetWString(utf8File);
    if (!res.empty()) {

        std::wcout << L"◊÷∑˚£∫" << res << "\n";
    }
    else {
        std::cout << "NULL";
    }
}



