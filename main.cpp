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

vector<vector<string> >  make_com()
{
	string cmd;

	cout << "$ ";
	getline(cin, cmd);
	cout << endl;
	
	return parse(cmd);


}

bool create_tree(vector<vector<string> > v)
{
	Shell_Base* left = 0;


	if((v.at(0)).at(0) == "exit")
	{
		return true;
	}

	for(unsigned i = 0; i < v.size(); ++i)
	{
		if(((v.at(i)).at(0) == "&&") || ((v.at(i)).at(0) == "||") || ((v.at(i)).at(0) == ";"))
		{
			if(i == 0)
			{
				cout << "Error: invalid command.\n";
				return false;
			}

			if( ((i + 1) < v.size()) &&  ((v.at(i)).at(0) == "&&"))
			{
				Shell_Base* temp = new Command(v.at(i));	
				
				Shell_Base * a = new And(left, temp);
				a->execute();
				if( a->get_executed() == -1)
				{
					return false;
				}
			}
			else if( ((i + 1) < v.size()) && ((v.at(i)).at(0) == "||"))   
			{
				Shell_Base* temp  =  new Command(v.at(i + 1));

				Shell_Base* a = new Or(left, temp);				
				a->execute();
				if( a->get_executed() == -1)
				{
					return false;
				}

			}
			else if( ((v.at(i)).at(0) == ";"))   
			{
				Shell_Base* temp = new Command(v.at(i + 1));
				Shell_Base* a = new Semi(left, temp);				
				a->execute();
				if( a->get_executed() == -1)
				{
					return false;
				}	
			}		

		
		}
		else if((v.at(i)).at(0) == "#")
		{
			return true;
		}
		else
		{

			Shell_Base* a = new Command(v.at(i));
			a->execute();
			left = a;
		
		}


	}
	return true;	

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
    
    string a = "s";
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
    
    string e = "s";
    string f = "I love Brian Crites.";
    vector<string> v3;
    v3.push_back(e);
    v3.push_back(f);

    Shell_Base * C = new Command(v3);

    cout << "executing child C:" << endl;
    C->execute(); cout << endl;

    // Test case for Or composite class (uses A, B, and C from Leaf class)
    /*
    Shell_Base * D = new Or(A,B);

    cout << "executing A || B:" << endl;
    D->execute(); cout << endl; 

    Shell_Base * E = new Or(D, C);

    cout << "executing (A || B) || C:" << endl;
    E->execute(); cout << endl;
    */

    // Test case for And composite class (uses A, B, and C from Leaf class)
    /* 
    Shell_Base * F = new And(A,B);

    cout << "executing A && B:" << endl;
    F->execute(); cout << endl;

    Shell_Base * G = new And(F, C);

    cout << "executing (A && B) && C:" << endl;
    G->execute(); cout << endl;
    */

    // Test case for Semi composite class (uses A, B, and C from Leaf class)
    /* 
    Shell_Base * H = new Semi(A,B);

    cout << "executing A;B:" << endl;
    H->execute(); cout << endl;

    Shell_Base * I = new Semi(H, C);

    cout << "executing (A;B);C:" << endl;
    I->execute(); cout << endl;
    */


	//print_parse(rshell());

/*
    while(create_tree(make_com()))
    {
	make_com();
    }
		    
  */
    return 0;
}









