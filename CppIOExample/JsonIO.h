#pragma once

#include "BaseIO.h"
//Read
#include "rapidjson/document.h"
//Write
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
using namespace MBaseIO;

namespace MJsonIO {
    rapidjson::Document GetDocument(const char* fileName) {
        rapidjson::Document doc;
        char* ptr = GetCharsV(fileName);
        doc.Parse(ptr);
        delete ptr;
        return doc;
    }

    typedef rapidjson::GenericDocument<rapidjson::UTF8<wchar_t> > WDocument;
    typedef rapidjson::GenericValue<rapidjson::UTF8<wchar_t> > WValue;
    WDocument GetWDocument(const char* fileName) {
        WDocument doc;
        wchar_t* ptr = GetWCharsV(fileName);
        doc.Parse(ptr);
        delete ptr;
        return doc;
    }


    bool SaveRapidJson(rapidjson::Document& doc, const char* fileName) {
        //1.Document=>char*
        rapidjson::StringBuffer buffer;
        rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
        doc.Accept(writer);
        const char* output = buffer.GetString();
        //2.char*=>file
        OverWriteFile(fileName, output);
        return true;
    }

    typedef rapidjson::GenericStringBuffer<rapidjson::UTF8<wchar_t> > WStringBuffer;
    typedef rapidjson::PrettyWriter<WStringBuffer, rapidjson::UTF8<wchar_t>, rapidjson::UTF8<wchar_t>> WPrettyWriter;
    bool SaveWRapidJson(WDocument& doc, const char* fileName) {
        WStringBuffer buffer;
        WPrettyWriter writer(buffer);
        doc.Accept(writer);
        const wchar_t* output = buffer.GetString();
        OverWriteUTF8(fileName, output);
        return true;
    }
}