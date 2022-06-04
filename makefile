.PHONY: all clean


all: main1 test_ao_client ao_client singleton pollServer clientReactor guard
main1: main1.o
	gcc main1.o -o main1 -lpthread
main1.o: main1.c
	gcc -c main1.c
singleton: singleton.o
	g++ singleton.o -o singleton
singleton.o: singleton.cpp
	g++ -c singleton.cpp
test_ao_client: test_ao_client.o
	gcc test_ao_client.o -o test_ao_client -lpthread
test_ao_client.o: test_ao_client.c
	gcc -c test_ao_client.c
ao_client: ao_client.o
	gcc ao_client.o -o ao_client -lpthread
ao_client.o: ao_client.c
	gcc -c ao_client.c
clientReactor: clientReactor.o
	g++ clientReactor.cpp -o clientReactor -lpthread
clientReactor.o: clientReactor.cpp
	g++ -c clientReactor.cpp
pollServer: pollServer.o 
	g++ pollServer.cpp reactor.cpp -o pollServer -pthread -lpthread 
pollServer.o: pollServer.cpp
	g++ -c pollServer.cpp
guard: guard.o
	g++ guard.o -o guard -lpthread
guard.o: guard.cpp
	g++ -c guard.cpp




clean :
	rm -f *.o main1 guard singleton pollServer clientReactor ao_client test_ao_client