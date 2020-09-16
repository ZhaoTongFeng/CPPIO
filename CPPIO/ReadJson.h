#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "rapidjson/document.h"


/*
* ��ȡJSON�ļ����ݵ�Document
*/
rapidjson::Document GetDocument(const std::string& fileName) {
    rapidjson::Document doc;
    //1.�ļ�=>�ַ���
    std::ifstream file(fileName, std::ifstream::ate);
    if (!file) {
        std::cout << "Open File Faild";
        return doc;
    }
    std::ifstream::pos_type size = file.tellg();
    file.seekg(0, std::ifstream::beg);
    std::vector<char> buffer(static_cast<size_t>(size) + 1);
    file.read(buffer.data(), size);
    file.close();
    //2.�ַ���=>Document
    doc.Parse(buffer.data());
    return doc;
}

#include "Read.h"

typedef rapidjson::GenericDocument<rapidjson::UTF16<> > WDocument;
typedef rapidjson::GenericValue<rapidjson::UTF16<> > WValue;
//��ȡUTF8�����JSON�ļ����ݵ�Document
WDocument GetWDocument(const std::string& fileName) {
    WDocument doc;
    std::wstring wstr = GetWString(fileName.c_str());
    doc.Parse(wstr.c_str());
    return doc;
}