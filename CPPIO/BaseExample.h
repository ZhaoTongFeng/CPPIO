#pragma once
#include "Write.h"
#include "Read.h"

void ReadTest() {
    char fileName[] = "./file/read.txt";

    MFileReader::GetChars(fileName);
    
    MFileReader::GetCharsV(fileName);
    MFileReader::GetWChars(fileName);
    MFileReader::GetWCharsV(fileName);

    MFileReader::GetString(fileName);
    MFileReader::GetWString(fileName);
   
}

void WriteTest() {
    const char truncFileName[] = "./file/truncFile.txt";
    const char appFileName[] = "./file/appFile.txt";
    const char utf8File[] = "./file/utf8.txt";

    char content[] = "abcd1234����˹���_˹������ܧ�";
    wchar_t wcontent[] = L"abcd1234����˹���_˹������ܧ�";


    for (int i = 0; i < 2; i++) {
        OverwriteContent(truncFileName, content);
        AppendContent(appFileName, content);
    }
    OverwriteUTF8(utf8File, wcontent);


    wchar_t* res = MFileReader::GetWChars(utf8File);
    std::wcout << L"UTF8�ַ���" << res << "\n";
}



