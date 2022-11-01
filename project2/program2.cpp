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
    cout<<"Podaj nazwe lacza: ";
    string nazwa_lacza;
    cin>>nazwa_lacza;
    const char *myfifo = nazwa_lacza.c_str();

    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    int fd = open(myfifo,O_RDONLY);
    char sentence [256];

    printf ("Enter sentence to append: ");
    
    if(read(fd,sentence,strlen(sentence)+1) == -1) return 2; 
    fgets (sentence,256,stdout);
    printf("User2: %s\n", sentence);

    close(fd);
    return(0); 
}