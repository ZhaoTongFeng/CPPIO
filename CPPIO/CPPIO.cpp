#include "BaseExample.h"
#include "JsonExample.h"
#include "BinaryExample.h"


//Console用的ANSI，自动识别地区设置默认编码为GB2312，但是默认创建的文本编码为UTF-8
//而在代码中的字符串，肯定默认就是GB2312

int main()
{
    setlocale(LC_ALL, "");

    //第二篇，普通文件读写
    //ReadTest();
    //WriteTest();

    //第三篇，JSON文件读写
    //ReadJSON();
    //ReadWJSON();
    //ReadBlocks();
    //WriteJSON();
    
    //第四篇，二进制文件读写
    //BinaryIO();
    //TransToBinary();
    //BitTest();
    //BinaryArray();
    //SaveLoadTest();
    return 0;
}