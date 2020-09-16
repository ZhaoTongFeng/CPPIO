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

    //����JSON->C/C++
    //�ַ���
    assert(documnet.HasMember("hello"));
    assert(documnet["hello"].IsString());
    printf("hello=%s\n", documnet["hello"].GetString());

    //����������
    rapidjson::Value::MemberIterator iter = documnet.FindMember("hello");//�����ǲ�ȷ��һ����Ա�Ƿ���ڵ�ʱ����documnet.HasMember("hello")+documnet["hello"]��������β��ң�����FindMemberֻ��һ��
    assert(iter != documnet.MemberEnd());
    assert(iter->value.IsString());
    assert(strcmp("world", iter->value.GetString()) == 0);
    //����û��ʹ�ñ����ľ��棬��װʹ�õ��������
    (void)iter;

    //����ֵ
    bool t = documnet["t"].GetBool();
    bool f = documnet["f"].GetBool();

    //NULL
    bool isNull = documnet["n"].IsNull();

    //Integer
    assert(documnet["i"].IsNumber());
    int i1 = documnet["i"].GetInt();
    //Double
    double d = documnet["pi"].GetDouble();




    //�����vector����
    //���浽Value
    const rapidjson::Value& a = documnet["a"];
    assert(a.IsArray());
    //1.�������Array
    for (rapidjson::SizeType i = 0; i < a.Size(); i++) {
        printf("a[%d]=%d\n", i, a[i].GetInt());
    }
    int y = a[0].GetInt();
    //2.����������Array
    for (rapidjson::Value::ConstValueIterator it = a.Begin(); it != a.End(); ++it) {
        printf("%d\n", it->GetInt());
    }
    //3.C++11��Χforѭ������Array
    for (auto& v : a.GetArray()) {
        printf("%d\n", v.GetInt());
    }

    //�ͱ���Array���ƣ�Ҳ�ܱ���Document��Objec
    static const char* kTypeNames[] = { "Null","False","True","Object","Array","String","Number" };
    for (rapidjson::Value::ConstMemberIterator it = documnet.MemberBegin(); it != documnet.MemberEnd(); ++it) {
        printf("Type of member %s is %s\n", it->name.GetString(), kTypeNames[it->value.GetType()]);
    }
    //C++11
    for (auto& m : documnet.GetObject()) {
        printf("Type of member %s is %s\n", m.name.GetString(), kTypeNames[m.value.GetType()]);
    }

    /**
    * Number����
    * ���ж�Ӧ�Ļ�ȡ����
    * unsigned  32λ�޷�������
    * int       32λ�з�������
    * uint64_t  64λ�޷�������
    * int64_t   64λ�з�������
    * double    64λ˫���ȸ�����
    */

    //��ѯString
    rapidjson::SizeType size = documnet["hello"].GetStringLength();//SizeType��ʵ���޷���������typedef unsigned SizeType;
    //"a\u0000b"������ַ���GetStringLength�᷵�س���Ϊ3����strlen����1����ΪC/C++��\0���ɽ�β�ַ���

    //�Ƚ�
    if (documnet["hello"] == documnet["n"]) {}//�Ƚ�����ֵ��true:���ͺ����ݶ����
    //Array/Object��Ƚϣ����ҽ������ǵ����������൱�����ǲ����
    //ע�⣬���һ��Object�к����ظ������ĳ�Ա�������κ�Object��Ƚ϶�����false


    //����/�޸�
    //��ʹ��Ĭ�Ϲ��캯������Value/Documentʱ�����ǵ�����ΪNULL��Ҫ���������ͣ���Ҫ����SetXXX()����
    rapidjson::Document outDoc;
    outDoc.SetObject();

    rapidjson::Value val;
    val.SetInt(100);
    val = 100;

    //���캯������
    rapidjson::Value val2(true);
    rapidjson::Value val3(1);
    rapidjson::Value val4(1.2);
    rapidjson::Value val5(123u);

    rapidjson::Value val6(rapidjson::kObjectType);
    rapidjson::Value val7(rapidjson::kArrayType);

    //ת�����壬A=B�����ǰ�B��ֵ���Ƹ�A�����ǰ�B��ֵ�ƶ���A
    val = val3;//val=1,val3=Null
    //������ֵ
    //PushBack() Ҳ����ת�����塣
    //��C++11�����Ϊת�Ƹ�ֵ����(Move Assignment Operator)
    outDoc.AddMember("val", val, outDoc.GetAllocator());

    //ֱ��Add/Pushһ��Value����ʱ������ת�������������ã�ͨ��Move��������
    rapidjson::Document::AllocatorType& allocator = outDoc.GetAllocator();
    outDoc.PushBack(rapidjson::Value().SetInt(312), allocator);
    outDoc.PushBack(rapidjson::Value(32).Move(), allocator);






    //����String
    //�����ֲ���
    //1.copy-string:���仺������Ȼ���Դ���ݸ��ƹ���
    //2.const-string:�򵥵Ĵ洢�ַ���ָ��

    //Copy-String���ǰ�ȫ�ģ���Ϊ��ӵ�����ݵĿ�¡
    //Const-String�����ڴ洢�ַ�������ֵ

    //Ϊ�����û��Զ����ڴ���䷽ʽ����һ������������Ҫ�����ڴ�ʱ��Ҫ����һ��allocator�������ͱ���ÿһ��Value�洢Allocator/Document��ָ��
    //��˼���ǣ�ֱ�ӽ�allocator���뺯��������ֱ��ͨ��allocator���ж�̬�ڴ����

    char buffer[10];
    int len = sprintf_s(buffer, "%s", "abcd");
    rapidjson::Value val20;
    val20.SetString(buffer, len, outDoc.GetAllocator());//����һ������Ҫlenth������
    memset(buffer, 0, sizeof(buffer));

    //�����ַ�������ֵ
    rapidjson::Value val21;
    val21.SetString("rapidJSON");
    val21 = "rapidJSON";

    //��ʹ��char*�����������Ҳ�ǰ�ȫ������£�ʹ��StringRef����

    const char* str = "qewjnqwd";
    size_t str_len = strlen(str);
    val21.SetString(rapidjson::StringRef(str));
    val21 = rapidjson::StringRef(str);
    val21.SetString(rapidjson::StringRef(str, str_len));//������Դ�����ַ�
    val21 = rapidjson::StringRef(str, str_len);


    //�޸�Array
    //Clear()
    //Reserve(SizeType, Allocator&)
    //Value& PushBack(Value&, Allocator&)
    //template <typename T> GenericValue& PushBack(T, Allocator&)
    //Value& PopBack()
    //ValueIterator Erase(ConstValueIterator pos)
    //ValueIterator Erase(ConstValueIterator first, ConstValueIterator last)

    //Reserve��PushBack���ܻ�Ϊ�����ڴ棬��ҪAllocator
    for (int x = 0; x < 10; x++) {
        outDoc.PushBack(x, outDoc.GetAllocator());
    }
    //Pushback���ص���������ã����Ϊ�����ӿڣ�Fluent Interface��
    outDoc.PushBack("123", outDoc.GetAllocator()).PushBack("WQD", outDoc.GetAllocator());

    outDoc.PushBack(rapidjson::Value("key", outDoc.GetAllocator()).Move(), outDoc.GetAllocator());


    //�޸�Object
    //Object�Ǽ�ֵ�Լ���
    //���
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
    //ɾ��
    //bool RemoveMember(const Ch * name)��ʹ�ü������Ƴ���Ա������ʱ�临�Ӷȣ���
    //bool RemoveMember(const Value & name)������ name ��һ�� Value������һ����ͬ��
    //MemberIterator RemoveMember(MemberIterator)��ʹ�õ������Ƴ���Ա��_ ���� _ ʱ�临�Ӷȣ���
    //MemberIterator EraseMember(MemberIterator)�����������Ƶ�ά�ֳ�Ա��������ʱ�临�Ӷȣ���
    //MemberIterator EraseMember(MemberIterator first, MemberIterator last)���Ƴ�һ����Χ�ڵĳ�Ա��ά�ִ�������ʱ�临�Ӷȣ���

    //MemberIterator RemoveMember(MemberIterator) ʹ���ˡ�ת������ַ�����ɳ���ʱ�临�Ӷȡ������Ͼ�������������λ�õĳ�Ա��Ȼ������ĳ�Աת����������λ�á���ˣ���Ա�Ĵ���ᱻ�ı䡣

    //���Value
    rapidjson::Document targetDoc;
    rapidjson::Document::AllocatorType& ac = targetDoc.GetAllocator();

    rapidjson::Value val23("123");
    rapidjson::Value val24(val23, ac);//���
    targetDoc.SetArray().PushBack(val23, ac).PushBack(val24, ac);

    val23.CopyFrom(targetDoc, ac);//����doc���Ƹ�val23������doc�����
    val24.SetObject().AddMember("array", val23, ac);
    targetDoc.PushBack(val24, ac);

    //������Щ������������ı�ԭ���Ľṹ�����ǵ���allocator�Ļ���copyfrom����

    //����Vvalue��ʱ�临�Ӷȳ���
    val2.Swap(val22);
}



#include "rapidjson/filereadstream.h"

#include "rapidjson/encodedstream.h"
//ת��
//http://rapidjson.org/zh-cn/md_doc_encoding_8zh-cn.html
#include "rapidjson/encodings.h"
#include "rapidjson/stringbuffer.h"
#include <cstdio>
#pragma warning(disable:4996)
void FileStream() {
    //ʹ��RAPIDJSON���ַ�����ȡ���ļ�
    //FILE* fp = fopen(fileName, "rb");
    //char readBuffer[65536];
    //rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    //rapidjson::EncodedInputStream<rapidjson::UTF8<>, rapidjson::FileReadStream> eis(is);
    //doc.ParseStream<0,rapidjson::UTF8<> >(eis);
}

void Transcode() {
    //��ȫû���κ����⣬ֱ�ӳ�������wchar_t������ת������UTF16����
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
    ////ת��
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