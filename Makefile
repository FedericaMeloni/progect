OUTPUT = SpaceDefender
SORGENTI = main.o controllo.o nemici.o 
LIBRERIE = -lncurses

SpaceDefender: $(SORGENTI)
	gcc -o $(OUTPUT) $(SORGENTI) $(LIBRERIE)
	
main.o: main.c macro.h 
	gcc -c -o main.o main.c 

controllo.o: controllo.c macro.h
	gcc -c -o controllo.o controllo.c

nemici.o: nemici.c  macro.h
	gcc -c -o nemici.o nemici.c 
	
clean:
	rm *.o $(OUTPUT)
