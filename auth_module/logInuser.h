#include<string>
#include<iostream>
#include<fstream>
#include "../json_Module/json.hpp"
using json = nlohmann::json;
using namespace std;
int log_in(string username, string password)
{    fstream file;
     file.open("users.json", ios::in|ios::out|ios::app);
     if(!file.is_open())
     {
         cout<<"Error opening file";
         return -1;
     }
     if(file.peek()==EOF)
     {
         cout<<"No users in file";
         return -1;
     }
    json j=json::parse(file);
    file.close();
      for(auto i:j)
    {
      if(i["username"]==username && i["password"]==password)
      {   cout<<"log in success\n"<<endl;
          system("pause");
          cout<<"\n";
          return 0;
      }
  }
    return 1;

}