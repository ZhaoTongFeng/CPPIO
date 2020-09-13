#pragma once


//���Ч���ǣ�ͨ��Helperʹ�õ�������
//�ڳ���������һ��GameLoader������ѡ��Ҫʹ�õĵ�������

//�궨��ʹ����д
#define RJH RapidJSONHelper

#include "RapidJSONHelper.h"
#include "ReadJson.h"
#include "WriteJson.h"





void SaveTest() {
    int level = 0;

    //1.��ʼ��Ϸ����ȡ����
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

    //2.��Ϸ�У�ģ��ʹ�õȼ�����������
    std::cout << "\nLEVEL:" << level << "\n";
    level++;

    //3.��Ϸ���������ºͱ�������
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

    //1.��Ϸ��ʼ����ȡ����
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
    //2.��Ϸ�У�����Object
    pawn->Upgrade();
    pawn->Print();

    //3.��Ϸ������
    //һ���յ�Document
    rapidjson::Document outDoc(rapidjson::kObjectType);
    //װ������
    rapidjson::Value v(rapidjson::kObjectType);
    pawn->Save(outDoc.GetAllocator(), v);
    outDoc.AddMember("pawn", v, outDoc.GetAllocator());
    //����
    SaveFile(outDoc, fileName);
}



//ͬʱʹ�õ�ö�ٺͼ�������
enum TypeID {
    TActor = 0,
    TCharacter,
    THero,
    NUM_ACTOR_TYPES
};

//�趨KEY
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



    //1.��Ϸ��ʼ����ȡ����
    const std::string fileName = "save.json";
    rapidjson::Document doc = ReadFile(fileName);
    if (!doc.IsObject()) {
        doc.SetObject();
        //�״δ��������ɸ�Actor��ʵ����ӵ�����
        Actor* ac = nullptr;
        for (int i = 0; i < 3; i++) {
            //3��Character
            ac = new Character(i, i, i, i, i);
            actors.push_back(ac);
        }
        for (int i = 0; i < 2; i++) {
            //3��Hero
            ac = new Hero(i, i, i, i);
            actors.push_back(ac);
        }
    }
    else {
        //��ȡ������������
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


    //2.��Ϸ�У�����Object




    //3.��Ϸ������
    //һ���յ�Document
    rapidjson::Document outDoc(rapidjson::kObjectType);

    //װ�����ݣ���������������ÿһ�����Save����
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

    //����
    SaveFile(outDoc, fileName);

    return 0;
}

