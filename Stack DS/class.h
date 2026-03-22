#ifndef CLASS_H
#define CLASS_H

#include<iostream>
using namespace std;
#define SIZE 5

class Stack
{
    private:
    int stack[SIZE];
    int top;

    public:
        //constructor
        Stack()
        {
            top = -1;
        }

        void push(int value);

        void pop();

        void peek();

        void display();
};

#endif
