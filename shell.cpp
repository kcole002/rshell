#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <vector>

using namespace std;

class Shell_Base 
{
	public:
    virtual void execute() = 0;
   // virtual void print() = 0;
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
        };

    	void execute()
        {
            if (com.size() != 0)
            {    
                char * args[com.size() + 1];

           // args[0] = (char*)com.c_str();
           // args[1] = NULL;

                for (unsigned i = 0; i < com.size(); i++)
                {
                    args[i] = (char*)com.at(i).c_str();
                }   

                args[com.size()] = NULL;

                pid_t pid = fork();

                if(pid == 0)
                {   
                    // child
                    cout << "child: " << pid << endl;
                    if (execvp(args[0], args) == -1)
                    {
                        perror("exec");
                    }

                }

                if (pid > 0)
                {
                    // parent
                    if (wait(0) == -1)
                    {
                        perror("Wait");
                    }
                    cout << "parent: " << pid << endl;
                }
            }   
        };


       // void print();

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

        virtual void execute();
        virtual void print();
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











