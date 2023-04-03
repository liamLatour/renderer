CC = g++
CFLAGS = -Wall -g
CUDAARGS = -L/usr/local/cuda/lib64 -lcudart

SFMLARGS = -lsfml-graphics -lsfml-window -lsfml-system

start: main
	./main

main: host.o device.o
	$(CC) $(CFLAGS) -o main host.o device.o $(CUDAARGS) $(SFMLARGS)

host.o: host.cpp
	$(CC) $(CFLAGS) -O2 -c host.cpp -I/usr/local/cuda/include/

device.o: device.cu
	nvcc -O2 -c device.cu

clean:
	rm -f *.o

