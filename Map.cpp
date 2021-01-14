#include <iostream>
#include <string>
#include <ctime>
#include "Map.h"

using namespace std;

Map::Map(Hero* h){
    heroes=h;
    maxi=20;
    maxj=20;
    for(int i=0;i<maxi;i++){
        for(int j=0;j<maxj;j++)
            grid[i][j]='+';
    }
    int numofmarkets=10+rand()%6;  //Paragw enan tuxaio ari8mo anamesa sto Min marketplaces=10 kai max marketplaces=15
    int i,j;
    while(numofmarkets > 0){
        i=rand()%maxi;
        j=rand()%maxj;
        grid[i][j]='M';
        numofmarkets--;
    }

    //Initializing hero's position at (0,0)
    tempchar=grid[0][0];
    x=y=0;
    grid[0][0]='H';
}

void Map::move(){
    char awnser;
    do{
        print();
        cout << "Would you like to move? n=no / a=left / d =right / w = up / s = down" << endl;
        cin >> awnser;
        if(awnser == 'a') moveLeft();
        else if(awnser == 'd') moveRight();
        else if(awnser == 'w') moveUp();
        else if(awnser == 's') moveDown();
    } while(awnser != 'n');
}

void Map::moveRight(){
    if(y+1 <= maxi){
        grid[x][y]=tempchar;
        y++;
        tempchar=grid[x][y];
        checkBlock(x,y);
        grid[x][y]='H';
    }
    else{
        cout << "You cant go there!" << endl;
    }
}

void Map::moveLeft(){
    if(y-1 >= 0){
        grid[x][y]=tempchar;
        y--;
        tempchar=grid[x][y];
        checkBlock(x,y);
        grid[x][y]='H';
    }
    else{
        cout << "You cant go there!" << endl;
    }
}

void Map::moveUp(){
    if(x-1 >= 0){
        grid[x][y]=tempchar;
        x--;
        tempchar=grid[x][y];
        checkBlock(x,y);
        grid[x][y]='H';
    }
    else{
        cout << "You cant go there!" << endl;
    }
}

void Map::moveDown(){
    if(x+1 <= maxi){
        grid[x][y]=tempchar;
        x++;
        tempchar=grid[x][y];
        checkBlock(x,y);
        grid[x][y]='H';
    }
    else{
        cout << "You cant go there!" << endl;
    }
}

void Map::checkBlock(int i,int j){
    if(grid[i][j]== 'M'){
        cout << "You have reached a marketplace!\nWould you like to enter? y/n" << endl;
    }
    else if(grid[i][j] == '+'){
        int prob=rand()%100;
        if(prob <= 30){
            cout << "A monster has appeared!\nPrepare to battle!" << endl;
        }
    }
}

void Map::print(){
    for(int i=0;i<maxi;i++){
        for(int j=0;j<maxj;j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }
    cout << endl << endl;
}