# Makefile for UdpTesterApp

CC = g++
FLAGS  = -DSOMETHING

INCLUDES = -I. -IInclude

CCFLAGS = -O3 -Wall -fno-strict-aliasing -c $(INCLUDES) $(FLAGS)
LINKFLAGS = -lstdc++ -lpthread

all: UdpTesterApp

APP_SRC = UdpTesterApp.cpp \
		Timer.cpp

APP_OBJ = UdpTesterApp.o \
		Timer.o

UdpTesterApp: $(APP_OBJ)
	$(CC) -o UdpTesterApp $(APP_OBJ) $(LINKFLAGS)

UdpTesterApp.o: UdpTesterApp.cpp UdpTesterApp.h Include/Globals.h Include/Timer.h
	$(CC) $(CCFLAGS) -o UdpTesterApp.o UdpTesterApp.cpp

Timer.o: Include/Timer.cpp Include/Timer.h Include/Globals.h
	$(CC) $(CCFLAGS) -o Timer.o Include/Timer.cpp

clean:
	@echo "[ CLEANING UP... ]"
	rm -f *.o
	rm -f UdpTesterApp
