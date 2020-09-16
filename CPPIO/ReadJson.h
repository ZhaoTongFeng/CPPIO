#pragma once
#include <iostream>
#include <fstream>
#include <vector>

#include "rapidjson/document.h"


/*
* 读取JSON文件数据到Document
*/
rapidjson::Document GetDocument(const std::string& fileName) {
    rapidjson::Document doc;
    ////1.文件=>字符串
    //std::ifstream file(fileName, std::ifstream::ate);
    //if (!file) {
    //    std::cout << "Open File Faild";
    //    return doc;
    //}
    //std::ifstream::pos_type size = file.tellg();
    //file.seekg(0, std::ifstream::beg);
    //std::vector<char> buffer(static_cast<size_t>(size) + 1);
    //file.read(buffer.data(), size);
    //file.close();
    ////2.字符串=>Document
    //doc.Parse(buffer.data());
    doc.Parse(GetCharsV(fileName.c_str()));
    return doc;
}

#include "Read.h"

typedef rapidjson::GenericDocument<rapidjson::UTF16<> > WDocument;
typedef rapidjson::GenericValue<rapidjson::UTF16<> > WValue;

#include "rapidjson/filereadstream.h"

#include "rapidjson/encodedstream.h"
//转码
//http://rapidjson.org/zh-cn/md_doc_encoding_8zh-cn.html
#include "rapidjson/encodings.h"
#include "rapidjson/stringbuffer.h"
#include <cstdio>
#pragma warning(disable:4996)
//读取UTF8编码的JSON文件数据到Document
WDocument GetWDocument(const char* fileName) {
    WDocument doc;
    //FILE* fp = fopen(fileName, "rb");
    //char readBuffer[65536];
    //rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    //rapidjson::EncodedInputStream<rapidjson::UTF8<>, rapidjson::FileReadStream> eis(is);
    //doc.ParseStream<0,rapidjson::UTF8<> >(eis);
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
    char* s = buffer.data();
    rapidjson::StringStream source(s);
    rapidjson::GenericStringBuffer<rapidjson::UTF16<>> target;
    bool hasError = false;
    while (source.Peek() != '\0')
        if (!rapidjson::Transcoder<rapidjson::UTF8<>, rapidjson::UTF16<> >::Transcode(source, target)) {
            hasError = true;
            break;
        }

    if (!hasError) {
        const wchar_t* t = target.GetString();
        doc.Parse(t);
    }
    return doc;
}

