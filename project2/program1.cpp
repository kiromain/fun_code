#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <dirent.h>

#include <sys/stat.h>
#include <sys/types.h>
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

    if((mkfifo("myfifo", 0777)) < 0){
    	printf("Nie mozna stworzyc pliku\n");
    	return 1;
	}

    fd = open("myfifo", O_WRONLY);
    if(fd < 0)
    {
        printf("Nie mozna otworzyc pliku\n");
        return 1;
    }

    char sentence [256];
    printf ("Wprowadz wiadomosc : ");
    cin.getline(sentence,250,'END');

    if((write(fd,sentence,strlen(sentence)+1))<0){
        printf("\n %s \n", strerror(errno));
        return 1;
    }

    close(fd);
    return 0; 

    
}
