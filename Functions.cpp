#include <iostream>
#include <fstream>
#include "Functions.h"
#include "Monster.h"

using namespace std;

string WeaponNames[119],ArmorNames[78],MonsterNames[98],PotionNames[3],FireSpellNames[15],IceSpellNames[6],LightningSpellNames[3];
int    weaponindex     ,armorindex    ,monsterindex    ,potionindex   ,firespellindex    ,icespellindex   ,lightningspellindex;

bool inputAnswer()
{
    char input;
    cin >> input;
    bool acceptable = input == 'y' || input == 'Y' || input == 'n' || input == 'N';
    while (acceptable == false){
        cout << "Wrong input. Try again." << endl;
        cin >> input;
        acceptable = input == 'y' || input == 'Y' || input == 'n' || input == 'N';
    }

    return (input == 'y' || input == 'Y');   
}

int inputNumber(const int max)
{
    unsigned input;
    cin >> input;
    bool acceptable = input <= max;
    while (acceptable == false){
        cout << "Wrong input. Try again." << endl;
        cin >> input;
        acceptable = input <= max;
    }
    return input;
}

int randomLevel(const int heroAverage){
    return heroAverage + rand()%5 - 2; // ==return heroAverage +/- 2;
}

int level(Hero** heroes, const int numOfHeroes){
    int sum = 0;
    for (int i=0; i<numOfHeroes; i++)
        sum += heroes[i]->getLevel().getRL();
    int average = sum / numOfHeroes;
    return randomLevel(average);
}

Monster* monsterGenerator(const int heroAverage){
    int type = rand() % 3;
    Monster* monster;
    switch (type){
        case 0:
            monster = new Dragon(MonsterNames[monsterindex++],randomLevel(heroAverage));
            return monster;
        case 1:
            monster = new Exosceleton(MonsterNames[monsterindex++],randomLevel(heroAverage));
            return monster;
        case 2:
            monster = new Spirit(MonsterNames[monsterindex++],randomLevel(heroAverage));
            return monster;
    }
}





//Random Name Generator

void InitializeNameArrays(){
    weaponindex=0;
    armorindex=0;
    monsterindex=0;
    potionindex=0;
    firespellindex=0;
    icespellindex=0;
    lightningspellindex=0;
    int i;
    ifstream myfile;
    string line;

    myfile.open("WeaponNames.txt");
    for(i=0;i<119;i++){
        getline(myfile,line);
        WeaponNames[i]=line;
    }
    myfile.close();

    myfile.open("ArmorNames.txt");
    for(i=0;i<78;i++){
        getline(myfile,line);
        ArmorNames[i]=line;
    }
    myfile.close();

    myfile.open("MonsterNames.txt");
    for(i=0;i<98;i++){
        getline(myfile,line);
        MonsterNames[i]=line;
    }
    myfile.close();

    myfile.open("PotionNames.txt");
    for(i=0;i<3;i++){
        getline(myfile,line);
        PotionNames[i]=line;
    }
    myfile.close();

    myfile.open("firespells.txt");
    for(i=0;i<15;i++){
        getline(myfile,line);
        FireSpellNames[i]=line;
    }
    myfile.close();

    myfile.open("icepells.txt");
    for(i=0;i<6;i++){
        getline(myfile,line);
        IceSpellNames[i]=line;
    }
    myfile.close();

    myfile.open("lightningspells.txt");
    for(i=0;i<3;i++){
        getline(myfile,line);
        LightningSpellNames[i]=line;
    }
    myfile.close();
}

void swap(string* n1,string* n2){
    string temp=*n1;
    n1=n2;
    n2=&temp;
}

string genName(string type){
    int tempindex;
    string tempname;
    if(type == "weapon"){
        if(weaponindex >= 119) weaponindex=0;
        tempindex=rand()%(119-weaponindex);
        tempname=WeaponNames[tempindex];
        swap(WeaponNames[tempindex],WeaponNames[118-weaponindex++]);
        return tempname;
    }
    if(type == "armor"){
        if(armorindex >= 78) armorindex=0;
        tempindex=rand()%(78-armorindex);
        tempname=ArmorNames[tempindex];
        swap(ArmorNames[tempindex],ArmorNames[77-armorindex++]);
        return tempname;
    }
    if(type == "monster"){
        if(monsterindex >= 98) monsterindex=0;
        tempindex=rand()%(98-monsterindex);
        tempname=MonsterNames[tempindex];
        swap(MonsterNames[tempindex],MonsterNames[97-monsterindex++]);
        return tempname;
    }
    else if(type == "potion"){
        if(potionindex >= 3) potionindex=0;
        tempindex=rand()%(3-potionindex);
        tempname=PotionNames[tempindex];
        swap(PotionNames[tempindex],PotionNames[2-potionindex++]);
        return tempname;
    }
    else if(type == "firespell"){
        if(firespellindex >= 15) firespellindex=0;
        tempindex=rand()%(15-firespellindex);
        tempname=FireSpellNames[tempindex];
        swap(FireSpellNames[tempindex],FireSpellNames[14-firespellindex++]);
        return tempname;
    }
    else if(type == "icespell"){
        if(icespellindex >= 6) icespellindex=0;
        tempindex=rand()%(6-icespellindex);
        tempname=IceSpellNames[tempindex];
        swap(IceSpellNames[tempindex],IceSpellNames[5-icespellindex++]);
        return tempname;
    }
    else if(type == "lightningspell"){
        if(lightningspellindex >= 3) lightningspellindex=0;
        tempindex=rand()%(3-lightningspellindex);
        tempname=LightningSpellNames[tempindex];
        swap(LightningSpellNames[tempindex],LightningSpellNames[2-lightningspellindex++]);
        return tempname;
    }
    else return "ERROR";
}
