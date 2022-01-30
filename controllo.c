#include "macro.h"

char sprite_astronave[RIGHE][COLONNE] = {{'+', '+', '+', ' ', ' ', ' '},
                                         {'+', '+', '+', '+', '+', '+'},
                                         {'+', '+', '+', ' ', ' ', ' '}};

char nemico_vuoto[RIGHE][COLONNE]={{"     "},{"     "},{"     "}};

char sprite_nemico[RIGHE][COLONNE] = {{'+', '+', '+', '+', '+'},
                                         {'+', '+', '+', '+', '+'},
                                         {'+', '+', '+', '+', '+'}};


void astronave (int pipeout)
{
    int c,n, i;
    pid_t missile;
    Object * array_nemici;
    Object astronave;
    astronave.pos.x = 1;
    astronave.pos.y = MAXY/2;
    astronave.id = ID_ASTRONAVE;

    // Comunico a check le coordinate di partenza di astronave
    write(pipeout,&astronave,sizeof(astronave));

    // Lettura dei tasti
    while (true)
    {
        switch (c = getch())
        {
            case KEY_UP:
                if(astronave.pos.y > 0)
                    astronave.pos.y -= 1;
                break;

            case KEY_DOWN:
                if (astronave.pos.y < MAXY - RIGHE)
                    astronave.pos.y += 1;
                break;

            case KEY_SPACE:
                creazioneMissili(pipeout, astronave.pos);
                break;
        }
        write(pipeout,&astronave,sizeof(astronave));
    }
}

void creazioneMissili(int pipeout, Coordinate astronave)
{
    Coordinate missile;
    //coordinate partenza missile
    missile.x = astronave.x + COLONNE;
    missile.y = astronave.y + 1;
    startMissileUp(pipeout, missile);
    startMissileDown(pipeout, missile);
}

void startMissileUp(int pipeout, Coordinate start)
{
    switch (fork())
    {
        case -1:
            perror("Errore nell'esecuzione della fork");
            _exit(1);

        case 0:
            missileUp(pipeout, start);
            break;
    }
}

void startMissileDown(int pipeout, Coordinate start)
{
    switch (fork())
    {
        case -1:
            perror("Errore nell'esecuzione della fork");
            _exit(1);

        case 0:
            missileDown(pipeout, start);
            break;
    }
}

void missileUp (int pipeout, Coordinate start)
{
    int i;
    Object missile;

    missile.pos = start;
    missile.pid = getpid();
    missile.vite = 1;
    missile.id = ID_MISSILE_UP;

    while (missile.pos.x < MAXX && missile.pos.y > 0)
    {
        missile.pos.x ++;
        //missile.pos.x = missile.pos.x + SHIFT_VERTICALE;
        //missile.pos.y --;
        usleep(MISSILE_DELAY);
        write(pipeout, &missile, sizeof(missile));


    }
    _exit(0);
}

void missileDown (int pipeout, Coordinate start)
{
    int i;
    Object missile;

    missile.pos = start;
    missile.pid = getpid();
    missile.vite = 1;
    missile.id = ID_MISSILE_DOWN;

    while (missile.pos.x < MAXX && missile.pos.y < MAXY)
    {
        missile.pos.x = missile.pos.x + SHIFT_VERTICALE;
        missile.pos.y ++;
        usleep(MISSILE_DELAY);
        write(pipeout, &missile, sizeof(missile));

    }
    _exit(0);
}

void check(int pipein)
{
    Object valore_letto, nemico,astronave, missileUp, missileDown;

    int i, k,n;

    do{
        read(pipein,&valore_letto,sizeof(valore_letto));

        switch (valore_letto.id)
        {
            case ID_ASTRONAVE:
                astronave.pos = valore_letto.pos;
                
                for (i = 0; i < RIGHE; i++)
                {
                    for (k = 0; k < COLONNE; k++) {
                        attron(COLOR_PAIR(ERASE_PAIR));
                        mvprintw(astronave.old_pos.y, astronave.old_pos.x, "%c", sprite_astronave[i][k]);
                        astronave.old_pos.x += 1;
                    }
                    astronave.old_pos.x = 1;
                    astronave.old_pos.y += 1;
                }
                astronave.old_pos.y -= RIGHE;

                for (i = 0; i < RIGHE; i++)
                {
                    for (k = 0; k < COLONNE; k++) {

                        attron(COLOR_PAIR(ASTRONAVE_PAIR));
                        mvprintw(astronave.pos.y, astronave.pos.x, "%c", sprite_astronave[i][k]);
                        astronave.pos.x += 1;
                    }
                    astronave.pos.x = 1;
                    astronave.pos.y += 1;
                }
                astronave.pos.y -= RIGHE;

                astronave.old_pos = astronave.pos;

                //mvprintw(0,25, "%d", valore_letto.pos.y);
                //mvprintw(1,25, "%d", valore_letto.pos.x);
                break;

            case ID_MISSILE_UP:
                /*
                mvprintw(valore_letto.old_pos.y, valore_letto.old_pos.x , "0");
                mvprintw(valore_letto.pos.y, valore_letto.pos.x, sprite_missile);
                mvprintw(0,70, "pos x:%d", valore_letto.pos.x);
                mvprintw(1,70, "pos y:%d", valore_letto.pos.y);
                mvprintw(0,80, "old x:%d", valore_letto.old_pos.x);
                mvprintw(1,80, "old y:%d", valore_letto.old_pos.y);


                mvprintw(missileUp.pos.y, missileUp.pos.x, " ");
                mvprintw(valore_letto.pos.y, valore_letto.pos.x, sprite_missile);
                missileUp = valore_letto;
                mvprintw(0,80, "Missile UP x:%d", valore_letto.pos.x);
                mvprintw(1,80, "Missile UP y:%d", valore_letto.pos.y);
                if (valore_letto.pos.x == MAXX || valore_letto.pos.y == 0)
                    mvprintw(missileUp.pos.y, missileUp.pos.x, " ");
                */
                break;

            case ID_MISSILE_DOWN:

                missileDown.pos = valore_letto.pos;

                mvprintw(missileDown.pos.y, missileDown.pos.x, "0");
                mvprintw(missileDown.pos.y, missileDown.pos.x, sprite_missile);


                mvprintw(0,30, "pos %d", missileDown.pos.x);
                mvprintw(1,30, "old %d", missileDown.old_pos.x);

                //if (valore_letto.pos.x == MAXX || valore_letto.pos.y == MAXY)
                  //mvprintw(missileDown.pos.y, missileDown.pos.x, " ");
                break;


            case ID_NEMICO:         
               
                    for(c=0;c<NUM_NEMICI;c++){
		                if(valore_letto.sprite>=c&&valore_letto.sprite<=c){
                           mvaddch(valore_letto.y, valore_letto.x, nemico_vuoto); 
                           mvaddch(valore_letto.y, valore_letto.x, nemici.sprite);
                           array_nemici[c]=valore_letto;
                        }
                    }       



	
                    if(valore_letto.vite==1){
			           //Cancello la vecchia posizione dell'alieno			
                       mvaddch(valore_letto.pos.y, valore_letto.pos.x, nemico_vuoto);
                       mvaddch(valore_letto.pos.y, valore_letto.pos.x, sprite_nemico);
		               nemico=valore_letto;
                    }
                    if(valore_letto.vite==0){
			           //Cancello la vecchia posizione dell'alieno			
                       mvaddch(valore_letto.pos.y, valore_letto.pos.x,nemico_vuoto);
		               nemico=valore_letto;
                    }
                
	    }
     
        


        refresh();
    } while (true);
}
