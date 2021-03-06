#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include "Spells.h"

using namespace std;

//CONSTRUCTORS
//CONSTRUCTORS
//CONSTRUCTORS

Spell::Spell(int lvl,const string s):  name(s) {
    levelRequired = max(randomLevel(lvl),1);
    mpRequired = 30 + levelRequired*10;
    minDamage = 10 + levelRequired*5;
    maxDamage = 50 + levelRequired*5;
    price = 100 + levelRequired*50;
}

IceSpell::IceSpell(int lvl,const string s): Spell(lvl,s){
    damageReduction = 7 + levelRequired*3;
}

FireSpell::FireSpell(int lvl,const string s): Spell(lvl,s){
    defenseReduction  = 3 + levelRequired*2; 
}

LightningSpell::LightningSpell(int lvl,const string s): Spell(lvl,s){
    dodgeReduction = 2 + levelRequired*2; 
}


//DESTRUCTORS

Spell::~Spell() {}

IceSpell::~IceSpell() {}

FireSpell::~FireSpell() {}

LightningSpell::~LightningSpell() {}



//COPY-CONSTRUCTORS

Spell::Spell(const Spell& s){
    if (this!=&s){
        name = s.name;
        minDamage = s.minDamage;
        maxDamage = s.maxDamage;
        levelRequired = s.levelRequired;
        mpRequired = s.mpRequired;
    }
}

IceSpell::IceSpell(const IceSpell& i):Spell(i){
    if (this!=&i)
        damageReduction = i.damageReduction;
}

FireSpell::FireSpell(const FireSpell& f):Spell(f){
    if (this!=&f)
        defenseReduction = f.defenseReduction;
}

LightningSpell::LightningSpell(const LightningSpell& l):Spell(l){
    if (this!=&l)
        dodgeReduction = l.dodgeReduction;
}


//ASSIGNMENT OPERATOR OVERLOADS

Spell& Spell::operator=(const Spell& s){
    if (this!=&s)
    {
        name = s.name;
        minDamage = s.minDamage;
        maxDamage = s.maxDamage;
        levelRequired = s.levelRequired;
        mpRequired = s.mpRequired;
    }
    return *this;
}

IceSpell& IceSpell::operator=(const IceSpell& i){
    Spell::operator=(i);
    if (this!=&i)
        damageReduction = i.damageReduction;
    return *this;
}

FireSpell& FireSpell::operator=(const FireSpell& f){
    Spell::operator=(f);
    if (this!=&f)
        defenseReduction = f.defenseReduction;
    return *this;
}

LightningSpell& LightningSpell::operator=(const LightningSpell& l){
    Spell::operator=(l);
    if (this!=&l)
        dodgeReduction = l.dodgeReduction;
    return *this;
}


//SPELL
//SPELL
//SPELL

string Spell::getName() const{return name;}
int Spell::getPrice() const {return price;}
int Spell::getLevelReq() const {return levelRequired;}
int Spell::getMP() const {return mpRequired;}
int Spell::getMin() const {return minDamage;}
int Spell::getMax() const {return maxDamage;}

//PRINT
//PRINT
//PRINT
void Spell::print() const{
    cout << "Name: " << name << "\nPrice: " << price << endl;
    cout << "Minimum Damage: " << minDamage << ".\t" << "Maximum Damage: " << maxDamage << endl;
    cout << "Required level: " << levelRequired << ".\t" << "Required MP: " << mpRequired << endl;
}

void IceSpell::print() const{
    cout << "This is an IceSpell" << endl;
    Spell::print();
    cout << "It also reduces enemy damage by " << damageReduction << endl << endl;
}

void FireSpell::print() const{
    cout << "This is a FireSpell" << endl;
    Spell::print();
    cout << "It also reduces enemy defense by " << defenseReduction << endl << endl;
}

void LightningSpell::print() const{
    cout << "This is a LightningSpell" << endl;
    Spell::print();
    cout << "It also reduces enemy dodge chance by " << dodgeReduction << "%" << endl << endl;
}



//GETREDUCTION
//GETREDUCTION
//GETREDUCTION

int IceSpell::getReduction() const {return damageReduction;}
int FireSpell::getReduction() const {return defenseReduction;}
int LightningSpell::getReduction() const {return dodgeReduction;}


//TYPE
//TYPE
//TYPE

int IceSpell::type() const {return 1;}
int FireSpell::type() const {return 2;}
int LightningSpell::type() const {return 3;}
