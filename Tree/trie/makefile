CC = g++

DEP = dictionary.h
OBJ = dictionary.o Main.o

dictionary.o : dictionary.cpp $(DEP) 
	$(CC) -c dictionary.cpp
Main.o : Main.cpp $(DEP)
	$(CC) -c Main.cpp

Dictionary : $(OBJ)
	$(CC) -o Dictionary $(OBJ)


