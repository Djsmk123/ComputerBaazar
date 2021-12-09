using namespace std;
string pass()
  {
    int i,x;
    char ch;
    string pass;
    for(i=0;i>=0;)
     {
       ch=getch();

      if(ch!=8&&ch!=13)
        {
         cout<<"*";
         pass[i]=ch;
         i++;
        }
      else if (ch==8) // if backspace is presssed
       {
         cout<<"\b \b"; // moves cursor to the left print <space> again move cursor to left
         i--;
       }
      else if(ch==13)
    {
         pass[i]='\0'; // if enter is pressed, last character in match[] becomes null
          break;         // for end of string
    }
    else
    {
         break;
    }
  }
 return pass.c_str();
}