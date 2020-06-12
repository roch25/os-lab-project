./run : main.o process.o scheduling.o
	gcc -o process main.o process.o scheduling.o
main.o: main.c process.h scheduling.h
	gcc -c main.c
process.o: process.c process.h
	gcc -c process.c
scheduling.o: scheduling.c scheduling.h
	gcc -c scheduling.c
