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

    public:
        LivingBeing(const std::string,const int);
        virtual ~LivingBeing();

        void takeDamage(int);
        virtual void faint() = 0;

        void printName();
        std::string getName() const;
        int getHP() const;
        int getLevel() const;

        virtual bool dodge() = 0;
};