#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "rapidjson/document.h"

#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
/*
* ±£´æDocument
*/
bool SaveFile(rapidjson::Document& doc, const std::string& fileName) {
    //3.Document=>char*
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    const char* output = buffer.GetString();

    //×Ö·û´®=>ÎÄ¼þ
    std::ofstream outFile(fileName, std::ofstream::trunc | std::ofstream::out);
    if (!outFile) {
        std::cout << "Open File Faild";
        return false;
    }
    outFile << output;
    outFile.close();
    return true;
}

