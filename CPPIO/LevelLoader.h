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

    //�Զ�����������ʽ���ļ���ȡ���ڴ�
    //ate:loaded with stream buffer at the end (ate)
    std::ifstream file(fileName, std::ios::in | std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        printf("File %s not found", fileName.c_str());
        return false;
    }
    //��ȡStream Buffer��ǰ��λ�ã���Ϊ֮ǰate��ȡ������ĩβ�����Ե�ǰλ�þ���File��Size-1��
    std::ifstream::pos_type fileSize = file.tellg();

    //��ָ��������λ
    file.seekg(0, std::ios::beg);

    //����һ������
    std::vector<char> bytes(static_cast<size_t>(fileSize) + 1);
    //��ȡ������
    file.read(bytes.data(), static_cast<size_t>(fileSize));
    //ת����RapidJSON Document
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
    //д��KV
    JsonHelper::AddInt(doc.GetAllocator(), doc, "version", 2);

    rapidjson::Value child(rapidjson::kObjectType);
    JsonHelper::AddInt(doc.GetAllocator(), child, "propertice1", 2);
    JsonHelper::AddInt(doc.GetAllocator(), child, "propertice2", 2);

    doc.AddMember("obj", child, doc.GetAllocator());

    //��ȡ�ַ���
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    const char* output = buffer.GetString();
    //д���ļ�
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
    //�����ĵ�
    rapidjson::Document doc;
    if (!LevelLoader::LoadJSON("InFile/MyJSON.json", doc)) {
        return;
    }

    //��ȡ����
    int version = 0;
    if (!JsonHelper::GetInt(doc, "version", version)) {
        return;
    }
    printf("%d", version);

    //��������
    LevelLoader::SaveLevel("OutFile/MyJSON.json");
}