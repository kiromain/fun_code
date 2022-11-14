#include <iostream>
#include <windows.h>
#include <stdio.h>

using namespace std;

int main(int argc, const char **argv)
{
    wcout << "Tworzenie lacza nazwanego..." << endl;
    // tworzy lacze nazwane
    HANDLE pipe = CreateNamedPipeW(
        L"\\\\.\\pipe\\my_pipe", // nazwa lacza
        PIPE_ACCESS_OUTBOUND, // moze wysylac tylko
        PIPE_TYPE_BYTE, // wysyla wiadomosc jako byte stream
        1, // pozwala na jedno polaczenie
        0, // brak wychodzacego bufora
        0, // brak wchodzacego bufora
        0, // defaultowe timeWS
        NULL // defaultowwe bezpieczenstwo
    );
    if (pipe == NULL || pipe == INVALID_HANDLE_VALUE) {
        wcout << "Blad tworzenie lacza do wyslania... ";
        // sprawdza bledy w kodzie za pomoca GetLastError()
        system("pause");
        return 1;
    }
    wcout << "Czeka na polaczenie sie drugiej osoby..." << endl;
    
    BOOL result = ConnectNamedPipe(pipe, NULL);
    if (!result) {
        wcout << "Blad w polaczeniu lacza..." << endl;
        // sprawdza blad kodu za pomoca GetLastError()
        CloseHandle(pipe); // zamyka lacze 
        system("pause");
        return 1;
    }
    wcout << "Wysylanie wiadomosci do klienta..." << endl;

    wchar_t buffer[256];
    fgetws(buffer,256,stdin); // wprowdzenie wiadomosci do terminala

    DWORD numBytesWritten = 0;
    result = WriteFile(
        pipe,
        buffer, // wiadomosc wyslana
        wcslen(buffer) * sizeof(wchar_t), // rozmiar wyslanej wiadomosci w bytach (bytes)
        &numBytesWritten, // przechowuje rozmiar wyslanej wiadomosci
        NULL 
    );
    if (result) {
        wcout << "Byte wyslane: " << numBytesWritten << endl;
    } else {
        wcout << "Blad w wysylaniu." << endl;
        // sprawdza blad kodu za pomoca GetLastError()
    }
    // konczy lacze nazwane (rozlacza drugiego uzytkownika)
    CloseHandle(pipe);
    wcout << "Koniec." << endl;
    system("pause");
    return 0;
}
