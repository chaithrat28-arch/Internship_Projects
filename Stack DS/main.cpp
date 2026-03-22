/*******************************************************************************************************
NAME : CHAITHRA T
DATE : 07/03/2026 – 09/03/2026 
PROJECT TITLE : Stack Data Structure in C++
DESCRIPTION : Design and implement a Stack Data Structure in C++ and perform stack operations such as 
              Push, Pop, Peek, Display and Exit using the LIFO (Last In First Out) principle.
PRE-REQUISITE : C++ programming, OOPs, Arrays and Data Structure.
**********************************************************************************************************/
#include<iostream>
#include"class.h"
using namespace std;

int main()
{
    int choice,value;
    Stack st;

    while(1)
    {
        cout << "Select which operation u need to perform:\n";
        cout << "1.Push\n2.Pop\n3.Peek\n4.Display\n5.Exit\n";
        cout <<"Enter choice:";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter value: ";
                cin >> value;
                st.push(value);
                cout << "------------------------------\n";
                break;
            case 2:
                st.pop();
                cout << "------------------------------\n";
                break;
            case 3:
                st.peek();
                cout << "------------------------------\n";
                break;
            case 4:
                st.display();
                cout << "\n----------------------------------------\n";
                break;
            case 5:
                cout << "Exiting...\n";
                exit(0);
    
            default:
                cout << "Invalid Option\n";
        }
    }
}