#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <codecvt>//����ת��ͽ���



//���ı��ļ���String�����������ʹ��GetXXXV
class MFileReader {
public:
    //***************************************************************
    //��խ�ַ�����                                                  *
    //***************************************************************
    //916,1007
    static char* GetChars(const char* fileName) {
        char* buffer = nullptr;
        //���ļ�������|�ļ�ָ������ĩβ��
        std::ifstream ifs(fileName,
            std::ifstream::in | std::ifstream::ate | std::ifstream::binary
        );
        if (!ifs) {
            std::cout << fileName << "�ļ���ʧ��\n";
            return buffer;
        }
        //��ȡ�ļ���С
        size_t size = static_cast<size_t>(ifs.tellg());
        //�ļ�ָ�����õ���λ
        ifs.seekg(0, ifs.beg);

        //Array buffer
        buffer = new char[size + 1];
        ifs.read(buffer, size);
        buffer[size] = 0;
        ifs.close();
        
        std::cout << "gcount:" << ifs.gcount() << "\n";
        std::cout << "arr.len: " << strlen(buffer) << " \nContent:" << buffer << "\n";
        return buffer;
    }
    //916,1008
    static char* GetCharsV(const char* fileName) {
        std::ifstream ifs(fileName,
            std::ifstream::in | std::ifstream::ate
        );
        if (!ifs) {
            std::cout << fileName << "�ļ���ʧ��\n";
            return NULL;
        }
        size_t size = static_cast<size_t>(ifs.tellg());
        ifs.seekg(0, ifs.beg);
        //����vector������
        std::vector<char> vec(size+1);
        ifs.read(vec.data(), size);
        ifs.close();

        //�ͷŻ��߷����ַ���
        //����ֱ�ӽ�vec�����ݿ�����char*����Ϊ�ں������������֮��û����new������vector���char�������vector�ͷš�
        //res = vec.data();
        char* res = new char[vec.size()];
        strncpy_s(res, vec.size(), vec.data(), vec.size());

        std::cout << "gcount:" << ifs.gcount() << "\n";
        std::cout << "vec.size: " << vec.size() << " \nContent:" << vec.data() << "\n";
        return res;
    }
    //operator >> �����ڶ�ȡ�ı�����
    //ʹ�����ַ�����UTF8���ļ����������������Ĵ���String.size()�ķ���ֵ���ص�Ҳ���������������ļ��Ŀռ��С
    static std::string GetString(const char* fileName) {
        std::string res = "";
        std::ifstream ifs(fileName);
        if (!ifs) {
            std::cout << fileName << "�ļ���ʧ��\n";
            return res;
        }
        while (ifs) {
            ifs >> res;
        }
        
        ifs.close();

        std::cout << "gcount:" << ifs.gcount() << "\n";
        std::cout << "str.size:" << res.size() << " \nContent:" << res << "\n";
        return res;
    }
    //***************************************************************
    //�ÿ��ַ�����                                                  *
    //***************************************************************
    //296��339
    static wchar_t* GetWChars(const char* fileName) {
        wchar_t* res = nullptr;
        std::wifstream ifs(fileName,
            std::wifstream::in | std::wifstream::ate | std::ifstream::binary
        );
        if (!ifs) {
            std::cout << fileName << "�ļ���ʧ��\n";
            return res;
        }
        //��Ҫ���ý��뷽ʽ
        std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
        ifs.imbue(std::locale(ifs.getloc(), codecvtToUnicode));

        size_t size = static_cast<size_t>(ifs.tellg());
        ifs.seekg(0, ifs.beg);

        res = new wchar_t[size];
        ifs.read(res, size);
        ifs.close();

        std::wcout << "gcount:" << ifs.gcount() << "\n";
        std::wcout << "arr.len: " << wcslen(res) << " \nContent:" << res << "\n";
        return res;
    }
    //296��325
    //�ļ���С��325�����ַ�������ȷ�����С��
    static wchar_t* GetWCharsV(const char* fileName) {
        std::wifstream ifs(fileName,
            std::wifstream::in | std::wifstream::ate
        );
        if (!ifs) {
            std::cout << fileName << "�ļ���ʧ��\n";
            return NULL;
        }
        std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
        ifs.imbue(std::locale(ifs.getloc(), codecvtToUnicode));
        
        size_t size = static_cast<size_t>(ifs.tellg());
        ifs.seekg(0, ifs.beg);

        std::vector<wchar_t> vec(size);
        ifs.read(vec.data(), size);
        ifs.close();

        //vector to wchar_t*
        wchar_t* res = new wchar_t[vec.size()];
        wcscpy_s(res, vec.size(), vec.data());

        std::wcout << "gcount:" << ifs.gcount() << "\n";
        std::wcout << "vec.size: " << vec.size() << " \nContent:" << vec.data() << "\n";
        return res;
    }

    //����Ƕ�ȡ�ı��ļ���ʹ�����ַ�ʽ�����㣬����wstring.size()���صľ����ַ����ĸ���
    static std::wstring GetWString(const char* fileName) {
        std::wstring res = L"";
        std::wifstream ifs(fileName);
        if (!ifs) {
            std::cout << fileName << "�ļ���ʧ��\n";
            return res;
        }
        std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
        ifs.imbue(std::locale(ifs.getloc(), codecvtToUnicode));

        while (ifs)
        {
            ifs >> res;
        }
        
        ifs.close();

        std::wcout << L"gcount:" << ifs.gcount() << L"\n";
        std::wcout << L"wstr.size:" << res.size() << L" \nContent:" << res << L"\n";
        return res;
    }
};