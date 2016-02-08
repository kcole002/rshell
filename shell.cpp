#include <iostream>

using namespace std;

class Shell_Base 
{
    virtual void execute() = 0;
    virtual void print() = 0;
};

class Command : public Shell_Base
{
    private:
        string com;

    public:
        Command() : Shell_Base() {};
        Command(string com) : Shell_Base()
        {
            this->com = com;
        };

        void execute();
        void print();

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

        virtual void execute();
        virtual void print();
};

class Or : public Operator
{
    public:
        Or() : Operator() {};
        Or(Shell_Base * l, Shell_Base * r) : Operator(l, r) {};

        void execute();
        void print();
};













