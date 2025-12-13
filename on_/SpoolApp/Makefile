# Makefile for UdpTesterApp

CC = g++
FLAGS  = -DSOMETHING

CCFLAGS = -O3 -Wall -fno-strict-aliasing -c $(INCLUDES) $(FLAGS)
LINKFLAGS = -lstdc++ -lpthread

# Paths
ESP_SRC_INCLUDE := ../../src/Include
LOCAL_INCLUDE := .
INCLUDES := -I$(LOCAL_INCLUDE) -I$(ESP_SRC_INCLUDE)

all: UdpTesterApp

APP_SRC = UdpTesterApp.cpp \
		Timer.cpp

APP_OBJ = UdpTesterApp.o \
		Timer.o

UdpTesterApp: $(APP_OBJ)
	$(CC) -o UdpTesterApp $(APP_OBJ) $(LINKFLAGS)

UdpTesterApp.o: UdpTesterApp.cpp UdpTesterApp.h $(ESP_SRC_INCLUDE)/Globals.h $(ESP_SRC_INCLUDE)/Timer.h
	$(CC) $(CCFLAGS) -o UdpTesterApp.o UdpTesterApp.cpp

Timer.o: $(ESP_SRC_INCLUDE)/Timer.cpp $(ESP_SRC_INCLUDE)/Timer.h $(ESP_SRC_INCLUDE)/Globals.h
	$(CC) $(CCFLAGS) -o Timer.o $(ESP_SRC_INCLUDE)/Timer.cpp

clean:
	@echo "[ CLEANING UP... ]"
	rm -f *.o
	rm -f UdpTesterApp
