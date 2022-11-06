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

int main(int argc, char *argv[])
{
    int fd;

    // FIFO file path
    /*
    cout<<"Podaj nazwe lacza: ";
    string nazwa_lacza;
    cin>>nazwa_lacza;
    const char *myfifo = nazwa_lacza.c_str();*/

    mkfifo("myfifo", 0777);

    fd = open("myfifo", O_WRONLY);
    if(fd < 0)
    {
        printf("\n %s \n", strerror(errno));
        return 0;
    }

    char sentence [256];
    printf ("Wprowadz wiadomosc : ");
    cin.getline(sentence,250,'END');

    if((write(fd,sentence,strlen(sentence)+1))<0){
        printf("\n %s \n", strerror(errno));
        return 0;
    }

    close(fd);
    return(0); 

    
}
system("myfile.sh");