COMPILE = g++
FLAGS = -Wall -Werror -ansi -pedantic 
PROGRAM = a.out
OBJECTS = shell.o
MAIN = main.cpp

%.o: %.cpp
	$(COMPILE) $(FLAGS) -c $^

all: $(OBJECTS)
	$(COMPILE) $(FLAGS) $(OBJECTS) $(MAIN) -o $(PROGRAM)

rshell: shell.cpp
	$(COMPILE) $(FLAGS) -c shell.cpp -o $(OBJECTS)

clean:
	rm -f $(OBJECTS) $(PROGRAM)

test: all
	./$(PROGRAM)

main: 
	$(COMPILE) $(FLAGS) $(MAIN) -o $(PROGRAM)
