main: main.o customers_db.o
	gcc main.o customers_db.o -o main

main.o: main.c
	gcc -Wall -c main.c

customers_db.o: customers_db.c customers_db.h
	gcc -Wall -c customers_db.c

clean:
	@rm -f *.o main