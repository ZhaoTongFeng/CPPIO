#pragma once

#include <iostream>
#include <fstream>
#include <vector>

#include "rapidjson/document.h"

//using namespace rapidjson;

void PartOne() {
    std::cout << "Hello World!\n";
    const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
    printf("Original JSON:\n %s\n", json);

    rapidjson::Document documnet;
    documnet.Parse(json);

    assert(documnet.IsObject());

    //读：JSON->C/C++
    //字符串
    assert(documnet.HasMember("hello"));
    assert(documnet["hello"].IsString());
    printf("hello=%s\n", documnet["hello"].GetString());

    //迭代器方法
    rapidjson::Value::MemberIterator iter = documnet.FindMember("hello");//当我们不确定一个成员是否存在的时候，用documnet.HasMember("hello")+documnet["hello"]会造成两次查找，而用FindMember只需一次
    assert(iter != documnet.MemberEnd());
    assert(iter->value.IsString());
    assert(strcmp("world", iter->value.GetString()) == 0);
    //消除没有使用变量的警告，假装使用的这个变量
    (void)iter;

    //布尔值
    bool t = documnet["t"].GetBool();
    bool f = documnet["f"].GetBool();

    //NULL
    bool isNull = documnet["n"].IsNull();

    //Integer
    assert(documnet["i"].IsNumber());
    int i1 = documnet["i"].GetInt();
    //Double
    double d = documnet["pi"].GetDouble();




    //数组和vector类似
    //保存到Value
    const rapidjson::Value& a = documnet["a"];
    assert(a.IsArray());
    //1.常规遍历Array
    for (rapidjson::SizeType i = 0; i < a.Size(); i++) {
        printf("a[%d]=%d\n", i, a[i].GetInt());
    }
    int y = a[0].GetInt();
    //2.迭代器遍历Array
    for (rapidjson::Value::ConstValueIterator it = a.Begin(); it != a.End(); ++it) {
        printf("%d\n", it->GetInt());
    }
    //3.C++11范围for循环遍历Array
    for (auto& v : a.GetArray()) {
        printf("%d\n", v.GetInt());
    }

    //和遍历Array类似，也能遍历Document的Objec
    static const char* kTypeNames[] = { "Null","False","True","Object","Array","String","Number" };
    for (rapidjson::Value::ConstMemberIterator it = documnet.MemberBegin(); it != documnet.MemberEnd(); ++it) {
        printf("Type of member %s is %s\n", it->name.GetString(), kTypeNames[it->value.GetType()]);
    }
    //C++11
    for (auto& m : documnet.GetObject()) {
        printf("Type of member %s is %s\n", m.name.GetString(), kTypeNames[m.value.GetType()]);
    }

    /**
    * Number类型
    * 都有对应的获取函数
    * unsigned  32位无符号整数
    * int       32位有符号整数
    * uint64_t  64位无符号整数
    * int64_t   64位有符号整数
    * double    64位双精度浮点数
    */

    //查询String
    rapidjson::SizeType size = documnet["hello"].GetStringLength();//SizeType其实是无符号整数，typedef unsigned SizeType;
    //"a\u0000b"，这个字符串GetStringLength会返回长度为3，而strlen返回1，因为C/C++把\0当成结尾字符串

    //比较
    if (documnet["hello"] == documnet["n"]) {}//比较两个值，true:类型和内容都相等
    //Array/Object相比较，当且仅当他们的整个子树相当，他们才相等
    //注意，如果一个Object中含有重复命名的成员，它与任何Object相比较都返回false


    //创建/修改
    //当使用默认构造函数构造Value/Document时，他们的类型为NULL，要更改其类型，需要调用SetXXX()函数
    rapidjson::Document outDoc;
    outDoc.SetObject();

    rapidjson::Value val;
    val.SetInt(100);
    val = 100;

    //构造函数重载
    rapidjson::Value val2(true);
    rapidjson::Value val3(1);
    rapidjson::Value val4(1.2);
    rapidjson::Value val5(123u);

    rapidjson::Value val6(rapidjson::kObjectType);
    rapidjson::Value val7(rapidjson::kArrayType);

    //转移语义，A=B，不是把B的值复制给A，而是把B的值移动到A
    val = val3;//val=1,val3=Null
    //正常赋值
    //PushBack() 也采用转移语义。
    //在C++11里面称为转移赋值操作(Move Assignment Operator)
    outDoc.AddMember("val", val, outDoc.GetAllocator());

    //直接Add/Push一个Value，临时对象不能转换成正常的引用，通过Move函数可以
    rapidjson::Document::AllocatorType& allocator = outDoc.GetAllocator();
    outDoc.PushBack(rapidjson::Value().SetInt(312), allocator);
    outDoc.PushBack(rapidjson::Value(32).Move(), allocator);






    //创建String
    //有两种策略
    //1.copy-string:分配缓冲区，然后把源数据复制过来
    //2.const-string:简单的存储字符串指针

    //Copy-String总是安全的，因为它拥有数据的克隆
    //Const-String可用于存储字符串字面值

    //为了让用户自定义内存分配方式，当一个操作可能需要分配内存时，要求传入一个allocator，这样就避免每一个Value存储Allocator/Document的指针
    //意思就是，直接将allocator传入函数，函数直接通过allocator进行动态内存分配

    char buffer[10];
    int len = sprintf_s(buffer, "%s", "abcd");
    rapidjson::Value val20;
    val20.SetString(buffer, len, outDoc.GetAllocator());//还有一个不需要lenth的重载
    memset(buffer, 0, sizeof(buffer));

    //对于字符串字面值
    rapidjson::Value val21;
    val21.SetString("rapidJSON");
    val21 = "rapidJSON";

    //即使是char*，如果不复制也是安全的情况下，使用StringRef函数

    const char* str = "qewjnqwd";
    size_t str_len = strlen(str);
    val21.SetString(rapidjson::StringRef(str));
    val21 = rapidjson::StringRef(str);
    val21.SetString(rapidjson::StringRef(str, str_len));//更快可以处理空字符
    val21 = rapidjson::StringRef(str, str_len);


    //修改Array
    //Clear()
    //Reserve(SizeType, Allocator&)
    //Value& PushBack(Value&, Allocator&)
    //template <typename T> GenericValue& PushBack(T, Allocator&)
    //Value& PopBack()
    //ValueIterator Erase(ConstValueIterator pos)
    //ValueIterator Erase(ConstValueIterator first, ConstValueIterator last)

    //Reserve和PushBack可能会为分配内存，需要Allocator
    for (int x = 0; x < 10; x++) {
        outDoc.PushBack(x, outDoc.GetAllocator());
    }
    //Pushback返回的自身的引用，这称为流畅接口（Fluent Interface）
    outDoc.PushBack("123", outDoc.GetAllocator()).PushBack("WQD", outDoc.GetAllocator());

    outDoc.PushBack(rapidjson::Value("key", outDoc.GetAllocator()).Move(), outDoc.GetAllocator());


    //修改Object
    //Object是键值对集合
    //添加
    //Value& AddMember(Value&, Value&, Allocator & allocator)
    //Value& AddMember(StringRefType, Value&, Allocator&)
    //template <typename T> Value& AddMember(StringRefType, T value, Allocator&)

    rapidjson::Value val22(rapidjson::kObjectType);
    val22.AddMember("KEY", "VALUE", outDoc.GetAllocator());

    //
    val22.AddMember(
        rapidjson::Value("KEY", outDoc.GetAllocator()).Move(),
        rapidjson::Value("VALUE", outDoc.GetAllocator()).Move(),
        outDoc.GetAllocator()
    );
    //删除
    //bool RemoveMember(const Ch * name)：使用键名来移除成员（线性时间复杂度）。
    //bool RemoveMember(const Value & name)：除了 name 是一个 Value，和上一行相同。
    //MemberIterator RemoveMember(MemberIterator)：使用迭代器移除成员（_ 常数 _ 时间复杂度）。
    //MemberIterator EraseMember(MemberIterator)：和上行相似但维持成员次序（线性时间复杂度）。
    //MemberIterator EraseMember(MemberIterator first, MemberIterator last)：移除一个范围内的成员，维持次序（线性时间复杂度）。

    //MemberIterator RemoveMember(MemberIterator) 使用了“转移最后”手法来达成常数时间复杂度。基本上就是析构迭代器位置的成员，然后把最后的成员转移至迭代器位置。因此，成员的次序会被改变。

    //深复制Value
    rapidjson::Document targetDoc;
    rapidjson::Document::AllocatorType& ac = targetDoc.GetAllocator();

    rapidjson::Value val23("123");
    rapidjson::Value val24(val23, ac);//深拷贝
    targetDoc.SetArray().PushBack(val23, ac).PushBack(val24, ac);

    val23.CopyFrom(targetDoc, ac);//整个doc复制给val23，但是doc不会变
    val24.SetObject().AddMember("array", val23, ac);
    targetDoc.PushBack(val24, ac);

    //上面这些操作，都不会改变原本的结构，都是调用allocator的或者copyfrom函数

    //交换Vvalue，时间复杂度常数
    val2.Swap(val22);
}



