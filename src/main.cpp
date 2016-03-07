#include <iostream>
#include "shell.cpp"
#include <boost/tokenizer.hpp>
#include <vector>

using namespace std;
using namespace boost;

bool par_found(string cmd)
{
	for(unsigned i = 0; i < cmd.size(); ++i)
	{
		if(cmd.at(i) == '(' || cmd.at(i) == ')')
		{
			return true;
		}
	}
	return false;
}

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

bool check_par(string cmd)
{
	int open_par = 0;
	int close_par = 0;

	for(unsigned i = 0; i < cmd.size(); ++i)
	{
		if(cmd.at(i) == '(')
		{
			++open_par;
		}
		else if(cmd.at(i) == ')')
		{
			++close_par;
		}
	}

	if(open_par != close_par)
	{
		cout << "Error: Hanging parentheses/n";
		return false;
	}
	return true;
}

string replace_par(string cmd)
{
	int open = 0;
	int close = 0;

	for(unsigned i = 0; i < cmd.size(); ++i)
	{
		if(cmd.at(i) == '(')
		{
			++open;
			if(open == 1)
			{
				cmd.at(i) = '"';
			}

		}
		else if(cmd.at(i) == ')')
		{
			++close;
			if(open == close)
			{
				cmd.at(i) = '"';
				open = 0;
				close = 0;
			}
		}
	}
	return cmd;	

}

bool create_tree(vector<vector<string> > v);

