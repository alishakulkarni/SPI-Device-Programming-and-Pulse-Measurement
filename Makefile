IOT_HOME = /opt/iot-devkit/1.7.2/sysroots
PWD:= $(shell pwd)

KDIR:=$(IOT_HOME)/i586-poky-linux/usr/src/kernel
PATH := $(PATH):$(IOT_HOME)/x86_64-pokysdk-linux/usr/bin/i586-poky-linux

ARCH = x86
CROSS_COMPILE = i586-poky-linux-
SROOT=$(IOT_HOME)/i586-poky-linux/
CC=i586-poky-linux-gcc
CFLAGS= -Wall -pthread

all: main.o Display.o IOinit.o Ultrasound.o
	$(CC) $(CFLAGS) -o main main.o Display.o IOinit.o Ultrasound.o
	$(CC) $(CFLAGS) -o unexport Unexport.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

Display.o: Display.c Display.h
	$(CC) $(CFLAGS) -c Display.c

IOinit.o: IOinit.c IOinit.h
	$(CC) $(CFLAGS) -c IOinit.c

Ultrasound.o: Ultrasound.c Ultrasound.h
	$(CC) $(CFLAGS) -c Ultrasound.c
	
clean:
	rm -f *.o
	rm -f main
	rm -f unexport
