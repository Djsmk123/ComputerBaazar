#include <iostream>
#include<string>
#include<list>
#include<conio.h>
#include<fstream>
#include "passwordInput.h"
#include "registerNewUser.h"
#include "json.hpp"
#include <chrono>
#include <ctime> 
#include "loginuser.h"
using json = nlohmann::json;
//user Class
class authentication
{
private:
    string username;
    string password;
public:
void login()
{  //login function
    int flag=1;
    while (flag!=0)
    {
    cout<<"Enter your username: ";
    cin>>username;
    cout<<"Enter your password: ";
    password=pass();
    flag=log_in(username,password);
    }
    
}
    void register_user()
    {     
         int flag=1;
        while(flag!=0)
        {
            cout<<"Enter username: ";
            cin>>username;
            cout<<"Enter password: ";
            password=pass();
            flag=reg_user(username,password);
          
        }
 }
 string get_username()
 {
     return username;
 }
};
//Structure for order Details
struct orderDetails
{
    string item_code;
    int quantity;
    double price;
};
//Structure for new Entry
struct purchasedetails
{
    string pid;
    string name_of_customer;
    string date;
    list< orderDetails> order;
};
class shop
{
private:
   list<purchasedetails> list_of_purchase;
public:
    void addNewEntry(string username)
    {
        purchasedetails newEntry;
        fstream file;
        string file_name=username+"purchase.json";
        file.open(file_name,ios::in|ios::out|ios::app);
    
        if(!file.is_open())
        {
            cout<<"File not found"<<endl;
        }
    
        while(1)
        {
        cout<<"Enter the product id: ";
        cin>>newEntry.pid;
        cout<<"Enter the name of the customer: ";
        cin.ignore();
        getline(cin,newEntry.name_of_customer);
         auto start = chrono::system_clock::now();
            auto end = chrono::system_clock::now();
            chrono::duration<double> elapsed_seconds = end-start;
            time_t end_time = std::chrono::system_clock::to_time_t(end);
            newEntry.date=ctime(&end_time);
        
        while(1)
        {
            orderDetails newOrder;
            cout<<"Enter the item code: ";
            cin>>newOrder.item_code;
            cout<<"Enter the quantity: ";
            cin>>newOrder.quantity;
            //cout<<"Enter the price: ";
            //cin>>newOrder.price;
            fstream available_items;
            string file_name="availProd.json";
            available_items.open(file_name,ios::in|ios::out|ios::app);
             int flag=0;
            if(!available_items.is_open())
            {
                cout<<"File not found!!!"<<endl;
                break;
            }
            else
            {
                json j;
                j=json::parse(available_items);
                double price=0;
                for(auto i=j.begin();i!=j.end();i++)
                {    if(i.key()=="price")
                       price=i.value();
                    if(i.key()=="itemcode")
                    {
                      if(i.value()==newOrder.item_code.c_str())
                    {
                        flag=1;
                        newOrder.price=price;
                        break;
                    }
                    }
                  
                }
            }
            if(flag==1)
            {
                newEntry.order.push_back(newOrder);
            }
            else
            {
                cout<<"Item not available"<<endl;
            }
            cout<<"Do you want to add more items? (y/n)";
            char ch;
            cin>>ch;
             if(ch=='n')
             break;
        }
    
        list_of_purchase.push_back(newEntry);
        cout<<"New entry added successfully"<<endl;
         cout<<"Do you want to add more enteries? (y/n)";
            char ch;
            cin>>ch;
            if(ch=='n')
                break;
        }
     
        for(auto x:list_of_purchase)
        {
            json j;
            j["pid"]=x.pid;
            j["name_of_customer"]=x.name_of_customer;
            j["date"]=x.date;
            for(auto x:x.order)
            {
                json j1;
                j1["item_code"]=x.item_code;
                j1["quantity"]=x.quantity;
                j1["price"]=x.price;
                j["order"].push_back(j1);
            }
            file<<j<<endl;
        }
    }
    void searching()
    {
        
    }
    void modification()
    {
    }
    void removeRecord()
    {
    }

};
//Driver Code

int main()
{     int choice=1;
      bool isAuthenticated=false;
      authentication auth;
     while (choice!=3)
     {    system("cls");
         cout<<"********Welcome to the Computer Bazaar***********"<<endl;
         cout<<"1.New user(Registered Here)"<<endl;
         cout<<"2.Existing user(Login Here)"<<endl;
         cout<<"3.Exit"<<endl;
         cout<<"Enter your choice"<<endl;
          cin>>choice;
         switch(choice)
         {
             case 1:
             {
                 cout<<"hi"<<endl;
                 auth.register_user();
                 choice=3;
                 isAuthenticated=true;
                 break;
             }
             case 2:
             {   
                 auth.login();
                  isAuthenticated=true;
                 choice=3;
                 break;
             }
             case 3:
             {
                 cout<<"Exit"<<endl;
                 break;
             }
             default:
             {
                 cout<<"Invalid Choice"<<endl;
                 break;
             }
         }
     }
     system("cls");
        if(isAuthenticated)
        {
            while(choice!=5)
            {  system("cls");
                cout<<"********Welcome to the Computer Bazaar***********"<<endl;
                cout<<"1.Add new entry"<<endl;
                cout<<"2.Searching"<<endl;
                cout<<"3.Modification"<<endl;
                cout<<"4.Remove Record"<<endl;
                cout<<"5.Exit"<<endl;
                cout<<"Enter your choice"<<endl;
                cin>>choice;
                switch(choice)
                {
                    case 1:
                    {
                        shop s;
                        s.addNewEntry(auth.get_username());
                        break;
                    }
                    case 2:
                    {
                        shop s;
                        s.searching();
                        break;
                    }
                    case 3:
                    {
                        shop s;
                        s.modification();
                        break;
                    }
                    case 4:
                    {
                        shop s;
                        s.removeRecord();
                        break;
                    }       
                    case 5:
                    {
                        cout<<"Exit"<<endl;
                        break;
                    }
        }
            }
        }
        return 0;   
}
