#include <iostream>
#include <string>
#include <ctime>
#include "Grid.h"
#include "Functions.h"

using namespace std;

Grid::Grid(Hero** h,int numofh){
    numofheroes = numofh;
    heroes = h;
    maxi = 20;
    maxj = 20;
    for(int i=0; i<maxi ;i++){
        for(int j=0; j<maxj; j++)
            map[i][j] = '+';
    }

    int numofmarkets = 50 + rand()%6;  //Paragei enan tuxaio ari8mo anamesa sto min marketplaces=15 kai max marketplaces=20
    int i,j;
    while(numofmarkets > 0){
        i = rand()%maxi;
        j = rand()%maxj;
        map[i][j]='M';
        numofmarkets--;
    }

    int unreachables = 30 + rand()%11;  //Paragei enan tuxaio ari8mo anamesa sto min unreachables=30 kai max unreachables=40
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
        if(inputAnswer() == true) Marketplace market(heroes,numofheroes);
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
    string* names=new string[monstersInBattle];
    if (monstersInBattle == 1)
        cout << "\nA monster has appeared!\nPrepare to battle!" << endl;
    else
        cout << "\nMonsters have appeared!\nPrepare to battle!" << endl;
    Effects effects;
    Monster** monsters = new Monster*[monstersInBattle];
    for (int i=0; i< monstersInBattle; i++){
        monsters[i] = monsterGenerator(level());
        names[i]=monsters[i]->getName();
    }
    while ( (heroesInBattle>0) && (monstersInBattle>0) ){
        cout << endl << endl;
        effects.newRound();
        for (int i=0; i<heroesInBattle; i++){
            heroes[i]->gainHP();
            heroes[i]->gainMP();
            if (monstersInBattle>0){
                bool acceptableAction = false;
                while (!acceptableAction){
                battleStats(monsters,monstersInBattle,heroesInBattle);
                int action = battleMenu(i);
                    switch (action){
                        int monsterIndex;
                        int damage;
                        int index;
                        case 1:
                            acceptableAction = true;
                            monsterIndex = chooseMonster(monsters,monstersInBattle);
                            cout << heroes[i]->getName() << " attacks " << names[monsterIndex] << endl;
                            damage = heroes[i]->attack();
                            if (monsters[monsterIndex]->defend(damage)  == 1)
                                removeMonster(monsters,monstersInBattle,monsterIndex,names);
                            break;
                        case 2:
                            index = heroes[i]->castSpell();
                            if (index > -1){
                                acceptableAction = true;
                                monsterIndex = chooseMonster(monsters,monstersInBattle);
                                int* result = new int[2];
                                result = heroes[i]->cast(index,monsters[monsterIndex]);
                                switch (result[0]){
                                    case 0:
                                        if (result[1] == 1)
                                            removeMonster(monsters,monstersInBattle,monsterIndex,names);
                                        break;
                                    default:
                                        effects.addEffect(monsters[monsterIndex],result);
                                }
                                delete result;
                            }
                            break;
                        case 3:
                            index = heroes[i]->usePotion();
                            if (index > -1){
                                acceptableAction = true;
                                heroes[i]->use(index);
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
            monsters[i]->gainHP();
            if (heroesInBattle > 0){
                int damage = monsters[i]->attack();
                int randomHero = rand() % heroesInBattle;
                heroes[randomHero]->takeDamageMessage(monsters[i]->getName());
                if (heroes[randomHero]->defend(damage))
                    heroFainted(heroes,heroesInBattle,randomHero);
            }
        }
    }
    if (heroesInBattle > 0){
        cout << "The heroes have won!" << endl;
        for (int i=0; i<heroesInBattle; i++){
            heroes[i]->gainXP(initialMonsters);
            heroes[i]->gainGold(initialMonsters);
        }
    }
    else
        cout << "The heroes have lost!" << endl;
    for (int i=0; i<initialMonsters; i++){
        delete monsters[i];
    }
    delete monsters;
    delete names;
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
    cout << "\nWhat would you like " << heroes[index]->getName() << " to do?" << endl;
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
    cout << "\n" << endl;
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

Marketplace::~Marketplace(){
    for(int i=0;i<noh;i++){
        delete w[i];
        delete a[i];
    }
    for(int i=0;i<2*noh+1;i++) delete p[i];
    delete w;
    delete a;
    delete p;
    delete s;
}

Marketplace::Marketplace(Hero** heroes,int n){
    this->noh=n;
    int i;
    w = new Weapon*[noh];   //To market periexei 2 opla gia ka8e xarakthra
    a = new Armor*[noh];   //To market periexei 2 panoplies gia ka8e xarakthra
    s = new Spell*[3];              //To market periexei 1 spell gia ka8e eidous spell
    p = new Potion*[2*noh+1];      //To market periexei 2 HP kai 2 MP potion kai ena allo potion agility h dexterity h strength potion
    for(int i=0;i<noh;i++){
        stock.addArmor( *(a[i]=new Armor( randomLevel(heroes[i]->getLevel().getRL()) , genName("armor") ) ) );
        stock.addWeapon( *(w[i]=new Weapon( randomLevel(heroes[i]->getLevel().getRL()) , genName("weapon") ) ) );
    }
    //Arxikopoihsh spell
    //To prwto spell einai analogo tou level tou prwtou xarakthra
    stock.addSpell( s[0]=new FireSpell(randomLevel(heroes[0]->getLevel().getRL()) , genName("firespell") ) );
    //To deutero spell einai analogo tou level tou deuterou xarakthra, an uparxei
    if(noh >= 2) stock.addSpell( s[1]=new IceSpell(randomLevel(heroes[1]->getLevel().getRL()) , genName("icespell") ) );
    else stock.addSpell( s[1]=new IceSpell(randomLevel(heroes[0]->getLevel().getRL()) , genName("icespell") ) );
    //To trito spell einai analogo tou level tou trito xarakthra, an uparxei
    if(noh == 3) stock.addSpell( s[2]=new LightningSpell(randomLevel(heroes[2]->getLevel().getRL()) , genName("lightningspell")) );
    else stock.addSpell( s[2]=new LightningSpell( randomLevel(heroes[0]->getLevel().getRL()) , genName("lightningspell") ) );
    //Arxikopoihsh potion
    for(int i=0;i<noh; i++){
        stock.addPotion( *(p[i]=new Potion(randomLevel(heroes[i]->getLevel().getRL()),"HP") ) );
        stock.addPotion( *(p[i+noh]=new Potion(randomLevel(heroes[i]->getLevel().getRL()),"MP" ) ) );
    }
    stock.addPotion( *(p[2*noh]=new Potion( level(heroes,noh),genName("potion")) ) );
    menu(heroes,noh); //Otan teleiwsei o constructor kalei thn menu
}

void Marketplace::menu(Hero** heroes,int numofheroes){
    cout << "What would you like to do?\n" << endl;
    int input,inputH,inputSwitch;
    char inputS;
    bool answer;
    do{
        cout << "To buy items press 1\nTo sell items press 2\nTo leave press 3\n" << endl;
        input=inputNumber(3);
        if(input == 1){
            do{
                cout << "To browse weapons press 1\nTo browse armors press 2\nTo browse spells press 3\nTo browse potions press 4\nTo go back press 5\n" << endl;
                inputSwitch=inputNumber(5);
                switch(inputSwitch){
                    case 1 :
                        if(stock.getWeaponsSize() > 0){
                            cout << "\n\nThis marketplace now has the following weapons on stock :" << endl;
                            stock.printWeapons();
                            cout << "Would you like to buy a weapon? y/n" << endl;
                            answer=inputAnswer();
                            while(answer == true){
                                inputH=0;
                                if(numofheroes >= 2){
                                    cout << "Which hero to buy the weapon?" << endl;
                                    for(int i=0;i<numofheroes;i++)
                                        cout << "Press " << i+1 << " if you would like " << heroes[i]->getName() << " who has " << heroes[i]->getGold() << " gold to buy the weapon." << endl;
                                    inputH=inputNumber(numofheroes) - 1;
                                }
                                cout << "Enter the number of the weapon you would like to buy." << endl;
                                input=inputNumber(stock.getWeaponsSize())-1;
                                cout << "Buying :\n" << endl; stock.getWeapon(input).print(); cout << "Continue? y/n" << endl;
                                if(inputAnswer() == true){
                                    if( heroes[inputH]->buy(stock.getWeapon(input)) == true ){
                                        cout << "Succesfuly bought "; stock.getWeapon(input).print();
                                        stock.removeWeapon(input);
                                        cout << "New balance for " << heroes[inputH]->getName() << " is " << heroes[inputH]->getGold() << endl;
                                    }
                                }
                                if(stock.getWeaponsSize() > 0){
                                    cout << "Would you like to buy a weapon? y/n" << endl;
                                    answer=inputAnswer();
                                    if(answer == true){
                                        cout << "\n\nThis marketplace now has the following weapons on stock :" << endl;
                                        stock.printWeapons();
                                    }
                                }
                                else break;
                            }
                        }
                        else cout << "No weapons on stock" << endl;
                        break;

                    case 2 :
                        if(stock.getArmorsSize() > 0){
                            cout << "\n\nThis marketplace now has the following armors on stock :" << endl;
                            stock.printArmors();
                            cout << "Would you like to buy an armor? y/n" << endl;
                            answer=inputAnswer();
                            while(answer == true){
                                inputH=0;
                                if(numofheroes >= 2){
                                    cout << "Which hero to buy the armor?" << endl;
                                    for(int i=0;i<numofheroes;i++)
                                        cout << "Press " << i+1 << " if you would like " << heroes[i]->getName() << " who has " << heroes[i]->getGold() << " gold to buy the armor." << endl;
                                    inputH=inputNumber(numofheroes)-1;
                                }
                                cout << "Enter the number of the armor you would like to buy." << endl;
                                input=inputNumber(stock.getArmorsSize())-1;
                                cout << "Buying :" << endl; stock.getArmor(input).print(); cout << "Continue? y/n" << endl;
                                if(inputAnswer() == true){
                                    if( heroes[inputH]->buy(stock.getArmor(input)) == true ){
                                        cout << "Succesfuly bought "; stock.getArmor(input).print();
                                        stock.removeArmor(input);
                                        cout << "New balance for " << heroes[inputH]->getName() << " is " << heroes[inputH]->getGold() << endl;
                                    }
                                }
                                if(stock.getArmorsSize() > 0){
                                    cout << "Would you like to buy an armor? y/n" << endl;
                                    answer=inputAnswer();
                                    if(answer == true){
                                        cout << "\n\nThis marketplace now has the following armors on stock :" << endl;
                                        stock.printArmors();
                                    }
                                }
                                else break;
                            }
                        }
                        else cout << "No armors on stock" << endl;
                        break;
                    case 3 :
                        if(stock.getSpellsSize() > 0){
                            cout << "\n\nThis marketplace now has the following spells on stock :" << endl;
                            stock.printSpells();
                            cout << "Would you like to buy a spell? y/n" << endl;
                            answer=inputAnswer();
                            while(answer == true){
                                inputH=0;
                                if(numofheroes >= 2){
                                    cout << "Which hero to buy the spell?" << endl;
                                    for(int i=0;i<numofheroes;i++)
                                        cout << "Press " << i+1 << " if you would like " << heroes[i]->getName() << " who has " << heroes[i]->getGold() << " gold to buy the spell." << endl;
                                    inputH=inputNumber(numofheroes)-1;
                                }
                                cout << "Enter the number of the spell you would like to buy." << endl;
                                input=inputNumber(stock.getSpellsSize())-1;
                                cout << "Buying :" << endl; stock.getSpell(input)->print(); cout << "Continue? y/n" << endl;
                                if(inputAnswer() == true){
                                    if( heroes[inputH]->buy(stock.getSpell(input)) == true ){
                                        cout << "Succesfuly bought "; stock.getSpell(input)->print();
                                        stock.removeSpell(input);
                                        cout << "New balance for " << heroes[inputH]->getName() << " is " << heroes[inputH]->getGold() << endl;
                                    }
                                }
                                if(stock.getSpellsSize() > 0){
                                    cout << "Would you like to buy a spell? y/n" << endl;
                                    answer=inputAnswer();
                                    if(answer == true){
                                        cout << "\n\nThis marketplace now has the following spells on stock :" << endl;
                                        stock.printSpells();
                                    }
                                }
                                else break;
                            }
                        }
                        else cout << "No spells on stock" << endl;
                        break;
                    case 4 :
                        if(stock.getPotionsSize() > 0){
                            cout << "\n\nThis marketplace now has the following potions on stock :" << endl;
                            stock.printPotions();
                            cout << "Would you like to buy a potion? y/n" << endl;
                            answer=inputAnswer();
                            while(answer == true){
                                inputH=0;
                                if(numofheroes >= 2){
                                    cout << "Which hero to buy the potion?" << endl;
                                    for(int i=0;i<numofheroes;i++)
                                        cout << "Press " << i+1 << " if you would like " << heroes[i]->getName() << " who has " << heroes[i]->getGold() << " gold to buy the potion." << endl;
                                    inputH=inputNumber(numofheroes)-1;
                                }
                                cout << "Enter the number of the potion you would like to buy." << endl;
                                input=inputNumber(stock.getPotionsSize())-1;
                                cout << "Buying :" << endl; stock.getPotion(input).print(); cout << "Continue? y/n" << endl;
                                if(inputAnswer() == true){
                                    if( heroes[inputH]->buy(stock.getPotion(input)) == true ){
                                        cout << "Succesfuly bought "; stock.getPotion(input).print();
                                        stock.removePotion(input);
                                        cout << "New balance for " << heroes[inputH]->getName() << " is " << heroes[inputH]->getGold() << endl;
                                    }
                                }
                                if(stock.getPotionsSize() > 0){
                                    cout << "Would you like to buy a potion? y/n" << endl;
                                    answer=inputAnswer();
                                    if(answer == true){
                                        cout << "\n\nThis marketplace now has the following potions on stock :" << endl;
                                        stock.printPotions();
                                    }
                                }
                                else break;
                            }
                        }
                        else cout << "No potions on stock" << endl;
                        break;
                }
            }while(inputSwitch != 5);
        }
        else if(input == 2){
            do{
                inputH=0;
                if(numofheroes >= 2){
                    cout << "Which hero to sell an item?" << endl;
                    for(int i=0;i<numofheroes;i++)
                        cout << "Press " << i+1 << " if you would like " << heroes[i]->getName() << " who has " << heroes[i]->getGold() << " to sell an item." << endl;
                    cout << "To go back press " << numofheroes+1 << endl;
                    inputH=inputNumber(numofheroes+1)-1;
                    if(inputH == numofheroes) break;
                }
                cout << "Inventory of hero " << heroes[inputH]->getName() << " is :" << endl;
                heroes[inputH]->printInventory();
                do{
                    cout << "What type of item would you like to sell? Input w/a/s/p/b (weapon/armor/spell/potion/go back)" << endl;
                    switch(inputS=inputSell()){
                        case 'w' :
                            heroes[inputH]->sell("weapon");
                            break;
                        case 'a' :
                            heroes[inputH]->sell("armor");
                            break;
                        case 's' :
                            heroes[inputH]->sell("spell");
                            break;
                        case 'p' :
                            heroes[inputH]->sell("potion");
                            break;
                    }
                } while(inputS != 'b');
                if(numofheroes == 1) break;
            }while(inputH == numofheroes);
        }
    } while(input != 3);
}

Effects::Effects(){}

void Effects::addEffect(Monster* m, int* effects){
    monsters.push_back(m);
    type.push_back(effects[0]);
    amount.push_back(effects[1]);
    rounds.push_back(3);
}

void Effects::newRound(){
    for (int i=0; i<rounds.size(); i++){
        rounds[i]--;
        if (rounds[i] == 0){
            monsters[i]->regainStats(type[i],amount[i]);

            //monster
            vector<Monster*> tempMon;
            for(int j=0;j<monsters.size();j++){
                if(j != i) tempMon.push_back(monsters[j]);
            }
            monsters.clear();
            monsters = tempMon;

            //type
            vector<int> tempT;
            for(int j=0;j<type.size();j++){
                if(j != i) tempT.push_back(type[j]);
            }
            type.clear();
            type = tempT;

            //amount
            vector<int> tempAm;
            for(int j=0;j<amount.size();j++){
                if(j != i) tempAm.push_back(amount[j]);
            }
            amount.clear();
            amount = tempAm;

            //rounds
            vector<int> tempR;
            for(int j=0;j<rounds.size();j++){
                if(j != i) tempR.push_back(rounds[j]);
            }
            rounds.clear();
            rounds = tempR;
        }
    }
}


