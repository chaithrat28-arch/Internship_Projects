#include<iostream>
#include"classes.h"

using namespace std;

int main()
{
    int op;

    //creating object for bank
    Banker admin;

    cout << "::Welcome to Bank::\n";

    while(1)
    {
        cout << "Login as :\n";
        cout << "1. Banker\n";
        cout << "2. Customer\n";
        cout << "3. Exit\n";
        cout << "Enter your option: ";
        cin >> op;

        switch (op)
        {
            case 1:
            {
                string id;
                string pwd;

                cout << "\nEnter Banker ID:";
                cin >>id;
                cout << "Enter Password:";
                cin >> pwd;

                if(admin.login(id,pwd))
                {
                    cout << "\nBanker login successful.\n\n";
                    banker_menu(admin);
                }
                else
                {
                    cout << "Banker login failed...!!\n";
                }
            }
            break;
    
            case 2:
                admin.load_customers();
                customer_menu(admin);
                break;
            
            case 3:
                exit(0);
                break;

            default:
                cout << "ERROR: Invalid Login..!!\n";
                break;
        }

    }
    
}