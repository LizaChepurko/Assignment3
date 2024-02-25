.PHONY = all clean 

all: StrList

StrList: Main.o StrList.o StrList.h 
	gcc -Wall -g Main.o StrList.o -o StrList

Main.o: Main.c StrList.h
	gcc -Wall -g -c Main.c

StrList.o: StrList.c StrList.h
	gcc -Wall -g -c StrList.c

clean:
	rm -f *.o *.a StrList
