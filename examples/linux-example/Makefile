CC=gcc

CFLAGS=-Wall -pedantic -I ../../src -pthread

TARGET=timer_demo

all: $(TARGET)

$(TARGET):
	$(CC) $(CFLAGS) -c main.c
	$(CC) $(CFLAGS) -c ../../src/timer_software.c
	$(CC) $(CFLAGS) -o $(TARGET) main.o timer_software.o

clean:
	$(RM) $(TARGET) main.o timer_software.o
