#include <ncurses.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <cstdlib>
#include <pthread.h>
#include <typeinfo>
/*CLASES*/
#include "Bombas.h"
#include "Normal.h"
#include "Espina.h"
#include "Jugador.h"
#include "V.h"
#include "Item.h"
#include "Escenario.h"
#include "Tren.h"
#include "Invisible.h"
using namespace std;
void salir();
int menu();
int menu2();
int menu3();
string menunombre();
string menunombre_escenario();
void movimiento();
void Juego(string, string, int);
int kbhit(void);
void Cargando();
Escenario *Tablero;
Jugador *player;
Jugador *boot1;
Jugador *boot2;
Jugador *boot3;
Jugador *boot4;
int main(void)
{

    int opcion = menu();
    int escenario;
    int bomba;

    switch (opcion)
    {
    case 1:
    {
        escenario = menu2();
        bomba = menu3();
        string nombre = menunombre();
        string nombre_escenario = menunombre_escenario();
        player = new Jugador(nombre, " * ", true, 1);
        boot1 = new Jugador("Boot1", " Y ", true, 2);
        boot2 = new Jugador("Boot2", " 0 ", true, 2);
        boot3 = new Jugador("Boot3", " X ", true, 2);
        boot4 = new Jugador("Boot4", " Y", true, 2);
        int Vidas = 1 + rand() % (3 - 1);
        if (escenario == 1)
        {
            Tablero = new Invisible(Vidas, bomba, bomba, nombre_escenario);
        }
        else
        {
            Tablero = new Tren(nombre_escenario, 1 + rand() % (3 - 1));
        }
       // Cargando();
        boot1->setX(10);boot1->setY(0);
        boot2->setX(0);boot2->setY(12);
        boot3->setX(10);boot3->setY(12);
        Tablero->setposicion(0, 0, player);//*
        Tablero->setposicion(10,0, boot1); //Y
        Tablero->setposicion(0, 12, boot2);//x
        Tablero->setposicion(10,12,boot3);
        player->setX(0);
        player->setY(0);
        /*boots */
     
        if (escenario == 1)
        {
            Juego(nombre, nombre_escenario, Vidas);
        }
        else
        {
            Juego(nombre, nombre_escenario, -1);
        }
        break;
    }
    case 2:
    { //Salir.
        salir();
        break;
    }
    } //Fin del switch
}

void Juego(string Nombre, string nombre_escenario, int Vidas)
{
    erase();
    //Crear Jugadores bot
    Jugador *botplayer1 = new Jugador( "Boot1","-",true,1);
    Jugador *botplayer2 = new Jugador("boot2","-", true, 1);
    Jugador *botplayer3 = new Jugador("Boot3", "-", true, 1);
    Tablero->getMatrix()[0][0] = player;
    Tablero->getMatrix()[botplayer1->getX()][botplayer1->getY()] = botplayer1;
    Tablero->getMatrix()[botplayer2->getX()][botplayer2->getY()] = botplayer2;
    Tablero->getMatrix()[botplayer3->getX()][botplayer3->getY()] = botplayer3;
   // string player = player->toString();
    char ser = 'x';
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
       /* printw("%c", 'h');
        printw("%c", 'x');*/
        noecho();
        if ((cx >= 0 && cy >= 0) && (cx <= 10 && cy <= 12))
        {
            mvprintw(0, 15, "Jugador: ");
            mvprintw(0, 24, Nombre.c_str());
            mvprintw(0, 34, "Escenario: ");
            mvprintw(0, 43, nombre_escenario.c_str());
            move(cy, cx);
            if (Vidas > 0)
            {
                //mvprintw(0, 52,"Vidas <3: ");
                mvprintw(0, 52, "VIdas <3 : %d", Vidas);
            }
            for (int i = 0; i < 11; i++)
            {
                for (int j = 0; j < 13; j++)
                {
                    char it = Tablero->getMatrix()[i][j]->toString().at(0);
                    move(i + 1, j + 1);
                    printw(Tablero->getMatrix()[i][j]->toString().c_str());
                }
            }

            refresh();
            tecla = getch();
            //ARRIBA
            if (tecla == 119)
            {
                direccion = 1;
            }
            //IZQUIERDA
            if (tecla == 97)
            {
                direccion = 2;
            }
            //DERECHA
            if (tecla == 100)
            {
                direccion = 3;
            }
            //ABAJO
            if (tecla == 115)
            {
                direccion = 4;
            }
            else
            {
            }
            echo();
            if (direccion == 1)
            {
                if (cx - 1 >= 0)
                {
                    if (Tablero->getMatrix()[cx - 1][cy]->toString() == " ")
                    {
                        Item *temp = Tablero->getelemento(cx,cy);
                        Item *temp2 = Tablero->getelemento(cx-1, cy);
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
                        Item *temp = Tablero->getelemento(cx, cy);
                        Item *temp2 = Tablero->getelemento(cx, cy-1);
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
                        Item *temp = Tablero->getelemento(cx, cy);
                        Item *temp2 = Tablero->getelemento(cx , cy+1);
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
                        Item *temp = Tablero->getelemento(cx, cy);
                        Item *temp2 = Tablero->getelemento(cx + 1, cy);
                        Tablero->setMatrix(temp2, cx, cy);
                        Tablero -> setMatrix(temp, cx + 1, cy);
                        cx = cx + 1;
                    }
                }
            }
        }
        else
        {
            break;
        }
    }
    attroff(COLOR_PAIR(2));
    move(y / 2, (x / 2 - 4));
    refresh();
    curs_set(1);

}//fin del metodo

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

