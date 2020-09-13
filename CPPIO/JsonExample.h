#pragma once

#include "RapidJSONHelper.h"
#include "ReadJson.h"
#include "WriteJson.h"

//数组有可能越界警告
#pragma warning( disable : 6386 )
//俄罗斯方块中从文件读取出方块形状
void ReadBlocks() {
    const std::string fileName = "./json/Blocks.json";
    rapidjson::Document doc = ReadFile(fileName);
    if (!doc.IsObject()) {
        std::cout << "Faild to valid JSON";
        return;
    }
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
    for (int i = 0; i < shapeNum;i++) {
        //每个形状对应的角度数量
        blockNum[i] = vBlocks[i].Size();
        sumNum[i] += 0;
        count += blockNum[i];
    }

    //初始化三维数组[13][4][4]

    int*** blocks = new int**[count];

    for (int i = 0; i < count; i++) {
        blocks[i] = new int* [4];
        for (int j = 0; j < 4; j++) {
            blocks[i][j] = new int[4];
        }
    }

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
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
                int row = static_cast<int>(floor(k/4));
                int col = k%4;
                blocks[n][row][col] = matrix[k].GetInt();
            }
            n++;
        }
    }

    for (int i = 0; i < count; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0;k < 4; k++) {
                std::cout << blocks[i][j][k];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
    

    //释放数组资源
    //如果使用delete进行释放，会报C6283警告
    //用int*创建的数组，应该用delete[]来释放
    //delete 和 delete[]虽然都能将申请的空间释放掉，但区别就是析构函数，如果换成对象数组，那么只会调用第一个对象的析构函数。
    //https://docs.microsoft.com/zh-tw/visualstudio/code-quality/c6283?view=vs-2015
    //https://www.cnblogs.com/whwywzhj/p/7905176.html
    for (int i = 0; i < count; i++) {
        
        for (int j = 0; j < 4; j++) {
            delete[] blocks[i][j];
        }
      delete[] blocks[i];
    }
    delete[] blocks;
}

void ReadJSON() {    
    const std::string fileName = "./json/Heros.json";
    rapidjson::Document doc = ReadFile(fileName);
    if (!doc.IsObject()) {
        std::cout << "Faild to valid JSON";
        return;
    }
    std::cout << "id:" << doc["id"].GetString() << "\n";
    
    //深层节点
    rapidjson::Value& vStats = doc["stats"];
    rapidjson::Value& vHp = vStats["hp"];
    rapidjson::Value& vSpellblock = vStats["spellblock"];

    std::cout << "hp:"<<vHp.GetInt() << "\n";
    std::cout << "spellblock:"<<vSpellblock.GetDouble() << "\n";
    
    //拷贝到变量
    std::string key = doc["name"].GetString();
    std::cout << "key:" << key.size() << "\n";

    //遍历数组
    std::cout << "skins:";
    for (auto& kv : doc["skins"].GetArray()) {
        std::cout << kv.GetInt() << ",";
    }
    std::cout << "\n";
}

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

    //Array类似于std::vector
    rapidjson::Value key4(rapidjson::kArrayType);
    for (int i = 1; i < 9; i++) {
        key4.PushBack(i, doc.GetAllocator());
    }
    doc.AddMember("key4", key4, doc.GetAllocator());

    SaveFile(doc, "./json/WriteJSON.json");
}




void OtherOption() {
    //Update&&Delete Test
    const std::string fileName = "out.json";
    rapidjson::Document inDoc = ReadFile(fileName);
    if (!inDoc.IsObject()) { std::cout << "Faild to valid JSON"; return; }

    //Update
    rapidjson::Value::MemberIterator inkey1 = inDoc.FindMember("key1");
    inkey1->value = "update";

    //Delete
    rapidjson::Value::MemberIterator inkey2 = inDoc.FindMember("key2");
    inDoc.RemoveMember(inkey2);

    SaveFile(inDoc, fileName);
}









