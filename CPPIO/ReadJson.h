#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "rapidjson/document.h"

/*
* ��ȡJSON�ļ����ݵ�Document
*/
rapidjson::Document ReadFile(const std::string& fileName) {
    rapidjson::Document doc;
    //1.�ļ�=>char*
    std::ifstream file(fileName, std::ifstream::ate);
    if (!file) {
        std::cout << "Open File Faild";
        return doc;
    }
    //��ȡ�ĵ���С
    std::ifstream::pos_type size = file.tellg();
    file.seekg(0, std::ifstream::beg);
    //�洢��buffer
    std::vector<char> buffer(static_cast<size_t>(size) + 1);
    file.read(buffer.data(), size);
    file.close();
    //std::cout << buffer.data() << "\n";
    //2.�ַ���=>Document
    doc.Parse(buffer.data());
    return doc;
}

