#include <iostream>
#include <string>
#include <ctime>
#include "Grid.h"

using namespace std;

Grid::Grid(Hero** h,int numofh){
    numofheroes=numofh;
    heroes=new Hero*[numofh];
    for(int i=0;i<numofh;i++) heroes[i]=h[i];
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
        cin >> answer;
        if(answer == 'a') moveLeft();
        else if(answer == 'd') moveRight();
        else if(answer == 'w') moveUp();
        else if(answer == 's') moveDown();
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
        return true;
    }
    else if(map[i][j] == '+'){
        int prob=rand()%100;
        if(prob <= 30){
            cout << "A monster has appeared!\nPrepare to battle!" << endl;
        }
        return true;
    }
    else{
        cout << "You can go there!" << endl;
        return false;
    }
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
    char answer;
    cin >> answer;
    switch(answer){
        case '1' :
            move();
            return true;
        case '2' :
            for(int i=0;i<numofheroes;i++) heroes[i]->checkInventory();
            return true;
        case '3' :
            //To be changed
            return true;
        case '4' :
            return false;
    }
    return false;
}