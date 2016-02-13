COMPILE = g++
FLAGS = -Wall -Werror -ansi -pedantic 
PROGRAM = rshell.out
OBJECTS = shell.o
MAIN = main.cpp

%.o: %.cpp
	$(COMPILE) $(FLAGS) -c $^

all: $(OBJECTS)
	$(COMPILE) $(FLAGS) $(OBJECTS) $(MAIN) -o $(PROGRAM)

rshell: all

clean:
	rm -f $(OBJECTS) $(PROGRAM)

test: all
	./$(PROGRAM)

main: 
	$(COMPILE) $(FLAGS) $(MAIN) -o $(PROGRAM)
