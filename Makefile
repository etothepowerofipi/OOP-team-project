Client	: Items.o Spells.o LivingBeing.o Hero.o Monster.o Map.o Client.cpp
	g++  Items.o Spells.o LivingBeing.o Hero.o Monster.o Map.o -o Client Client.cpp
	./Client

Map.o :	Map.cpp
	g++ -c Map.cpp

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

clean	:
	rm Client *.o