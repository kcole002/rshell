#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <vector>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

class Shell_Base 
{
    protected:
    int executed;

	public:
    Shell_Base()
    {
        executed = 0;
    };

    virtual void execute() = 0;
    virtual int get_executed() = 0;
};

class Command : public Shell_Base
{
    private:
        vector<string> com;

    public:
        Command() : Shell_Base() {};
        Command(vector<string> com) : Shell_Base()
        {
            this->com = com;
            executed = 0;
        };

    	void execute()
        {
            if (com.size() != 0)
            {   
                int size = com.size() + 1; 
                char **args = new char*[size];

                for (unsigned i = 0; i < com.size(); i++)
                {
                    args[i] = (char*)com.at(i).c_str();
                }   

                args[com.size()] = NULL;

		        string check = "exit";

                if (args[0] == check.c_str())
                {
                   executed = -1;
                }
                
                else
                {
                    pid_t pid = fork();

                    if(pid < 0)
                    {perror("forking error");}

                    if(pid == 0)
                    {   
                        // child
                        //cout << "child: " << pid << endl;
                        int s = execvp(args[0], args);
                    
                        if (s == -1)
                            {perror("exec");}

                        exit(errno);
                                   
                    }

                    if (pid > 0)
                    {
                        // parent
                        int status;
                        wait(&status);
                    
                        //cout << "status: " << status << endl;
                        executed = status;

                        //cout << "parent: " << pid << endl;
                    }
                }
            }

            else
            {
                cout << "Error: Passed in an empty array." << endl; 
            }
          //  cout << "executed value: " << executed << endl;
        };

        int get_executed()
        {
            return executed;
        };

        void set_executed(int value)
        {
            executed = value;
        };

};


class Operator : public Shell_Base
{
    protected:
        Shell_Base * l;
        Shell_Base * r;

    public:
        Operator() : Shell_Base() {};
        Operator(Shell_Base * l, Shell_Base * r) : Shell_Base()
        {
            this->l = l;
            this->r = r;
        };

        int get_executed()
        {
            return executed;
        }

        virtual void execute() = 0;
        virtual void set_left(Shell_Base * left) = 0;
        virtual void set_right(Shell_Base * right) = 0;
};

class Or : public Operator
{
    public:
        Or() : Operator() {};
        Or(Shell_Base * l, Shell_Base * r)
        {
            this->l = l;
            this->r = r;

            if (l != 0)
            {
                if (l->get_executed() > 0)
                    executed = 0;

                else if (l->get_executed() == 0)
                    executed = 1;
            }

            else 
            {
              //  cout << "Error: no left child." << endl;
            }
        };

        void execute()
        {
            if (r != 0)
            {
                if (executed == 0)
                {
                    r->execute();

                    if (r->get_executed() != 0)
                        executed = 1;
                }
            }

            else
            {
              //  cout << "Error: no right child." << endl;
            }
        };

        void set_left (Shell_Base * left)
        {
            l = left;
        };

        void set_right (Shell_Base * right)
        {
            r = right;
        };
};

class And : public Operator
{
	public:
		And() : Operator() {};
		And(Shell_Base* l, Shell_Base* r)
        {
            this->l = l;
            this->r = r;

            if (l != 0)
            {
                if (l->get_executed() > 0)
                    executed = 1;
                else if (l->get_executed() == 0)
                    executed = 0;
            }

            else 
            {
              //  cout << "Error: no left child." << endl;
            }
        };

        void set_left(Shell_Base * left)
        {
            l = left;
        };

        void set_right(Shell_Base * right)
        {
            r = right;
        };

		void execute()
        {
            if (r != 0)
            {
                if (executed == 0)
                {
                    r->execute();

                    if (r->get_executed() != 0)
                        executed = 1;
                }
            }

            else 
            {
               // cout << "Error: no right child." << endl;
            }
        };
};

/*
class Hash : public Operator
{
	public:
		Hash() : Operator() {};
		Hash(Shell_Base* l, Shell_Base* r) : Operator(l, r) {}; //right child will be ignored

		void execute();  //exit after left child is executed

};
*/

class Semi : public Operator
{
	public:
		Semi() : Operator() {};
		Semi(Shell_Base* l, Shell_Base* r)
        {
            this->l = l;
            this->r = r;

            executed = 0;
        }

        void set_left(Shell_Base * left)
        {
            l = left;
        };

        void set_right(Shell_Base * right)
        {
            r = right;
        };

		void execute()
        {
            if (r != 0)
            {
                r->execute();
            
                if (r->get_executed() != 0)
                     executed = 1;
            }
            
            else 
            {
               // cout << "Error: no right child." << endl;
            }
        };
};

class Test : public Shell_Base
{
    private:
        vector<string> v;

    public:
        Test() : Shell_Base() {}
        Test(vector<string> s) : Shell_Base()
        {
            this->v = s;
        }

        int get_executed()
        {
           return executed;
        } 

        void execute()
        {
            if (v.empty())
            {
                cout << "(False)" << endl;
            }

            else
            {
                if (v.at(0) == "-f") // -f 
                {
                    if (v.size() < 2)
                    {
                        cout << "Error--filepath is not specified for test -f" << endl;
                    }

                    else
                    {
                        const string pathname = v.at(1);
                        struct stat sb;

                        if (stat(pathname.c_str(), &sb) == -1)
                        {   
                            executed = 0;
                        }

                        else 
                        {
                            executed = 1;
                        }

                        if (S_ISREG(sb.st_mode))
                        {
                            executed = 1;
                            cout << "(True)" << endl;
                        }

                        else 
                        {
                            executed = 0;
                            cout << "(False)" << endl;
                        }
                        
                    }
                
                }

                else if (v.at(0) == "-d") // -d
                {
                    if (v.size() < 2)
                    {
                        cout << "Error--filepath is not specified for test -d." << endl;
                    }

                    else 
                    {
                        const string pathname = v.at(1);
                        struct stat sb;

                        if (stat(pathname.c_str(), &sb) == -1)
                        {
                            executed = 0;
                        }

                        else 
                        {
                            executed = 1;
                        }

                        if (S_ISDIR(sb.st_mode) )
                        {
                            executed = 1;
                            cout << "(True)" << endl;
                        }

                        else 
                        {
                            executed = 0;
                            cout << "(False)" << endl;
                        }

                    }
                }

                else 
                {
                    struct stat sb;
                    string pathname = "";

                    if (v.at(0) == "-e")
                    {
                        if (v.size() < 2)
                        {
                            executed = 0;
                            cout << "Error--there is no filepath specified for test -f" << endl;
                        }

                        else 
                        {   
                            pathname = v.at(1);
                        }
                    }

                    else 
                    {
                        if (v.size() < 1)
                        {
                            executed = 0;
                            cout << "Error--there is no filepath specified for test command." << endl;
                        }

                        else
                        {
                            pathname = v.at(0);
                        }
                    }

                    if (pathname != "")
                    {
                        if (stat(pathname.c_str(), &sb) == -1)
                        {
                            executed = 0;
                            cout << "(False)" << endl;
                        }

                        else 
                        {
                            executed = 1;
                            cout << "(True)" << endl;
                        }
                    }
                }
            }
        }
};

















