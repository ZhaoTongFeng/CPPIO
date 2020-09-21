#pragma once
#include "Write.h"
#include "Read.h"

void ReadTest() {
    const char* fileName = "./file/read.txt";
    
    
    MFileReader::GetChars(fileName);
   
    MFileReader::GetCharsV(fileName);
    
    MFileReader::GetWChars(fileName);

    MFileReader::GetWCharsV(fileName);
   
}

void WriteTest() {
    const char truncFileName[] = "./file/truncFile.txt";
    const char appFileName[] = "./file/appFile.txt";
    const char utf8File[] = "./file/utf8.txt";

    char content[] = "abcd1234\n∂Ú»¯Àπ∂ÚÀ_Àπß°ß‰ß‚ß‡ß‹ß„";
    wchar_t wcontent[] = L"abcd1234\n∂Ú»¯Àπ∂ÚÀ_Àπß°ß‰ß‚ß‡ß‹ß„";


    for (int i = 0; i < 2; i++) {
        OverwriteContent(truncFileName, content);
        AppendContent(appFileName, content);
    }
    OverwriteUTF8(utf8File, wcontent);


    const wchar_t* res = MFileReader::GetWChars(utf8File);
    std::wcout << L"UTF8◊÷∑˚£∫" << res << "\n";
}



