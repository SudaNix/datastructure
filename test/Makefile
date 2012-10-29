CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
EXE_FILES := $(addprefix bin/,$(notdir $(CPP_FILES:.cpp=.out)))
LD_FLAGS := -L../lib/ -lds -lboost_unit_test_framework
CC_FLAGS := -Wall

all: $(EXE_FILES)

bin/%.out: obj/%.o 
	g++ $^ src/test_objects/student.o src/test_objects/profile.o -o $@ $(LD_FLAGS) 

obj/%.o: src/%.cpp
	g++ $(CC_FLAGS) -c -o $@ $<

clean:
	rm -f obj/*.o bin/*.out
