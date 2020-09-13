#pragma once
#include <iostream>
#include <string>
//1.������ļ�
#include <fstream>

bool OverwriteContent(const char* fileName, const char* content) {
    //2.���ļ�

    //���ļ�����һ
    std::ofstream truncfile(fileName,
        std::ofstream::out |
        std::ofstream::trunc    //ģʽ����д
    );

    //���ļ�������
    //std::ofstream truncfile;
    //truncfile.open("truncFile.txt", 
    //    std::ofstream::out | 
    //    std::ofstream::trunc    //ģʽ����д
    //);


    //����ļ��Ƿ�򿪳ɹ�
    if (!truncfile.is_open()) {
        std::cout << "Open truncFile fail";
        return false;
    }
    truncfile.write(content, std::strlen(content));

    //4.�ر�
    truncfile.close();
    return true;
}

bool AppendContent(const char* fileName,const char* content) {
    std::ofstream appfile(fileName,
        std::ofstream::out |
        std::ofstream::app      //ģʽ��׷��
    );
    if (!appfile) {
        std::cout << "Open appfile fail";
        return false;
    }
    appfile.write(content, std::strlen(content));

    appfile.close();
    return true;
}

//��ȡUTF8�ļ�
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