#include "Grid.h"
using namespace std;

void InitializeNameArrays();
string generateRandomName(string* names,int cap);
string genName(string type);

int main(void){
    srand(time(0));
    InitializeNameArrays();

    cout << "Choose a difficulty :\nHard mode : You only have 1 hero!(press '1')\nMedium mode : You have 2 heroes!(press '2')\nEasy mode : You have 3 heroes!(press '3')" << endl;
    int dif,intAnswer;
    cin >> dif;
    Hero** heroes=new Hero*[dif];
    string name;
    for(int i=0;i<dif;i++){
        cout << "Choose a name for hero number " << i+1 << "!" << endl;
        cin >> name;
        cout << "Choose a class for "<< name << "!\n" << endl;
        cout << "Warriors have increased damage and agility. To make " << name << " a warrior press '1'\n" << endl;
        cout << "Paladins have increased damage and dexterity. To make " << name << " a paladin press '2'\n" << endl;
        cout << "Sorcerers have increased dexterity and agility. To make " << name << " a sorcerer press '3'\n" << endl;
        cin >> intAnswer;
        switch(intAnswer){
            case 1 :
                heroes[i]=new Warrior(name);
                break;
            case 2 :
                heroes[i]=new Paladin(name);
                break;
            case 3 :
                heroes[i]=new Sorcerer(name);
        }
    }
    Grid grid(heroes,dif);

    while(grid.menu() == true); //Start game
    for(int i=0;i<dif;i++){
        delete heroes[i];
    }
    delete[] heroes;
    
    cout << "\n\nGame over!" << endl;

    return 0;
}