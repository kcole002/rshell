#include <iostream>
#include "shell.cpp"
#include <boost/tokenizer.hpp>
#include <vector>

using namespace std;
using namespace boost;


void print_parse(vector<vector<string> > vec)
{
	if(vec.size() == 0)
	{
		cout << "Empty vector\n";
		cout << endl;
		return;
	}
	for(unsigned i = 0; i < vec.size(); ++i)
	{
		for(unsigned j = 0; j < (vec.at(i)).size(); ++j)
		{
			cout << (vec.at(i)).at(j) << " ";
		}
		cout << endl;
	
	}
	cout << endl;
	return;
}

vector<vector<string> > parse(string com)
{
	vector<vector<string> > v;
	vector<string> v2;

    char_separator<char> delim(" ", "|&#);");
    tokenizer<char_separator<char> >mytok(com, delim);

    for(tokenizer<char_separator<char> >::iterator it = mytok.begin(); it != mytok.end(); ++it)
    {
	v2.push_back(*it);			
    }

    for(unsigned i = 0; i < v2.size(); ++i)
    {

	vector<string> v3;

	if(v2.at(i) == "|")      //check for || command
	{
		++i;
		if(v2.at(i) == "|")
		{
			v3.push_back("||");
		}
		else       //exit if || isn't fully implemented
		{
			cout << "Invalid Command Line2." << endl;
			exit(1);
		}
	}
	else if(v2.at(i) == "&")      //check for && command
	{
		++i;
		if(v2.at(i) == "&")
		{
			v3.push_back("&&");
		}
		else       //exit if && isn't fully implemented
		{
			cout << "Invalid Command Line1." << endl;
			exit(1);
		}
	}
	else if(v2.at(i) == ";")
	{
		v3.push_back(v2.at(i));
	}
	else if(v2.at(i) == "#")
	{
		return v;
	}
	else            //create a command vector without connectors or hashes
	{
 
		while((i < v2.size()) && (v2.at(i) != "&") && (v2.at(i) != "|") && (v2.at(i) != ";") && (v2.at(i) != "#"))
		{

			v3.push_back(v2.at(i));
			++i;
		}
	
		i = i - 1;
	
	}
        v.push_back(v3);
    }


    return v;

}

vector<vector<string> >  rshell()
{
	string cmd;

	cout << "$ ";
	getline(cin, cmd);
	cout << endl;
	
	return parse(cmd);


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
    // DELETE OUTPUT FOR EXECUTE IN Command::execute()
    // DELETE OUTPUT STATEMENTS OF ELSE BRANCH OF execute() IN EVERY CLASS
    
    string a = "ls";
    string b = "-a";
    
    vector<string> v1;

    v1.push_back(a);
    v1.push_back(b);

    Shell_Base * A = new Command(v1);

    cout << "executing child A:" << endl;
    A->execute(); cout << endl;

    string c = "ls";
    //string d = "-a";

    vector<string> v2;
    v2.push_back(c);
    //v2.push_back(d);

    Shell_Base * B = new Command(v2);

    cout << "executing child B:" << endl;
    B->execute(); cout << endl;    
    
    string e = "echo";
    string f = "I love Brian Crites.";
    vector<string> v3;
    v3.push_back(e);
    v3.push_back(f);

    Shell_Base * C = new Command(v3);

    cout << "executing child C:" << endl;
    C->execute(); cout << endl;

    string g = "echo";
    string h = "KSAOHUB";

    vector<string> v4;
    v4.push_back(g);
    v4.push_back(h);

    Shell_Base * N = new Command(v4);
    cout << "executing child N:" << endl;
    N->execute(); cout << endl;

    // Test case for Or composite class (uses A, B, and C from Leaf class)
    /*
    Shell_Base * D = new Or(A,B);

    cout << "executing A || B:" << endl;
    D->execute(); cout << endl; 

    Shell_Base * E = new Or(D, C);

    cout << "executing A || B || C:" << endl;
    E->execute(); cout << endl;
    */

    // Test case for And composite class (uses A, B, and C from Leaf class)
    /* 
    Shell_Base * F = new And(A,B);

    cout << "executing A && B:" << endl;
    F->execute(); cout << endl;

    Shell_Base * G = new And(F, C);

    cout << "executing A && B && C:" << endl;
    G->execute(); cout << endl;
    */

    // Test case for Semi composite class (uses A, B, and C from Leaf class)
    /* 
    Shell_Base * H = new Semi(A,B);

    cout << "executing A;B:" << endl;
    H->execute(); cout << endl;

    Shell_Base * I = new Semi(H, C);

    cout << "executing A;B;C:" << endl;
    I->execute(); cout << endl;
    */


	//print_parse(rshell());

    // Test case for all composite classes together
    
    Shell_Base * J = new Or(A, B);
    Shell_Base * K = new And(J, C);
    Shell_Base * L = new Semi(K, N);

    cout << "executing A || B:" << endl;
    J->execute(); cout << endl;

    cout << "executing A || B && C:" << endl;
    K->execute(); cout << endl;

    cout << "executing A || B && C; N:" << endl;
    L->execute(); cout << endl;
    

    return 0;
}









