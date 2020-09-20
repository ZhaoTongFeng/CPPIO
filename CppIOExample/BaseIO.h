#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <codecvt> //����ת��ͽ���
using namespace std;

namespace MBaseIO {
    //***************************************************************
    //Read                                                          *
    //***************************************************************
    //��ȡխ�ַ�������char*Ϊ���壩
    char* GetChars(const char* fileName) {
        cout << "\nMBaseIO::GetChars:\n";
        char* buffer = nullptr;
        //���ļ�������|�ļ�ָ������ĩβ��
        std::ifstream ifs(fileName,std::ios::in | std::ios::ate);
        if (!ifs) {
            cout << fileName << "�ļ���ʧ��\n";
            return buffer;
        }
        //��ȡ�ļ���С
        size_t size = static_cast<size_t>(ifs.tellg());
        //�ļ�ָ�����õ���λ
        ifs.seekg(0, ifs.beg);

        //Array buffer
        buffer = new char[size+1];
        ifs.read(buffer, size);
        buffer[size] = 0;
        ifs.close();

        cout << "gcount:" << ifs.gcount() << "\t";
        cout << "size:" << size << "\t\t";
        cout << "strlen: " << strlen(buffer) << endl;
        cout << buffer << endl;
        return buffer;
    }

    //��ȡխ�ַ�������vectorΪ���壩
    char* GetCharsV(const char* fileName) {
        cout << "\nMBaseIO::GetCharsV:\n";
        char* res = nullptr;
        std::ifstream ifs(fileName,
            std::ifstream::in | std::ios::ate 
        );
        if (!ifs) {
            cout << fileName << "�ļ���ʧ��\n";
            return NULL;
        }
        size_t size = static_cast<size_t>(ifs.tellg());
        ifs.seekg(0, ifs.beg);
        //����vector������
        std::vector<char> vec(size + 1, 0);
        ifs.read(vec.data(), size);
        ifs.close();

        //����ֱ�ӽ�vec�����ݿ�����char*����Ϊ�ں������������֮��û����new������vector���char�������vector�ͷš�
        //res = vec.data();
        res = new char[vec.size()];
        strncpy_s(res, vec.size(), vec.data(), vec.size());

        cout << "gcount:" << ifs.gcount() << "\t";
        cout << "size:" << size << "\t\t";
        cout << "strlen:" << strlen(res) << "\t";
        cout << "vec.size(): " << vec.size() << endl;
        cout << res << endl;
        return res;
    }

    //��ȡ���ַ�������wchar_t*Ϊ���壩
    wchar_t* GetWChars(const char* fileName) {
        cout << "\nMBaseIO::GetWChars:\n";
        
        wchar_t* buffer = nullptr;
        std::wifstream ifs(fileName,
            std::wifstream::in | std::wifstream::ate
        );
        if (!ifs) {
            cout << fileName << "�ļ���ʧ��\n";
            return buffer;
        }
        //��Ҫ���ý��뷽ʽ
        std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
        ifs.imbue(std::locale(ifs.getloc(), codecvtToUnicode));

        //�������������size������wchar_t��������������charΪ��λ��������
        size_t size = static_cast<size_t>(ifs.tellg());
        ifs.seekg(0, ifs.beg);

        //����Ҫ��������г�ʼ��������ᵼ�º����wcout�޷����
        buffer = new wchar_t[size + 1];
        wmemset(buffer, 0, size + 1);
        ifs.read(buffer, size);
        ifs.close();

        size_t realSize = wcslen(buffer);
        if (realSize == 0) {
            return nullptr;
        }
        
        cout << "gcount:" << ifs.gcount() << "\t";
        cout << "size:" << size << "\t\t";
        cout << "realSize:" << realSize << "\t";
        cout << "wcslen(buffer):" << wcslen(buffer) << "\t";

        //���ʵ�ʴ�С��֮ǰ����Ŀռ�С������С����Ŀռ�
        if (realSize < size) {
            realSize++;
            wchar_t* res = new wchar_t[realSize];
            wmemmove(res, buffer, realSize);
            delete[] buffer;

            cout << "wcslen(res): " << wcslen(res) << endl;
            wcout << res << endl;
            return res;
        }
        else {
            wcout << buffer << endl;
            return buffer;
        }
    }

    //��ȡ���ַ�������vectorΪ���壩
    wchar_t* GetWCharsV(const char* fileName) {
        cout << "\nMBaseIO::GetWCharsV:\n";
        std::wifstream ifs(fileName,
            std::wifstream::in | std::wifstream::ate 
        );
        if (!ifs) {
            cout << fileName << "�ļ���ʧ��\n";
            return NULL;
        }
        std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
        ifs.imbue(std::locale(ifs.getloc(), codecvtToUnicode));

        size_t size = static_cast<size_t>(ifs.tellg());
        ifs.seekg(0, ifs.beg);

        std::vector<wchar_t> vec(size + 1,0);
        ifs.read(vec.data(), size);
        ifs.close();

        //vector to wchar_t*
        wchar_t* res = new wchar_t[vec.size()];
        wcscpy_s(res, vec.size(), vec.data());

        cout << "gcount:" << ifs.gcount() << "\t";
        cout << "size:" << size << "\t\t";
        cout << "wcslen: " << wcslen(res) << "\t";
        cout << "vec.size(): " << vec.size() << endl;
        wcout << res << endl;
        return res;
    }

    //***************************************************************
    //Write                                                         *
    //***************************************************************
    //����д��
    bool OverWriteFile(const char* fileName, const char* content) {
        cout << "\nMBaseIO::OverWriteFile:\n";
        //���ļ�
        std::ofstream truncfile(fileName,
            std::ios::out |
            std::ios::trunc    //ģʽ����д
        );
        if (!truncfile.is_open()) {
            cout << fileName << " Open fail" << endl;
            return false;
        }
        //д��
        truncfile.write(content, std::strlen(content));
        //�ر�
        truncfile.close();
        cout << "strlen(content):" << strlen(content) << endl;
        return true;
    }
    //׷��д��
    bool AppendFile(const char* fileName, const char* content) {
        cout << "\nMBaseIO::AppendFile:\n";
        std::ofstream appfile(fileName,
            std::ios::out |
            std::ios::app      //ģʽ��׷��
        );
        if (!appfile) {
            cout << fileName << " Open fail" << endl;
            return false;
        }
        appfile.write(content, std::strlen(content));
        appfile.close();
        cout << "strlen(content):" << strlen(content) << endl;
        return true;
    }

    //����д��UTF8
    bool OverWriteUTF8(const char* fileName, const wchar_t* content) {
        cout << "\nMBaseIO::OverWriteUTF8:\n";
        std::wofstream wof;
        wof.open(fileName, 
            std::ios::out | std::ios::trunc
        );
        if (!wof.is_open()) {
            cout << fileName << "Open fail" << endl;
            return false;
        }
        std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
        wof.imbue(std::locale(wof.getloc(), codecvtToUnicode));
        wof.write(content, wcslen(content));
        wof.close();
        
        cout << "wcslen(content):"<<wcslen(content) << endl;
        return true;
    }
}