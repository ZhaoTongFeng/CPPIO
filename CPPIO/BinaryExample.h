#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include "Read.h"
#include "BinaryIO.h"

//用文本模式打开二进制文件发生错误

//Class或者Struct读写二进制
class MyClass
{
public:
    MyClass() :a(0), b(0), c(0) {};
    int a;
    float b;
    double c;
    char chars[512] = "qwertyui";
    void Print() { std::cout << a << "\n" << b << "\n" << c << "\n" << chars; };
};
void BinaryIO() {
    std::string fileName = "./binary/outfile.bin";
    //Write
    MyClass cls;
    cls.a = 10;
    cls.b = 2.1f;
    cls.c = 3.2;

    std::fstream outfile(fileName, std::fstream::out | std::fstream::binary);
    outfile.write(reinterpret_cast<char*>(&cls), sizeof(cls));
    outfile.close();

    //Read
    MyClass cls2;
    std::fstream infile(fileName, std::fstream::in | std::fstream::binary);
    infile.read(reinterpret_cast<char*>(&cls2), sizeof(cls2));
    infile.close();
    cls2.Print();
}


//把文本文件转换成二进制文件，并进行压缩测试
//对字符串没有任何用处
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





void BitTest() {
    std::string fileName = "./binary/array-bool.bin";

    int a = 0;
    SetBit(a, 9, 1);
    SetBit(a, 8, 1);

    std::fstream outfile(fileName, std::fstream::out | std::fstream::binary);
    outfile.write(reinterpret_cast<char*>(&a), sizeof(a));
    outfile.close();
    std::cout << sizeof(a) << "\n";

    int b;
    std::fstream infile(fileName, std::fstream::in | std::fstream::binary);
    infile.read(reinterpret_cast<char*>(&b), sizeof(a));
    infile.close();
    std::cout << b << "\n";

    bool x1;
    GetMask(b, 9, x1);
    std::cout << x1 << "\n";
    GetMask(b, 8, x1);
    std::cout << x1 << "\n";
}


void BinaryArray() {
    std::string fileName = "./binary/array.bin";

    //写
    int b1[] = { 1,2,3,4,5 };
    int a1 = static_cast<int>(sizeof(b1) / sizeof(int));
    std::fstream outfile(fileName, std::fstream::out | std::fstream::binary);
    outfile.write(reinterpret_cast<char*>(&a1), sizeof(int));
    outfile.write(reinterpret_cast<char*>(b1), sizeof(b1));
    outfile.close();
    
    //读
    int a2;
    int* b2;
    std::fstream infile(fileName, std::fstream::in | std::fstream::binary);
    infile.read(reinterpret_cast<char*>(&a2), sizeof(int));
    b2 = new int[a2];
    infile.read(reinterpret_cast<char*>(b2), a2*sizeof(int));
    infile.close();

    //打印数组整体大小
    std::cout << sizeof(b1) << "\n";
    //打印数组元素
    for (int i = 0; i < a2; i++) {
        std::cout << b2[i];
    }
}







//固定方块尺寸BLOCK_LEN * BLOCK_LEN
const int BLOCK_LEN = 4;

