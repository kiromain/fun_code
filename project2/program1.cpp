#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#inlcude <string>

int main(int argc, char *argv[])
{
    int fd , numw;
    char sentence [256];

    fd = open("myfifo", O_WRONLY);
    if(fd < 0)
    {
        printf("Nie mozna otworzyc pliku\n");
        return 1;
    }
    
    printf ("Wprowadz wiadomosc : ");
    fgets(sentence,250,stdin);

    numw = write(fd,sentence,strlen(sentence)+1);
    if(numw < 0)
    {
        printf("Nie udalo sie napisac wiadomosci");
        return 1;
    }

    close(fd);
    return 0; 
}