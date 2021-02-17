#include <iostream>
#include <string>
#include "Functions.h"

class Spell
{
    protected:
        std::string name;
        int price;
        int minDamage;
        int maxDamage;
        int levelRequired;
        int mpRequired;

    public:
        Spell(int ,const std::string);
        virtual ~Spell();
        Spell(const Spell&);
        Spell& operator=(const Spell&);

        //accessors
        std::string getName() const;
        int getPrice() const;
        int getLevelReq() const;
        int getMP() const;
        int getMin() const;
        int getMax() const;

        virtual int getReduction() const =0;
        virtual void print() const ;
};

class IceSpell: public Spell
{
    private:
        int damageReduction;

    public:
        IceSpell(int ,const std::string);
        ~IceSpell();
        IceSpell(const IceSpell&);
        IceSpell& operator=(const IceSpell&);

        int getReduction() const;
        void print() const;
};

class FireSpell: public Spell
{
    private:
        int defenseReduction;
        
    public:
        FireSpell(int ,const std::string);
        ~FireSpell();
        FireSpell(const FireSpell&);
        FireSpell& operator=(const FireSpell&);

        int getReduction() const;
        void print() const;
};

class LightningSpell: public Spell
{
    private:
        int dodgeReduction;
        
    public:
        LightningSpell(int ,const std::string);
        ~LightningSpell();
        LightningSpell(const LightningSpell&);
        LightningSpell& operator=(const LightningSpell&);

        int getReduction() const;
        void print() const;
};

