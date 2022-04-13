//Sydney Honyouti
//QOTD.cpp File
//Due Date: 3/2/22

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include "qotd.h"
#include <WinSock2.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

const int MAXNAME = 80;
const int MAXBUF = 128;

int main() {
    //1. WSAStartup - must always initialize the Windows Sockets Library
    WORD wVersionRequired = 0x0101;
    WSADATA wsaData;
    SOCKET s;
    char msg[MAXBUF] = "";
    char buf[MAXBUF] = "";
    char host[MAXNAME] = "";
    char service[MAXNAME] = "";
    char protocol[4] = "";

    string userIPAddress;

    int err = WSAStartup(wVersionRequired, &wsaData);
    if (err) {
        cout << "Unable to intitialize the Windows Socket Library" << endl;
        return -1;
    }

    //socket, connect - done by connectsock
    //need to set the host, service, protocol
    strcpy_s(protocol, "udp");

    //Asking the name or IP address of QOTD server
    cout << "Name or IP address of QOTD server? ";
    getline(cin, userIPAddress);
    strcpy(msg, userIPAddress.c_str());


    strcpy_s(service, "17");

    s = connectsock(host, service, protocol);

    if (s != INVALID_SOCKET) {
        string User_Input_Message;

        while(true) {

            //Prompting for reading a command
            cout << "Command to send? ";
            getline(cin, User_Input_Message);
            strcpy(msg, User_Input_Message.c_str());
            cout << endl;

            if (_stricmp("quit", msg) == 0) {
                break;
            }
            else if (_stricmp("sendqotd", msg) == 0) {
                //You have to do a sendto()
                int numBytesSent = UDP_send(s, msg, strlen(msg), host, service);

                //Wait time
                cout << "Quote of the day: " << endl;
                int status = wait(s, WAIT_TIME, WAIT_TIME);

                //Keep going through the loop until status is 0
                //this shows that there is no more data to be received
                do {
                    if (status == 1) {
                        int numBytesRecv = UDP_recv(s, msg, MAX_RECV_BUF, host, service);
                        //Loop though the msg or buf array
                        for (int x = 0; x < numBytesRecv; x++) {
                            cout << msg[x];
                        }
                    }
                    //Check on the status to make sure that it is not still 0
                    status = wait(s, WAIT_TIME, WAIT_TIME);
                } while (status != 0);
            }
            else { cout << "Please but in 'sendqotd' command " << endl; }
            cout << endl;
        }

        //Close socket
        closesocket(s);

    }
    //WSACleanup - this is going to shut down the windowsSocket library
    WSACleanup();
}