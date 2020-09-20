#pragma once
#include <string>

#include "rapidjson/document.h"

class RapidJSONHelper {
public:
    static int GetFloat(const rapidjson::Value& obj, const char* key, float& outValue) {
        auto iter = obj.FindMember(key);
        if (iter == obj.MemberEnd()) {
            return false;
        }
        auto& property = iter->value;
        if (!property.IsDouble()) {
            return false;
        }
        outValue = property.GetFloat();
        return true;
    }
    static int GetInt(const rapidjson::Value& obj, const char* key, int& outValue) {
        auto iter = obj.FindMember(key);
        if (iter == obj.MemberEnd()) {
            return false;
        }
        auto& property = iter->value;
        if (!property.IsInt()) {
            return false;
        }
        outValue = property.GetInt();
        return true;
    }
    static int GetString(const rapidjson::Value& obj, const char* key, string& outValue) {
        auto iter = obj.FindMember(key);
        if (iter == obj.MemberEnd()) {
            return false;
        }
        auto& property = iter->value;
        if (!property.IsString()) {
            return false;
        }
        outValue = property.GetString();
        return true;
    }


    static void AddFloat(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& obj, const char* key, float inValue) {
        rapidjson::Value v(inValue);
        obj.AddMember(rapidjson::StringRef(key), v, alloc);
    }
    static void AddInt(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& obj, const char* key, int inValue) {
        rapidjson::Value v(inValue);
        obj.AddMember(rapidjson::StringRef(key), v, alloc);
    }
    static void AddString(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& obj, const char* key, const string& inValue) {
        rapidjson::Value v;
        v.SetString(inValue.c_str(), static_cast<rapidjson::SizeType>(inValue.length()), alloc);
        obj.AddMember(rapidjson::StringRef(key), v, alloc);
    }

    static int Get(const rapidjson::Value& obj, const char* key, float& outValue) {
        return GetFloat(obj, key, outValue);
    }
    static int Get(const rapidjson::Value& obj, const char* key, int& outValue) {
        return GetInt(obj, key, outValue);
    }
    static int Get(const rapidjson::Value& obj, const char* key, string& outValue) {
        return GetString(obj, key, outValue);
    }
    static void Add(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& obj, const char* key, float inValue) {
        AddFloat(alloc, obj, key, inValue);
    }
    static void Add(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& obj, const char* key, int inValue) {
        AddInt(alloc, obj, key, inValue);
    }
    static void Add(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& obj, const char* key, const string& inValue) {
        AddString(alloc, obj, key, inValue);
    }
};

