#include <iostream>
#include <string>
#include <ctime>
#include "Map.h"

using namespace std;

Map::Map(){
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

void Map::moveDown(){
    grid[x][y]=tempchar;
    if(y+1 != 0 && y+1 != maxj){
        y++;
        tempchar=grid[x][y];
        grid[x][y]='H';
    }
    else{
        cout << "You cant go there!" << endl;
    }
}

void Map::moveUp(){
    grid[x][y]=tempchar;
    if(y-1 != 0 && y-1 != maxj){
        y--;
        tempchar=grid[x][y];
        grid[x][y]='H';
    }
    else{
        cout << "You cant go there!" << endl;
    }
}

void Map::moveRight(){
    grid[x][y]=tempchar;
    if(x+1 != 0 && x+1 != maxi){
        x++;
        tempchar=grid[x][y];
        grid[x][y]='H';
    }
    else{
        cout << "You cant go there!" << endl;
    }
}

void Map::moveLeft(){
    grid[x][y]=tempchar;
    if(x-1 != 0 && x-1 != maxi){
        x--;
        tempchar=grid[x][y];
        grid[x][y]='H';
    }
    else{
        cout << "You cant go there!" << endl;
    }
}

void Map::print(){
    for(int i=0;i<maxi;i++){
        for(int j=0;j<maxj;j++)
            cout << grid[i][j] << " ";
        cout << endl;
    }
}