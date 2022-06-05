.PHONY: all clean


all: main1 clientAoTest ClientAo singleton pollServer reacClient guard
main1: main1.o
	gcc main1.o -o main1 -lpthread
main1.o: main1.c
	gcc -c main1.c
singleton: singleton.o
	g++ singleton.o -o singleton
singleton.o: singleton.cpp
	g++ -c singleton.cpp
clientAoTest: clientAoTest.o
	gcc clientAoTest.o -o clientAoTest -lpthread
clientAoTest.o: clientAoTest.c
	gcc -c clientAoTest.c
ClientAo: ClientAo.o
	gcc ClientAo.o -o ClientAo -lpthread
ClientAo.o: ClientAo.c
	gcc -c ClientAo.c
reacClient: reacClient.o
	g++ reacClient.cpp -o reacClient -lpthread
reacClient.o: reacClient.cpp
	g++ -c reacClient.cpp
pollServer: pollServer.o 
	g++ pollServer.cpp reactor.cpp -o pollServer -pthread -lpthread 
pollServer.o: pollServer.cpp
	g++ -c pollServer.cpp
guard: guard.o
	g++ guard.o -o guard -lpthread
guard.o: guard.cpp
	g++ -c guard.cpp




clean :
	rm -f *.o main1 guard singleton pollServer reacClient ClientAo clientAoTest