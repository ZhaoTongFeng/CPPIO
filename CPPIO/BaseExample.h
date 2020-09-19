#pragma once
#include "Write.h"
#include "Read.h"

void ReadTest() {
    const char* fileName = "./file/read.txt";
    
    std::cout << "MFileReader::GetChars:\n";
    MFileReader::GetChars(fileName);
    
    std::cout << "\nMFileReader::GetCharsV:\n";
    MFileReader::GetCharsV(fileName);
    
    std::cout << "\nMFileReader::GetString:\n";
    MFileReader::GetString(fileName);
    
    std::cout << "**************************************";

    std::cout << "\nMFileReader::GetWChars:\n";
    MFileReader::GetWChars(fileName);

    std::cout << "\nMFileReader::GetWCharsV:\n";
    MFileReader::GetWCharsV(fileName);
    
    std::cout << "\nMFileReader::GetWString:\n";
    MFileReader::GetWString(fileName);
   
}

void WriteTest() {
    const char truncFileName[] = "./file/truncFile.txt";
    const char appFileName[] = "./file/appFile.txt";
    const char utf8File[] = "./file/utf8.txt";

    char content[] = "abcd1234¶òÈøË¹¶òË_Ë¹§¡§ä§â§à§Ü§ã";
    wchar_t wcontent[] = L"abcd1234¶òÈøË¹¶òË_Ë¹§¡§ä§â§à§Ü§ã";


    for (int i = 0; i < 2; i++) {
        OverwriteContent(truncFileName, content);
        AppendContent(appFileName, content);
    }
    OverwriteUTF8(utf8File, wcontent);


    wchar_t* res = MFileReader::GetWChars(utf8File);
    std::wcout << L"UTF8×Ö·û£º" << res << "\n";
}



