#pragma once
#include <iostream>
#include <string>
//1.引入库文件
#include <fstream>
#include <vector>
#include <stdio.h>


void readTest() {

    //std::cout << "输入字符串：";
    //char c1 = std::cin.get();
    //char c2;
    //char c3;
    //std::cin.get(c2).get(c3);


    //std::cout << c1 << c2 << c3;
    //
    //std::cin.ignore(1);

    //char cn1[256];
    //char cn2[256];
    //std::cin.getline(cn1,256);
    //std::cin.getline(cn2,256);
    //
    //char cn3[10];
    //std::cin.read(cn3, 10);
    //std::cout << cn1 << "\n" << cn2 << "\n" << cn3;
}


void putbackTest() {
    std::cout << "输入一个数字或者一个单词:";

    //std::cin.seekg(0, std::cin.beg);

    char c = std::cin.get();//提取首个字符
    std::cout << "tellg:" << std::cin.tellg() << "\n";

    ////继承自ios
    ////手动设置状态
    //std::cin.setstate(std::cin.failbit);
    ////根据掩码获取状态,不能判断good，good时0&0=0
    //if (std::cin.rdstate()&std::cin.failbit) {
    //    std::cout << "failbit" << "\n";
    //}
    //if (std::cin.good()) {
    //    std::cout << "good" << "\n";
    //}
    ////如果failbit或者badbit被设置返回false
    //if (std::cin) {
    //    std::cout << "good" << "\n";
    //}
    //if (!std::cin) {
    //    std::cout << "good" << "\n";
    //}
    ////清除状态
    //std::cin.clear();

    //std::cout << std::cin.bad() << "\n";

    //根据输入的字符先进行判断
    if ((c >= '0') && (c <= '9')) {
        std::cin.putback(c);//放回原位，还原
        int n;
        std::cin >> n;
        std::cout << n;
    }
    else {
        //std::cin.putback(c);
        std::cin.putback('m');//放回其它字符

        std::string str;
        std::cin >> str;
        std::cout << str;
    }




}

void ungetTest() {
    //std::cout << "输入一个数字或者一个单词:";
    ////提取首个字符
    //char c = std::cin.get();

    ////根据输入的字符先进行判断
    //if ((c >= '0') && (c <= '9')) {
    //    //放回原位，还原
    //    std::cin.unget();
    //    int n;
    //    std::cin >> n;
    //    std::cout << n;
    //}
    //else {
    //    std::cin.unget();
    //    std::string str;
    //    std::cin >> str;
    //    std::cout << str;
    //}

    std::cout << "输入一个数字或者一个单词:";
    //提取首个字符
    char c = std::cin.peek();

    //根据输入的字符先进行判断
    if ((c >= '0') && (c <= '9')) {
        int n;
        std::cin >> n;
        std::cout << n;
    }
    else {
        std::string str;
        std::cin >> str;
        std::cout << str;
    }
}





void tieTest() {
    std::ostream* prevstr;
    std::ofstream ofs;
    ofs.open("test.txt");

    std::cout << "tie example:\n";

    //std::cin.tie()返回值是Get，参数是Set
    *std::cin.tie() << "This is inserted into cout";

    //这里将cin的输出对象绑定到了ofs，所以在此调用cin的时候，就会将数据输出到ofs而不是cout
    prevstr = std::cin.tie(&ofs);
    *std::cin.tie() << "This is inserted into the file";
    std::cin.tie(prevstr);

    ofs.close();

    ////默认情况下为true，这意味着C++和C流使用相同的缓冲区，因此，可以自由地混合使用流。同步C++标准流可以确保线程安全。
    ////但是这里测试的没有发生异步的情况，可能是版本问题
    ////关闭iostream对象和cstdio流同步，可以提高输入输出效率
    //std::ios::sync_with_stdio(false);
    //std::cout << "a\n";
    //std::printf("b\n");
    //std::cout << "c\n";

    ////默认情况下，cin绑定的是cout，每次执行<<操作的时候都要调用flush，这样会增加IO负担，可以通过tie(0)解除绑定
    //std::cin.tie(0);

    //std::ofstream file("text.txt");
    //std::cin.tie(&file);

    //char c;
    //while (std::cin>>c)
    //{
    //    file << c;
    //}
    //file.close();
}