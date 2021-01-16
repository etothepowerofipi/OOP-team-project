#include <iostream>
#include <string>
#include <ctime>
#include "Grid.h"
#include "Functions.h"

using namespace std;

Grid::Grid(Hero** h,int numofh){
    numofheroes=numofh;
    // heroes=new Hero*[numofh];
    // for(int i=0;i<numofh;i++) heroes[i]=h[i];
    heroes=h;
    maxi=20;
    maxj=20;
    for(int i=0;i<maxi;i++){
        for(int j=0;j<maxj;j++)
            map[i][j]='+';
    }

    int numofmarkets=10+rand()%6;  //Paragw enan tuxaio ari8mo anamesa sto Min marketplaces=10 kai max marketplaces=15
    int i,j;
    while(numofmarkets > 0){
        i=rand()%maxi;
        j=rand()%maxj;
        map[i][j]='M';
        numofmarkets--;
    }

    int numofunreachable=30+rand()%11;  //Paragw enan tuxaio ari8mo anamesa sto Min unreachable=30 kai max unreachable=40
    while(numofunreachable > 0){
        do{
            i=rand()%maxi;
            j=rand()%maxj;
        }while( canPlace(i,j) == false );
        map[i][j]='X';
        numofunreachable--;
    }

    //Initializing hero's position at (0,0)
    tempchar=map[0][0];
    x=y=0;
    map[0][0]='H';
}

bool Grid::canPlace(int i,int j){
    if(i == 0 && j == 1) return false;
    else if(i == 1 && j == 0) return false;
    else if(map[i][j] == 'M') return false;
    else{
        if(i-1 >= 0 && map[i-1][j] == 'X') return false;
        else if(i+1 <= maxi && map[i+1][j] == 'X') return false;
        else if(j-1 >= 0 && map[i][j-1] == 'X') return false;
        else if(j+1 <= maxj && map[i][j+1] == 'X') return false;
    }
    return true;
}

void Grid::move(){
    int answer;
    do{
        print();
        cout << "Would you like to move? n=no / a=left / d =right / w = up / s = down" << endl;
        answer = inputMenu();
        switch (answer){
            case 1:
                moveLeft();
                break;
            case 2:
                moveRight();
                break;
            case 3:
                moveUp();
                break;
            case 4:
                moveDown();
        }
    } while(answer != 5);
}

void Grid::moveRight(){
    if(y+1 <= maxi){
        if(checkBlock(x,y+1) == true){
            map[x][y]=tempchar;
            y++;
            tempchar=map[x][y];
            map[x][y]='H';
        }
        else cout << "You can't go there!" << endl;
    }
    else{
        cout << "You can't go there!" << endl;
    }
}

void Grid::moveLeft(){
    if(y-1 >= 0){
        if(checkBlock(x,y-1) == true){
            map[x][y]=tempchar;
            y--;
            tempchar=map[x][y];
            map[x][y]='H';
        }
        else cout << "You can't go there!" << endl;
    }
    else{
        cout << "You can't go there!" << endl;
    }
}

void Grid::moveUp(){
    if(x-1 >= 0){
        if(checkBlock(x-1,y) == true){
            map[x][y]=tempchar;
            x--;
            tempchar=map[x][y];
            map[x][y]='H';
        }
        else cout << "You can't go there!" << endl;
    }
    else{
        cout << "You can't go there!" << endl;
    }
}

void Grid::moveDown(){
    if(x+1 <= maxi){
        if(checkBlock(x+1,y) == true){
            map[x][y]=tempchar;
            x++;
            tempchar=map[x][y];
            map[x][y]='H';
        }
        else cout << "You can't go there!" << endl;
    }
    else{
        cout << "You can't go there!" << endl;
    }
}

bool Grid::checkBlock(int i,int j){
    if(map[i][j]== 'M'){
        cout << "You have reached a marketplace!\nWould you like to enter? y/n" << endl;
        return true;
    }
    else if(map[i][j] == '+'){
        int prob=rand()%100;
        if(prob <= 30){
            battle();
        }
        return true;
    }
    else{
        cout << "You can go there!" << endl;
        return false;
    }
}

