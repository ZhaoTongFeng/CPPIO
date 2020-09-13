#pragma once


//最佳效果是，通过Helper使用第三方库
//在程序中设置一个GameLoader，可以选择要使用的第三方库

//宏定义使用缩写
#define RJH RapidJSONHelper

#include "RapidJSONHelper.h"
#include "ReadJson.h"
#include "WriteJson.h"





void SaveTest() {
    int level = 0;

    //1.开始游戏：读取数据
    const std::string fileName = "save.json";
    rapidjson::Document doc = ReadFile(fileName);
    if (!doc.IsObject()) {
        doc.SetObject();
        doc.AddMember("level", level, doc.GetAllocator());
        SaveFile(doc, fileName);
    }
    else {
        rapidjson::Value::MemberIterator iter = doc.FindMember("level");
        level = iter->value.GetInt();
    }

    //2.游戏中：模拟使用等级和升级操作
    std::cout << "\nLEVEL:" << level << "\n";
    level++;

    //3.游戏结束：更新和保存数据
    rapidjson::Value::MemberIterator iter = doc.FindMember("level");
    iter->value = level;
    SaveFile(doc, fileName);
}


class Pawn {
public:
    Pawn() :x(0.0f), y(0.0f), z(0.0f), level(-1), name("") {};
    Pawn(int lv, std::string na) :x(0.0f), y(0.0f), z(0.0f), level(lv), name(na) {};
    int GetLevel() { return level; }
    void Upgrade() { level++; }
    void Print() { std::cout << "name:" << name << "\nLv:" << level << "\nPosition:(" << x << "," << y << "," << z << ")\n"; }
    void Load(const rapidjson::Value& obj) {
        RapidJSONHelper::Get(obj, "x", x);
        RapidJSONHelper::Get(obj, "y", y);
        RapidJSONHelper::Get(obj, "z", z);
        RapidJSONHelper::Get(obj, "name", name);
        RapidJSONHelper::Get(obj, "level", level);
    }
    void Save(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& obj) {
        RapidJSONHelper::Add(alloc, obj, "x", x);
        RapidJSONHelper::Add(alloc, obj, "y", y);
        RapidJSONHelper::Add(alloc, obj, "z", z);
        RapidJSONHelper::Add(alloc, obj, "name", name);
        RapidJSONHelper::Add(alloc, obj, "level", level);
    }
private:
    //Position
    float x;
    float y;
    float z;

    std::string name;
    int level;
};


void SaveTest2() {
    Pawn* pawn = nullptr;

    //1.游戏开始：读取数据
    const std::string fileName = "save.json";
    rapidjson::Document doc = ReadFile(fileName);
    if (!doc.IsObject()) {
        doc.SetObject();
        pawn = new Pawn(0, "pawn");
    }
    else {
        pawn = new Pawn();
        rapidjson::Value v = doc["pawn"].GetObject();
        pawn->Load(v);
    }
    //2.游戏中：更新Object
    pawn->Upgrade();
    pawn->Print();

    //3.游戏结束：
    //一个空的Document
    rapidjson::Document outDoc(rapidjson::kObjectType);
    //装入数据
    rapidjson::Value v(rapidjson::kObjectType);
    pawn->Save(outDoc.GetAllocator(), v);
    outDoc.AddMember("pawn", v, outDoc.GetAllocator());
    //保存
    SaveFile(outDoc, fileName);
}



//同时使用到枚举和计数功能
enum TypeID {
    TActor = 0,
    TCharacter,
    THero,
    NUM_ACTOR_TYPES
};

//设定KEY
const char* TypeNames[NUM_ACTOR_TYPES] = {
    "Actor",
    "Character",
    "Hero"
};

class Actor {
public:
    Actor() :x(0.0f), y(0.0f), z(0.0f) {}
    Actor(float x, float y, float z) :x(x), y(y), z(z) {}

    virtual void Load(const rapidjson::Value& obj) {
        RJH::Get(obj, "x", x);
        RapidJSONHelper::Get(obj, "y", y);
        RapidJSONHelper::Get(obj, "z", z);
    }
    virtual void Save(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& obj) {
        RapidJSONHelper::Add(alloc, obj, "x", x);
        RapidJSONHelper::Add(alloc, obj, "y", y);
        RapidJSONHelper::Add(alloc, obj, "z", z);
    }


    template<class T>
    static Actor* Create(const rapidjson::Value& obj) {
        T* t = new T();
        t->Load(obj);
        return t;
    }

    virtual TypeID GetType()const { return TActor; }
protected:
    //Position
    float x;
    float y;
    float z;
};

class Character :public Actor {
public:
    Character() :Actor(), health(0.0f), power(0.0f) {};
    Character(float x, float y, float z) :Actor(x, y, z), health(0.0f), power(0.0f) {};
    Character(float x, float y, float z, float health, float power) :Actor(x, y, z), health(health), power(power) {};
    void Load(const rapidjson::Value& obj) override
    {
        Actor::Load(obj);
        RapidJSONHelper::Get(obj, "health", health);
        RapidJSONHelper::Get(obj, "power", power);
    }
    void Save(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& obj) override
    {
        Actor::Save(alloc, obj);
        RapidJSONHelper::Add(alloc, obj, "health", health);
        RapidJSONHelper::Add(alloc, obj, "power", power);

    }
    TypeID GetType()const override { return TCharacter; }
protected:
    float health;
    float power;
};


