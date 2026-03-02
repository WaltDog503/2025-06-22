CC = g++
CPPFLAGS = -std=c++11 -g -Wall

main: main.o date.o item.o itemList.o
	$(CC) $(CPPFLAGS) -o main main.o date.o item.o itemList.o

main.o: main.cpp main.h date.h item.h itemList.h
	$(CC) $(CPPFLAGS) -c main.cpp

itemList.o: itemList.cpp itemList.h item.h date.h
	$(CC) $(CPPFLAGS) -c itemList.cpp

item.o: item.cpp item.h date.h
	$(CC) $(CPPFLAGS) -c item.cpp

date.o: date.cpp date.h
	$(CC) $(CPPFLAGS) -c date.cpp

clean:
	rm -f *.o main
