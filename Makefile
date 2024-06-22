CC = g++
CFLAGS = -Wfatal-errors -Wc++11-extensions -Wall -g

main: main.o rubiks_cube.o
	$(CC) $(CFLAGS) -o main main.o rubiks_cube.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp rubiks_cube.cpp

rubiks_cube.o: rubiks_cube.cpp
	$(CC) $(CFLAGS) -c rubiks_cube.cpp

clean:
	$(RM) main main.o rubiks_cube.o