int kbhit(void)
{
    struct timeval timeout;
    fd_set readfds;
    int how;

    /* look only at stdin (fd = 0) */
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);

    /* poll: return immediately */
    timeout.tv_sec = 0L;
    timeout.tv_usec = 0L;

    how = select(1, &readfds, (fd_set *)NULL, (fd_set *)NULL, &timeout);
    /* Change "&timeout" above to "(struct timeval *)0"       ^^^^^^^^
         * if you want to wait until a key is hit
         */

    if ((how > 0) && FD_ISSET(0, &readfds))
        return 1;
    else
        return 0;
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
/*  while (true)
    {
        
      //  if (kbhit())
       // {
            tecla = getch();
            //ARRIBA
            if (tecla == 119)
            {
                direccion = 1;
            }
            //IZQUIERDA
            if (tecla == 97)
            {
                direccion = 2;
            }
            //DERECHA
            if (tecla == 100)
            {
                direccion = 3;
            }
            //ABAJO
            if (tecla == 115)
            {
                direccion = 4;
            }
      //  }
        if ((cx > 0 && cy > 0) && (cx < x && cy < y))
        {
           mvprintw(0,30,"Jugador: ");
           mvprintw(0, 39,Nombre.c_str());
           move(cy, cx);
           printw("*");

           refresh();
           usleep(1000000 / 5);
           if (direccion == 1)
           {
               cy = cy - 1;
               move(cy + 1, cx);
               printw(" ");
               refresh();
            }
            if (direccion == 2)
            {
                cx = cx - 1;
                move(cy, cx + 1);
                printw(" ");
                refresh();
            }
            if (direccion == 3)
            {
                cx = cx + 1;
                move(cy, cx - 1);
                printw(" ");
                refresh();
            }
            if (direccion == 4)
            {
                cy = cy + 1;
                move(cy - 1, cx);
                printw(" ");
                refresh();
            }
        }
        else
        {
            break;
        }
    }*/
/*for (int i = 0; i < 11; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                Item *Objeto = Tablero->getelemento(i, j);
               
                if (Objeto!=NULL)
                {
                    if (typeid(*Objeto) == typeid(Jugador))
                    {
                        Jugador *actual = dynamic_cast<Jugador *>(Objeto);

                        if (actual != NULL)
                        {
                            move(j + 1, x + 1);
                            printw(actual->toString().c_str());
                        }
                    }
                }else{
                    printw("    ");
                    }//FIN DEL IF DE VER SI ESTA NULO 
            }
        }*/

/* mvprintw(0, 15, "Jugador: ");
            mvprintw(0, 24, Nombre.c_str());
            mvprintw(0, 34, "Escenario: ");
            mvprintw(0, 43, nombre_escenario.c_str());
            move(cy, cx);
            if (Vidas > 0)
            {
                //mvprintw(0, 52,"Vidas <3: ");
                mvprintw(0, 52, "VIdas <3 : %d", Vidas);
            }*/