////////////////////////////////////////////////////////////////////
//从JSON文件中读取数据转换成二进制
////////////////////////////////////////////////////////////////////
void JsonToBinary(const char* inFileName, const char* outFileName) {
    ////////////////////////////////////////////////////////////////
    //读取并解析JSON
    ////////////////////////////////////////////////////////////////
    rapidjson::Document doc = GetDocument(inFileName);
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

    for (int i = 0; i < shapeNum; i++) {
        //每个形状对应的角度数量
        blockNum[i] = vBlocks[i].Size();
        sumNum[i] += 0;
        count += blockNum[i];
    }

    //初始化三维数组[13][BLOCK_LEN][BLOCK_LEN]
    bool*** blocks = new bool** [count];
    for (int i = 0; i < count; i++) {
        blocks[i] = new bool* [BLOCK_LEN];
        for (int j = 0; j < BLOCK_LEN; j++) {
            blocks[i][j] = new bool[BLOCK_LEN];
            for (int k = 0; k < BLOCK_LEN; k++) {
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
                int row = static_cast<int>(floor(k / BLOCK_LEN));
                int col = k % BLOCK_LEN;
                blocks[n][row][col] = static_cast<bool>(matrix[k].GetInt());
            }
            n++;
        }
    }
    
    ////////////////////////////////////////////////////////////////
    //存储为二进制
    ////////////////////////////////////////////////////////////////
    //将208个bit保存到7个32bit的int变量中(224的空间，最后剩下16个空bit);
    int size = count * BLOCK_LEN * BLOCK_LEN;
    int arrSize = static_cast<size_t>(ceil((float)size / 32.0f));//ceil向上取整
    
    int* arr = new int[arrSize];
    for (int i = 0; i < arrSize; i++) {
        arr[i] = 0;
    }
    //设置bit位
    int bitPtr = 0;
    for (int i = 0; i < count; i++) {
       for (int j = 0; j < BLOCK_LEN; j++) {
           for (int k = 0; k < BLOCK_LEN; k++) {
               SetBit(arr[static_cast<int>(floor(bitPtr / 32))], (bitPtr++) % 32, blocks[i][j][k]);               
           }
       }
    }

    std::fstream outfile(outFileName, std::fstream::out | std::fstream::binary);
    outfile.write(reinterpret_cast<char*>(&arrSize), sizeof(int));
    outfile.write(reinterpret_cast<char*>(&count), sizeof(int));
    outfile.write(reinterpret_cast<char*>(arr), sizeof(int)* arrSize);
    outfile.close();

    std::cout << sizeof(int) * arrSize << "\n";


    for (int i = 0; i < count; i++) {
        for (int j = 0; j < BLOCK_LEN; j++) {
            delete[] blocks[i][j];
        }
        delete[] blocks[i];
    }
    delete[] blockNum;
    delete[] sumNum;
    delete[] arr;
}


////////////////////////////////////////////////////////////////////
//从二进制还原成数组
////////////////////////////////////////////////////////////////////
void LoadBinaryBlocks(const char* outFileName) {
    //用了N个32位int型变量保存所有数据（7个）
    int arrSize = 0;

    //一共有多少个方块（13个）
    int count = 0;

    //用于接收arrSize个32位int
    int* intArr = nullptr;

    //读取
    std::fstream infile(outFileName, std::fstream::in | std::fstream::binary);
    infile.read(reinterpret_cast<char*>(&arrSize), sizeof(int));
    infile.read(reinterpret_cast<char*>(&count), sizeof(int));
    intArr = new int[arrSize];
    for (int i = 0; i < arrSize; i++) {
        intArr[i] = 0;
    }
    infile.read(reinterpret_cast<char*>(intArr), sizeof(int) * arrSize);
    infile.close();

    //三维数组存储count个BLOCK_LEN*BLOCK_LEN矩阵
    bool*** blocks = new bool** [count];
    for (int i = 0; i < count; i++) {
        blocks[i] = new bool* [BLOCK_LEN];
        for (int j = 0; j < BLOCK_LEN; j++) {
            blocks[i][j] = new bool[BLOCK_LEN];
            for (int k = 0; k < BLOCK_LEN; k++) {
                blocks[i][j][k] = 0;
            }
        }
    }

    //遍历每一个bit，13*4*4=208<32*7=224
    bool isT;
    int col = 0;
    for (int i = 0; i < count * BLOCK_LEN * BLOCK_LEN; i++) {
        GetMask(intArr[static_cast<int>(floor((float)i / 32.0f))], i % 32, isT);
        int x = static_cast<int>(floor((float)i / 16.0f));
        int y = (int)(((float)i / 4.0f)) % BLOCK_LEN;
        int z = i % BLOCK_LEN;
        blocks[x][y][z] = isT;
    }

    //显示读取数据
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < BLOCK_LEN; j++) {
            for (int k = 0; k < BLOCK_LEN; k++) {
                std::cout << blocks[i][j][k]<<" ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

//测试
void SaveLoadTest(){
    const char* inFileName = "./json/Blocks.json";
    const char* outFileName = "./binary/Blocks.bin";
    JsonToBinary(inFileName, outFileName);
    LoadBinaryBlocks(outFileName);
}