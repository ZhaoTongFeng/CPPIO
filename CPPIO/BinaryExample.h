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


//Class或者Struct读写二进制
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

//把某一位设置成0或者1
void BitSetMask(int& value,int index,bool isT) {
    if (index < 0 || index >= 32) { return; }
    value = isT ? value | (1 << index) : value & (~(1 << index));
    return;
}

//判断某一位是否为1
void BitMask(int value, int index,bool& isT) {
    if (index < 0 || index >= 32) { return; }
    isT = ((value >> index) & 1) == 1;
    return;
}



void BinaryArray() {
    //std::string fileName = "./binary/array.bin";

    //int a[] = { 1,2,3,4,5 };

    //std::fstream outfile(fileName, std::fstream::out | std::fstream::binary);
    //outfile.write(reinterpret_cast<char*>(a), sizeof(a));
    //outfile.close();
    //std::cout << sizeof(a)<<"\n";

    //int b[5];
    //std::fstream infile(fileName, std::fstream::in | std::fstream::binary);
    //infile.read(reinterpret_cast<char*>(b), sizeof(a));
    //infile.close();
    //for (int i = 0; i < 5; i++) {
    //    std::cout << b[i];
    //}

    //std::string fileName = "./binary/array-bool.bin";

    //bool a[] = { 1,0,1,1,0,1,0,0 };

    //std::fstream outfile(fileName, std::fstream::out | std::fstream::binary);
    //outfile.write(reinterpret_cast<char*>(a), sizeof(a));
    //outfile.close();
    //std::cout << sizeof(a) << "\n";

    //bool b[8];
    //std::fstream infile(fileName, std::fstream::in | std::fstream::binary);
    //infile.read(reinterpret_cast<char*>(b), sizeof(a));
    //infile.close();
    //for (int i = 0; i < 8; i++) {
    //    std::cout << b[i];
    //}

    std::string fileName = "./binary/array-bool.bin";

    int a = 0;
    BitSetMask(a, 9, 1);
    BitSetMask(a, 8, 1);

    std::fstream outfile(fileName, std::fstream::out | std::fstream::binary);
    outfile.write(reinterpret_cast<char*>(&a), sizeof(a));
    outfile.close();
    std::cout << sizeof(a) << "\n";

    int b;
    std::fstream infile(fileName, std::fstream::in | std::fstream::binary);
    infile.read(reinterpret_cast<char*>(&b), sizeof(a));
    infile.close();
    std::cout << b<<"\n";

    bool x1;
    BitMask(b, 9, x1);
    std::cout << x1<<"\n";
    BitMask(b, 8, x1);
    std::cout << x1<<"\n";
}

#include "Read.h"
//把文本文件转换成二进制文件，并进行压缩测试
//然而没有任何卵用
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


//因为上面的操作完全是复制粘贴，下面测试手动对Block进行排列，将三维数组保存成二进制文件并重新读取
void TestBlocks() {

    const char* fileName = "./json/Blocks.json";
    rapidjson::Document doc = GetDocument(fileName);
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

    //初始化三维数组[13][4][4]
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
    

    //将文件中的数组读取到三维数组
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
    //for (int i = 0; i < count; i++) {
    //   for (int j = 0; j < 4; j++) {
    //       for (int k = 0; k < 4; k++) {
    //           std::cout << blocks[i][j][k];
    //       }
    //       std::cout << std::endl;
    //   }
    //   std::cout << std::endl;
    //}

    //存储为二进制
    //将208个bit保存到7个32bit的int变量中(224的空间，最后剩下16个空bit);
    std::string outFileName = "./binary/Blocks.bin";
    int size = count * 4 * 4;
    int arrSize = static_cast<size_t>(ceil((float)size / 32.0f));//ceil向上取整
    int* arr = new int[arrSize];
    for (int i = 0; i < arrSize; i++) {
        arr[i] = 0;
    }
    
    int bitPtr = 0;
    for (int i = 0; i < count; i++) {
       for (int j = 0; j < 4; j++) {
           for (int k = 0; k < 4; k++) {
               BitSetMask(arr[static_cast<int>(floor(bitPtr / 32))], (bitPtr++) % 32, blocks[i][j][k]);               
           }
       }
    }
    

    std::fstream outfile(outFileName, std::fstream::out | std::fstream::binary);
    outfile.write(reinterpret_cast<char*>(arr), sizeof(int)* arrSize);
    std::cout << sizeof(int) * arrSize << "\n";
    outfile.close();

    //还原成数组
    //先接受7个int型变量
    int* newarr = new int[arrSize];
    std::fstream infile(outFileName, std::fstream::in | std::fstream::binary);
    infile.read(reinterpret_cast<char*>(newarr), sizeof(int)* arrSize);
    infile.close();

    //初始化三维数组[13][4][4]
    bool*** newblocks = new bool** [count];
    for (int i = 0; i < count; i++) {
        newblocks[i] = new bool* [4];
        for (int j = 0; j < 4; j++) {
            newblocks[i][j] = new bool[4];
            for (int k = 0; k < 4; k++) {
                newblocks[i][j][k] = 0;
            }
        }
    }

    //13*16=208
    //根据已知的尺寸进行遍历设置，这些数据需要进行记录，以便读取的时候使用
    //这里其实就用了3个数据，count=13，rol=4，row=4，其实可以直接保存在之前剩余的16个bit里面，然后这里读出来
    bool isT;
    int col = 0;
    for (int i = 0; i < size; i++) {
        BitMask(newarr[static_cast<int>(floor((float)i/32.0f))], i%32, isT);
        int x = static_cast<int>(floor((float)i / 16.0f));
        int y = (int)(((float)i/4.0f))%4;
        int z = i % 4;
        newblocks[x][y][z] = isT;
    }

    for (int i = 0; i < count; i++) {
       for (int j = 0; j < 4; j++) {
           for (int k = 0; k < 4; k++) {
               std::cout << newblocks[i][j][k];
           }
           std::cout << std::endl;
       }
       std::cout << std::endl;
    }
}


//用文本模式打开二进制文件发生错误