#include "rapidjson/filereadstream.h"

#include "rapidjson/encodedstream.h"
//转码
//http://rapidjson.org/zh-cn/md_doc_encoding_8zh-cn.html
#include "rapidjson/encodings.h"
#include "rapidjson/stringbuffer.h"
#include <cstdio>
#pragma warning(disable:4996)
void FileStream() {
    //使用RAPIDJSON的字符串读取大文件
    //FILE* fp = fopen(fileName, "rb");
    //char readBuffer[65536];
    //rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    //rapidjson::EncodedInputStream<rapidjson::UTF8<>, rapidjson::FileReadStream> eis(is);
    //doc.ParseStream<0,rapidjson::UTF8<> >(eis);
}

void Transcode() {
    //完全没有任何问题，直接出来就是wchar_t，但是转换成了UTF16编码
    //typedef rapidjson::GenericDocument<rapidjson::UTF16<> > WDocument;
    //typedef rapidjson::GenericValue<rapidjson::UTF16<> > WValue;
    //std::ifstream file(fileName, std::ifstream::ate);
    //if (!file) {
    //    std::cout << "Open File Faild";
    //    return doc;
    //}
    //std::ifstream::pos_type size = file.tellg();
    //file.seekg(0, std::ifstream::beg);
    //std::vector<char> buffer(static_cast<size_t>(size) + 1);
    //file.read(buffer.data(), size);
    //file.close();
    ////转码
    //char* s = buffer.data();
    //rapidjson::StringStream source(s);
    //rapidjson::GenericStringBuffer<rapidjson::UTF16<>> target;
    //bool hasError = false;
    //while (source.Peek() != '\0')
    //    if (!rapidjson::Transcoder<rapidjson::UTF8<>, rapidjson::UTF16<> >::Transcode(source, target)) {
    //        hasError = true;
    //        break;
    //    }

    //if (!hasError) {
    //    const wchar_t* t = target.GetString();
    //    doc.Parse(t);
    //}
    //return doc;
}