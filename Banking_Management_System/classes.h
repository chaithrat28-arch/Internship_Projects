#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include<fstream>
#include<vector>
using namespace std;

class User
{
protected:
    string user_id;
    string user_pwd;

public:
    User(){}
    User(string id, string pwd)
    {
        user_id = id;
        user_pwd = pwd;
    }
    bool login(string id, string inputpwd)
    {
        if(user_id == id && user_pwd == inputpwd)
            return true;
        else
            return false;
    }
};

class Customer : public User
{
private:
    double balance;
    string name;
    //creating vector for transactions
    vector<string> transactions;

public:
    Customer(){}
    Customer(string id,string pwd, string name,double bal = 0): User(id, pwd), name(name),balance(bal) {}

    string get_id() 
    { 
        return user_id; 
    }
    string get_name() 
    { 
        return name; 
    }
    double get_balance()
    {
        return balance;
    }

    string get_pwd()
    {
        return user_pwd;
    }

    void view_account();
    void deposit(double);
    void withdraw(double);
    void view_transaction();

    void save_history();  
    void load_history(); 
};

class Banker : public User
{
public:
    //creating vector for customers
    vector<Customer> customers;

    Banker();
    void create_customer();   
    void view_customer();   
    
    void save_customers();  
    void load_customers(); 
};

void banker_menu(Banker &);

void customer_menu(Banker &);

#endif

