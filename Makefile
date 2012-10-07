SHELL = /bin/sh
CXX = g++
CFLAGSXX = -fPIC -Wall
LDFALGS = -shared
TARGET = lib/libds.so.1.0

SOURCES = $(shell echo src/*.cpp)
HEADERS = $(shell echo include/*.h)
OBJECTS = $(SOURCES:.cpp=.o)

all: 
	g++ -Wall -fPIC -c -ggdb src/dynamicarray.cpp -o obj/dynamicarray.o
	g++ -shared -ggdb -Wl,-soname,libds.so.1 obj/dynamicarray.o -o lib/libds.so.1.0
	ln -sf lib/libds.so.1.0 libds.so.1
	ln -sf libds.so.1 libds.so

$(TARGET): $(OBJECTS)
	$(CXX) $(CFLAGSXX) $(LDFALGS) -o $(TARGET) $(OBJECTS)

lib/libds.so: lib/libds.so.1.0
	ln -sf lib/libds.so.1 lib/libds.so

lib/libds.so.1: lib/libds.so.1.0
	ln -sf lib/libds.so.1.0 lib/libds.so.1

clean:
	rm -f lib/* obj/*
