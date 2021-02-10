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
    char answer;
    do{
        print();
        cout << "Would you like to move? n=no / a=left / d =right / w = up / s = down" << endl;
        answer = inputMove();
        switch (answer){
            case 'a':
                moveLeft();
                break;
            case 'd':
                moveRight();
                break;
            case 'w':
                moveUp();
                break;
            case 's':
                moveDown();
        }
    } while(answer != 'n');
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
        if(inputAnswer() == true){
            market=new Marketplace(heroes,numofheroes);
            market->menu();
        }
        return true;
    }
    else if(map[i][j] == '+'){
        int prob=rand()%100;
        if(prob <= 30){
            cout << "Battle\n";
            // battle();
        }
        return true;
    }
    else{
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
                    heroes[i]->attack(monsters[rand()%3]);
            }
        }
    }
    return true; //Na to bgaloume sto telos
}

int Grid::battleMenu(int index){
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
    int i;
    heroes=h;
    Weapon** w = new Weapon*[2*numofheroes];   //To market periexei 2 opla gia ka8e xarakthra 
    Armor** a = new Armor*[2*numofheroes];   //To market periexei 2 panoplies gia ka8e xarakthra
    Spell** s = new Spell*[3];              //To market periexei 1 spell gia ka8e eidous spell
    Potion** p = new Potion*[2*noh+1];      //To market periexei 2 HP kai 2 MP potion kai ena allo potion agility h dexterity h strength potion
    for(int i=0;i<numofheroes;i++){ // pw = new Weapon klp /.../ w[i] = &pw;
        stock.addWeapon( *(w[i]=new Weapon( heroes[i]->getLevel().getRL() , genName("weapon") ) ) );
        stock.addWeapon( *(w[i+numofheroes]=new Weapon( heroes[i]->getLevel().getRL() , genName("weapon") ) ) );

        stock.addArmor( *(a[i]=new Armor( heroes[i]->getLevel().getRL() , genName("armor") ) ) );
        stock.addArmor( *(a[i+numofheroes]=new Armor( heroes[i]->getLevel().getRL() , genName("armor") ) ) );
    }
    //Arxikopoihsh spell
    //To prwto spell einai analogo tou level tou prwtou xarakthra
    stock.addSpell( s[0]=new FireSpell(heroes[0]->getLevel().getRL() , genName("firespell") ) );

    //To deutero spell einai analogo tou level tou deuterou xarakthra, an uparxei
    if(numofheroes >= 2) stock.addSpell( s[1]=new IceSpell(heroes[1]->getLevel().getRL() , genName("icespell") ) );
    else stock.addSpell( s[1]=new IceSpell(heroes[0]->getLevel().getRL() , genName("icespell") ) );

    //To trito spell einai analogo tou level tou trito xarakthra, an uparxei
    if(numofheroes == 3) stock.addSpell( s[2]=new LightningSpell(heroes[2]->getLevel().getRL() , genName("lightningspell")) );
    else stock.addSpell( s[2]=new LightningSpell( heroes[2]->getLevel().getRL() , genName("lightningspell") ) );

    //Arxikopoihsh potion
    for(int i=0;i<numofheroes; i++){
        stock.addPotion( *(p[i]=new Potion(randomLevel(heroes[i]->getLevel().getRL()),"HP") ) );
        stock.addPotion( *(p[i+numofheroes]=new Potion(randomLevel(heroes[i]->getLevel().getRL()),"MP" ) ) );
    }
    stock.addPotion( *(p[i+numofheroes]=new Potion( level(heroes,numofheroes),genName("potion")) ) );

}

void Marketplace::menu(){
    cout << "What would you like to do?\n" << endl;
    unsigned int input,inputH;
    do{
        cout << "To buy items press 1\nTo sell items press 2\nTo leave press 3\n" << endl;
        input=inputNumber(3);
        if(input == 1){
            cout << "This marketplace currently has the following items on stock :" << endl;
            stock.print();

            cout << "Would you like to buy a weapon? y/n" << endl;
            if(inputAnswer() == true){
                do{
                    inputH=0;
                    if(numofheroes >= 2){
                        cout << "Which hero to buy the weapon?" << endl;
                        for(int i=0;i<numofheroes;i++)
                            cout << "Press " << i+1 << " if you would like " << heroes[i]->getName() << " who has " << heroes[i]->getMoney() << " to buy the weapon." << endl;
                        inputH=inputNumber(numofheroes)-1;
                    }
                    cout << "Enter the number of the weapon you would like to buy." << endl;
                    input=inputNumber(stock.getWeaponsSize());
                    if( heroes[inputH]->buy(stock.getWeapon(input)) == true ) stock.removeWeapon(input);
                    cout << "Would you like to buy another weapon? y/n" << endl;
                }while(inputAnswer() != false);
            }

            cout << "Would you like to buy an armor? y/n" << endl;
            if(inputAnswer() == true){
                do{
                    inputH=0;
                    if(numofheroes >= 2){
                        cout << "Which hero to buy the armor?" << endl;
                        for(int i=0;i<numofheroes;i++)
                            cout << "Press " << i+1 << " if you would like " << heroes[i]->getName() << " who has " << heroes[i]->getMoney() << " to buy the armor." << endl;
                        inputH=inputNumber(numofheroes)-1;
                    }
                    cout << "Enter the number of the armor you would like to buy." << endl;
                    input=inputNumber(stock.getArmorsSize());
                    if( heroes[inputH]->buy(stock.getArmor(input)) == true ) stock.removeArmor(input);
                    cout << "Would you like to buy another armor? y/n" << endl;
                }while(inputAnswer() != false);
            }

            cout << "Would you like to buy a spell? y/n" << endl;
            if(inputAnswer() == true){
                do{
                    inputH=0;
                    if(numofheroes >= 2){
                        cout << "Which hero to buy the spell?" << endl;
                        for(int i=0;i<numofheroes;i++)
                            cout << "Press " << i+1 << " if you would like " << heroes[i]->getName() << " who has " << heroes[i]->getMoney() << " to buy the spell." << endl;
                        inputH=inputNumber(numofheroes)-1;
                    }
                    cout << "Enter the number of the spell you would like to buy." << endl;
                    input=inputNumber(stock.getSpellsSize());
                    if( heroes[inputH]->buy(stock.getSpell(input)) == true ) stock.removeSpell(input);
                    cout << "Would you like to buy another spell? y/n" << endl;
                }while(inputAnswer() != false);
            }

            cout << "Would you like to buy a potion? y/n" << endl;
            if(inputAnswer() == true){
                do{
                    inputH=0;
                    if(numofheroes >= 2){
                        cout << "Which hero to buy the potion?" << endl;
                        for(int i=0;i<numofheroes;i++)
                            cout << "Press " << i+1 << " if you would like " << heroes[i]->getName() << " who has " << heroes[i]->getMoney() << " to buy the potion." << endl;
                        inputH=inputNumber(numofheroes)-1;
                    }
                    cout << "Enter the number of the potion you would like to buy." << endl;
                    input=inputNumber(stock.getPotionsSize());
                    if( heroes[inputH]->buy(stock.getPotion(input)) == true ) stock.removePotion(input);
                    cout << "Would you like to buy another potion? y/n" << endl;
                }while(inputAnswer() != false);
            }

        }
        else if(input == 2){
            cout << "Which item to sell?" << endl;
        }
    } while(input != 3);
}