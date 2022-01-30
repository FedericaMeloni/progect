#ifndef SPACE_DEFENDER_MACRO_H
#define SPACE_DEFENDER_MACRO_H

#include <stdio.h>
#include <curses.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>


//MACRO colori
#define ERASE_PAIR 2
#define ASTRONAVE_PAIR 3

#define KEY_SPACE ' '

#define MAXX 80
#define MAXY 25
#define RIGHE 3
#define COLONNE 6
//int MAXY = 24;
//int MAXX = 80;


//macro nemici
#define NUM_NEMICI 12
#define NUM_NEMICI_COLONNA 6
#define SPESSORE_NEMICO 5
#define ALTEZZA_NEMICO 3
      

#define ID_ASTRONAVE 'A'
#define ID_MISSILE_UP 'U'
#define ID_MISSILE_DOWN 'D'
#define ID_NEMICO 'N'


#define MISSILE_DELAY 1000000 // Ritardo velocità missili
#define SHIFT_VERTICALE 5

// Struttura che rappresenta un posizione
typedef struct {
    int x;
    int y;
} Coordinate;

typedef struct {
    int type;               // Identificatore dell'entità che invia i dati
    Coordinate pos;         // Posizione attuale dell'oggetto
    Coordinate old_pos;     // Posizione precedente dell'oggetto
    pid_t pid;              // Pid del processo proprietario
    int vite;               // Vita dell'oggetto
    char id;                 // Id dell'oggetto
} Object;

#define sprite_missile "-"

void astronave(int pipeout);
void creazioneMissili(int pipeout, Coordinate astronave);
void startMissileUp(int pipeout, Coordinate start);
void startMissileDown(int pipeout, Coordinate start);
void missileUp (int pipeout, Coordinate start);
void missileDown (int pipeout, Coordinate start);
void check(int pipein);

void startMissile(int pipeout, Coordinate start, char id);

void nemico(int pipeout, int x, int y, int n);

#endif //SPACE_DEFENDER_MACRO_H
