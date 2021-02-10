#include <iostream>
#include <string>
#include <ctime>
#include "Monster.h"
using namespace std;


//CONSTRUCTORS
//CONSTRUCTORS
//CONSTRUCTORS

Monster::Monster(const string s, const int lvl=1):  LivingBeing(s,lvl) {
    healthPower=50+lvl*15;
}

Dragon::Dragon(const string n,int lvl) :  Monster(n,lvl) {
    minAttack=5+6*lvl;
    maxAttack=10+6*lvl;
    defense=10+4*lvl;
    dodgeChance=10+2*lvl;
}
Exosceleton::Exosceleton(const string n,int lvl) : Monster(n,lvl) {
    minAttack=3+3*lvl;
    maxAttack=3+3*lvl;
    defense=20+5*lvl;
    dodgeChance=10+2*lvl;
}
Spirit::Spirit(const string n,int lvl) : Monster(n,lvl) {
    minAttack=3+3*lvl;
    maxAttack=3+3*lvl;
    defense=10+4*lvl;
    dodgeChance=20+3*lvl;
}

//DESTRUCTORS
//DESTRUCTORS
//DESTRUCTORS

Monster::~Monster() {}

Dragon::~Dragon() {}

Exosceleton::~Exosceleton() {}

Spirit::~Spirit() {}

//MONSTER
//MONSTER
//MONSTER
int Monster::attack(){
    int damage=rand()%(maxAttack+1);
    if(damage < minAttack) damage+=minAttack;
    return damage;
}

bool Monster::takeDamage(int damage){
    if(dodge()){
        cout << name + " dodges the attack!" << endl;
        return false;
    }
    damage -= defense;
    return LivingBeing::takeDamage(max(damage,0));
}

bool Monster::dodge(){
    int temp = rand()%100;
    return (temp <= dodgeChance);
}

void Monster::faint(){
    cout << name + " has fainted! It's out of the battle!" << endl;
}

Monster* monsterGenerator(const int heroAverage){
    int type = rand() % 3;
    Monster* monster;
    switch (type){
        case 0:
            monster = new Dragon(genName("monster"),randomLevel(heroAverage));
            break;
        case 1:
            monster = new Exosceleton(genName("monster"),randomLevel(heroAverage));
            break;
        case 2:
            monster = new Spirit(genName("monster"),randomLevel(heroAverage));
            break;
    }
    return monster;
}