CC = gcc
FLAG = -pedantic -O3 -Wno-unused-result
minilaska: find.o game_engine.o recursive.o shift.o vector.o board.o main.o
	$(CC) $(FLAG) -o minilaska main.o find.o game_engine.o recursive.o shift.o vector.o board.o
	make clean

find.o:find.c find.h
	$(CC) $(FLAG) -c find.c

game_engine.o : game_engine.c game_engine.h
	$(CC) $(FLAG) -c game_engine.c

recursive.o: recursive.c recursive.h
	$(CC) $(FLAG) -c recursive.c

shift.o: shift.c shift.h
	$(CC) $(FLAG) -c shift.c

vector.o:vector.c vector.h
	$(CC) $(FLAG) -c vector.c

board.o:board.c board.h
	$(CC) $(FLAG) -c board.c

main.o:main.c
	$(CC) $(FLAG) -c main.c

clean:
	rm *.o