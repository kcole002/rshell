COMPILE = g++
FLAGS = -Wall -Werror -std=c++0x
PROGRAM = a.out
OBJECTS = shell.o
MAIN = main.cpp

%.o: %.cpp
	$(COMPILE) $(FLAGS) -c $^

all: $(OBJECTS)
	$(COMPILE) $(FLAGS) $(OBJECTS) $(MAIN) -o $(PROGRAM)

clean:
	rm -f $(OBJECTS) $(PROGRAM)

test:
	./$(PROGRAM)

main: 
	$(COMPILE) $(FLAGS) $(MAIN) -o $(PROGRAM)
