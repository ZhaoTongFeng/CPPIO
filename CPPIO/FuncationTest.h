#pragma once
#include <iostream>
#include <string>
//1.������ļ�
#include <fstream>
#include <vector>
#include <stdio.h>


void readTest() {

    //std::cout << "�����ַ�����";
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
    std::cout << "����һ�����ֻ���һ������:";

    //std::cin.seekg(0, std::cin.beg);

    char c = std::cin.get();//��ȡ�׸��ַ�
    std::cout << "tellg:" << std::cin.tellg() << "\n";

    ////�̳���ios
    ////�ֶ�����״̬
    //std::cin.setstate(std::cin.failbit);
    ////���������ȡ״̬,�����ж�good��goodʱ0&0=0
    //if (std::cin.rdstate()&std::cin.failbit) {
    //    std::cout << "failbit" << "\n";
    //}
    //if (std::cin.good()) {
    //    std::cout << "good" << "\n";
    //}
    ////���failbit����badbit�����÷���false
    //if (std::cin) {
    //    std::cout << "good" << "\n";
    //}
    //if (!std::cin) {
    //    std::cout << "good" << "\n";
    //}
    ////���״̬
    //std::cin.clear();

    //std::cout << std::cin.bad() << "\n";

    //����������ַ��Ƚ����ж�
    if ((c >= '0') && (c <= '9')) {
        std::cin.putback(c);//�Ż�ԭλ����ԭ
        int n;
        std::cin >> n;
        std::cout << n;
    }
    else {
        //std::cin.putback(c);
        std::cin.putback('m');//�Ż������ַ�

        std::string str;
        std::cin >> str;
        std::cout << str;
    }




}

void ungetTest() {
    //std::cout << "����һ�����ֻ���һ������:";
    ////��ȡ�׸��ַ�
    //char c = std::cin.get();

    ////����������ַ��Ƚ����ж�
    //if ((c >= '0') && (c <= '9')) {
    //    //�Ż�ԭλ����ԭ
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

    std::cout << "����һ�����ֻ���һ������:";
    //��ȡ�׸��ַ�
    char c = std::cin.peek();

    //����������ַ��Ƚ����ж�
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

    //std::cin.tie()����ֵ��Get��������Set
    *std::cin.tie() << "This is inserted into cout";

    //���ｫcin���������󶨵���ofs�������ڴ˵���cin��ʱ�򣬾ͻὫ���������ofs������cout
    prevstr = std::cin.tie(&ofs);
    *std::cin.tie() << "This is inserted into the file";
    std::cin.tie(prevstr);

    ofs.close();

    ////Ĭ�������Ϊtrue������ζ��C++��C��ʹ����ͬ�Ļ���������ˣ��������ɵػ��ʹ������ͬ��C++��׼������ȷ���̰߳�ȫ��
    ////����������Ե�û�з����첽������������ǰ汾����
    ////�ر�iostream�����cstdio��ͬ������������������Ч��
    //std::ios::sync_with_stdio(false);
    //std::cout << "a\n";
    //std::printf("b\n");
    //std::cout << "c\n";

    ////Ĭ������£�cin�󶨵���cout��ÿ��ִ��<<������ʱ��Ҫ����flush������������IO����������ͨ��tie(0)�����
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