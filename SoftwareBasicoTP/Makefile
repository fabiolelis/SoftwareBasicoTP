all: SB
SB: decoder.o main.o
	gcc -o SB decoder.o main.o
decoder.o: decoder.h
	gcc -o decoder.o -c decoder.h -W -Wall -ansi
main.o: main.c decoder.h
	gcc -o main.o -c main.c -W -Wall -ansi
clean:
	rm -rf *.o
mrproper: clean
	rm -rf SB
