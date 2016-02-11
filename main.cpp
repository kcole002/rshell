#include <iostream>
#include "shell.cpp"
#include <boost/tokenizer.hpp>
#include <vector>

using namespace std;
using namespace boost;

vector<string> parse(string com)
{
    vector<string> v;

    char_separator<char> delim(" ", "|&#);");
    tokenizer< char_separator<char> >mytok(com, delim);

    for (tokenizer< char_separator<char> >::iterator it = mytok.begin(); it != mytok.end(); ++it)
        v.push_back(*it);

    return v;
};

void rshell()
{
	string cmd;

	cout << "$ ";
	getline(cin, cmd);
	cout << endl;
	
	parse(cmd);


}


int main()
{ 
    // Test case for parse
    /*
    vector<string> test_vector;
    string test_string = "ls assignments | | cd CS100 && iss ; hello";   

    test_vector =  parse(test_string);

    for (unsigned int i = 0; i < test_vector.size(); i++)
    {
        cout << '(' << test_vector.at(i) << ')' << ' ';
    }

    cout << endl;
    */
    
    // Test case for Command Leaf class
    
    string a = "ls";
    string b = "-a";
    
    vector<string> v1;

    v1.push_back(a);
    v1.push_back(b);

    Shell_Base * A = new Command(v1);

    A->execute(); cout << endl;

    string c = "&&";
    string d = "-a";

    vector<string> v2;
    v2.push_back(c);
    v2.push_back(d);

    Shell_Base * B = new Command(v2);

    B->execute(); cout << endl;
    
  
    return 0;
}









