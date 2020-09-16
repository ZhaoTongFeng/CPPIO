#pragma once
#include <iostream>
#include <string>
#include <fstream>


std::string GetString(const char* fileName) {
    std::string res = "";
    std::ifstream ifs(fileName);
    if (!ifs) {
        std::cout << fileName << "�ļ���ʧ��\n";
        return res;
    }
    //std::codecvt_utf8<char, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < char, 0x10ffff, std::consume_header >;
    //ifs.imbue(std::locale(ifs.getloc(), codecvtToUnicode));
    //***********************************************************
    ifs >> res;
    
    std::cout << "Read " << ifs.gcount() << " characters\nContent:" << res << "\n";
    return res;
}

//��ȡUTF-8
#include <codecvt>
std::wstring GetWString(const char* fileName)
{
    std::wstring wst = L"";
    std::wifstream wif(fileName);
    if (!wif) {
        std::cout << fileName << "�ļ���ʧ��\n";
        return wst;
    }
    //***********************************************************
    //wifstream�Ľ����ʽ
    std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
    wif.imbue(std::locale(wif.getloc(), codecvtToUnicode));
    wif >> wst;
    //����wcout�Ľ����ʽ
    std::wcout.imbue(std::locale("chs"));
    std::wcout << L"Read " << wst.size() << L" characters\nContent:" << wst << L"\n";
    return wst;
}


//�ֶ�����
char* GetChars(const char* fileName) {
    //���ļ�������|�ļ�ָ������ĩβ��
    std::ifstream ifs(fileName,
        std::ifstream::in  | std::ifstream::ate
    );
    if (!ifs) {
        std::cout << fileName << "�ļ���ʧ��\n"; 
        return NULL;
    }
    std::ifstream::pos_type size = ifs.tellg();
    ifs.seekg(0, ifs.beg);
    //***********************************************************
    //�������黺����
    char* buffer = new char[static_cast<size_t>(size)+1];
    //��ȡ������
    ifs.read(buffer, static_cast<size_t>(size));
    buffer[static_cast<size_t>(size)] = 0;
    std::cout << "Read " << ifs.gcount() << " characters\nContent:" << buffer << "\n";
    ifs.close();
    //�ͷŻ��߷����ַ���
    //delete[] buffer;
    //buffer = nullptr;
    return buffer;
}


//vector
#include <vector>
char* GetCharsV(const char* fileName) {
    //���ļ�������|�ļ�ָ������ĩβ��
    std::ifstream ifs(fileName,
        std::ifstream::in | std::ifstream::ate
    );
    if (!ifs) {
        std::cout << fileName << "�ļ���ʧ��\n";
        return NULL;
    }
    //��ȡ�ļ���С
    std::ifstream::pos_type size = ifs.tellg();
    //�ļ�ָ�����õ���λ
    ifs.seekg(0, ifs.beg);
    //***********************************************************
    //����vector������
    std::vector<char> vec(static_cast<size_t>(size) + 1);

    //��ȡ��vector
    ifs.read(vec.data(), static_cast<size_t>(size));
    std::cout << "Read " << ifs.gcount() << " characters\nContent:" << vec.data() << "\n";
    //std::cout << "Read " << vec.size() << " characters\nContent:" << vec.data() << "\n";

    ifs.close();
    //�ͷŻ��߷����ַ���
    //����ֱ�ӽ�vec�����ݿ�����char*����Ϊ�ں������������֮��vec���char�������vec�ͷš�
    //res = vec.data();
    char* res = new char[vec.size() + 1];
    strncpy_s(res, vec.size(), vec.data(), vec.size());
    res[vec.size()] = 0;
    return res;
}




