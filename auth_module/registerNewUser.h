#include<string>
#include<iostream>
#include<fstream>
#include "../json_Module/json.hpp"
using json = nlohmann::json;
using namespace std;
int reg_user(string username, string password,string email)
{   //check if the username is already taken
    fstream file;
    file.open("users.json", ios::in | ios::out|ios::app); //open the file  
    json j=json::parse(file);
    file.close();
        for(auto& i:j)
        {
            if(i["username"]==username)
            {
                cout<<"Username already taken"<<endl;
                system("pause");
                return 1;
            }
        }
       //if the username is not taken
        json j1;
        j1["username"]=username;
        j1["password"]=password;
        j1["email"]=email;
        j.push_back(j1);
        remove("users.json");
        file.open("users.json", ios::out | ios::app);
        file<<j;
        cout<<"Registration Successful"<<endl;
        system("pause");
        return 0;
}