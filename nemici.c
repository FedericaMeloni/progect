
#include "macro.h"


void nemico(int pipeout, int x, int y, int n){


	//Pid processo figlio bomba e processo padre nave
	int pid_missile_alieno;
	
	int spostamentox; 	//Spostamento orizzontale
	int spostamentoy=-1; 	//Spostamento verticale
	int direzione=-1; 

	//Impostazione valori di partenza dell'alieno
	Object* array_nemici;
	Object nemico, old_nemico;
	nemico.pos.x=x; 
	nemico.pos.y=y;
	nemico.vite=2;
	nemico.pid=getpid();

	array_nemici[n]=nemico;

    
	int movimento_sin_2volte;
	write(pipeout, &array_nemici, sizeof(array_nemici));

	
	while(nemico.vite>0){
		//Se gli alieni si muovono verso sinistra 2 volte smettono di farlo e tornano a muoversi verticalmente
		movimento_sin_2volte=2;

		if(movimento_sin_2volte!=0){
			spostamentox=0; 
			movimento_sin_2volte--; 
			if(direzione==1){spostamentoy=+1;}
			if(direzione==-1){spostamentoy=-1;}
		}

		/* Se supero l'area Y schermo inizo il movimento a destra e inverto la direzione y */
		if (nemico.pos.y + spostamentoy < 4 || nemico.pos.y + spostamentoy > MAXY-2){
			spostamentoy=0;
			spostamentox=-10;
			direzione=-direzione;
		}
		
		nemico.pos.x+=spostamentox;
		nemico.pos.y+=spostamentoy;

		/* Inserisco una pausa per rallentare il movimento */
		usleep(320000);

		if(nemico.pos.x<0){ //se il nemico raggiunge la fine dello schermo
			nemico.vite=0;
		}	



		/* Comunico le coordinate correnti al processo padre */
		write(pipeout, &array_nemici, sizeof(array_nemici));
	}
        exit(0);
};




