main: main.o	query.o	 customers_db.o	
	gcc main.o	query.o customers_db.o -o main
main.o: main.c
	gcc -Wall -c main.c
query.o:	query.c	query.h
	gcc -Wall -c query.c
customers_db.o: customers_db.c customers_db.h
	gcc -Wall -c customers_db.c
clean:
	@rm -f *.o main