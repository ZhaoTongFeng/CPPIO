#pragma once

#include "RapidJSONHelper.h"
#include "ReadJson.h"
#include "WriteJson.h"

//C++ ���������ڳ�ʼ������ʱ���Զ��� ��\0�� �����ַ�����ĩβ������Ҳ���������������ʽ���г�ʼ��char greeting[] = "Hello";
//C++��char�ַ�����Ȼ����'\0'��β�ģ���string�ַ�����������'\0'��β�ġ�

//�����п���Խ�羯��
//�������ﻹ���ڴ�й©
#pragma warning( disable : 6386 )
//����˹�����д��ļ���ȡ��������״
void ReadBlocks() {

    const static char* fileName = "./json/Blocks.json";
    rapidjson::Document doc = GetDocument(fileName);
    if (!doc.IsObject()) {
        std::cout << "Faild to valid JSON";
        return;
    }
    rapidjson::Value& vBlocks = doc["Blocks"];

    //��״����
    const int shapeNum = vBlocks.Size();

    //��״�ķ�������
    int* blockNum = new int[shapeNum];

    //��״��Χ
    int* sumNum = new int[shapeNum];

    //��ʼ����ά����
    for (int i = 0; i < shapeNum; i++) {
        blockNum[i] = 0;
        sumNum[i] = 0;
    }

    //��������
    int count = 0;
    for (int i = 0; i < shapeNum; i++) {
        //ÿ����״��Ӧ�ĽǶ�����
        blockNum[i] = vBlocks[i].Size();
        sumNum[i] += 0;
        count += blockNum[i];
    }

    //��ʼ����ά����[13][4][4]

    int*** blocks = new int** [count];

    for (int i = 0; i < count; i++) {
        blocks[i] = new int* [4];
        for (int j = 0; j < 4; j++) {
            blocks[i][j] = new int[4];
            for (int k = 0; k < 4; k++) {
                blocks[i][j][k] = 0;
            }
        }
    }


    //���ļ��е������ȡ����ά����
    int n = 0;
    for (int i = 0; i < shapeNum; i++) {
        for (int j = 0; j < blockNum[i]; j++) {
            rapidjson::Value matrix = vBlocks[i][j].GetArray();
            for (int k = 0; k < static_cast<int>(matrix.Size()); k++) {
                int row = static_cast<int>(floor(k / 4));
                int col = k % 4;
                blocks[n][row][col] = matrix[k].GetInt();
            }
            n++;
        }
    }

    //�鿴������ά�����е�����
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                std::cout << blocks[i][j][k];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }


    //�ͷ�������Դ
    //���ʹ��delete�����ͷţ��ᱨC6283����
    //��int*���������飬Ӧ����delete[]���ͷ�
    //delete �� delete[]��Ȼ���ܽ�����Ŀռ��ͷŵ����������������������������ɶ������飬��ôֻ����õ�һ�����������������
    //https://docs.microsoft.com/zh-tw/visualstudio/code-quality/c6283?view=vs-2015
    //https://www.cnblogs.com/whwywzhj/p/7905176.html
    for (int i = 0; i < count; i++) {

        for (int j = 0; j < 4; j++) {
            delete[] blocks[i][j];
        }
        delete[] blocks[i];
    }
    delete[] blocks;

    delete[] blockNum;
    delete[] sumNum;

}

//��ȡӢ������Ӣ������
void ReadJSON() {    
    //1.���ļ��ж�ȡ���ݣ����ַ���ת����`rapidjson::Document`
    const char* fileName = "./json/Riven.json";
    rapidjson::Document doc = GetDocument(fileName);
    if (!doc.IsObject()) {
        std::cout << "Faild to valid JSON";
        return;
    }

    //2.��`rapidjson::Document`��ȡ����
    //������������ʹ��
    std::string id = doc["id"].GetString();
    std::cout << "id:" << id << " characters size:" << id.size() <<" id[0]:"<<id[0]<< "\n";
    
    //��ȡ����
    std::cout << "key:" << doc["key"].GetString() << "\n";
    
    std::string name = doc["name"].GetString();
    std::cout << "name:" << name << " characters size:"<< name.size() <<" key[0]:"<< name[0]<< "\n";
    
    std::cout << "title:" << doc["title"].GetString() << "\n";
    

    //��������
    std::cout << "skins:";
    for (auto& kv : doc["skins"].GetArray()) {
        std::cout << kv.GetInt() << ",";
    }
    std::cout << "\n";

    //��ȡ������
    rapidjson::Value& vStats = doc["stats"];
    rapidjson::Value& vHp = vStats["hp"];
    rapidjson::Value& vSpellblock = vStats["spellblock"];

    std::cout << "hp:"<<vHp.GetInt() << "\n";
    std::cout << "spellblock:"<<vSpellblock.GetDouble() << "\n";
}


void ReadWJSON() {
    //1.��ȡ����
    const char* fileName = "./json/Riven.json";
    WDocument doc = GetWDocument(fileName);

    if (!doc.IsObject()) {
        std::cout << "Faild to valid JSON";
        return;
    }

    //2.��ȡ����
    //������������ʹ��
    std::wstring id = doc[L"id"].GetString();
    std::wcout << L"id:" << id << "\tid.size()" << id.size() << "\tid[0]:" << id[0] << L"\n";
    std::wcout << L"key:" << doc[L"key"].GetString() << L"\n";

    std::wstring name = doc[L"name"].GetString();
    std::wcout << L"name:" << name << L"\tname.size():" << name.size() << L"\tname[0]:" << name[0] << L"\n";
    std::wcout << L"title:" << doc[L"title"].GetString() << L"\n";

    //��������
    std::cout << "skins:";
    for (auto& kv : doc[L"skins"].GetArray()) {
        std::cout << kv.GetInt() << ",";
    }
    std::cout << "\n";

    //��ȡ������
    WValue& vStats = doc[L"stats"];
    WValue& vHp = vStats[L"hp"];
    WValue& vSpellblock = vStats[L"spellblock"];

    std::cout << "hp:" << vHp.GetInt() << "\n";
    std::cout << "spellblock:" << vSpellblock.GetDouble() << "\n";
}
















//���Թ���һ��JSON Document��д���ļ�
void WriteJSON() {
    //1.��ʼ��Document
    rapidjson::Document doc;
    doc.SetObject();

    //2.�������
    doc.AddMember("key1", "string", doc.GetAllocator());

    //Object
    rapidjson::Value key2(rapidjson::kObjectType);
    key2.AddMember("key2.1", 123, doc.GetAllocator());
    key2.AddMember("key2.2", true, doc.GetAllocator());
    doc.AddMember("key2", key2, doc.GetAllocator());

    doc.AddMember("key3", 1.23, doc.GetAllocator());

    //Array������std::vector
    rapidjson::Value key4(rapidjson::kArrayType);
    for (int i = 1; i < 9; i++) {
        key4.PushBack(i, doc.GetAllocator());
    }
    doc.AddMember("key4", key4, doc.GetAllocator());

    SaveFile(doc, "./json/WriteJSON.json");
}




void OtherOption() {
    //Update&&Delete Test
    const char* fileName = "out.json";
    rapidjson::Document inDoc = GetDocument(fileName);
    if (!inDoc.IsObject()) { std::cout << "Faild to valid JSON"; return; }

    //Update
    rapidjson::Value::MemberIterator inkey1 = inDoc.FindMember("key1");
    inkey1->value = "update";

    //Delete
    rapidjson::Value::MemberIterator inkey2 = inDoc.FindMember("key2");
    inDoc.RemoveMember(inkey2);

    SaveFile(inDoc, fileName);
}