#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "rapidjson/document.h"

#include "Read.h"

/*
* 读取JSON文件数据到Document
*/

rapidjson::Document GetDocument(const char* fileName) {
    rapidjson::Document doc;    
    doc.Parse(MFileReader::GetCharsV(fileName));
    return doc;
}



typedef rapidjson::GenericDocument<rapidjson::UTF8<wchar_t> > WDocument;
typedef rapidjson::GenericValue<rapidjson::UTF8<wchar_t> > WValue;
//读取UTF8编码的JSON文件数据到Document
WDocument GetWDocument(const char* fileName) {
    WDocument doc;
    doc.Parse(MFileReader::GetWCharsV(fileName));
    return doc;
}

