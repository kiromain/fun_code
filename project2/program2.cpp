#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    char sentence [256];
    int fp, numr ,numop;
    
    /*
    fp = mkfifo("myfifo", S_IFIFO|0666);
    if(fp < 0)
    {
        printf("Cant make a file\n");
        return 1;
    }*/
    printf("Message: %s\n",sentence); 

    numop = open("myfifo",O_RDONLY);
    if(numop < 0)
    {
        printf("Cant open the file\n");
        return 1;
    }

    numr = read(fp,&sentence,sizeof(sentence));
    if( numr < 0)
    {
         printf("Cant read the message\n");
        return 1;
    }
    fgets(sentence,256,stdin);

    printf("Message: %s\n",sentence);
    close(fp);
    
    return 0; 
}