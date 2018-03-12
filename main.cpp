/*INCLUDES*/
#include <ncurses.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <vector>
#include <typeinfo>
#include <stdlib.h>
#include <sstream>
/*CLASES*/
#include "Jugador.h"
#include "Bombas.h"
#include "Espina.h"
#include "V.h"
#include "Normal.h"
#include "Escenario.h"
#include "Invisible.h"
#include "Tren.h"
/*METODOS*/
void salir();
int menu();
int menu();
int menu2();
int menu3();
string menunombre();
string menunombre_escenario();
int tipoBomba();
void Cargando();
void EscenarioInvisible();
int tipobomba;
void Juego(string, string, int);
void crearBomba();
Jugador *moverbots(Jugador *);
int convertirNumero(char);
int getPX(string);
int getPY(string);
/*Variables globales*/
int e;
Jugador *jugador;
int T_escenario;
Escenario *Tablero = NULL;
int vida = 1 + rand() % (3 - 1);
Jugador *boot1 = NULL;
Jugador *boot2 = NULL;
Jugador *boot3 = NULL;
Jugador *boot4 = NULL;
Tren *Temporal = NULL;
/*STD*/
using namespace std;
int main(void)
{
    int escenario;
    switch (menu())
    {
    case 1:
    {
        escenario = menu2();
        T_escenario=escenario;
        tipobomba = menu3();
        string Nombre = menunombre();
        string nombre_escenario = menunombre_escenario();
        jugador = new Jugador(2, Nombre, true, 1, 0, 0);
        boot1 = new Jugador(2, "Boot1", 1, 2, 10, 0);
        boot2 = new Jugador(2, "Boot2", 1, 2, 0, 12);
        boot3 = new Jugador(2, "Boot3", 1, 2, 10, 12);
        boot4 = new Jugador(2, "Boot4", 1, 2, 5, 6);

        if (escenario == 1)
        { //Invisible
            Tablero = new Invisible(nombre_escenario, tipobomba);
            Cargando();
            erase();
            Juego(Nombre, nombre_escenario, vida);
        }
        else
        { //EL otro
            Tablero = new Tren(nombre_escenario);
            Temporal=new Tren(nombre_escenario);
            
            Cargando();
            erase();
            Juego(Nombre, nombre_escenario, -1);
        }

        break;
    }
    case 2:
    {
        salir();
    }
    } //Fin del switch
} //fin del main.

int menu()
{
    initscr();
    int x, y;
    getmaxyx(stdscr, y, x);
    move(0, (x / 2 - 18));
    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        attron(COLOR_PAIR(1));
        printw("<< MENU PRINCIPAL >>");
        attroff(COLOR_PAIR(1));
        init_pair(2, COLOR_CYAN, COLOR_BLACK);
        attron(COLOR_PAIR(2));
        move(1, 0);
        printw("Seleccione una opcion :\n");
        move(2, 1);
        printw("1)Iniciar Juego\n");
        move(3, 1);
        printw("2) Salir \n");
        printw("Usted selecciono: ");
        attroff(COLOR_PAIR(2));
    }
    int cx = 0;
    int cy = 2;
    int tecla;
    move(cy, cx);
    refresh();
    while (true)
    {
        noecho();
        tecla = getch();
        if (tecla == 10)
        {
            if (cy == 2)
            {
                return 1;
            }
            if (cy == 3)
            {
                return 2;
            }
        }
        else
        {
            if (tecla == 65 && cy > 2)
            {
                //printw(" arriba");
                cy = cy - 1;
                move(cy, cx);
            }
            else if (tecla == 66 && cy <= 4)
            {
                cy = cy + 1;
                move(cy, cx);
            }
            else
            {
                //No hara nada
            }
        }
        refresh();
    }
    echo();
    return 0;
}

void salir()
{
    int x, y;
    getmaxyx(stdscr, y, x);
    erase();
    if (has_colors)
    {
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        attron(COLOR_PAIR(1));
        move(y / 2, (x / 2 - 6));
        printw("Hasta la proxima :( ");
        refresh();
        usleep(1000000 / 2);
        printw(".");
        refresh();
        usleep(1000000 / 2);
        printw(".");
        refresh();
        usleep(1000000 / 2);
        printw(".");
        usleep(1000000 / 2);
        printw(":D");
        refresh();
        usleep(1000000 / 2);
        attroff(COLOR_PAIR(1));
    }
    endwin();
    exit(0);
}

