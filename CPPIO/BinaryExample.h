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