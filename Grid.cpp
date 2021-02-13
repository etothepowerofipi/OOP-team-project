#include <iostream>
#include <string>
#include <ctime>
#include "Grid.h"
#include "Functions.h"

using namespace std;

Grid::Grid(Hero** h,int numofh){
    numofheroes=numofh;
    heroes=h;
    maxi=20;
    maxj=20;
    for(int i=0;i<maxi;i++){
        for(int j=0;j<maxj;j++)
            map[i][j]='+';
    }

    int numofmarkets=15+rand()%6;  //Paragw enan tuxaio ari8mo anamesa sto min marketplaces=15 kai max marketplaces=21
    int i,j;
    while(numofmarkets > 0){
        i=rand()%maxi;
        j=rand()%maxj;
        map[i][j]='M';
        numofmarkets--;
    }

    int unreachables=30+rand()%11;  //Paragw enan tuxaio ari8mo anamesa sto min unreachables=30 kai max unreachables=40
    while(unreachables > 0){
        do{
            i=rand()%maxi;
            j=rand()%maxj;
        }while( canPlace(i,j) == false );
        map[i][j]='X';
        unreachables--;
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
        cout << "Would you like to move? n = no / a = left / d = right / w = up / s = down" << endl;
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
        if(prob < 30) return battle();
        else return true;
    }
    return false;
}

bool Grid::battle(){
    int heroesInBattle = numofheroes;
    const int initialMonsters =  heroesInBattle + rand()%2;
    int monstersInBattle = initialMonsters;
    if (monstersInBattle == 1)
        cout << "A monster has appeared!\nPrepare to battle!" << endl;
    else
        cout << "Monsters have appeared!\nPrepare to battle!" << endl;

    Monster** monsters = new Monster*[monstersInBattle];
    for (int i=0; i< monstersInBattle; i++)
        monsters[i] = monsterGenerator(level());

    while ( (heroesInBattle>0) && (monstersInBattle>0) ){
        cout << "\n\n" << endl;
        for (int i=0; i<heroesInBattle; i++){
            heroes[i]->gainMP();
            if (monstersInBattle>0){
                bool acceptableAction = false;
                while (!acceptableAction){
                battleStats(monsters,monstersInBattle,heroesInBattle);
                int action = battleMenu(i);
                    switch (action){
                        int monsterIndex;
                        int damage;
                        case 1:
                            acceptableAction = true;
                            monsterIndex = chooseMonster(monsters,monstersInBattle);
                            damage = heroes[i]->attack();
                            if (monsters[monsterIndex]->defend(damage))
                                monsterFainted(monsters,monstersInBattle,monsterIndex);
                            break;
                        

                        case 2:
                            if (int spellIndex = heroes[i]->castSpell() > -1){
                                acceptableAction = true;
                                damage = heroes[i]->cast(heroes[i]->getInventory().getSpell(spellIndex));
                                monsterIndex = chooseMonster(monsters,monstersInBattle);
                                if (monsters[monsterIndex]->defend(damage))
                                    monsterFainted(monsters,monstersInBattle,monsterIndex);
                            }
                            break;
                        

                        case 3:
                            if (int potionIndex = heroes[i]->usePotion() > -1){
                                acceptableAction = true;
                                heroes[i]->use(heroes[i]->getInventory().getPotion(potionIndex));
                                heroes[i]->removePotion(potionIndex);
                            }
                            break;
                        

                        case 4:
                            acceptableAction = true;
                            heroes[i]->checkInventory();
                        
                    }
                }
            }
        }
        for (int i=0; i<monstersInBattle; i++){
            cout << "\n" << endl;
            int randomHero = rand() % heroesInBattle;
            int damage = monsters[i]->attack();
            cout << monsters[i]->getName() << " attacks " + heroes[randomHero]->getName() + " for " << damage << " damage!" << endl;
            if (heroes[randomHero]->defend(damage))
                heroFainted(heroes,heroesInBattle,randomHero);
        }
    }
    if (heroesInBattle>0){
        cout << "The heroes have won!" << endl;
        for (int i=0; i<heroesInBattle; i++){
            heroes[i]->gainXP(initialMonsters);
            heroes[i]->gainGold(initialMonsters);
        }
    }
    else {
        cout << "The heroes have lost!" << endl;
    }
    return (heroesInBattle>0);
}

void Grid::battleStats(Monster** monsterArray, const int monsters, const int heroes) const{
    cout << "Heroes:" << endl;
    for (int i=0; i<heroes; i++)
        this->heroes[i]->print();
    cout << "Monsters:" << endl;
    for (int i=0; i<monsters; i++)
        monsterArray[i]->print();
}

