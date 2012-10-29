SHELL = /bin/sh
CXX = g++
CFLAGSXX = -fPIC -Wall
LDFALGS = -shared
TARGET = lib/libds.so.1.0

SOURCES = $(shell echo src/*.cpp)
HEADERS = $(shell echo include/*.h)
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET) 

# FIXME: rewrite target and dependencies.

$(TARGET): 
	g++ -Wall -fPIC -c -ggdb src/dynamicarray.cpp -o obj/dynamicarray.o
	g++ -Wall -fPIC -c -ggdb src/singlelinkedlist.cpp -o obj/singlelinkedlist.o
	g++ -shared -ggdb -Wl,-soname,libds.so.1 obj/dynamicarray.o obj/singlelinkedlist.o -o lib/libds.so.1.0
	cd lib/; ln -sf libds.so.1.0 libds.so.1
	cd lib/; ln -sf libds.so.1 libds.so
	cd test/; make
	cd example/dynamicarray/; make


clean:
	rm -f lib/* obj/*
	cd test/; make clean
	cd example/dynamicarray/; make clean
