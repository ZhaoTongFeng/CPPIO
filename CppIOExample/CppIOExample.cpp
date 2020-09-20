#include "TestBase.h"
#include "TestJSON.h"
#include "TestBinary.h"

int main()
{
    setlocale(LC_ALL, "chs");

    //第二篇，普通文件读写
    //BaseTest();

    //第三篇，JSON文件读写
    //ReadJSON();
    //ReadWJSON();
    //WriteJSON();
    ReadBlocks();
    
    //第四篇，二进制文件读写
    //BinFileIO();
    //BitTest();
    //BinaryArray();
    //LevelTest();
    return 0;
}