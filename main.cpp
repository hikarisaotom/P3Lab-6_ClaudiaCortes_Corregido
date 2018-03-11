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
/*Variables globales*/
int e;
Jugador *jugador;
Escenario *Tablero = NULL;
int vida = 1 + rand() % (3 - 1);
Jugador *boot1 = NULL;
Jugador *boot2 = NULL;
Jugador *boot3 = NULL;
Jugador *boot4 = NULL;
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
        tipobomba = menu3();
        string Nombre = menunombre();
        string nombre_escenario = menunombre_escenario();
        jugador = new Jugador(2, Nombre, true, 1, 0, 0);
        boot1= new Jugador(2, "Boot1", 1, 2, 10, 0);
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
        printw("Espere mientras cargamos los elementos :D ");
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

void Juego(string Nombre, string nombre_escenario, int Vidas)
{
    //Crear Jugador
    Tablero->getMatrix()[0][0] = jugador;
    //Meterlos en la Matriz
    Tablero->setMatrix(boot1
, 10, 0);
    Tablero->setMatrix(boot2, 0, 12);
    Tablero->setMatrix(boot3, 10, 12);
    Tablero->setMatrix(boot4, 5, 6);

    int x, y;
    int cx = 0;
    int cy = 0;
    getmaxyx(stdscr, y, x);
    move(y / 2, x / 2 - 18);
    int tecla;
    int direccion;
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(2));
    refresh();
    curs_set(0);
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
                    if (Tablero->getMatrix()[i][j]->toString() == "8")
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
            else if (tecla == 109)
            {
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
                        cy = cy - 1;
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
                        cy = cy + 1;
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
                    }
                }
            }
            if (direccion == 5)
            {
                crearBomba();
            }
        }
    }
    attroff(COLOR_PAIR(2));
    move(y / 2, (x / 2 - 4));
    printw("Perdió!!");
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
            if (Tablero->getMatrix()[i][j]->toString() == "8")
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
