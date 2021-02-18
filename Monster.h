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

        int maxHP() const;
        bool dodge();
        void faint();
                
    public:
        Monster(const std::string,const int);
        virtual ~Monster();

        int attack(); //Epistrefei tuxaio arithmo anamesa sto minAttack kai to maxAttack.
        bool defend(int);
        void takeSpell(Spell*);
        void gainHP();
        void regainStats(const std::string, const int);


        virtual std::string type() const = 0;
        void print() const;
};

class Dragon: public Monster
{
    public:
        Dragon(const std::string,const int);
        ~Dragon();

        std::string type() const;
};

class Exosceleton: public Monster
{
    public:
        Exosceleton(const std::string,const int);
        ~Exosceleton();

        std::string type() const;
};

class Spirit: public Monster
{
    public:
        Spirit(const std::string,const int);
        ~Spirit();

        std::string type() const;
};

Monster* monsterGenerator(const int);
void removeMonster(Monster**, int&, const int);
int chooseMonster(Monster**, const int);