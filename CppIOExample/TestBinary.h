#pragma once

#include "BaseIO.h"
#include "JsonIO.h"
#include "BinaryIO.h"

using namespace MBaseIO;
using namespace MJsonIO;
using namespace MBinaryIO;

//持久化测试
class MyClass
{
public:
    MyClass() :a(0), b(0), c(0) {};
    int a;
    float b;
    double c;
    char chars[512] = "qwertyui";
    void Print() { cout << a << "\n" << b << "\n" << c << "\n" << chars; };
};

void BinaryIO() {
    string fileName = "./binary/BinaryIO.bin";
    //Write
    MyClass cls;
    cls.a = 10;
    cls.b = 2.1f;
    cls.c = 3.2;

    fstream outfile(fileName, fstream::out | fstream::binary);
    outfile.write(reinterpret_cast<char*>(&cls), sizeof(cls));
    outfile.close();

    //Read
    MyClass cls2;
    fstream infile(fileName, fstream::in | fstream::binary);
    infile.read(reinterpret_cast<char*>(&cls2), sizeof(cls2));
    infile.close();
    cls2.Print();
}


//设置比特位测试
void BitTest() {
    string fileName = "./binary/BitTest.bin";

    int a = 0;
    SetBit(a, 9, 1);
    SetBit(a, 8, 1);

    fstream outfile(fileName, fstream::out | fstream::binary);
    outfile.write(reinterpret_cast<char*>(&a), sizeof(a));
    outfile.close();
    cout << sizeof(a) << "\n";

    int b;
    fstream infile(fileName, fstream::in | fstream::binary);
    infile.read(reinterpret_cast<char*>(&b), sizeof(a));
    infile.close();
    cout << b << "\n";

    bool x1;
    GetMask(b, 9, x1);
    cout << x1 << "\n";
    GetMask(b, 8, x1);
    cout << x1 << "\n";
}


void BinaryArray() {
    string fileName = "./binary/BinaryArray.bin";

    //Write
    int b1[] = { 1,2,3,4,5 };
    int a1 = static_cast<int>(sizeof(b1) / sizeof(int));
    fstream outfile(fileName, fstream::out | fstream::binary);
    outfile.write(reinterpret_cast<char*>(&a1), sizeof(int));
    outfile.write(reinterpret_cast<char*>(b1), sizeof(b1));
    outfile.close();

    //Read
    int a2;
    int* b2;
    fstream infile(fileName, fstream::in | fstream::binary);
    infile.read(reinterpret_cast<char*>(&a2), sizeof(int));
    b2 = new int[a2];
    infile.read(reinterpret_cast<char*>(b2), a2 * sizeof(int));
    infile.close();

    //数组整体大小
    cout << sizeof(b1) << "\n";
    //数组元素
    for (int i = 0; i < a2; i++) {
        cout << b2[i];
    }
}



//固定方块尺寸BLOCK_LEN * BLOCK_LEN
const int BLOCK_LEN = 4;

class TetrisLevel {
private:
    const char* jsonFileName;
    const char* binaryFileName;

    //方块的三维数组
    int*** blocks;

    //方块总数
    int count;
public:
    TetrisLevel(const char* inFileName, const char* outFileName):
        count(0),
        blocks(nullptr)
    {
        jsonFileName = inFileName;
        binaryFileName = outFileName;
        if (!LoadBin()) {
            LoadJson();
            SaveToBin();
        }
    }
    ~TetrisLevel() {
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < BLOCK_LEN; j++) {
                delete[] blocks[i][j];
            }
            delete[] blocks[i];
        }
    }

    //从JSON文件读取数据
    bool LoadJson() {
        //形状数量
        int shapeNum;
        //一个形状有多少个方块
        int* blockNum;
        //一个形状的第一个方块下标
        int* sumNum;

        rapidjson::Document doc = GetDocument(jsonFileName);
        if (!doc.IsObject()) {
            cout << "Faild to valid JSON";
            return false;
        }
        rapidjson::Value& vBlocks = doc["Blocks"];
        shapeNum = vBlocks.Size();
        blockNum = new int[shapeNum];
        sumNum = new int[shapeNum];
        for (int i = 0; i < shapeNum; i++) {
            blockNum[i] = 0;
            sumNum[i] = 0;
        }

        for (int i = 0; i < shapeNum; i++) {
            //每个形状对应的角度数量
            blockNum[i] = vBlocks[i].Size();
            sumNum[i] += 0;
            count += blockNum[i];
        }

        //初始化三维数组[13][BLOCK_LEN][BLOCK_LEN]
        blocks = new int** [count];
        for (int i = 0; i < count; i++) {
            blocks[i] = new int* [BLOCK_LEN];
            for (int j = 0; j < BLOCK_LEN; j++) {
                blocks[i][j] = new int[BLOCK_LEN];
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
                    blocks[n][row][col] = static_cast<int>(matrix[k].GetInt());
                }
                n++;
            }
        }
        delete[] blockNum;
        delete[] sumNum;
        return true;
    }
    //将数据保存为二进制格式
    bool SaveToBin() {
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

        fstream outfile(binaryFileName, fstream::out | fstream::binary);
        outfile.write(reinterpret_cast<char*>(&arrSize), sizeof(int));
        outfile.write(reinterpret_cast<char*>(&count), sizeof(int));
        outfile.write(reinterpret_cast<char*>(arr), sizeof(int) * arrSize);
        outfile.close();

        cout << sizeof(int) * arrSize << "\n";
        delete[] arr;
        return true;
    }

    //从二进制文件中读取数据
    bool LoadBin() {
        //用了N个32位int型变量保存所有数据（7个）
        int arrSize = 0;

        //一共有多少个方块（13个）
        count = 0;

        //用于接收arrSize个32位int
        int* intArr = nullptr;

        //读取
        fstream infile(binaryFileName, fstream::in | fstream::binary);
        if (!infile) {
            cout << binaryFileName<<" Not Found";
            return false;
        }

        infile.read(reinterpret_cast<char*>(&arrSize), sizeof(int));
        infile.read(reinterpret_cast<char*>(&count), sizeof(int));
        intArr = new int[arrSize];
        for (int i = 0; i < arrSize; i++) {
            intArr[i] = 0;
        }
        infile.read(reinterpret_cast<char*>(intArr), sizeof(int) * arrSize);
        infile.close();

        //三维数组存储count个BLOCK_LEN*BLOCK_LEN矩阵
        blocks = new int** [count];
        for (int i = 0; i < count; i++) {
            blocks[i] = new int* [BLOCK_LEN];
            for (int j = 0; j < BLOCK_LEN; j++) {
                blocks[i][j] = new int[BLOCK_LEN];
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
        PrintAllBlocks();
        return true;
    }

    void PrintAllBlocks() {
        //显示读取数据
        for (int i = 0; i < count; i++) {
            for (int j = 0; j < BLOCK_LEN; j++) {
                for (int k = 0; k < BLOCK_LEN; k++) {
                    cout << blocks[i][j][k] << " ";
                }
                cout << std::endl;
            }
            cout << std::endl;
        }
    }
};

//测试
void LevelTest() {
    const char* inFileName = "./json/Blocks.json";
    const char* outFileName = "./binary/Blocks.bin";
    TetrisLevel* level = new TetrisLevel(inFileName, outFileName);
    delete level;
    level = new TetrisLevel(inFileName, outFileName);
    delete level;
}