#include <fstream>
#include <iostream>
#include <string>
#include <ctime>

class Item{
protected:
    std::string name;
    int price;
    int minLevel;
public:
    Item(int ,std::string ,std::string );
    Item();
    ~Item();
    Item& operator=(const Item& );

    virtual void print() const =0;
    std::string getName() const;
    int getPrice() const;
    int getMinLevel() const;
};

class Weapon : public Item{
    int damage;
    bool twoHanded;
public:
    Weapon(int ,std::string );
    Weapon();
    Weapon(const Weapon&);
    ~Weapon();
    Weapon& operator=(const Weapon& );

    bool areTheSame(Weapon,Weapon);
    void starterWeapon();
    int getDamage() const;
    bool getTwoHanded() const;
    void print() const;
};

class Armor : public Item{
    int protection;
public:
    Armor(int ,std::string );
    Armor();
    Armor(const Armor&);
    ~Armor();
    Armor& operator=(const Armor& );
    
    bool areTheSame(Armor,Armor);
    void starterArmor();
    int getProtection() const;
    void print() const;
};

class Potion : public Item{
    int effectPoints;
public:
    Potion(int ,std::string );
    ~Potion();
    Potion& operator=(const Potion& );

    std::string getUse() const;
    int getEffectPoints() const;
    void print() const;
};