bool Grid::battle(){
    int numOfMonsters = rand()%2 + numofheroes;
    if (numOfMonsters == 1)
        cout << "A monster has appeared!\nPrepare to battle!" << endl;
    else
        cout << "Monsters have appeared!\nPrepare to battle!" << endl;

    Monster** monsters = new Monster*[numOfMonsters];
    for (int i=0; i< numOfMonsters; i++){
        monsters[i] = monsterGenerator(level());
    }

    while (thereAreHeroes() && thereAreMonsters(monsters,numOfMonsters)){
        for (int i=0; i<numofheroes; i++){
            int action = battleMenu(i);
            switch (action){
                case 1:
                    heroes[i]->attack();
            }
    }
}

int Grid::battleMenu(const int index){
    cout << "What would you like " + heroes[index]->getName() + " to do?" << endl;
    cout << "To attack normally, type 1." << endl;
    cout << "To cast a spell, type 2." << endl;
    cout << "To use a potion, type 3." << endl;
    cout << "To change equipment, type 4." << endl;

    return inputNumber(4);
}

bool Grid::thereAreHeroes(){
    bool thereAre = false;
    int index = 0;
    while (index < numofheroes){
    if (heroes[index]->getHP() == 0)
        index++;
    else
        thereAre = true;
    }
    return thereAre;
}

bool Grid::thereAreMonsters(Monster** monsters, const int numofmonsters){
    bool thereAre = false;
    int index = 0;
    while (index < numofmonsters){
    if (monsters[index]->getHP() == 0)
        index++;
    else
        thereAre = true;
    }
    return thereAre;
}

int Grid::level() const{
    int sum = 0;
    for (int i=0; i<numofheroes; i++)
        sum += heroes[i]->getLevel().getRL();
    int average = sum / numofheroes;
    return randomLevel(average);
}

void Grid::print(){
    for(int i=0;i<maxi;i++){
        for(int j=0;j<maxj;j++)
            cout << map[i][j] << " ";
        cout << endl;
    }
    cout << endl << endl;
}

bool Grid::menu(){
    cout << "Choose your next move!" << endl;
    cout << "To keep moving press '1'\nTo check your inventory press '2'\nTo see your stats press '3'\nTo quit the game press '4'" << endl;
    int answer = inputNumber(4);
    switch(answer){
        case 1 :
            move();
            return true;
        case 2 :
            for(int i=0;i<numofheroes;i++) heroes[i]->checkInventory();
            return true;
        case 3 :
            for(int i=0;i<numofheroes;i++) heroes[i]->showStats();
            return true;
        case 4 :
            return false;
    }
    return false;
}

//////////////////////////////////////
//////////////MARKETPLACE////////////
////////////////////////////////////

Marketplace::Marketplace(Hero** h,int noh){
    heroes=h;
    Weapon* w[2*numofheroes];   //To market periexei 2 opla gia ka8e xarakthra
    Armor* a[2*numofheroes];   //To market periexei 2 panoplies gia ka8e xarakthra
    Spell* s[3];              //To market periexei 1 spell gia ka8e eidous spell
    Potion* p[2*noh+1];      //To market periexei 2 HP kai 2 MP potion kai ena allo potion agility h dexterity h strength potion
    for(int i=0;i<numofheroes;i++){
        stock.addWeapon(w[i]=new Weapon( heroes[i]->getLevel() , genName("weapon") ) );
        stock.addWeapon(w[i+numofheroes]=new Weapon( heroes[i]->getLevel() , genName("weapon") ) );

        stock.addArmor(a[i]=new Armor( heroes[i]->getLevel() , genName("armor") ) );
        stock.addArmor(a[i+numofheroes]=new Armor( heroes[i]->getLevel() , genName("armor") ) );
    }
    //Arxikopoihsh spell
    //To prwto spell einai analogo tou level tou prwtou xarakthra
    stock.addSpell(s[0]=new Spell(heroes[0]->getLevel() , genName("firespell") ) );

    //To deutero spell einai analogo tou level tou deuterou xarakthra, an uparxei
    if(numofheroes >= 2) stock.addSpell(s[1]=new Spell(heroes[1]->getLevel() , genName("icespell") ) );
    else stock.addSpell(s[1]=new Spell(heroes[0]->getLevel() , genName("icespell") ) );

    //To trito spell einai analogo tou level tou trito xarakthra, an uparxei
    if(numofheroes == 3) stock.addSpell(s[2]=new Spell(heroes[2]->getLevel() , genName("lightningspell")); );
    else spells[0]=new Spell(heroes[2]->getLevel() , genName("lightningspell"));

}

void Marketplace::menu(){
    cout << "What would you like to do?\n" << endl;
    unsigned int input;
    do{
        cout << "To buy items press 1\nTo sell items press 2\nTo leave press 3\n" << endl;
        input=inputNumber(3);
        if(input ==1){

        }
        else if(input == 2){

        }
    } while(input != 3);
}