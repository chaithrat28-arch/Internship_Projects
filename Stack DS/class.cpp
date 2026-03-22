#include"class.h"

//to push element in to stack
void Stack::push(int value)
{
    if(top == SIZE - 1)
    {
        cout << "Stack is full\n";
        return;
    }
    
    top++;

    stack[top] = value;
    cout << value <<" added to stack"<<endl;
}

//to pop element from stack
void Stack::pop()
{
    if( top == -1)
    {
        cout << "Stack is Empty\n";
    }

    cout << "Deleted element: " << stack[top] << endl;
    top--;
}

//printing topmost element in stack
void Stack::peek()
{
    if( top == -1)
    {
        cout << "Stack is Empty\n";
        return;
    }

    cout << "Topmost element is "<<stack[top] <<"\n";
}

//displaying all elements in stack
void Stack::display()
{
    // printf("top=> %d\n",top);
    if( top == -1)
    {
        cout << "Stack is Empty\n";
        return;
    }

    cout << "Elements in Stack:\n";
    for(int i=0;i <= top;i++)
    {
        cout <<stack[i] <<"\t";
    }
}