class Object {
public:
    virtual void Load(const rapidjson::Value& obj) = 0;
    virtual void Save(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& obj) = 0;
};




class Stats :public Object{
public:
    int hp;
    int mp;
    int movespeed;
    float armor;
    float spellblock;
    int attackrange;
    float crit;
    float attackdamage;
    float attackspeed;
    void Load(const rapidjson::Value& obj) override
    {
        RapidJSONHelper::Get(obj, "hp", hp);
        RapidJSONHelper::Get(obj, "mp", mp);
        RapidJSONHelper::Get(obj, "movespeed", movespeed);
        RapidJSONHelper::Get(obj, "armor", armor);
        RapidJSONHelper::Get(obj, "spellblock", spellblock);
        RapidJSONHelper::Get(obj, "attackrange", attackrange);
        RapidJSONHelper::Get(obj, "crit", crit);
        RapidJSONHelper::Get(obj, "attackdamage", attackdamage);
        RapidJSONHelper::Get(obj, "attackspeed", attackspeed);
    }
    void Save(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& obj) override
    {
        RapidJSONHelper::Add(alloc, obj, "hp", hp);
        RapidJSONHelper::Add(alloc, obj, "mp", mp);
        RapidJSONHelper::Add(alloc, obj, "movespeed", movespeed);
        RapidJSONHelper::Add(alloc, obj, "armor", armor);
        RapidJSONHelper::Add(alloc, obj, "spellblock", spellblock);
        RapidJSONHelper::Add(alloc, obj, "attackrange", attackrange);
        RapidJSONHelper::Add(alloc, obj, "crit", crit);
        RapidJSONHelper::Add(alloc, obj, "attackdamage", attackdamage);
        RapidJSONHelper::Add(alloc, obj, "attackspeed", attackspeed);
    }
};

class Hero :public Character {
public:
    Hero() :Character(), magic(0.0f) {};
    Hero(float x, float y, float z, float magic) :Character(x, y, z), magic(magic) {};
    
    
    void Load(const rapidjson::Value& obj) override
    {
        Character::Load(obj);
        RapidJSONHelper::Get(obj, "magic", magic);
    }
    void Save(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& obj) override
    {
        Character::Save(alloc, obj);
        RapidJSONHelper::Add(alloc, obj, "magic", magic);
    }
    TypeID GetType()const override { return THero; }
    
    std::string id;
    std::string key;
    std::string name;
    std::string title;
    Stats stats;

protected:
    float magic;
};




#include <unordered_map>
#include <functional>



int GameExample()
{
    std::vector<Actor*> actors;
    std::unordered_map<std::string, std::function<class Actor* (const rapidjson::Value&)>> ActorFactorMap{
        {"Actor",&Actor::Create<Actor>},
        {"Character",&Actor::Create<Character>},
        {"Hero",&Actor::Create<Hero>}
    };



    //1.游戏开始：读取数据
    const std::string fileName = "save.json";
    rapidjson::Document doc = ReadFile(fileName);
    if (!doc.IsObject()) {
        doc.SetObject();
        //首次创建，若干个Actor的实例添加到容器
        Actor* ac = nullptr;
        for (int i = 0; i < 3; i++) {
            //3个Character
            ac = new Character(i, i, i, i, i);
            actors.push_back(ac);
        }
        for (int i = 0; i < 2; i++) {
            //3个Hero
            ac = new Hero(i, i, i, i);
            actors.push_back(ac);
        }
    }
    else {
        //读取并创建到容器
        rapidjson::Value arr = doc["actors"].GetArray();
        for (rapidjson::SizeType i = 0; i < arr.Size(); i++) {
            const rapidjson::Value& vac = arr[i];
            std::string type;
            RapidJSONHelper::Get(vac, "type", type);
            auto iter = ActorFactorMap.find(type);
            if (iter != ActorFactorMap.end()) {
                Actor* actor = iter->second(vac["properties"]);
                actors.push_back(actor);
            }
        }
    }


    //2.游戏中：更新Object




    //3.游戏结束：
    //一个空的Document
    rapidjson::Document outDoc(rapidjson::kObjectType);

    //装入数据，遍历容器，调用每一个类的Save函数
    rapidjson::Value arr(rapidjson::kArrayType);
    for (Actor* actor : actors) {
        rapidjson::Value obj(rapidjson::kObjectType);
        RapidJSONHelper::Add(outDoc.GetAllocator(), obj, "type", TypeNames[actor->GetType()]);
        rapidjson::Value prop(rapidjson::kObjectType);
        actor->Save(outDoc.GetAllocator(), prop);

        obj.AddMember("properties", prop, outDoc.GetAllocator());
        arr.PushBack(obj, outDoc.GetAllocator());
    }
    outDoc.AddMember("actors", arr, outDoc.GetAllocator());

    //保存
    SaveFile(outDoc, fileName);

    return 0;
}

