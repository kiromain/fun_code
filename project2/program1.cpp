<<<<<<< HEAD
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
=======
#include <iostream>
#include <windows.h>
#include <stdio.h>

using namespace std;

int main(int argc, const char **argv)
{
    wcout << "Creating an instance of a named pipe..." << endl;
    // Create a pipe to send data
    HANDLE pipe = CreateNamedPipeW(
        L"\\\\.\\pipe\\my_pipe", // name of the pipe
        PIPE_ACCESS_OUTBOUND, // 1-way pipe -- send only
        PIPE_TYPE_BYTE, // send data as a byte stream
        1, // only allow 1 instance of this pipe
        0, // no outbound buffer
        0, // no inbound buffer
        0, // use default wait timeWS
        NULL // use default security attributes
    );
    if (pipe == NULL || pipe == INVALID_HANDLE_VALUE) {
        wcout << "Failed to create outbound pipe instance.";
        // look up error code here using GetLastError()
        system("pause");
        return 1;
    }
    wcout << "Waiting for a client to connect to the pipe..." << endl;
    // This call blocks until a client process connects to the pipe
    BOOL result = ConnectNamedPipe(pipe, NULL);
    if (!result) {
        wcout << "Failed to make connection on named pipe." << endl;
        // look up error code here using GetLastError()
        CloseHandle(pipe); // close the pipe
        system("pause");
        return 1;
    }
    wcout << "Sending data to pipe..." << endl;
    // This call blocks until a client process reads all the data
    wchar_t buffer[256];
    fgetws(buffer,256,stdin);

    DWORD numBytesWritten = 0;
    result = WriteFile(
        pipe, // handle to our outbound pipe
        buffer, // data to send
        wcslen(buffer) * sizeof(wchar_t), // length of data to send (bytes)
        &numBytesWritten, // will store actual amount of data sent
        NULL // not using overlapped IO
    );
    if (result) {
        wcout << "Number of bytes sent: " << numBytesWritten << endl;
    } else {
        wcout << "Failed to send data." << endl;
        // look up error code here using GetLastError()
    }
    // Close the pipe (automatically disconnects client too)
    CloseHandle(pipe);
    wcout << "Done." << endl;
    system("pause");
    return 0;
}
>>>>>>> 3d8023f4c3bea42fa1f59d2e1b867b2ccf76883c
