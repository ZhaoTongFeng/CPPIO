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
        std::cout << "MFileReader::GetChars:\n";
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

        std::cout << "size:" << size << std::endl;
        std::cout << "gcount:" << ifs.gcount() << std::endl;
        std::cout << "arr.len: " << strlen(buffer) << " \nContent:\n";
        std::cout << buffer << std::endl;
        
        return buffer;
    }
    //916,1008
    static char* GetCharsV(const char* fileName) {
        std::cout << "\nMFileReader::GetCharsV:\n";
        std::ifstream ifs(fileName,
            std::ifstream::in | std::ifstream::ate | std::ifstream::binary
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

        std::cout << "size:" << size << std::endl;
        std::cout << "gcount:" << ifs.gcount() << std::endl;
        std::cout << "vec[size]:" << (vec[size] == 0) << std::endl;
        std::cout << "res.len:" << strlen(res) << std::endl;
        std::cout << "vec.size(): " << vec.size() << " \nContent:\n";
        
        std::cout << res << std::endl;
        
        return res;
    }
    //operator >> �����ڶ�ȡ�ı�����
    //ʹ�����ַ�����UTF8���ļ����������������Ĵ���String.size()�ķ���ֵ���ص�Ҳ���������������ļ��Ŀռ��С

    static std::string GetString(const char* fileName) {
        std::cout << "\nMFileReader::GetString:\n";
        std::string res = "";
        std::ifstream ifs(fileName,
            std::ifstream::in | std::ifstream::ate | std::ifstream::binary
        );
        if (!ifs) {
            std::cout << fileName << "�ļ���ʧ��\n";
            return res;
        }
        size_t size = static_cast<size_t>(ifs.tellg());
        ifs.seekg(0, ifs.beg);
        char c;
        while (!ifs.eof()) {
            ifs.get(c);
            if(c!='\r')
                res += c;
        }
        //res += '0';

        ifs.close();
        const char* chars = res.c_str();

        std::cout << "size:" << size << std::endl;
        std::cout << "gcount:" << ifs.gcount() << std::endl;

        std::cout << "arr.len: " << strlen(chars) << " \nContent:\n";
        std::cout << chars << std::endl;
        
        std::cout << "str.size:" << res.size() << std::endl;
        std::cout << "Content:" << res << std::endl;
        
        return res;
    }
    //***************************************************************
    //�ÿ��ַ�����                                                  *
    //***************************************************************
    //296��339
    static wchar_t* GetWChars(const char* fileName) {
        std::cout << "\nMFileReader::GetWChars:\n";
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

        res = new wchar_t[size+1];
        ifs.read(res, size);
        ifs.close();
        res[size] = 0;

        std::cout << "gcount:" << ifs.gcount() << std::endl;
        //std::wcout << "res[8]:" << res[size-1] << std::endl;
        std::cout << "arr.len: " << wcslen(res) << std::endl;
        std::wcout << L"Content:\n" << res;
        return res;
    }
    //296��325
    //�ļ���С��325�����ַ�������ȷ�����С��
    static wchar_t* GetWCharsV(const char* fileName) {
        std::cout << "\nMFileReader::GetWCharsV:\n";
        std::wifstream ifs(fileName,
            std::wifstream::in | std::wifstream::ate | std::ifstream::binary
        );
        if (!ifs) {
            std::cout << fileName << "�ļ���ʧ��\n";
            return NULL;
        }
        std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
        ifs.imbue(std::locale(ifs.getloc(), codecvtToUnicode));
        
        size_t size = static_cast<size_t>(ifs.tellg());
        ifs.seekg(0, ifs.beg);

        std::vector<wchar_t> vec(size+1);
        ifs.read(vec.data(), size);
        ifs.close();
        vec[size] = 0;
        //vector to wchar_t*
        wchar_t* res = new wchar_t[vec.size()];
        wcscpy_s(res, vec.size(), vec.data());

        std::cout << "gcount:" << ifs.gcount() << std::endl;
        std::cout << "vec.size: " << vec.size()<< " \nContent:\n";
        std::wcout << res << L"\n";
        return res;
    }

    //����Ƕ�ȡ�ı��ļ���ʹ�����ַ�ʽ�����㣬����wstring.size()���صľ����ַ����ĸ���
    static std::wstring GetWString(const char* fileName) {
        std::cout << "\nMFileReader::GetWString:\n";
        std::wstring res = L"";
        std::wifstream ifs(fileName, 
            std::ifstream::in | std::ifstream::binary
        );
        if (!ifs) {
            std::cout << fileName << "�ļ���ʧ��\n";
            return res;
        }
        std::codecvt_utf8<wchar_t, 0x10ffff, std::consume_header>* codecvtToUnicode = new std::codecvt_utf8 < wchar_t, 0x10ffff, std::consume_header >;
        ifs.imbue(std::locale(ifs.getloc(), codecvtToUnicode));
        wchar_t c;
        while (!ifs.eof())
        {
            //ifs >> res;
            ifs.get(c);
            res += c;;
        }
        
        ifs.close();

        std::cout << "gcount:" << ifs.gcount() << std::endl;
        std::cout << "wstr.size:" << res.size() << " \nContent:\n";
        std::wcout << res;
        return res;
    }
};