void Cargando()
{
    int x, y;
    getmaxyx(stdscr, y, x);
    erase();
    if (has_colors)
    {
        start_color();
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        attron(COLOR_PAIR(1));
        move(y / 2, 15);
        printw("Espere mientras cargamos los elementos :3 ");
        refresh();
        usleep(1000000 / 2);
        printw(".");
        refresh();
        usleep(1000000 / 2);
        printw(".");
        refresh();
        usleep(1000000 / 2);
        printw(".");
        usleep(1000000 / 2);
        printw("Cargado!");
        refresh();
        usleep(1000000 / 2);
        attroff(COLOR_PAIR(1));
    }
    endwin();
}
Jugador *moverbots(Jugador *Objeto)
{
    bool movimiento = false;
    int x = Objeto->getX();
    int y = Objeto->getY();
    if (x == 10)
    {
        if (Tablero->getMatrix()[x - 1][y]->toString() == " ")
        {
            movimiento = true;
            Objeto->setX(x - 1);
            Item *temp = Tablero->getMatrix()[x][y];
            Item *temp2 = Tablero->getMatrix()[Objeto->getX()][Objeto->getY()];
            Tablero->setMatrix(temp2, x, y);
            Tablero->setMatrix(temp, Objeto->getX(), Objeto->getY());
            //Tablero->getMatrix()[x - 1][y] = boot1;
        }
    }
    else if (x - 1 >= 0)
    {
        if (Tablero->getMatrix()[x - 1][y]->toString() == " ")
        {
            movimiento = true;
            Objeto->setX(x - 1);
            Item *temp = Tablero->getMatrix()[x][y];
            Item *temp2 = Tablero->getMatrix()[Objeto->getX()][Objeto->getY()];
            Tablero->setMatrix(temp2, x, y);
            Tablero->setMatrix(temp, Objeto->getX(), Objeto->getY());
            // Tablero->getMatrix()[x - 1][y] = boot1;
        }
    }

    if (!movimiento && x == 0)
    {
        if (Tablero->getMatrix()[x + 1][y]->toString() == " ")
        {
            movimiento = true;
            Objeto->setX(x + 1);
            Item *temp = Tablero->getMatrix()[x][y];
            Item *temp2 = Tablero->getMatrix()[Objeto->getX()][Objeto->getY()];
            Tablero->setMatrix(temp2, x, y);
            Tablero->setMatrix(temp, Objeto->getX(), Objeto->getY());
            //Tablero->getMatrix()[x + 1][y] = boot1;
        }
    }
    else if (!movimiento && x + 1 <= 10)
    {
        if (Tablero->getMatrix()[x + 1][y]->toString() == " ")
        {
            movimiento = true;
            Objeto->setX(x - 1);
            Item *temp = Tablero->getMatrix()[x][y];
            Item *temp2 = Tablero->getMatrix()[Objeto->getX()][Objeto->getY()];
            Tablero->setMatrix(temp2, x, y);
            Tablero->setMatrix(temp, Objeto->getX(), Objeto->getY());
            // Tablero->getMatrix()[x + 1][y] = boot1;
        }
    }

    /*MOVIMIENTOS DE LA Y*/
    if (!movimiento && (y == 12))
    {
        if (Tablero->getMatrix()[x][y - 1]->toString() == " ")
        {
            movimiento = true;
            Objeto->setY(y - 1);
            Item *temp = Tablero->getMatrix()[x][y];
            Item *temp2 = Tablero->getMatrix()[Objeto->getX()][Objeto->getY()];
            Tablero->setMatrix(temp2, x, y);
            Tablero->setMatrix(temp, Objeto->getX(), Objeto->getY());
            // Tablero->getMatrix()[x][y-1] = boot1;
        }
    }
    else if (y - 1 >= 0)
    {
        if (Tablero->getMatrix()[x][y - 1]->toString() == " ")
        {
            movimiento = true;
            Objeto->setY(y - 1);
            Item *temp = Tablero->getMatrix()[x][y];
            Item *temp2 = Tablero->getMatrix()[Objeto->getX()][Objeto->getY()];
            Tablero->setMatrix(temp2, x, y);
            Tablero->setMatrix(temp, Objeto->getX(), Objeto->getY());
            //Tablero->getMatrix()[x][y - 1] = boot1;
        }
    }

    if (!movimiento && y == 0)
    {
        if (Tablero->getMatrix()[x][y + 1]->toString() == " ")
        {
            movimiento = true;
            Objeto->setY(y + 1);
            Item *temp = Tablero->getMatrix()[x][y];
            Item *temp2 = Tablero->getMatrix()[Objeto->getX()][Objeto->getY()];
            Tablero->setMatrix(temp2, x, y);
            Tablero->setMatrix(temp, Objeto->getX(), Objeto->getY());
            //Tablero->getMatrix()[x][y +1] = boot1;
        }
    }
    else if (!movimiento && y + 1 <= 12)
    {
        if (Tablero->getMatrix()[x][y + 1]->toString() == " ")
        {
            movimiento = true;
            Objeto->setY(y + 1);
            Item *temp = Tablero->getMatrix()[x][y];
            Item *temp2 = Tablero->getMatrix()[Objeto->getX()][Objeto->getY()];
            Tablero->setMatrix(temp2, x, y);
            Tablero->setMatrix(temp, Objeto->getX(), Objeto->getY());
            //  Tablero->getMatrix()[x][y + 1] = boot1;
        }
    }
}

