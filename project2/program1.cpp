#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

using namespace std;

int main(int argc, char *argv[])
{
    int fd;

    // FIFO file path
    cout<<"Podaj nazwe lacza: ";
    string nazwa_lacza;
    cin>>nazwa_lacza;
    const char *myfifo = nazwa_lacza.c_str();

    if(mkfifo(myfifo, 0777) == -1){
        perror("Blad");
        return 1;
    }

    fd = open(myfifo, O_WRONLY);

    char sentence [256];
    printf ("Enter sentence to append: ");
    fgets (sentence,256,stdin);

    write(fd,sentence,strlen(sentence)+1);

    close(fd);
    return(0); 
}