int Grid::battleMenu(const int index) const{
    cout << "What would you like " + heroes[index]->getName() + " to do?" << endl;
    cout << "To attack normally, type 1." << endl;
    cout << "To cast a spell, type 2." << endl;
    cout << "To use a potion, type 3." << endl;
    cout << "To change equipment, type 4." << endl;

    return inputNumber(4);
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
    numofheroes=noh;
    Weapon** w = new Weapon*[numofheroes];   //To market periexei 2 opla gia ka8e xarakthra 
    Armor** a = new Armor*[numofheroes];   //To market periexei 2 panoplies gia ka8e xarakthra
    Spell** s = new Spell*[3];              //To market periexei 1 spell gia ka8e eidous spell
    Potion** p = new Potion*[2*noh+1];      //To market periexei 2 HP kai 2 MP potion kai ena allo potion agility h dexterity h strength potion
    for(int i=0;i<numofheroes;i++){
        stock.addWeapon( *(w[i]=new Weapon( heroes[i]->getLevel().getRL() , genName("weapon") ) ) );
        // stock.addWeapon( *(w[i+numofheroes]=new Weapon( heroes[i]->getLevel().getRL() , genName("weapon") ) ) );

        stock.addArmor( *(a[i]=new Armor( heroes[i]->getLevel().getRL() , genName("armor") ) ) );
        // stock.addArmor( *(a[i+numofheroes]=new Armor( heroes[i]->getLevel().getRL() , genName("armor") ) ) );
    }
    //Arxikopoihsh spell
    //To prwto spell einai analogo tou level tou prwtou xarakthra
    stock.addSpell( s[0]=new FireSpell(heroes[0]->getLevel().getRL() , genName("firespell") ) );
    //To deutero spell einai analogo tou level tou deuterou xarakthra, an uparxei
    if(numofheroes >= 2) stock.addSpell( s[1]=new IceSpell(heroes[1]->getLevel().getRL() , genName("icespell") ) );
    else stock.addSpell( s[1]=new IceSpell(heroes[0]->getLevel().getRL() , genName("icespell") ) );

    //To trito spell einai analogo tou level tou trito xarakthra, an uparxei
    if(numofheroes == 3) stock.addSpell( s[2]=new LightningSpell(heroes[2]->getLevel().getRL() , genName("lightningspell")) );
    else stock.addSpell( s[2]=new LightningSpell( heroes[0]->getLevel().getRL() , genName("lightningspell") ) );

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
    char inputS;
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
                            cout << "Press " << i+1 << " if you would like " << heroes[i]->getName() << " who has " << heroes[i]->getGold() << " money to buy the weapon." << endl;
                        inputH=inputNumber(numofheroes)-1;
                    }
                    cout << "Enter the number of the weapon you would like to buy." << endl;
                    input=inputNumber(stock.getWeaponsSize())-1;
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
                            cout << "Press " << i+1 << " if you would like " << heroes[i]->getName() << " who has " << heroes[i]->getGold() << " money to buy the armor." << endl;
                        inputH=inputNumber(numofheroes)-1;
                    }
                    cout << "Enter the number of the armor you would like to buy." << endl;
                    input=inputNumber(stock.getArmorsSize())-1;
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
                            cout << "Press " << i+1 << " if you would like " << heroes[i]->getName() << " who has " << heroes[i]->getGold() << " money to buy the spell." << endl;
                        inputH=inputNumber(numofheroes)-1;
                    }
                    cout << "Enter the number of the spell you would like to buy." << endl;
                    input=inputNumber(3)-1;
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
                            cout << "Press " << i+1 << " if you would like " << heroes[i]->getName() << " who has " << heroes[i]->getGold() << " to money buy the potion." << endl;
                        inputH=inputNumber(numofheroes)-1;
                    }
                    cout << "Enter the number of the potion you would like to buy." << endl;
                    input=inputNumber(stock.getPotionsSize())-1;
                    if( heroes[inputH]->buy(stock.getPotion(input)) == true ) stock.removePotion(input);
                    cout << "Would you like to buy another potion? y/n" << endl;
                }while(inputAnswer() != false);
            }

        }
        else if(input == 2){
            for(int i=0; i<numofheroes; i++){
                cout << "Inventory of hero " << heroes[i]->getName() << " is :" << endl;
                do{
                    cout << "What type of item would you like to sell? Input w/a/s/p/b (weapon/armor/spell/potion/go back)" << endl;
                    switch(inputS=inputSell()){
                        case 'w' :
                            heroes[i]->sell("weapon");
                            break;
                        case 'a' :
                            heroes[i]->sell("armor");
                            break;
                        case 's' :
                            heroes[i]->sell("spell");
                            break;
                        case 'p' :
                            heroes[i]->sell("potion");
                            break;
                    }
                } while(inputS != 'b');
            }
        }
    } while(input != 3);
}