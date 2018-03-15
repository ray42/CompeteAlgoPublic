# Automatically generated Makefile

CC = g++ -std=c++1z
CFLAGS = -c -g -DDEBUG -W -Wextra -Wall -Weffc++ -pedantic
LDFLAGS = 

P1_BASE = rrrMain
P2_BASE = test

COMMON_SOURCES =  

P1_SOURCES = $(P1_BASE).cpp
P2_SOURCES = $(P2_BASE).cpp

COMMON_OBJECTS = $(COMMON_SOURCES:.cpp=.o)
P1_OBJECTS = $(P1_SOURCES:.cpp=.o)
P2_OBJECTS = $(P2_SOURCES:.cpp=.o)

P1_EXECUTABLE = $(P1_BASE)
P2_EXECUTABLE = $(P2_BASE)

.PHONY: all

all: $(P1_EXECUTABLE) $(P2_EXECUTABLE)

P1: $(P1_EXECUTABLE)

P2: $(P2_EXECUTABLE)

$(P1_EXECUTABLE): $(COMMON_OBJECTS) $(P1_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

$(P2_EXECUTABLE): $(COMMON_OBJECTS) $(P2_OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@



.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(P1_EXECUTABLE) $(P2_EXECUTABLE)
