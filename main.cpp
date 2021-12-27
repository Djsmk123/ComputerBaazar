//All the required libraries are included here
//The main function is the entry point of the program
// Header file for input output
#include <iostream>
// Header file for string
#include<string>
// Header file for 2Shop_class
#include "shop_module\Shop_class.h"
#include  "shop_module\products_class.h"
// Header file for users_authentication
#include "auth_module\Auth_class.h"
//Main function Declaration
 int MainModule();
//Driver Code
int main()
{   
    MainModule();
    
}
//Main function Implementation
int MainModule()
{
      int choice=1;
      bool isAuthenticated=false;
      //Authentication object is created
      authentication auth;
     while (choice!=4)
     {   //Menu is displayed
          system("cls");
         cout<<"********Welcome to the Computer Bazaar***********"<<endl;
         cout<<"1.New user(Registered Here)"<<endl;
         cout<<"2.Existing user(Login Here)"<<endl;
         cout<<"3.Forgot password"<<endl;
         cout<<"4.Exit"<<endl;
         cout<<"Enter your choice"<<endl;
          cin>>choice;
         switch(choice)
         {  //Switch case is used to perform the required operation
             case 1:
             {   //New user is created
                 auth.register_user();
                 choice=4;
                 isAuthenticated=true;
                 break;
             }
             case 2:
             {   //Existing user is logged in
                 auth.login();
                  isAuthenticated=true;
                 choice=4;
                 break;
             }
             
             case 3:
             {   //Forgot password is reset
                  auth.forgot_password();

                    break;
             }
             case 4:
             {
                 //Exit is performed
                 break;
             }
             default:
             {  //If the user enters the wrong choice
                 cout<<"Invalid Choice"<<endl;
                 break;
             }
         }
     }
  
     system("cls");
        //If the user is authenticated
        if(isAuthenticated)
        {
            while(choice!=8)
            {  system("cls");
               //Menu is displayed
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
                {  //Switch case is used to perform the required operation
                    case 1:
                    {   //New entry is added
                        shop s;
                        s.addNewEntry(auth.get_username());
                        break;
                    }
                    case 2:
                    {   //Bill is previewed
                        shop s;
                        s.previewBill(auth.get_username());
                        break;
                    }
                    case 3:
                    {  //New product is added 
                      
                       availableProducts a;
                         a.addNewProduct();
                        break;
                    }
                    case 4:
                    {
                        //All the products are listed
                        availableProducts a;
                        a.listAllProducts();
                        break;
                    }
                
                    case 5:
                    {   //Searching is performed
                        shop s;
                        s.searching(auth.get_username());
                        break;
                    }
                    case 6:
                    {   //Modification is performed
                        shop s;
                        s.modification(auth.get_username());
                        break;
                    }
                    case 7:
                    {  //Record is removed
                        shop s;
                        s.removeRecord(auth.get_username());
                        break;
                    }       
                    case 8:
                    {  //Exit is performed
                        cout<<"Exit"<<endl;
                        break;
                    }
                    default:
                    {  //If the user enters the wrong choice
                        cout<<"Invalid Choice"<<endl;
                        break;
                    }
        }
            }
        }
        return 0;   
}
