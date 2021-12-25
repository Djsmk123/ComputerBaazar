#include<iostream>
#include<fstream>
#include<string>
#include <chrono>
#include "..\json_module\json.hpp"
#include<list>
#include <ctime> 
using json = nlohmann::json;
using namespace std;
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
            cin.ignore();
             getline(cin,p.name);
            cout<<"Enter the item code of the product: ";
            cin>>p.item_code;
            cout<<"Enter the price of the product: ";
            cin>>p.price;
            int flag=0;
            for(auto &i:j)
            {
                if(i["itemcode"]==p.item_code)
                {   cout<<"Product already exists";
                    flag=1;
                    break;
                }
            }
           
            if(flag==0)
            {
                products.push_back(p);
            }
            cout<<"Do you want to add more products?(y/n)";
            char ch;
            cin>>ch;
            if(ch=='n' || 'N')
            {
                break;
            } 
            system("pause");
        }
        if(products.size()>0)
        {  
            for(auto &i:products)
            {
                j.push_back(
                {
                    {"itemName",i.name},
                    {"itemcode",i.item_code},
                    {"price",i.price}
                });
            }
             file.close();
            remove("availProd.json");
            file.open("availProd.json", ios::out);
            file<<j;
            cout<<"Products added successfully";
            cout<<"-----------------------------------------"<<endl;
            file.close();
        }


    }
};