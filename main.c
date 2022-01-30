#include "macro.h"


int arrayMissili[5];

int main()
{
    int pipe_check[2];   //Descrittori pipe
    pid_t pidAst;

    initscr();				// Inizializza schermo di output
    noecho();				// Imposta modalità della tastiera
    curs_set(0); 	        // Nasconde il cursore
    keypad(stdscr,1);       // Attivo la gestione dei tasti speciali
    cbreak();			    // Disattiva l'input stdin bufferizzato

    start_color();
    init_pair(1,COLOR_BLACK,COLOR_BLACK);
    init_pair(ERASE_PAIR,COLOR_BLACK,COLOR_BLACK);
    init_pair(ASTRONAVE_PAIR,COLOR_YELLOW,COLOR_BLACK);
    bkgd(COLOR_PAIR(1));

    
    int n,pid_nemico; 
    int c=0; //contatore per capire quando passare alla prossima colonna
    int h=ALTEZZA_NEMICO; //posizione del nemico all'interno di una colonna
    int s=MAXX-SPESSORE_NEMICO; //posizione del nemico all'interno della riga 

    if(pipe(pipe_check) == -1)
    {
        perror("Errore nella creazione della pipe!");
        _exit(1);
    }

    switch (pidAst = fork())
    {
        case -1:
            perror("Errore nell'esecuzione della fork.");
            exit(1);

        case 0:
            close(pipe_check[0]);
            astronave(pipe_check[1]);

        default:
         
           /* Generazione nemici*/
           for(n=0; n<NUM_NEMICI; n++){

                pid_nemico=fork();
	    	   
                switch(pid_nemico){
			    case -1:
				   perror("Errore nell\'esecuzione della pipe!\n");
				   _exit(1);
			    case 0:
				   //Chiusura descrittore di lettura
				   close(pipe_check[0]); 
				   //Il secondo processo figlio invoca la funzione NEMICO
				   nemico(pipe_check[1], s, h, n);
                   c++; //il sesto nemico ovvero quello in posizione 5 è l'ultimo della colonna
				   exit(0);
		         
		        }
               h=h+ALTEZZA_NEMICO*2;
               if(c==5){
                 c=0; 
                 s=s-SPESSORE_NEMICO*2;
               }
           }
    }


	
    close(pipe_check[1]); //chiusura del descrittore di scrittura
    check(pipe_check[0]); // il processo padre invoca la funzione di controllo
    

    kill(pid_nemico, 1);
    kill(pidAst,1);

    endwin();
    return 0;
}
