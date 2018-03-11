#build
EXE: main.o Tren.o Invisible.o Bombas.o Escenario.o Item.o Jugador.o  Espina.o V.o
	g++ main.o Tren.o Invisible.o Bombas.o Escenario.o Item.o Jugador.o  Espina.o V.o -o EXE -lncurses

#main
main.o: main.cpp Bombas.h  Espina.h Jugador.h V.h Item.h Escenario.h Tren.h Invisible.h V.h Espina.h Normal.h 
	g++ -c main.cpp      

#Tren
Tren.o:  Escenario.cpp  Escenario.h Tren.h  
	g++ -c Tren.cpp

#Invisible
Invisible.o: Invisible.cpp Invisible.h  Escenario.h   
	g++ -c Invisible.cpp
#Bombas
Bombas.o: Bombas.cpp  Item.h Bombas.h 
	g++ -c Bombas.cpp

#Escenario
Escenario.o:Escenario.cpp  Item.h  V.h Normal.h  Espina.h Bombas.h 
	g++ -c Escenario.cpp

#Item
Item.o:Item.cpp Item.h
	g++ -c Item.cpp 
#Jugador
Jugador.o:Jugador.cpp  Jugador.h Item.h
	g++ -c Jugador.cpp 
#Espina
Espina.o: Espina.cpp  Espina.h Bombas.h
	g++ -c Espina.cpp 
#V
V.o: V.cpp V.h Bombas.h
	g++ -c V.cpp 
#normal
normal.o:Normal.cpp Normal.h Bombas.h
	g++ -c Normal.cpp




