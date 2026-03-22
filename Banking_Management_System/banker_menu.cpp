#include"classes.h"

void banker_menu(Banker &admin)
{
    while (1)
    {
        int choice;
        cout << "1. Create Customer\n";
        cout << "2. View All Customers\n";
        cout << "3. Logout\n";
        cout << "Choose an option:";
        cin >> choice;

        switch(choice)
        {
            case 1: 
                admin.create_customer(); 
                break;
            case 2: 
                admin.load_customers();
                admin.view_customer(); 
                break;
            case 3: 
                cout << "Logged out successfully.\n\n";
                return; 
        }
    }

}

Banker::Banker() : User("B01", "admin123") {}

void Banker::create_customer()
{
    string customer_id;
    string customer_name;
    string customer_pwd;

    cout << "\nEnter Customer ID: ";
    cin >> customer_id;

    for (int i = 0; i < customers.size(); i++)
    {
        if (customers[i].get_id() == customer_id)
        {
            cout << "Customer ID already exists!\n";
            return;
        }
    }

    cout << "Enter Customer Name: ";
    cin >> customer_name;

    cout << "Enter Customer Password: ";
    cin >> customer_pwd;

    Customer c(customer_id, customer_pwd, customer_name,0);
    customers.push_back(c); //adding customer to vector

    cout << "\nCustomer created successfully.\n";

    //storing to file
    save_customers();
}

void Banker::view_customer()
{
    //fetching from file
    
    if (customers.empty())
    {
        cout << "No customers available.\n";
        return;
    }

    cout << "\n--- Customer List ---\n";
    for (int i = 0; i < customers.size(); i++)
    {
        cout << "Customer ID  : " << customers[i].get_id() << endl;
        cout << "Customer Name: " << customers[i].get_name() << endl;
        cout <<"\n";
    }
    
}

void Banker::save_customers()
{
    ofstream fout("customer_data.txt");

    for (int i = 0; i < customers.size(); i++)
    {
        fout << customers[i].get_id() << " "
             << customers[i].get_name() << " "
             << customers[i].get_pwd() << " "
             << customers[i].get_balance() << endl;
    }

    fout.close();
}

void Banker::load_customers()
{
    customers.clear();   // clear vector, load only once

    ifstream fin("customer_data.txt");

    if (!fin)   // file if not exist first time
        return;

    string id, name, pwd;
    double bal;

    while (fin >> id >> name >> pwd >> bal)
    {
        Customer c(id, pwd, name, bal);
        customers.push_back(c);
    }

    fin.close();
}
