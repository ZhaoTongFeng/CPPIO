#pragma once

#include "RapidJSONHelper.h"
#include "JsonFileIO.h"
using namespace MJsonFileIO;


void ReadJSON() {
    //1.���ļ��ж�ȡ���ݣ����ַ���ת����`rapidjson::Document`
    const char* fileName = "./json/Riven.json";
    rapidjson::Document doc = GetDocument(fileName);
    if (!doc.IsObject()) {
        cout << "Faild to valid JSON";
        return;
    }

    //2.��`rapidjson::Document`��ȡ����
    //������������ʹ��
    string id = doc["id"].GetString();
    cout << "id:" << id << " characters size:" << id.size() << " id[0]:" << id[0] << endl;
    cout << "key:" << doc["key"].GetString() << endl;
    string name = doc["name"].GetString();
    cout << "name:" << name << " characters size:" << name.size() << " key[0]:" << name[0] << endl;
    cout << "title:" << doc["title"].GetString() << endl;

    //��������
    cout << "skins:";
    for (auto& kv : doc["skins"].GetArray()) {
        cout << kv.GetInt() << ",";
    }
    cout << endl;

    //������
    rapidjson::Value& vStats = doc["stats"];
    rapidjson::Value& vHp = vStats["hp"];
    rapidjson::Value& vSpellblock = vStats["spellblock"];

    cout << "hp:" << vHp.GetInt() << endl;
    cout << "spellblock:" << vSpellblock.GetDouble() << endl;
}


void ReadWJSON() {
    const char* fileName = "./json/Riven.json";
    WDocument doc = GetWDocument(fileName);

    if (!doc.IsObject()) {
        cout << "Faild to valid JSON";
        return;
    }

    wstring id = doc[L"id"].GetString();
    wcout << L"id:" << id << "\tid.size()" << id.size() << "\tid[0]:" << id[0] << L"\n";
    wcout << L"key:" << doc[L"key"].GetString() << L"\n";

    wstring name = doc[L"name"].GetString();
    wcout << L"name:" << name << L"\tname.size():" << name.size() << L"\tname[0]:" << name[0] << L"\n";
    wcout << L"title:" << doc[L"title"].GetString() << L"\n";

    cout << "skins:";
    for (auto& kv : doc[L"skins"].GetArray()) {
        cout << kv.GetInt() << ",";
    }
    cout << endl;

    WValue& vStats = doc[L"stats"];
    WValue& vHp = vStats[L"hp"];
    WValue& vSpellblock = vStats[L"spellblock"];

    cout << "hp:" << vHp.GetInt() << endl;
    cout << "spellblock:" << vSpellblock.GetDouble() << endl;

    //����֮�󱣴�
    const char* newName = "./json/Riven-Update.json";
    vHp.SetInt(100000);
    SaveWRapidJson(doc, newName);
}



//���㹹��һ��JSON DOM��д���ļ�
void WriteJSON() {
    //1.��ʼ��Document
    rapidjson::Document doc;
    doc.SetObject();

    //2.��������
    doc.AddMember("key1", "string", doc.GetAllocator());
    //Object
    rapidjson::Value key2(rapidjson::kObjectType);
    key2.AddMember("key2.1", 123, doc.GetAllocator());
    key2.AddMember("key2.2", true, doc.GetAllocator());
    doc.AddMember("key2", key2, doc.GetAllocator());
    doc.AddMember("key3", 1.23, doc.GetAllocator());
    //Array
    rapidjson::Value key4(rapidjson::kArrayType);
    for (int i = 1; i < 9; i++) {
        key4.PushBack(i, doc.GetAllocator());
    }
    doc.AddMember("key4", key4, doc.GetAllocator());

    //3.���浽�ļ�
    SaveRapidJson(doc, "./json/WriteJSON.json");
}




//�����п���Խ�羯��
#pragma warning( disable : 6386 )


//����˹�����д��ļ���ȡ��������״
const int BLOCK_LENGTH = 4;
void ReadBlocks() {
    const char* fileName = "./json/Blocks.json";
    rapidjson::Document doc = GetDocument(fileName);
    if (!doc.IsObject()) {
        cout << "Faild to valid JSON";
        return;
    }
    //��ȡ�ڵ�
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
    //��ʼ����ά����[13][BLOCK_LENGTH][BLOCK_LENGTH]
    int*** blocks = new int** [count];
    for (int i = 0; i < count; i++) {
        blocks[i] = new int* [BLOCK_LENGTH];
        for (int j = 0; j < BLOCK_LENGTH; j++) {
            blocks[i][j] = new int[BLOCK_LENGTH];
            for (int k = 0; k < BLOCK_LENGTH; k++) {
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
                int row = static_cast<int>(floor(k / BLOCK_LENGTH));
                int col = k % BLOCK_LENGTH;
                blocks[n][row][col] = matrix[k].GetInt();
            }
            n++;
        }
    }
    //�鿴������ά�����е�����
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < BLOCK_LENGTH; j++) {
            for (int k = 0; k < BLOCK_LENGTH; k++) {
                cout << blocks[i][j][k] << " ";
            }
            cout << std::endl;
        }
        cout << std::endl;
    }
    for (int i = 0; i < count; i++) {

        for (int j = 0; j < BLOCK_LENGTH; j++) {
            delete[] blocks[i][j];
        }
        delete[] blocks[i];
    }
    delete[] blocks;
    delete[] blockNum;
    delete[] sumNum;
}