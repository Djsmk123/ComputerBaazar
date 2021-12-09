#include<string>
#include<iostream>
#include<fstream>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
int log_in(string username, string password)
{    fstream file;
    file.open("users.json", ios::in);
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