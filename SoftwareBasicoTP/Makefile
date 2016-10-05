all: SB
SB: main.o
	gcc -o SB main.o
main.o: main.c Decoder.h
	gcc -o main.o -c main.c -W -Wall -ansi
clean:
	rm -rf *.o
mrproper: clean
	rm -rf SB
