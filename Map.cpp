#include <iostream>
#include <string>
#include <ctime>
#include "Map.h"

using namespace std;

Map::Map(){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++)
            grid[i][j]='C';
    }
    int numofmarkets=10+rand()%6;  //Paragw enan tuxaio ari8mo anamesa sto Min marketplaces=10 kai max marketplaces=15
    int i,j;
    while(numofmarkets > 0){
        i=rand()%10;
        j=rand()%10;
        grid[i][j]='M';
    }
}

void Map::print(){
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++)
            cout << grid[i][j];
        cout << endl;
    }
}