void Juego(string Nombre, string nombre_escenario, int Vidas)
{
    //Crear Jugador
    Tablero->getMatrix()[0][0] = jugador;
    //Meterlos en la Matriz
    Tablero->setMatrix(boot1, 10, 0);
    Tablero->setMatrix(boot2, 0, 12);
    Tablero->setMatrix(boot3, 10, 12);
    Tablero->setMatrix(boot4, 5, 6);

    int x, y;
    int cx = 0;
    int cy = 0;
    Tren *Temporal;
    getmaxyx(stdscr, y, x);
    move(y / 2, x / 2 - 18);
    int tecla;
    int direccion;
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(2));
    refresh();
    curs_set(0);
    vector<string> listapos;
    if (T_escenario==2)
    {//ES EL ESCENARIO DEL TREN
        Temporal = new Tren("PRUEBA");
        /*DERECHA */
        listapos.push_back("2-5");
        listapos.push_back("2-6");
        listapos.push_back("2-7");
        listapos.push_back("2-8");
        /*ABAJO*/
        listapos.push_back("3-8");
        listapos.push_back("4-8");
        listapos.push_back("5-8");
        listapos.push_back("6-8");
        listapos.push_back("7-8");
        /*IZQUIERDA*/
        listapos.push_back("7-7");
        listapos.push_back("7-6");
        listapos.push_back("7-5");
        listapos.push_back("7-4");
    }
    while (true)
    {
        mvprintw(0, 15, "-> Jugador: ");
        mvprintw(0, 24, Nombre.c_str());
        mvprintw(0, 34, "-> Escenario: ");
        mvprintw(0, 43, nombre_escenario.c_str());
        move(cy, cx);
        if (Vidas > 0)
        {
            mvprintw(0, 52, "-> Vidas <3 : %d", Vidas);
        }
        if (vida == 0)
        {
            /*Entonces te moriste we....*/
            break;
        }
        noecho();
        int cont = 0;
        if ((cx >= 0 && cy >= 0) && (cx <= 10 && cy <= 12))
        {
            for (int i = 0; i < 11; i++)
            {
                for (int j = 0; j < 13; j++)
                {
                    char it = Tablero->getMatrix()[i][j]->toString().at(0);
                    if (Tablero->getMatrix()[i][j]->toString() == "Q")
                    {
                        Normal *bomba;
                        bomba = dynamic_cast<Normal *>(Tablero->getMatrix()[i][j]);
                        bomba->setContador(bomba->getContador() - 1);
                        Tablero->getMatrix()[i][j]->toString();
                        int alcance = bomba->getAlcance();
                        refresh();
                        if (bomba->getContador() == 0)
                        {
                            if (i - alcance >= 0)
                                for (int k = 1; k <= alcance; k++)
                                {
                                    if (Tablero->getMatrix()[i - k][j]->toString() != "O")
                                        Tablero->setMatrix(new Item(0, i - k, j), i - k, j);
                                    else
                                        k = 100;
                                }
                            if (i + alcance <= 10)
                                for (int k = 1; k <= alcance; k++)
                                {
                                    if (Tablero->getMatrix()[i + k][j]->toString() != "O")
                                        Tablero->setMatrix(new Item(0, i + k, j), i + k, j);
                                    else
                                        k = 100;
                                }

                            if (j - alcance >= 0)
                                for (int k = 1; k <= alcance; k++)
                                {
                                    if (Tablero->getMatrix()[i][j - k]->toString() != "O")
                                        Tablero->setMatrix(new Item(0, i, j - k), i, j - k);
                                    else
                                        k = 100;
                                }

                            if (j + alcance <= 12)
                                for (int k = 1; k <= alcance; k++)
                                {
                                    if (Tablero->getMatrix()[i][j + k]->toString() != "O")
                                        Tablero->setMatrix(new Item(0, i, j + k), i, j + k);
                                    else
                                        k = 100;
                                }
                            Tablero->setMatrix(new Item(0, i, j), i, j);
                        }
                    }
                    move(i + 1, j + 1);
                    printw("%c", it);
                    if (Tablero->getMatrix()[i][j]->toString() == "*")
                    {
                        cont = cont + 1;
                    }
                }
            }
            if (cont == 0)
            {
                vida = vida - 1;
                Tablero->getMatrix()[cx][cy] = jugador;
            }
            refresh();
            tecla = getch();
            //ARRIBA
            if (tecla == 119)
            {
                direccion = 1;
            }
            //IZQUIERDA
            else if (tecla == 97)
            {
                direccion = 2;
            }
            //DERECHA
            else if (tecla == 100)
            {
                direccion = 3;
            }
            //ABAJO
            else if (tecla == 115)
            {
                direccion = 4;
            }
            //Crear Bomba
            else if ( tecla == 122)
            {
               // mvprintw(14, 14, "BOMBA");
                direccion = 5;
                
            }
            else
            {
                direccion = 0;
                
            }
                    echo();
                    if (direccion == 1)
                    {
                        if (cx - 1 >= 0)
                        {
                            if (Tablero->getMatrix()[cx - 1][cy]->toString() == " ")
                            {
                                Item *temp = Tablero->getMatrix()[cx][cy];
                                Item *temp2 = Tablero->getMatrix()[cx - 1][cy];
                                Tablero->setMatrix(temp2, cx, cy);
                                Tablero->setMatrix(temp, cx - 1, cy);
                                cx = cx - 1;
                                if(cx==2&&cy==4&&T_escenario==2){
                                    int x, y;
                                   
                                    if (Temporal != NULL)
                                    {
                                      //  mvprintw(14, 14, "entro!");
                                        Item *temp = new Item(5, 2, 4);
                                        for (int i = 0; i < listapos.size(); i++)
                                        {
                                            erase();
                                            x = getPX(listapos[i]);
                                            y = getPY(listapos[i]);
                                            Tablero->getMatrix()[x][y] = temp;
                                            for (int i = 0; i < 11; i++)
                                            {
                                                for (int j = 0; j < 13; j++)
                                                {
                                                    char it = Tablero->getMatrix()[i][j]->toString().at(0);
                                                    move(i + 1, j + 1);
                                                    printw("%c", it);
                                                    mvprintw(14, 20, "MOVIENDO EL CHUCU CHUCU !");
                                                }
                                                usleep(250000);
                                            }
                                            refresh();
                                        }
                                        erase();
                                    }
                                }
                            }
                        }
                    }
                    if (direccion == 2)
                    {
                        if (cy - 1 >= 0)
                        {
                            if (Tablero->getMatrix()[cx][cy - 1]->toString() == " ")
                            {
                                Item *temp = Tablero->getMatrix()[cx][cy];
                                Item *temp2 = Tablero->getMatrix()[cx][cy - 1];
                                Tablero->setMatrix(temp2, cx, cy);
                                Tablero->setMatrix(temp, cx, cy - 1);
                                //  mvprintw(5, 5, "moviendo");
                                moverbots(boot1);
                                cy = cy - 1;
                                if (cx == 2 && cy == 4 && T_escenario == 2)
                                {
                                    int x, y;
                                  
                                    if (Temporal != NULL)
                                    {
                                        //  mvprintw(14, 14, "entro!");
                                        Item *temp = new Item(5, 2, 4);
                                        for (int i = 0; i < listapos.size(); i++)
                                        {
                                            erase();
                                            x = getPX(listapos[i]);
                                            y = getPY(listapos[i]);
                                            Tablero->getMatrix()[x][y] = temp;
                                            for (int i = 0; i < 11; i++)
                                            {
                                                for (int j = 0; j < 13; j++)
                                                {
                                                    char it = Tablero->getMatrix()[i][j]->toString().at(0);
                                                    move(i + 1, j + 1);
                                                    printw("%c", it);
                                                    mvprintw(14, 20, "MOVIENDO EL CHUCU CHUCU !");
                                                }
                                                usleep(250000);
                                            }
                                            refresh();
                                        }
                                        erase();
                                    }
                                }
                            }
                        }
                    }
                    if (direccion == 3)
                    {
                        if (cy + 1 <= 12)
                        {
                            if (Tablero->getMatrix()[cx][cy + 1]->toString() == " ")
                            {
                                Item *temp = Tablero->getMatrix()[cx][cy];
                                Item *temp2 = Tablero->getMatrix()[cx][cy + 1];
                                Tablero->setMatrix(temp2, cx, cy);
                                Tablero->setMatrix(temp, cx, cy + 1);
                                // mvprintw(5, 5, "moviendo");
                                moverbots(boot1);
                                //moverbots(boot2);
                                /* moverbots(boot3);
                        moverbots(boot4);*/
                                cy = cy + 1;
                                if (cx == 2 && cy == 4 && T_escenario == 2)
                                {
                                    int x, y;
                                   
                                    if (Temporal != NULL)
                                    {
                                        //  mvprintw(14, 14, "entro!");
                                        Item *temp = new Item(5, 2, 4);
                                        for (int i = 0; i < listapos.size(); i++)
                                        {
                                            erase();
                                            x = getPX(listapos[i]);
                                            y = getPY(listapos[i]);
                                            Tablero->getMatrix()[x][y] = temp;
                                            for (int i = 0; i < 11; i++)
                                            {
                                                for (int j = 0; j < 13; j++)
                                                {
                                                    char it = Tablero->getMatrix()[i][j]->toString().at(0);
                                                    move(i + 1, j + 1);
                                                    printw("%c", it);
                                                    mvprintw(14, 20, "MOVIENDO EL CHUCU CHUCU !");
                                                }
                                                usleep(250000);
                                            }
                                            refresh();
                                        }
                                        erase();
                                    }
                                }
                            }
                        }
                    }
                    if (direccion == 4)
                    {
                        if (cx + 1 <= 10)
                        {
                            if (Tablero->getMatrix()[cx + 1][cy]->toString() == " ")
                            {
                                Item *temp = Tablero->getMatrix()[cx][cy];
                                Item *temp2 = Tablero->getMatrix()[cx + 1][cy];
                                Tablero->setMatrix(temp2, cx, cy);
                                Tablero->setMatrix(temp, cx + 1, cy);
        
                                cx = cx + 1;
                                if (cx == 2 && cy == 4 && T_escenario == 2)
                                {
                                    int x, y;
                                  
                                   

                                    if (Temporal != NULL)
                                    {
                                        //  mvprintw(14, 14, "entro!");
                                        Item *temp = new Item(5, 2, 4);
                                        for (int i = 0; i < listapos.size(); i++)
                                        {
                                            erase();
                                            x = getPX(listapos[i]);
                                            y = getPY(listapos[i]);
                                            Tablero->getMatrix()[x][y] = temp;
                                            for (int i = 0; i < 11; i++)
                                            {
                                                for (int j = 0; j < 13; j++)
                                                {
                                                    char it = Tablero->getMatrix()[i][j]->toString().at(0);
                                                    move(i + 1, j + 1);
                                                    printw("%c", it);
                                                    mvprintw(14, 20, "MOVIENDO EL CHUCU CHUCU !");
                                                }
                                                usleep(250000);
                                            }
                                            refresh();
                                        }
                                        erase();
                                    }
                                }
                            }
                        }
                    }
                    if (direccion == 5)
                    {
                        mvprintw(14, 20, "BOOMBA!");
                        crearBomba();
                        erase();
                    }
                }
            }
            attroff(COLOR_PAIR(2));
            move(y / 2, (x / 2 - 4));
            printw("Lo siento, ha perido....");
            refresh();
            usleep(1000000 / 2);
            curs_set(1);
        }

        void crearBomba()
        {

            for (int i = 0; i < 11; i++)
            {
                for (int j = 0; j < 13; j++)
                {
                    if (Tablero->getMatrix()[i][j]->toString() == "*")
                    {
                        if (j + 1 <= 12)
                        {
                            if (Tablero->getMatrix()[i][j + 1]->toString() == " ")
                            {
                                if (tipobomba == 1)
                                {
                                    Tablero->setMatrix(new Normal(1, i, j + 1, 4), i, j + 1);
                                }
                                if (tipobomba == 2)
                                {
                                    Tablero->setMatrix(new Espina(1, i, j + 1, 4, 0), i, j + 1);
                                }
                                if (tipobomba == 3)
                                {
                                    Tablero->setMatrix(new V(1, i, j + 1, 4), i, j + 1);
                                }
                                break;
                            }
                        }
                        if (i + 1 <= 10)
                        {
                            if (Tablero->getMatrix()[i + 1][j]->toString() == " ")
                            {
                                if (tipobomba == 1)
                                {
                                    Tablero->setMatrix(new Normal(1, i + 1, j, 4), i + 1, j);
                                }
                                if (tipobomba == 2)
                                {
                                    Tablero->setMatrix(new Espina(1, i + 1, j, 4, 0), i + 1, j);
                                }
                                if (tipobomba == 3)
                                {
                                    Tablero->setMatrix(new V(1, i + 1, j, 4), i + 1, j);
                                }
                                break;
                            }
                        }
                        if (j - 1 >= 0)
                        {
                            if (Tablero->getMatrix()[i][j - 1]->toString() == " ")
                            {
                                if (tipobomba == 1)
                                {
                                    Tablero->setMatrix(new Normal(1, i, j - 1, 4), i, j - 1);
                                }
                                if (tipobomba == 2)
                                {
                                    Tablero->setMatrix(new Espina(1, i, j - 1, 4, 0), i, j - 1);
                                }
                                if (tipobomba == 3)
                                {
                                    Tablero->setMatrix(new V(1, i, j - 1, 4), i, j - 1);
                                }
                                break;
                            }
                        }
                        if (i - 1 >= 0)
                        {
                            if (Tablero->getMatrix()[i - 1][j]->toString() == " ")
                            {
                                if (tipobomba == 1)
                                {
                                    Tablero->setMatrix(new Normal(1, i - 1, j, 4), i - 1, j);
                                }
                                if (tipobomba == 2)
                                {
                                    Tablero->setMatrix(new Espina(1, i - 1, j, 4, 0), i - 1, j);
                                }
                                if (tipobomba == 3)
                                {
                                    Tablero->setMatrix(new V(1, i - 1, j, 4), i - 1, j);
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
        int menu2()
        {
            erase();
            initscr();
            int x, y;
            getmaxyx(stdscr, y, x);
            move(0, (x / 2 - 18));
            if (has_colors())
            {
                start_color();
                init_pair(1, COLOR_WHITE, COLOR_BLACK);
                attron(COLOR_PAIR(1));
                printw("<< TIPO DE MENU >>");
                attroff(COLOR_PAIR(1));
                init_pair(2, COLOR_CYAN, COLOR_BLACK);
                attron(COLOR_PAIR(2));
                move(1, 0);
                printw("Seleccione el tipo de escenario en el que desea jugar :\n");
                move(2, 1);
                printw("1)Invisible. \n");
                move(3, 1);
                printw("2) Tren  \n");
                printw("Tipo de escenario seleccionado: ");
                attroff(COLOR_PAIR(2));
            }
            int cx = 0;
            int cy = 2;
            int tecla;
            move(cy, cx);
            refresh();
            while (true)
            {
                noecho();
                tecla = getch();
                if (tecla == 10)
                {
                    if (cy == 2)
                    {
                        return 1;
                    }
                    if (cy == 3)
                    {
                        return 2;
                    }
                }
                else
                {
                    //printw("%i",tecla);
                    if (tecla == 65 && cy > 2)
                    {
                        //printw(" arriba");
                        cy = cy - 1;
                        move(cy, cx);
                    }
                    else if (tecla == 66 && cy <= 4)
                    {
                        //printw(" abajo");
                        cy = cy + 1;
                        move(cy, cx);
                    }
                    else
                    {
                        //No hara nada
                    }
                }
                refresh();
            }
            echo();
            return 0;
        }

        int menu3()
        {
            erase();
            initscr();
            int x, y;
            getmaxyx(stdscr, y, x);
            move(0, (x / 2 - 18));
            if (has_colors())
            {
                start_color();
                init_pair(1, COLOR_WHITE, COLOR_BLACK);
                attron(COLOR_PAIR(1));
                printw("<< TIPO DE BOMBAS >>");
                attroff(COLOR_PAIR(1));
                init_pair(2, COLOR_CYAN, COLOR_BLACK);
                attron(COLOR_PAIR(2));
                move(1, 0);
                printw("Seleccione el tipo de Bomba que desea utilizar:\n");
                move(2, 1);
                printw("1)Bomba Normal. \n");
                move(3, 1);
                printw("2)Bomba Espina \n");
                move(4, 1);
                printw("3)Bomba V   \n");
                printw("Tipo de escenario seleccionado: ");
                attroff(COLOR_PAIR(2));
            }
            int cx = 0;
            int cy = 2;
            int tecla;
            move(cy, cx);
            refresh();
            while (true)
            {
                noecho();
                tecla = getch();
                if (tecla == 10)
                {
                    if (cy == 2)
                    {
                        return 1;
                    }
                    if (cy == 3)
                    {
                        return 2;
                    }
                    if (cy == 4)
                    {
                        return 3;
                    }
                }
                else
                {
                    //printw("%i",tecla);
                    if (tecla == 65 && cy > 2)
                    {
                        //printw(" arriba");
                        cy = cy - 1;
                        move(cy, cx);
                    }
                    else if (tecla == 66 && cy <= 4)
                    {
                        //printw(" abajo");
                        cy = cy + 1;
                        move(cy, cx);
                    }
                    else
                    {
                        //No hara nada
                    }
                }
                refresh();
            }
            echo();
            return 0;
        }

        string menunombre()
        {
            erase();
            initscr();
            cbreak();
            echo();
            string Nombre;
            int yMax, xMax;
            getmaxyx(stdscr, yMax, xMax);
            mvprintw(yMax / 2, 15, "Ingrese su nombre por favor: ");
            char ch = getch();
            stringstream ss;
            while (ch != '\n')
            {
                Nombre.push_back(ch);
                ss << ch;
                ch = getch();
            }
            move(1, 0);
            noecho();
            endwin();
            return Nombre;
        }

        string menunombre_escenario()
        {
            erase();
            initscr();
            cbreak();
            echo();
            string Nombre;
            int yMax, xMax;
            getmaxyx(stdscr, yMax, xMax);
            mvprintw(yMax / 2, 15, "Ingrese el nombre del escenario: ");
            char ch = getch();
            stringstream ss;
            while (ch != '\n')
            {
                Nombre.push_back(ch);
                ss << ch;
                ch = getch();
            }
            move(1, 0);
            noecho();
            endwin();
            return Nombre;
        }

        void movertren()
        {
            /*

            int x, y;
            mvprintw(14, 14, "MOVIENDO CHUCU CHUCU");
           
            if (Temporal != NULL)
            {
                mvprintw(14, 14, "entro!");
                Item *temp = new Item(5, 2, 4);
                for (int i = 0; i < listapos.size(); i++)
                {
                    erase();
                    x = getPX(listapos[i]);
                    y = getPY(listapos[i]);
                    Tablero->getMatrix()[x][y] = temp;
                    for (int i = 0; i < 11; i++)
                    {
                        for (int j = 0; j < 13; j++)
                        {
                            char it = Tablero->getMatrix()[i][j]->toString().at(0);
                            move(i + 1, j + 1);
                            printw("%c", it);
                        }
                        usleep(250000);
                    }
                    refresh();
                }
            }*/
        }

        int convertirNumero(char le)
        {
            int n = 0;

            if (le == '1')
            {
                n = 1;
            }
            else if (le == '2')
            {
                n = 2;
            }
            else if (le == '3')
            {
                n = 3;
            }
            else if (le == '4')
            {
                n = 4;
            }
            else if (le == '5')
            {
                n = 5;
            }
            else if (le == '6')
            {
                n = 6;
            }
            else if (le == '7')
            {
                n = 7;
            }
            if (le == '8')
            {
                n = 8;
            }
            else if (le == '9')
            {
                n = 9;
            }

            return n;

        } //Fin de la funcion convertir nuermeo

        int getPX(string palabra)
        {
            int x;
            x = convertirNumero(palabra[0]);
            return x;

        } //Fin getX

        int getPY(string palabra)
        {
            int y = 0;
            y = convertirNumero(palabra[2]);
            return y;
        }

        /*
boot1->Inteligenciaartificial(boot1->getX(), boot1->getY(), Tablero->getMatrix());
Tablero->getMatrix()[boot1->getX()][boot1->getY()];
int x = boot1->getX();
int y = boot1->getY();
bool movimiento = false;
if (x == 10)
{

    if (Tablero->getMatrix()[x - 1][boot1->getY()]->toString() == " ")
    {
        boot1->setX(x - 1);
        Tablero->getMatrix()[x - 1][boot1->getY()] = boot1;
        movimiento = true;
    }
}
else if (x == 0)
{
    if (Tablero->getMatrix()[x + 1][boot1->getY()]->toString() == " ")
    {
        boot1->setX(x + 1);
        Tablero->getMatrix()[x + 1][boot1->getY()] = boot1;
        movimiento = true;
    }
}
else if (x - 1 >= 0)
{
    if (Tablero->getMatrix()[x - 1][boot1->getY()]->toString() == " ")
    {
        boot1->setX(x - 1);
        Tablero->getMatrix()[x - 1][boot1->getY()] = boot1;
        movimiento = true;
    }
}
else if (x + 1 <= 10)
{
    if (Tablero->getMatrix()[x + 1][boot1->getY()]->toString() == " ")
    {

        boot1->setX(x + 1);
        Tablero->getMatrix()[x + 1][boot1->getY()] = boot1;
        movimiento = true;
    }
}
if (!movimiento)
{
    if (y == 12)
    {

        if (Tablero->getMatrix()[x][boot1->getY() - 1]->toString() == " ")
        {
            boot1->setY(y - 1);
            Tablero->getMatrix()[x][y - 1] = boot1;
        }
    }
    else if (y == 0)
    {
        if (Tablero->getMatrix()[x][boot1->getY() + 1]->toString() == " ")
        {
            boot1->setY(y + 1);
            Tablero->getMatrix()[x][y + 1] = boot1;
        }
    }
    else if (y - 1 >= 0)
    {
        if (Tablero->getMatrix()[x][boot1->getY() - 1]->toString() == " ")
        {
            boot1->setY(y - 1);
            Tablero->getMatrix()[x][y - 1] = boot1;
        }
    }
    else if (y + 1 <= 12)
    {
        if (Tablero->getMatrix()[x][boot1->getY() + 1]->toString() == " ")
        {
            boot1->setY(y + 1);
            Tablero->getMatrix()[x][y + 1] = boot1;
        }
    }
}
*/

        /* int bx = boot1->getX();
    int by = boot1->getY();
    boot1->Inteligenciaartificial(bx, by,Tablero->getMatrix());
    int b2x = boot2->getX();
    int b2y = boot2->getY();
    boot1->Inteligenciaartificial(bx, by, Tablero->getMatrix());
    int b3x = boot3->getX();
    int b3y = boot3->getY();
    boot1->Inteligenciaartificial(bx, by, Tablero->getMatrix());
    int b4x = boot4->getX();
    int b4y = boot4->getY();

    Tablero->setMatrix(boot1,boot1->getX(),boot1->getY());
    Tablero->setMatrix(boot2, boot2->getX(), boot2->getY());
    Tablero->setMatrix(boot3, boot3->getX(), boot3->getY());
    Tablero->setMatrix(boot4, boot4->getX(), boot4->getY());*/