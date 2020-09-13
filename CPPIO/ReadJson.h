#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "rapidjson/document.h"

/*
* 读取JSON文件数据到Document
*/
rapidjson::Document ReadFile(const std::string& fileName) {
    rapidjson::Document doc;
    //1.文件=>char*
    std::ifstream file(fileName, std::ifstream::ate);
    if (!file) {
        std::cout << "Open File Faild";
        return doc;
    }
    //获取文档大小
    std::ifstream::pos_type size = file.tellg();
    file.seekg(0, std::ifstream::beg);
    //存储到buffer
    std::vector<char> buffer(static_cast<size_t>(size) + 1);
    file.read(buffer.data(), size);
    file.close();
    //std::cout << buffer.data() << "\n";
    //2.字符串=>Document
    doc.Parse(buffer.data());
    return doc;
}

