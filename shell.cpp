#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <vector>
#include <errno.h>

using namespace std;

class Shell_Base 
{
	public:
    virtual void execute() = 0;
};

class Command : public Shell_Base
{
    private:
        vector<string> com;
        int executed;

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
                char * args[com.size() + 1];

                for (unsigned i = 0; i < com.size(); i++)
                {
                    args[i] = (char*)com.at(i).c_str();
                }   

                args[com.size()] = NULL;

                pid_t pid = fork();

                if(pid < 0)
                    perror("forking error");

                if(pid == 0)
                {   
                    // child
                    cout << "child: " << pid << endl;
                    int s = execvp(args[0], args);
                    
                    if (s == -1)
                        perror("exec");


                    exit(errno);
                                   
                }

                if (pid > 0)
                {
                    // parent
                    int status;
                    wait(&status);
                    
                    //cout << "status: " << status << endl;
                    executed = status;

                    cout << "parent: " << pid << endl;
                }
            }

            else
            {
                cout << "Error: Passed in an empty array." << endl; 
            }
            cout << "executed value: " << executed << endl;
        };

};

/*
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

        virtual void execute() = 0;
        virtual void print() = 0;
};

class Or : public Operator
{
    public:
        Or() : Operator() {};
        Or(Shell_Base * l, Shell_Base * r) : Operator(l, r) {};

        void execute()
	{
	//	if(execvp(
	};
        void print();
};

class And : public Operator
{
	public:
		And() : Operator() {};
		And(Shell_Base* l, Shell_Base* r) : Operator(l, r) {};

		void execute();
		void print();
};

class Hash : public Operator
{
	public:
		Hash() : Operator() {};
		Hash(Shell_Base* l, Shell_Base* r) : Operator(l, r) {}; //right child will be ignored

		void execute();  //exit after left child is executed.
		void print();

};

class Semi : public Operator
{
	public:
		Semi() : Operator() {};
		Semi(Shell_Base* l, Shell_Base* r) : Operator(l, r) {};

		void execute();
		void print();
};
*/











