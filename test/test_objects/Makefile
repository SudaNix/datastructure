
student: main.o
	g++ main.o student.o profile.o -o student

main.o: main.cpp student.o profile.o
	g++ -c main.cpp

student.o: student.h student.cpp profile.o
	g++ -c student.cpp

profile.o: profile.cpp profile.h
	g++ -c profile.cpp

clean:
	rm -f *.o student
