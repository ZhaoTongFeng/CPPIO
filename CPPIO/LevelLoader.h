#pragma once
#include <stdio.h>
#include <iostream>

#include <string>
#include <functional>
#include <unordered_map>
#include <fstream>
#include <vector>

#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

class LevelLoader
{
public:
	static bool LoadJSON(const std::string& fileName, rapidjson::Document& outDoc);
	static void SaveLevel(const std::string& fileName);
};

class JsonHelper {
public:
	static bool GetInt(const rapidjson::Value& inObject, const char* inProperty, int& outInt);
	static void AddInt(rapidjson::Document::AllocatorType& alloc,
		rapidjson::Value& inObject, const char* name, int value);
};







bool LevelLoader::LoadJSON(const std::string& fileName, rapidjson::Document& outDoc)
{

    //以二进制流的形式将文件读取到内存
    //ate:loaded with stream buffer at the end (ate)
    std::ifstream file(fileName, std::ios::in | std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        printf("File %s not found", fileName.c_str());
        return false;
    }
    //获取Stream Buffer当前的位置（因为之前ate读取到数据末尾，所以当前位置就是File的Size-1）
    std::ifstream::pos_type fileSize = file.tellg();

    //把指针置于首位
    file.seekg(0, std::ios::beg);

    //申请一个容器
    std::vector<char> bytes(static_cast<size_t>(fileSize) + 1);
    //读取到容器
    file.read(bytes.data(), static_cast<size_t>(fileSize));
    //转换成RapidJSON Document
    outDoc.Parse(bytes.data());
    if (!outDoc.IsObject()) {
        printf("File %s is not valid JSON", fileName.c_str());
        return false;
    }
    return true;
}

void LevelLoader::SaveLevel(const std::string& fileName)
{
    rapidjson::Document doc;
    doc.SetObject();
    //写入KV
    JsonHelper::AddInt(doc.GetAllocator(), doc, "version", 2);

    rapidjson::Value child(rapidjson::kObjectType);
    JsonHelper::AddInt(doc.GetAllocator(), child, "propertice1", 2);
    JsonHelper::AddInt(doc.GetAllocator(), child, "propertice2", 2);

    doc.AddMember("obj", child, doc.GetAllocator());

    //获取字符串
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    const char* output = buffer.GetString();
    //写入文件
    std::ofstream outFile(fileName);
    if (outFile.is_open()) {
        outFile << output;
    }
}

bool JsonHelper::GetInt(const rapidjson::Value& inObject, const char* inProperty, int& outInt)
{
    auto itr = inObject.FindMember(inProperty);
    if (itr == inObject.MemberEnd()) {
        return false;
    }
    auto& property = itr->value;
    if (!property.IsInt()) {
        return false;
    }
    outInt = property.GetInt();
    return true;
}

void JsonHelper::AddInt(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* name, int value)
{
    rapidjson::Value v(value);
    inObject.AddMember(rapidjson::StringRef(name), v, alloc);
}


void LevelLoaderTest() {
    //加载文档
    rapidjson::Document doc;
    if (!LevelLoader::LoadJSON("InFile/MyJSON.json", doc)) {
        return;
    }

    //读取数据
    int version = 0;
    if (!JsonHelper::GetInt(doc, "version", version)) {
        return;
    }
    printf("%d", version);

    //保存数据
    LevelLoader::SaveLevel("OutFile/MyJSON.json");
}