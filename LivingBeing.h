#include <iostream>
#include <string>
#include <vector>
#include "Items.h"
#include "Spells.h"

class LivingBeing
{
    protected:
        std::string name;
        int healthPower;
        int level;

        virtual int maxHP() const = 0;
        virtual bool dodge() = 0;
        virtual void faint() = 0;

    public:
        LivingBeing(const std::string,const int);
        virtual ~LivingBeing();

        bool takeDamage(int);
        virtual bool defend(int) = 0;

        void takeDamageMessage(std::string);
        std::string getName() const;
        int getHP() const;
        int getLevel() const;

        virtual void print() const = 0;
};