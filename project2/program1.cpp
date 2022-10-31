#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

using namespace std;

int main()
{
     cout<<"Podaj nazwe katalogu: ";
     string name1;
     cin>>name1;
     const char* name = name1.c_str();

     DIR *dir; // pointer zeby otworzyc katalog;
     struct dirent *entry; // pliki znajdujacy sie w tym katalogu

     //otwiera
     dir = opendir(name);
     if(!dir)
     {
          cout<<"Nie znaleziono katalogu"<<endl;
          return;
     }else{
          int fdes,res;
          string nazwa_lacza1;
          
          char arr1[150];

          cout<<"Podaj nazwe lacza nazwanego : ";
          cin>>nazwa_lacza1;
          const char* nazwa_lacza = nazwa_lacza1.c_str();

          if(mkfifo(nazwa_lacza,S_IRUSR | S_IWUSR)<0){ 
               perror("Blad");
               return;
          }else{
               while(1)
               {
                    fdes = open(nazwa_lacza,O_WRONLY);
                    fgets(arr1, 10, stdin);
                    write(fdes,arr1,strlen(arr1)+1);
                    close(fdes);
               }
          }
     }
     
     //zamyka
     closedir(dir);
     //system("my_bash_script.sh");
}
