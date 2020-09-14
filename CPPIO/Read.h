#pragma once
#include <iostream>
#include <fstream>

void ReadV1(char* fileName) {
    std::ifstream ifstreamfile(fileName,
        std::ifstream::in
    );
    if (!ifstreamfile) {
        std::cout << "�ļ���ʧ��";
        return;
    }
    char c;
    while (ifstreamfile.good())
    {
        c = ifstreamfile.get();
        std::cout << c;
    }
    ifstreamfile.close();
    return;
}

//����һ��vector
#include <vector>
char* ReadV2(char* fileName) {
    //���ļ�������|������|�ļ�ָ������ĩβ��
    std::ifstream ifstreamfile(fileName,
        std::ifstream::in | std::ifstream::ate
    );
    if (!ifstreamfile) {
        std::cout << "�ļ���ʧ��"; 
        return NULL;
    }
    //��ȡ�ļ���С
    std::ifstream::pos_type size = ifstreamfile.tellg();
    //�ļ�ָ�����õ���λ
    ifstreamfile.seekg(0, ifstreamfile.beg);
    //***********************************************************
    //����vector������
    std::vector<char> vec(static_cast<size_t>(size) + 1);
    
    //��ȡ��vector
    ifstreamfile.read(vec.data(), static_cast<size_t>(size));
    std::cout << "Read " << ifstreamfile.gcount() << " characters\nContent:" << vec.data() << "\n";
    
    ifstreamfile.close();
    //�ͷŻ��߷����ַ���
    //����ֱ�ӽ�vec�����ݿ�����char*����Ϊ�ں������������֮��vec���char�������vec�ͷš�
    //res = vec.data();
    char* res = new char[vec.size()+1];
    strncpy_s(res, vec.size(),vec.data(), vec.size());
    res[vec.size()] = 0;
    return res;
}

//����������̬����
char* ReadV3(char* fileName) {
    //���ļ�������|������|�ļ�ָ������ĩβ��
    std::ifstream ifstreamfile(fileName,
        std::ifstream::in  | std::ifstream::ate
    );
    if (!ifstreamfile) {
        std::cout << "�ļ���ʧ��"; 
        return NULL;
    }
    std::ifstream::pos_type size = ifstreamfile.tellg();
    ifstreamfile.seekg(0, ifstreamfile.beg);
    //***********************************************************
    //�������黺����
    char* buffer = new char[static_cast<size_t>(size)+1];
    //��ȡ������
    ifstreamfile.read(buffer, static_cast<size_t>(size));
    buffer[static_cast<size_t>(size)] = 0;
    std::cout << "Read " << ifstreamfile.gcount() << " characters\nContent:" << buffer << "\n";
    ifstreamfile.close();
    //�ͷŻ��߷����ַ���
    //delete[] buffer;
    //buffer = nullptr;
    return buffer;
}


std::string ReadV4(char* fileName) {
    //���ļ�������|������|�ļ�ָ������ĩβ��
    std::ifstream ifstreamfile(fileName,
        std::ifstream::in
    );
    if (!ifstreamfile) {
        std::cout << "�ļ���ʧ��";
        return "";
    }
    //***********************************************************
    std::string res;
    ifstreamfile >> res;
    return res;
}




//��ȡUTF-8

#include <codecvt>
std::wstring ReadUTF8(char* fileName)
{
    std::wifstream wif(fileName,
        std::wifstream::in
    );
    if (!wif) {
        std::cout << "�ļ���ʧ��";
        return L"";
    }
    //***********************************************************
    //����
    std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
    wif.imbue(std::locale(wif.getloc(), codecvtToUnicode));
    std::wstring wst;
    wif >> wst;
    return wst;
}