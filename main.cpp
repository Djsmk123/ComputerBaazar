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
//available products data structure
struct product
{
    string name;
    string item_code;
    string price;
};
class availableProducts
{  private:
    list<product> products;
   public:
   void listAllProducts(){
       fstream file;
       file.open("availProd.json",ios::in);
         json j=json::parse(file);
         cout<<"Available Products"<<endl;
           cout<<"-----------------------------------------"<<endl;
         for(auto& i:j)
         {
                cout<<"Name: "<<i["itemName"]<<endl;
                cout<<"Item Code: "<<i["itemcode"]<<endl;
                cout<<"Price: "<<i["price"]<<endl;
                cout<<"-----------------------------------------"<<endl;
         }
         system("pause");
   }
    void addNewProduct()
    {
        product p;
         fstream file;
            file.open("availProd.json", ios::in | ios::out);
            if(!file)
            {
                cout<<"file not found";
                return;
            }
            json j=json::parse(file);
            
        while(1)
        { 
            cout<<"Enter the name of the product: ";
            cin>>p.name;
            cout<<"Enter the item code of the product: ";
            cin>>p.item_code;
            cout<<"Enter the price of the product: ";
            cin>>p.price;
            int flag=0;
            for(auto &i:j)
            {
                if(i["itemcode"]==p.item_code)
                {
                    flag=1;
                    break;
                }
            }
            if(flag==1)
            {
                cout<<"Product already exists";
                continue;
            }
            else
            {
                products.push_back(p);  
            }
            cout<<"Do you want to add more products?(y/n)";
            char ch;
            cin>>ch;
            if(ch=='n' ||'N')
            {
                break;
            } 
        }
        if(products.size()>0)
        {  cout<<"here"<<endl;
            system("pause");
            for(auto &i:products)
            {
                j.push_back(
                {
                    {"itemName",i.name},
                    {"itemcode",i.item_code},
                    {"price",i.price}
                });
            }
             system("pause");
            cout<<j<<endl;
             system("pause");
             file.close();
            remove("availProd.json");
            file.open("availProd.json", ios::out);
            file<<j;
        }


    }
};
//user Class
class authentication
{
private:
    string username;
    string password;
    string email;
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
void forgot_password(){
    cout<<"Enter your email: ";
    cin>>email;
    cout<<"Enter your username: ";
    cin>>username;
    fstream file;
    file.open("users.json",ios::in);
    if(!file)
    {
        cout<<"file not found";
        return;
    }
    
    json j=json::parse(file);
    file.close();
    for(auto &i:j)
    {
        if(i["username"]==username && i["email"]==email)
        {
            fstream file;
            file.open("mail.txt",ios::in | ios::out| ios::app);
            if(!file)
            {
                cout<<"file not found";
                return;
            }
            file<<"Do not reply this email as it is auto generated.\nYour password is: "<<i["password"];
            file<<"\nThank You for using our service";
            file.close();
            string s= "curl --ssl-reqd   --url smtps://smtp.gmail.com:465   --user youremailusername@gmail.com:password   --mail-from youremailusername@gmail.com --mail-rcpt ";
            s+=email;
            s+="   --upload-file mail.txt"; 
             system(s.c_str());
             cout<<"Check your email for your password"<<endl;
             cout<<"Thank You for using our service"<<endl;
                system("pause");
                remove("mail.txt");
                return;
        }
    }
    cout<<"User and email not valid"<<endl;
     system("pause");
        return ;
}
    void register_user()
    {     
         int flag=1;
        while(flag!=0)

        {    cout<<"Enter your email address:";
              cin>>email;
             cout<<"Enter your username: ";
             cin>>username;
             cout<<"Enter your password: ";
              password=pass();
              flag=reg_user(username,password,email);
          
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
    string price;
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
        json j=json::parse(file);
        int flag=0;
        for(auto &i:j)
        {
            if(i["pid"]==newEntry.pid)
            {
                cout<<"Product id already exists"<<endl;
                system("pause");
                flag=1;
                break;
            }
        }
        if(flag==1)
        {
            break;
        }
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
            fstream available_items;
            string file_name="availProd.json";
            available_items.open(file_name,ios::in|ios::out|ios::app);
             int flag=0;
            if(!available_items.is_open())
            {
                cout<<"File not found"<<endl;
                break;
            }
            else
            {
                json j;
                j=json::parse(available_items);
                for(auto& i:j)
                {    cout<<i["itemcode"]<<endl;
                   if(i["itemcode"]==newOrder.item_code)
                   {   cout<<"price: "<<i["price"]<<endl;
                   newOrder.price=i["price"];
                       flag=1;
                       break;
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
    void searching(string username)
    {
        int ch=0;
        while(ch!=4)
        {   int flag=0;
            fstream file;
            string file_name=username+"purchase.json";
            file.open(file_name,ios::in|ios::out|ios::app);
            if(!file.is_open())
            {
            cout<<"No purchase history found"<<endl;
            break;
            }
            json j;
            j=json::parse(file);
            cout<<"1. Search by product id"<<endl;
            cout<<"2. Search by customer name"<<endl;
            cout<<"3. Search by date"<<endl;
            cout<<"4. Go back"<<endl;
            cout<<"Enter your choice: ";
            cin>>ch;
            switch(ch)
            {
                case 1:{ 
                     string pid;
                    cout<<"Enter the product id: ";
                    cin>>pid;
                    for(auto &i:j)
                    {
                        if(i["pid"]==pid)
                        {    cout<<"-----------------------------------------"<<endl;
                            cout<<"Product id: "<<i["pid"]<<endl;
                            cout<<"Name of customer: "<<i["name_of_customer"]<<endl;
                            cout<<"Date: "<<i["date"]<<endl;
                             cout<<"-----------------------------------------"<<endl;
                             cout<<"Order details:\n "<<endl;
                            for(auto &x:i["order"])
                            { cout<<"-----------------------------------------"<<endl;
                                cout<<"Item code: "<<x["item_code"]<<endl;
                                cout<<"Quantity: "<<x["quantity"]<<endl;
                                cout<<"Price: "<<x["price"]<<endl;
                               cout<<"-----------------------------------------"<<endl;
                            }
                            flag=1;
                            break;
                        }
                    }
                    if(flag==0)
                    {
                        cout<<"No such entry found"<<endl;
                    }
                    break;
                }
                case 2:
                {
                    string name;
                    cout<<"Enter the customer name: ";
                    cin>>name;
                    for(auto &i:j)
                    {
                        if(i["name_of_customer"]==name)
                        {   cout<<"-----------------------------------------"<<endl;
                            cout<<"Product id: "<<i["pid"]<<endl;
                            cout<<"Name of customer: "<<i["name_of_customer"]<<endl;
                            cout<<"Date: "<<i["date"]<<endl;
                             cout<<"-----------------------------------------"<<endl;
                            cout<<"Order details:\n "<<endl;
                            for(auto &x:i["order"])
                            {   cout<<"-----------------------------------------"<<endl;
                                cout<<"Item code: "<<x["item_code"]<<endl;
                                cout<<"Quantity: "<<x["quantity"]<<endl;
                                cout<<"Price: "<<x["price"]<<endl;
                              cout<<"-----------------------------------------"<<endl;
                            }
                            flag=1;
                            break;
                        }
                    }
                     if(flag==0)
                    {
                        cout<<"No such entry found"<<endl;
                    }
                      break;
                }
                case 3:
                {
                    string date;
                    cout<<"Enter the date: ";
    
                    cin>>date;
                    for(auto &i:j)
                    {
                        if(i["date"]==date)
                        {  cout<<"-----------------------------------------"<<endl;
                            cout<<"Product id: "<<i["pid"]<<endl;
                            cout<<"Name of customer: "<<i["name_of_customer"]<<endl;
                            cout<<"Date: "<<i["date"]<<endl;
                             cout<<"-----------------------------------------"<<endl;
                            cout<<"Order details:\n "<<endl;
                            cout<<"-----------------------------------------"<<endl;
                            for(auto &x:i["order"])
                            { cout<<"-----------------------------------------"<<endl;
                                cout<<"Item code: "<<x["item_code"]<<endl;
                                cout<<"Quantity: "<<x["quantity"]<<endl;
                                cout<<"Price: "<<x["price"]<<endl;
                              cout<<"-----------------------------------------"<<endl;
                            }
                              flag=1;
                              break;
                        }    
                    }
                     if(flag==0)
                    {
                        cout<<"No such entry found"<<endl;
                    }
                      break;
                }
                case 4:
                    break;
                default:
                    cout<<"Invalid choice"<<endl;
            }
        }
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
     while (choice!=4)
     {    system("cls");
         cout<<"********Welcome to the Computer Bazaar***********"<<endl;
         cout<<"1.New user(Registered Here)"<<endl;
         cout<<"2.Existing user(Login Here)"<<endl;
         cout<<"3.Forgot password"<<endl;
         cout<<"4.Exit"<<endl;
         cout<<"Enter your choice"<<endl;
          cin>>choice;
         switch(choice)
         {
             case 1:
             {
                 auth.register_user();
                 choice=4;
                 isAuthenticated=true;
                 break;
             }
             case 2:
             {   
                 auth.login();
                  isAuthenticated=true;
                 choice=4;
                 break;
             }
             
             case 3:
             {
                 auth.forgot_password();
                
                    break;
             }
             case 4:
             {
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
            while(choice!=8)
            {  system("cls");
                cout<<"********Welcome to the Computer Bazaar***********"<<endl;
                cout<<"1.Add new entry"<<endl;
                cout<<"2.Preview bill(using PID)"<<endl;
                cout<<"3.Add new product"<<endl;
                cout<<"4.List all products available"<<endl;
                cout<<"5.Searching"<<endl;
                cout<<"6.Modification"<<endl;
                cout<<"7.Remove Record"<<endl;
                cout<<"8.Exit"<<endl;
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
                        //shop s;
                        //s.previewBill();
                        break;
                    }
                    case 3:
                    {
                       availableProducts a;
                       a.addNewProduct();
                        break;
                    }
                    case 4:
                    {
                        availableProducts a;
                        a.listAllProducts();
                        break;
                    }
                
                    case 5:
                    {
                        shop s;
                        s.searching(auth.get_username());
                        break;
                    }
                    case 6:
                    {
                        shop s;
                        s.modification();
                        break;
                    }
                    case 7:
                    {
                        shop s;
                        s.removeRecord();
                        break;
                    }       
                    case 8:
                    {
                        cout<<"Exit"<<endl;
                        break;
                    }
        }
            }
        }
        return 0;   
}
