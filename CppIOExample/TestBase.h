#pragma once
#include "BaseFileIO.h"
using namespace MBaseFileIO;

void BaseTest() {
    //�ļ�
    const char* truncFileName = "./file/truncFile.txt";
    const char* appFileName = "./file/appFile.txt";
    const char* writeUTF8FileName = "./file/write-utf8.txt";

    //����
    const char* content = "abcdefgh";
    const wchar_t* UTF8Content = L"abcd1234\n����˹���_˹������ܧ�";

    //д��
    for (int i = 0; i < 2; i++) {
        OverWriteFile(truncFileName, content);
        AppendFile(appFileName, content);
    }
    OverWriteUTF8(writeUTF8FileName, UTF8Content);

    //��ȡ
    char* p1 = GetChars(truncFileName);
    char* p2 = GetCharsV(appFileName);
    wchar_t* p3 = GetWChars(writeUTF8FileName);
    wchar_t* p4 = GetWCharsV(writeUTF8FileName);
    
    //խ�ַ���ʽ��ȡ���ַ�
    char* p5 = GetChars(writeUTF8FileName);
    char* p6 = GetCharsV(writeUTF8FileName);

    //�ͷſռ�
    delete[] p1;
    delete[] p2;
    
    
    delete[] p3;
    delete[] p4;

    delete[] p5;
    delete[] p6;
}