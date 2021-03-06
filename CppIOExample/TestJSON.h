#pragma once

#include "RapidJSONHelper.h"
#include "JsonFileIO.h"
using namespace MJsonFileIO;


void ReadJSON() {
    //1.从文件中读取数据，将字符串转换成`rapidjson::Document`
    const char* fileName = "./json/Riven.json";
    rapidjson::Document doc = GetDocument(fileName);
    if (!doc.IsObject()) {
        cout << "Faild to valid JSON";
        return;
    }

    //2.从`rapidjson::Document`获取变量
    //拷贝到变量中使用
    string id = doc["id"].GetString();
    cout << "id:" << id << " characters size:" << id.size() << " id[0]:" << id[0] << endl;
    cout << "key:" << doc["key"].GetString() << endl;
    string name = doc["name"].GetString();
    cout << "name:" << name << " characters size:" << name.size() << " key[0]:" << name[0] << endl;
    cout << "title:" << doc["title"].GetString() << endl;

    //遍历数组
    cout << "skins:";
    for (auto& kv : doc["skins"].GetArray()) {
        cout << kv.GetInt() << ",";
    }
    cout << endl;

    //深层变量
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

    //更改之后保存
    const char* newName = "./json/Riven-Update.json";
    vHp.SetInt(100000);
    SaveWRapidJson(doc, newName);
}



//从零构建一个JSON DOM并写入文件
void WriteJSON() {
    //1.初始化Document
    rapidjson::Document doc;
    doc.SetObject();

    //2.添加内容
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

    //3.保存到文件
    SaveRapidJson(doc, "./json/WriteJSON.json");
}




//数组有可能越界警告
#pragma warning( disable : 6386 )


//俄罗斯方块中从文件读取出方块形状
const int BLOCK_LENGTH = 4;
void ReadBlocks() {
    const char* fileName = "./json/Blocks.json";
    rapidjson::Document doc = GetDocument(fileName);
    if (!doc.IsObject()) {
        cout << "Faild to valid JSON";
        return;
    }
    //获取节点
    rapidjson::Value& vBlocks = doc["Blocks"];

    //形状数量
    const int shapeNum = vBlocks.Size();

    //形状的方块数量
    int* blockNum = new int[shapeNum];

    //形状范围
    int* sumNum = new int[shapeNum];

    //初始化二维数组
    for (int i = 0; i < shapeNum; i++) {
        blockNum[i] = 0;
        sumNum[i] = 0;
    }
    //方块数量
    int count = 0;
    for (int i = 0; i < shapeNum; i++) {
        //每个形状对应的角度数量
        blockNum[i] = vBlocks[i].Size();
        sumNum[i] += 0;
        count += blockNum[i];
    }
    //初始化三维数组[13][BLOCK_LENGTH][BLOCK_LENGTH]
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
    //将文件中的数组读取到三维数组
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
    //查看现在三维数组中的数据
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
