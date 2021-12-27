#include<fstream>
#include<iostream>
#include<string>
#include<list>
#include "passwordInput.h"
#include "registerNewUser.h"
#include "loginuser.h"
#include "../json_Module/json.hpp"
using json = nlohmann::json;
using namespace std;
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
            string s= "curl --ssl-reqd   --url smtps://smtp.gmail.com:465   --user computerbazarbot74804@gmail.com:PdC35qcGgyX46H   --mail-from computerbazarbot74804@gmail.com  --mail-rcpt ";
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