bool parse_original(string com)
{
	vector<vector<string> > v;
	vector<string> v2;

    char_separator<char> delim(" ", "|&;#");
    tokenizer<char_separator<char> >mytok(com, delim);

    for(tokenizer<char_separator<char> >::iterator it = mytok.begin(); it != mytok.end(); ++it)
    {
	v2.push_back(*it);			
    }

    for(unsigned i = 0; i < v2.size(); ++i)
    {

		vector<string> v3;

	//	if(v2.at(i) == "||" || v2.at(i) == "&&" v2.at(i) == ';'

		if(v2.at(i) == "|")      //check for || command
		{
			++i;
			if(v2.at(i) == "|")
			{
				v3.push_back("||");
			}
			else       //exit if || isn't fully implemented
			{
				cout << "Invalid Command Line.1" << endl;
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
				cout << "Invalid Command Line.2" << endl;
				exit(1);
			}
		}
		else if(v2.at(i) == ";")
		{
			v3.push_back(v2.at(i));
		}
		else if(v2.at(i) == "#")
		{
			v3.push_back(v2.at(i));
			v.push_back(v3);
			return create_tree(v);
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
	return create_tree(v);

}

bool new_create_tree(vector<string> v);

bool parse(string com)
{
	vector<string> v;

	escaped_list_separator<char> sep("", " ", "\"");
	tokenizer<escaped_list_separator<char> >mytok(com, sep);

	for(tokenizer<escaped_list_separator<char> >::iterator it = mytok.begin(); it != mytok.end(); ++it)
	{
		if(*it == "#")
		{
			return new_create_tree(v);
		}
		v.push_back(*it);			
	}

/*	cout << "Vector contains:\n";	
	for(unsigned i = 0; i < v.size(); ++i)
	{
		cout << v.at(i) << endl;
	}

	cout << "---------------------\n";
*/	
	return new_create_tree(v);

}

bool new_create_tree(vector<string> v)
{
		//make sure first command is not && or ||
	if(v.at(0) == "||" || v.at(0) == "&&")
	{
		cout << "Error: invalid command\n";
		exit(1);
	}


	string temp_cmd = v.at(0);

	for(unsigned i = 1; i < v.size(); ++i)
	{
		


		if(v.at(i) == "||" || v.at(i) == "&&" || v.at(i) == ";")
		{
			string connector = v.at(i);
			
			//check if the string of commands has parentheses
			if(par_found(temp_cmd))
			{
				temp_cmd = replace_par(temp_cmd);
			//	cout << temp_cmd << endl;

				//if it does we will break it down again using parse
				parse(temp_cmd);
			}
			else
			{
				//bool keeps track of whether or not the command line (temp_cmd) was successful as executing or not
				bool check_succeed = parse_original(temp_cmd);
				if(check_succeed == false)
				{
					if(connector == "||")
					{
						if(i >= v.size())
						{
							//cout << "FLAG 1\n";
							cout << "Error: invalid connector location\n";
							return false;
						}
						vector<string> v_temp;
						for(unsigned j = i + 1; j < v.size(); ++j)
						{
							v_temp.push_back(v.at(j));
							
						}
						
						return new_create_tree(v_temp);
					}
					else if(connector == "&&")
					{
						return false;
					}
					else if(connector == ";")
					{
						if(i >= v.size())
						{
							cout << "FLAG 2\n";
							cout << "Error: invalid connector location\n";
							return false;
						}
						vector<string> v_temp;
						for(unsigned j = i + 1; j < v.size(); ++j)
						{
							v_temp.push_back(v.at(j));
							
						}
					
						return new_create_tree(v_temp);

					}
				}
				else
				{
					if(connector == "||")
					{
						vector<string> v_temp;
						unsigned k = 0;
						for(unsigned j = i + 1; j < v.size(); ++j)
						{
							if(v.at(j) != "||" || v.at(j) != "&&" || v.at(j) != ";")
							{
								k = j;
							}							
						}
						for(unsigned j = k; j < v.size(); ++j)
						{
							v_temp.push_back(v.at(j));						
						}
 						
						new_create_tree(v_temp);

						return true;
	
					}
					else if(connector == "&&")
					{
						if(i >= v.size())
						{
							//cout << "FLAG 3\n";
							cout << "Error: invalid connector location\n";
							return false;
						}
						vector<string> v_temp;
						for(unsigned j = i + 1; j < v.size(); ++j)
						{
							v_temp.push_back(v.at(j));
							
						}
						
						return new_create_tree(v_temp);

					}
					else if(connector == ";")
					{
						if(i >= v.size())
						{
						//	cout << "FLAG 4\n";
							cout << "Error: invalid connector location\n";
							return false;
						}
						vector<string> v_temp;
						for(unsigned j = i + 1; j < v.size(); ++j)
						{
							v_temp.push_back(v.at(j));
							
						}
						
						return new_create_tree(v_temp);

					}
				}
			}


		}
		else
		{
			temp_cmd = temp_cmd + " " + v.at(i);
		}
	}

	if(par_found(temp_cmd))
	{
		temp_cmd = replace_par(temp_cmd);
	//	cout << temp_cmd << endl;

				//if it does we will break it down again using parse
		parse(temp_cmd);
	}
	else
	{
		parse_original(temp_cmd);
	}

	return true;
}
const int ARRAY_MAX = 20;

bool make_com()
{
	string cmd;

    char hostname[ARRAY_MAX];
    char login[ARRAY_MAX];

    int result = getlogin_r(login, ARRAY_MAX);
    if (result)
    {
        perror("getlogin");
    }

    else 
    {
        cout << login;
    }
 
    result = gethostname(hostname, ARRAY_MAX);
    if (result)
    {
        perror("gethostname");
    }
    
    else
    {
        cout << '@' << hostname;
    }

	cout << "$ ";
	getline(cin, cmd);
	//cout << endl;

//	cout << "--------\nIn get_com()\n";

	if(par_found(cmd) == false)
	{
		return parse_original(cmd);
	}
	
	else
	{
		if(check_par(cmd) == false)
		{
			return true;
		}
		cmd = replace_par(cmd);
	//	cout << cmd << endl;
	//		cout << cmd << endl;
	
		return parse(cmd);

	}
	return true;
}

bool create_tree(vector<vector<string> > v)
{
	Shell_Base* left = 0;
	string exit = "exit";


	if((v.at(0)).at(0) == "exit")
	{
		return false;
	}
	if((v.at(0)).at(0) == "#")
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
				Shell_Base* temp = new Command(v.at(i + 1));	
				
				Shell_Base * a = new And(left, temp);
				if(v.at(i + 1).at(0)  == exit)
				{
					return false;
				}
				else if( ((v.at(i + 1)).at(0) == "&&") || ((v.at(i + 1)).at(0) == "||") || ((v.at(i + 1)).at(0) == ";"))
				{
					cout << "Error: Consecutive connectors.\n";
					return true;	
				}
				else if((v.at(i + 1)).at(0) == "#")
				{
					return true;
				}	
				

				a->execute();
			}
			else if( ((i + 1) < v.size()) && ((v.at(i)).at(0) == "||"))   
			{
				Shell_Base* temp  =  new Command(v.at(i + 1));

				Shell_Base* a = new Or(left, temp);
				if(v.at(i + 1).at(0)  == exit)
				{
					return false;
				}
				else if( ((v.at(i + 1)).at(0) == "&&") || ((v.at(i + 1)).at(0) == "||") || ((v.at(i + 1)).at(0) == ";"))
				{
					cout << "Error: Consecutive connectors.\n";
					return true;	
				}
				else if((v.at(i + 1)).at(0) == "#")
				{
					return true;
				}	

				a->execute();

			}
			else if( ((v.at(i)).at(0) == ";"))   
			{
				Shell_Base* temp = new Command(v.at(i + 1));
				Shell_Base* a = new Semi(left, temp);
				
				if(v.at(i + 1).at(0)  == exit)
				{
					return false;
				
				}
				else if( ((v.at(i + 1)).at(0) == "&&") || ((v.at(i + 1)).at(0) == "||") || ((v.at(i + 1)).at(0) == ";"))
				{
					cout << "Error: Consecutive connectors.\n";
					return true;	
				}
				else if((v.at(i + 1)).at(0) == "#")
				{
					return true;
				}
				
				a->execute();
				
			}		

		
		}
		else if((v.at(i)).at(0) == "#")
		{
			return true;
		}
		else
		{

			Shell_Base* a = new Command(v.at(i));
			if (i == 0 && v.at(i).at(0) != exit)
				{a->execute();}

			else if (i == 0 && v.at(i).at(0) == exit)
			{
				return false;
			}

			left = a;
			
			if (a->get_executed() == -1)
			{
				return false;
			}
		
		}


	}
	return true;	

}

void rshell()
{
    bool test = true;	
  	do
   	{ 
        test = make_com();
	cout << endl;
   	} while (test);
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
    /* 
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
    */
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
	
    
    // Test case for Test leaf class (uses a vector of strings with -f as its first element)
    /*
    vector<string> z;
    string filepath = "/home/csmajs/cdele005/CS100/Lab6/composite.h";
    z.push_back("-f");
    z.push_back(filepath);

    //cout << z.at(0) << ' ' << z.at(1) << endl;

    Shell_Base * J = new Test(z);

    J->execute();
    */


    //Running the whole file
    rshell();


    return 0;
}









