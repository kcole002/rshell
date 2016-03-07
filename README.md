Functionality

Our main.cpp file contains the following functions:

bool par_found- checks to see if the command line contains parentheses
bool check_par- makes sure that there are no hanging parentheses
string replace_par- repalces the outer parenthese of a group with quotation marks (for parsing)
bool parse_original- parses a command line that doesn't contain parentheses
bool parse- parses a command line with parentheses
bool make_com- this takes in the user input and calls parse and returns true if exit is not an executed command
bool create_tree- creates the inheritance tree that we use to determine which command should be executed
bool new_create_tree- handles precedence of command lines with parentheses
void rshell- runs the whole program in a while loop until exit is executed

Our shell.cpp file contains the following classes:

Shell_Base- the base abstact base class containing a variable called executed
Command- executes a single command from a vector
Operator- parent base class for our composite classes containd left and right Shell_Base*
Or, Semi, and And- composites that determine executed commands
Test- handles the test command line; similar to Command

ERRORS:

-For the test command with brackets, there MUST be a space after the opening bracket and before the closing bracket

-Our program cannot handle nested parentheses, the specifications did not mention this was necessary.

-We were having problems creating a bin folder when the project was built. We couldn't implement this part of the assignment

-Also, since out program continually asks for input until the user input 'exit'. We included 'exit' as an input line for our test cases. this was so that we can nptify the user on what was being tested before we actually ran individual tests.

-We couldn't get our Makefile to access the src directory to compile our program, so our test cases require a Makefile to also be in the src directory
