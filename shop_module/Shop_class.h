#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include <chrono>
#include "..\json_module\json.hpp"
#include<list>
#include <ctime> 
using json = nlohmann::json;
using namespace std;
struct orderDetails
{
    string item_code;
    string quantity;
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
         json j;
        string file_name=username+"purchase.json";
        file.open(file_name,ios::in|ios::out|ios::app);
        j=json::parse(file);  
        file.close();
        while(1)
        {
        cout<<"Enter the product id: ";
        cin>>newEntry.pid;
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
        if(flag==0)
        {
        cout<<"Enter the name of the customer: ";
        cin.ignore();
        getline(cin,newEntry.name_of_customer);
        auto start = chrono::system_clock::now();
        auto end = chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end-start;
        time_t end_time = std::chrono::system_clock::to_time_t(end);
        newEntry.date=ctime(&end_time);
        
        while(1)
        {    orderDetails newOrder;        
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
                {    
                   if(i["itemcode"]==newOrder.item_code)
                   {  
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
            cout<<"Do you want to add more items? (y/n):";
            char ch;
            cin>>ch;
             if(ch=='n')
             break;
        }
        }
        list_of_purchase.push_back(newEntry);
        newEntry.order.clear();
        cout<<"New entry added successfully"<<endl;
         cout<<"Do you want to add more enteries? (y/n)";
            char ch;
            cin>>ch;
            if(ch=='n')
                break;
        }
    for(auto x:list_of_purchase)
    {
        json j1;
        for(auto &i:x.order)
        {
            j1["item_code"]=i.item_code;
            j1["quantity"]=i.quantity;
            j1["price"]=i.price;
        }
        json j2;
        j2["pid"]=x.pid;
        j2["name_of_customer"]=x.name_of_customer;
        j2["date"]=x.date;
        j2["order"].push_back(j1);
        j.push_back(j2);
    }
    remove(file_name.c_str());
    file.open(file_name,ios::in|ios::out|ios::app);
    file<<j.dump(4);
    file.close();
    system("pause");
};
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
        
    void modification(string username)
    {
        int ch=0;
        while(ch!=2)
        {   int flag=0;
            fstream file;
            string file_name=username+"purchase.json";
            file.open(file_name,ios::in|ios::out|ios::app);
            if(!file.is_open())
            {
            cout<<"No purchase history found"<<endl;
            }

            json j;
            j=json::parse(file);
            file.close();
            cout<<"1. Modify by product id"<<endl;
            cout<<"2. Go back"<<endl;
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
                            {   cout<<"-----------------------------------------"<<endl;
                                cout<<"Item code: "<<x["item_code"]<<endl;
                                cout<<"Quantity: "<<x["quantity"]<<endl;
                                cout<<"Price: "<<x["price"]<<endl;
                               cout<<"-----------------------------------------"<<endl;
                            }
                            cout<<"-----------------------------------------"<<endl;
                            //to change Date and customerName
                            while(ch!=5)
                            {
                                cout<<"1. Change date"<<endl;
                                cout<<"2. Change customer name"<<endl;
                                cout<<"3. Change Order Details(Existing Order)"<<endl;
                                cout<<"4. Add New Order Details"<<endl;
                                cout<<"5. Go back"<<endl;
                                cout<<"Enter your choice: ";
                                cin>>ch;
                                switch(ch)
                                {
                                    case 1:
                                    {
                                        string date;
                                        cout<<"Enter the new date: ";
                                        cin>>date;
                                        i["date"]=date;
                                        break;
                                    }
                                    case 2:
                                    {
                                        string name;
                                        cout<<"Enter the new customer name: ";
                                        cin>>name;
                                        i["name_of_customer"]=name;
                                        break;
                                    }
                             case 3:
                                    {
                                        string item_code;
                                        string quantity;
                                        string price;
                                        cout<<"Enter the item code: ";
                                        cin>>item_code;
                                        cout<<"Enter the quantity: ";
                                        cin>>quantity;
                                        cout<<"Enter the price: ";
                                        cin>>price;
                                        int flag=0;
                                        for(auto &x:i["order"])
                                        {
                                            if(x["item_code"]==item_code)
                                            {
                                                x["quantity"]=quantity;
                                                x["price"]=price;
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
                                    {
                                        string item_code;
                                        string quantity;
                                        string price;
                                        int flag=0;
                                        cout<<"Enter the item code: ";
                                        cin>>item_code;
                                        cout<<"Enter the quantity: ";
                                        cin>>quantity;
                                        fstream file;
                                        file.open("availProd.json",ios::in|ios::out|ios::app);
                                        if(!file.is_open())
                                        {
                                            cout<<"No products available"<<endl;
                                        
                                        }
                                        json avail=json::parse(file);
                                        file.close();
                                        for(auto &x:avail)
                                        {
                                            if(x["itemCode"]==item_code)
                                            {
                                                price=x["price"];  
                                                flag=1;
                                                break;
                                            }
                                        }
                                        for(auto &x:i["order"])
                                        {
                                            if(x["item_code"]==item_code)
                                            {
                                                flag=0;
                                                break;
                                            }
                                        }
                                        if(flag==0)
                                        {
                                            cout<<"No such entry found"<<endl;
                                        }
                                    }
                                    case 5:
                                    {
                                        break;
                                    }
                                    default:
                                    {
                                        cout<<"Invalid choice"<<endl;
                                    }
                            }
                            }
                        }
                        break;
                    }
                    remove(file_name.c_str());
                    file.open(file_name,ios::out|ios::app);
                    cout<<j.dump(4)<<endl;
                    file<<j;
                    file.close();
                    cout<<"Modification successful"<<endl;
                    system("pause");
                    break;
                }
                case 2: break;
                default: cout<<"Invalid choice"<<endl;   
            }               
    }
    }
    void removeRecord(string username)
    {
        fstream file;
        int ch=0;
        string file_name=username+"purchase.json";
        file.open(file_name,ios::in|ios::out|ios::app);
        if(!file.is_open())
        {
            cout<<"No purchase history found"<<endl;
        }
        json j;
        j=json::parse(file);

        file.close();
        while(ch!=2)
        {
            cout<<"1. Remove by product id"<<endl;
            cout<<"2. Go back"<<endl;
            cout<<"Enter your choice: ";
            cin>>ch;
            switch(ch)
            {
                case 1:
                {
                    string pid;
                    int flag=0;
                    cout<<"Enter the product id: ";
                    cin>>pid;
                    for(auto &i:j)
                    {
                        if(i["pid"]==pid)
                        {
                             i.erase(i.find(pid));
                            cout<<"Removal successful"<<endl;
                            system("pause");
                            flag=1;
                            remove(file_name.c_str());
                            file.open(file_name,ios::out|ios::app);
                            file<<j;
                            file.close();
                            break;
                        }
                    }
                    if(flag==0)
                    {
                        cout<<"No such entry found"<<endl;
                    }
                    break;
                }
                case 2: break;
                default: cout<<"Invalid choice"<<endl;
            }
    }
    }
    void previewBill(string username)
    {
        fstream file;
        purchasedetails details;
         string  filename=username+"purchase.json";
        file.open(filename,ios::in);
        if(!file.is_open())
        {
            cout<<"No purchase history found"<<endl;
             system("pause");
            return;
        }
        if(file.peek()==EOF)
        {
            cout<<"No purchase history found"<<endl;
            system("pause");
            return;
        }
    
    
        json j=json::parse(file);
            file.close();
        cout<<"Enter the product id: ";
        cin>>details.pid;

        for(auto &i:j)
        {   if(i["pid"]==details.pid)
            {
                system("cls");
            
                double total=0;
                double gst=0;
             cout<<"Purchase id: "<<i["pid"]<<endl;
             cout<<"___________________________________________";
             cout<<"___________________________________________"<<endl;
              cout<<"___________________________________________";
             cout<<"___________________________________________"<<endl;
             cout<<"Customer name: "<<i["name_of_customer"]<<setw(30);
             cout<<"Date: "<<i["date"]<<endl;
              cout<<"___________________________________________";
             cout<<"___________________________________________"<<endl;
              cout<<"___________________________________________";
             cout<<"___________________________________________"<<endl;
            cout<<setw(85)<<("Order details ")<<endl;
            for(auto &x:i["order"])
            {   
                cout<<"Item code: "<<x["item_code"]<<endl;
                cout<<"Quantity: "<<x["quantity"]<<endl;
                cout<<"Price:"<<x["price"]<<endl;
                 cout<<"___________________________________________";
                 cout<<"___________________________________________"<<endl;
                double price=strtod(x["price"].get<string>().c_str(),NULL);
                double quantity=strtod(x["quantity"].get<string>().c_str(),NULL);
                 total+=price*quantity;
            }
            cout<<"___________________________________________";
             cout<<"___________________________________________"<<endl;
              cout<<"___________________________________________";
             cout<<"___________________________________________"<<endl;
            gst=total*0.18;
             cout<<setw(80)<<"GST(18%): "<<gst<<endl;
            cout<<setw(80)<<"Total:"<<total<<endl;
             cout<<"___________________________________________";
             cout<<"___________________________________________"<<endl;
              cout<<"___________________________________________";
             cout<<"___________________________________________"<<endl;
             system("pause");
             return ;
        }

        }
        cout<<"No such entry found"<<endl;
        cout<<"-----------------------------------------"<<endl;
        }
};
