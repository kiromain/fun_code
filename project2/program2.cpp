#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    // FIFO file path
    /*
    cout<<"Podaj nazwe lacza: ";
    string nazwa_lacza;
    cin>>nazwa_lacza;
    const char *myfifo = nazwa_lacza.c_str();*/

    int fd = open("myfifo",O_RDONLY);
    char sentence [256];

    printf ("Wiadomosc od uzytkownika numer 1: ");
    
    read(fd,sentence,strlen(sentence)+1);

    printf("Wiadomosc : %s\n", sentence);

    close(fd);
    return(0); 
}