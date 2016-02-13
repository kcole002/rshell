# rshell
Functionality

Our main.cpp file contains the following functions:
- void parse- seperates the user command line into a vector<vector<string> >
- bool make_com- this takes in the user input and calls parse and returns true if exit is not an executed command
- void create_tree- creates the inheritance tree that we use to determine which command should be executed
- void rshell- runs the whole program in a while loop until exit is executed

Our shell.cpp file contains the following classes:
- Shell_Base- the base abstact base class containing a variable called executed
- Command- executes a single command from a vector<string>
- Operator- parent base class for our composite classes containd left and right Shell_Base*
- Or, Semi, and And- composites that determine executed commands

We were having problems creating a bin folder when the project was built. We couldn't implement this part of the assignment

Also, since out program continually asks for input until the user input 'exit'. We included 'exit' as an input line for our test cases. this was so that we can nptify the user on what was being tested before we actually ran individual tests.

We couldn't get our Makefile to access the src directory to compile our program, so our test cases require a Makefile to also be in the src directory.
