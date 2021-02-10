#include <iostream>
#include <string>
#include <vector>
#include "LivingBeing.h"

class Monster: public LivingBeing
{
    protected:
        int minAttack;
        int maxAttack;
        int defense;
        int dodgeChance;
        
    public:
        Monster(const std::string,const int);
        virtual ~Monster();

        int attack(); //Epistrefei tuxaio arithmo anamesa sto minAttack kai to maxAttack.
        bool takeDamage(int);
        bool dodge();
        void faint();
};

class Dragon: public Monster
{
    public:
        Dragon(const std::string,const int);
        ~Dragon();
};

class Exosceleton: public Monster
{
    public:
        Exosceleton(const std::string,const int);
        ~Exosceleton();
};

class Spirit: public Monster
{
    public:
        Spirit(const std::string,const int);
        ~Spirit();
};

Monster* monsterGenerator(const int);
void monsterFainted(Monster**, int&, const int);
int chooseMonster(Monster**, const int);