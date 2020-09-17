#pragma once
#include <iostream>
#include <fstream>
#include <string>

class MyClass
{
public:
    MyClass() :a(0), b(0), c(0) {};
    int a;
    float b;
    double c;
    char chars[512]{ 'q','w','e','r','t' };
    //std::string str;
};


//Class����Struct��д������
void BinaryIO() {
    std::string fileName = "./binary/outfile.bin";
    //Write
    MyClass cls;
    cls.a = 10;
    cls.b = 2.1f;
    cls.c = 3.2;

    //cls.str = "qwe";
    std::fstream outfile(fileName, std::fstream::out | std::fstream::binary);
    outfile.write(reinterpret_cast<char*>(&cls), sizeof(cls));
    outfile.close();

    //Read
    MyClass cls2;
    std::fstream infile(fileName, std::fstream::in | std::fstream::binary);
    infile.read(reinterpret_cast<char*>(&cls2), sizeof(cls2));
    infile.close();
    std::cout << cls2.a << std::endl << cls2.b << std::endl << cls2.c << std::endl << cls2.chars;
}

void BinaryArray() {
    std::string fileName = "./binary/array.bin";

    int a[] = { 1,2,3,4,5 };

    std::fstream outfile(fileName, std::fstream::out | std::fstream::binary);
    outfile.write(reinterpret_cast<char*>(a), sizeof(a));
    outfile.close();
    std::cout << sizeof(a)<<"\n";

    int b[5];
    std::fstream infile(fileName, std::fstream::in | std::fstream::binary);
    infile.read(reinterpret_cast<char*>(b), sizeof(a));
    infile.close();
    for (int i = 0; i < 5; i++) {
        std::cout << b[i];
    }
}

#include "Read.h"
//���ı��ļ�ת���ɶ������ļ���������ѹ������
//Ȼ��û���κ�����
void TransToBinary() {
    const char truncFileName[] = "./file/truncFile.txt";
    const char appFileName[] = "./file/appFile.txt";
    const char utf8File[] = "./file/utf8.txt";
    const char* BlocksFileName = "./json/Blocks.json";
    const char* RivenFileName = "./json/Riven.json";

    const char newtruncFileName[] = "./binary/truncFile.txt";
    const char newappFileName[] = "./binary/appFile.txt";
    const char newutf8File[] = "./binary/utf8.txt";
    const char* newBlocksFileName = "./binary/Blocks.json";
    const char* newRivenFileName = "./binary/Riven.json";

    std::string names[] = { truncFileName ,appFileName ,utf8File ,BlocksFileName ,RivenFileName };
    std::string newnames[] = { newtruncFileName ,newappFileName ,newutf8File ,newBlocksFileName ,newRivenFileName };

    char* content = nullptr;
    std::ofstream outfile;

    for (int i = 0; i < 5; i++) {
        const char* fileName = names[i].c_str();
        content = MFileReader::GetCharsV(fileName);
        


        const char* newName = newnames[i].c_str();
        outfile.open(newName, std::fstream::out | std::fstream::binary);
        if (!outfile) {
            std::cout << fileName << "Open faild\n";
            return;
        }
        outfile.write(content, strlen(content));
        outfile.close();

        std::cout << strlen(content) << "\n" << content << "\n";
        
    }
}


//��Ϊ����Ĳ�����ȫ�Ǹ���ճ������������ֶ���Block�������У�����ά���鱣��ɶ������ļ������¶�ȡ
void TestBlocks() {

    const char* fileName = "./json/Blocks.json";
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

    bool*** blocks = new bool** [count];

    for (int i = 0; i < count; i++) {
        blocks[i] = new bool* [4];
        for (int j = 0; j < 4; j++) {
            blocks[i][j] = new bool[4];
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
                blocks[n][row][col] = static_cast<bool>(matrix[k].GetInt());
            }
            n++;
        }
    }
    delete[] blockNum;
    delete[] sumNum;
 

    std::string outFileName = "./binary/Blocks.bin";
    int size = count * 4 * 4;
    std::fstream outfile(outFileName, std::fstream::out | std::fstream::binary);
    outfile.write(reinterpret_cast<char*>(blocks), size);
    outfile.close();

    int* newblocks = new int[static_cast<size_t>(size / 4)];
    
    std::fstream infile(outFileName, std::fstream::in | std::fstream::binary);

    infile.read(reinterpret_cast<char*>(newblocks), size);
    infile.close();

    std::cout << size<< "\n";
    //�鿴������ά�����е�����
    for (int i = 0; i < size; i++) {
        std::cout << newblocks[i]<<" ";
    }
    //for (int i = 0; i < count; i++) {
    //    for (int j = 0; j < 4; j++) {
    //        for (int k = 0; k < 4; k++) {
    //            std::cout << blocks[i][j][k];
    //        }
    //        std::cout << std::endl;
    //    }
    //    std::cout << std::endl;
    //}
}


//���ı�ģʽ�򿪶������ļ���������