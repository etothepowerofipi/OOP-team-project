#include <iostream>
#include <string>
#include <ctime>
#include "Spells.h"

using namespace std;

//CONSTRUCTORS
//CONSTRUCTORS
//CONSTRUCTORS

Spell::Spell(int lvl,const string s):  name(s), mpRequired(30), minDamage(10), maxDamage(100) { //TOBECHANGED
    int base=rand()%4;
    levelRequired=lvl-2+base;
    if(levelRequired <= 0) levelRequired=1;
    price=100+50*base;
}

IceSpell::IceSpell(int lvl,const string s): Spell(lvl,s)
{
    damageReduction = 10; //TOBECHANGED
}

FireSpell::FireSpell(int lvl,const string s): Spell(lvl,s)
{
    defenseReduction  = 5; //TOBECHANGED
}

LightningSpell::LightningSpell(int lvl,const string s): Spell(lvl,s)
{
    dodgeReduction = 1; //TOBECHANGED
}


//DESTRUCTORS

Spell::~Spell() {}

IceSpell::~IceSpell() {}

FireSpell::~FireSpell() {}

LightningSpell::~LightningSpell() {}








//COPY-CONSTRUCTORS

Spell::Spell(const Spell& s)
{
    if (this!=&s)
    {
        name = s.name;
        minDamage = s.minDamage;
        maxDamage = s.maxDamage;
        levelRequired = s.levelRequired;
        mpRequired = s.mpRequired;
    }
}

IceSpell::IceSpell(const IceSpell& i):Spell(i)
{
    if (this!=&i)
        damageReduction = i.damageReduction;
}

FireSpell::FireSpell(const FireSpell& f):Spell(f)
{
    if (this!=&f)
        defenseReduction = f.defenseReduction;
}

LightningSpell::LightningSpell(const LightningSpell& l):Spell(l)
{
    if (this!=&l)
        dodgeReduction = l.dodgeReduction;
}


//ASSIGNMENT OPERATOR OVERLOADS

Spell& Spell::operator=(const Spell& s)
{
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

IceSpell& IceSpell::operator=(const IceSpell& i)
{
    Spell::operator=(i);
    if (this!=&i)
        damageReduction = i.damageReduction;
    return *this;
}

FireSpell& FireSpell::operator=(const FireSpell& f)
{
    Spell::operator=(f);
    if (this!=&f)
        defenseReduction = f.defenseReduction;
    return *this;
}

LightningSpell& LightningSpell::operator=(const LightningSpell& l)
{
    Spell::operator=(l);
    if (this!=&l)
        dodgeReduction = l.dodgeReduction;
    return *this;
}


//SPELL
//SPELL
//SPELL

string Spell::getName() const
{
    return name;
}

int Spell::getPrice() const
{
    return price;
}

int Spell::getLevelReq() const
{
    return levelRequired;
}

int Spell::getMP() const
{
    return mpRequired;
}

int Spell::getMin() const {
    return minDamage;
}

int Spell::getMax() const {
    return maxDamage;
}

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

int IceSpell::getReduction() const{
    return damageReduction;
}

int FireSpell::getReduction() const{
    return defenseReduction;
}

int LightningSpell::getReduction() const{
    return dodgeReduction;
}


//TYPE
//TYPE
//TYPE

string IceSpell::type() const{
    return "Ice";
}

string FireSpell::type() const{
    return "Fire";
}

string LightningSpell::type() const{
    return "Lightning";
}
