Client	: Functions.o Items.o Spells.o LivingBeing.o Hero.o Monster.o Grid.o Client.cpp
	g++  Functions.o Items.o Spells.o LivingBeing.o Hero.o Monster.o Grid.o -o Client Client.cpp
	./Client

Grid.o :	Grid.cpp
	g++ -c Grid.cpp

Monster.o : Monster.cpp
	g++ -c Monster.cpp

Hero.o : Hero.cpp
	g++ -c Hero.cpp

LivingBeing.o : LivingBeing.cpp
	g++ -c LivingBeing.cpp

Spells.o	:	Spells.cpp
	g++ -c Spells.cpp

Items.o	:	Items.cpp
	g++ -c Items.cpp

Functions.o : Functions.cpp
	g++ -c Functions.cpp

clean	:
	rm Client Client.exe *.o