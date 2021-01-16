#include <iostream>
#include <string>
#include <ctime>
#include "LivingBeing.h"
using namespace std;


//CONSTRUCTORS
//CONSTRUCTORS
//CONSTRUCTORS

LivingBeing::LivingBeing(const string s, const int lvl=1)
{
    name=s;
    level=lvl;
}

//DESTRUCTORS
//DESTRUCTORS
//DESTRUCTORS

LivingBeing::~LivingBeing() {}

//LivingBeing
//LivingBeing
//LivingBeing

void LivingBeing::takeDamage(const int damage)
{
    if (damage < healthPower)
        healthPower-= damage;
    else
        faint();
}

void LivingBeing::printName(){cout << name;}
string LivingBeing::getName() const{return name;}
int LivingBeing::getHP() const{return healthPower;}
int LivingBeing::getLevel() const{return level;}