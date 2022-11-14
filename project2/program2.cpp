#include <iostream>
#include <windows.h>

using namespace std;

int main(int argc, const char **argv)
{
    wcout << "Laczenie z laczem nazwanym..." << endl;
    // otwiera lacze nazwane
    HANDLE pipe = CreateFileW(
        L"\\\\.\\pipe\\my_pipe",
        GENERIC_READ, // mozna tylko czytac
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (pipe == INVALID_HANDLE_VALUE) {
        wcout << "Blad w polaczeniu lacza." << endl;
        // sprawdza bledy w kodzie za pomoca GetLastError()
        system("pause");
        return 1;
    }
    wcout << "Czytanie wiadomosci z lacza..." << endl;
    
    wchar_t buffer[128];
    DWORD numBytesRead = 0;
    BOOL result = ReadFile(
        pipe,
        buffer, // wiadomosc z lacza bedzie w buffer przechowywana
        127 * sizeof(wchar_t), // ilosc bytow przeznaczonych
        &numBytesRead, //przechowuje ilosc bytow potrzebnych do odczytu wiadomosci
        NULL 
    );
    if (result) {
        buffer[numBytesRead / sizeof(wchar_t)] = '\0';
        wcout << "Ilosc bytow odczytanych: " << numBytesRead << endl;
        wcout << "Wiadomosc: " << buffer << endl;
    } else {
        wcout << "Blad odczytania wiadomosci." << endl;
    }
    // Zamyka lacza nazwane
    CloseHandle(pipe);
    wcout << "Koniec." << endl;
    system("pause");
    return 0;
}