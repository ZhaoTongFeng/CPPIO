#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "rapidjson/document.h"

#include "Read.h"

/*
* ��ȡJSON�ļ����ݵ�Document
*/

rapidjson::Document GetDocument(const char* fileName) {
    rapidjson::Document doc;    
    doc.Parse(MFileReader::GetCharsV(fileName));
    return doc;
}



typedef rapidjson::GenericDocument<rapidjson::UTF8<wchar_t> > WDocument;
typedef rapidjson::GenericValue<rapidjson::UTF8<wchar_t> > WValue;
//��ȡUTF8�����JSON�ļ����ݵ�Document
WDocument GetWDocument(const char* fileName) {
    WDocument doc;
    doc.Parse(MFileReader::GetWCharsV(fileName));
    return doc;
}

