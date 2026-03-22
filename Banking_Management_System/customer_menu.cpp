#include"classes.h"

void customer_menu(Banker &admin)
{
    string id;
    string pwd;
    bool found = false;

    cout << "\nEnter Customer ID: ";
    cin >> id;
    cout << "Enter Password: ";
    cin >> pwd;

    //admin->customers(accessing vector)
    for (int i = 0; i < admin.customers.size(); i++)
    {
        if (admin.customers[i].login(id, pwd))
        {
            cout << "\nCustomer login successful.\n";
            found = true;
            //if both id and pwd matches then create object for custoner and assign same 
            Customer &cust = admin.customers[i];
            cust.load_history();      

            while (1)
            {
                int choice;
                cout << "\n1. View Account";
                cout << "\n2. Deposit";
                cout << "\n3. Withdraw";
                cout << "\n4. View Transactions";
                cout << "\n5. Logout";
                cout << "\nChoose option: ";
                cin >> choice;

                switch (choice)
                {
                    case 1:
                        cust.view_account();
                        break;

                    case 2:
                    {
                        double amt;
                        cout << "Enter deposit amount: ";
                        cin >> amt;

                        cust.deposit(amt);
                        admin.save_customers(); 
                        break;
                    }

                    case 3:
                    {
                        double amt;
                        cout << "Enter withdraw amount: ";
                        cin >> amt;
                        
                        cust.withdraw(amt);
                        admin.save_customers(); 
                        break;
                    }

                    case 4:
                        cust.view_transaction();
                        break;

                    case 5:
                        cout << "Logged out successfully.\n\n";
                        return;
                }
            }
        }
    }

    if (!found)
        cout << "Customer login failed.\n";
}

void Customer :: view_account()
{
    cout << "Account Balance: " << balance << endl;
}

void Customer :: deposit(double amount)
{
    if (amount <= 0)
    {
        cout << "Invalid deposit amount.\n";
        return;
    }

    balance = balance + amount; 
    //update transaction(sep. file)
    transactions.push_back("Deposit: "+ to_string(amount)+" Closing Balance: "+to_string(balance));
    save_history();
    cout << "Deposit Successful.\n";
}

void Customer :: withdraw(double amount)
{
    if (amount <= 0)
    {
        cout << "Invalid withdraw amount.\n";
        return;
    }

    if(amount > balance)
        {
            cout << "Insufficient balance.\n";
            return;
        }
        else
        {
            balance = balance - amount;
            //update transaction(sep. file)
            transactions.push_back("Withdraw: "+ to_string(amount)+" Closing Balance: "+to_string(balance));
            save_history();
            cout <<"Withdrawal Successful.\n";
        }
}

void Customer ::view_transaction()
{
    //print transaction upto date
    if(transactions.empty())
    {
        cout <<"No transactions yet.\n";
        return;
    }

    cout<< "\n--- Transactions History ---\n";
    for(int i=0;i < transactions.size();i++)
    {
        cout << transactions[i]<<endl;
    }
}

void Customer::save_history()
{
    string fname = "transaction_" + user_id + ".txt";
    ofstream fout(fname);

    for (int i = 0; i < transactions.size(); i++)
        fout << transactions[i] << endl;

    fout.close();
}

void Customer::load_history()
{
    transactions.clear();

    string fname = "transaction_" + user_id + ".txt";
    ifstream fin(fname);

    if (!fin)
        return;

    string line;
    while (getline(fin, line))
    {
        transactions.push_back(line);
    }

    fin.close();
}

