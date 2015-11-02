CC=g++

zadanie1.o: zadanie1.cpp
	$(CC) zadanie1.cpp -g -lrt -pthread
