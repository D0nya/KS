// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main(int argc, char* argv[])
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(1028);
	local.sin_addr.s_addr = htonl(INADDR_ANY);

	SOCKET s = socket(local.sin_family, SOCK_STREAM, 0);

	int c = bind(s, (struct sockaddr*)&local, sizeof(local));

	//Debug(socket info)//
	cout << "SOCKET descriptor: " << s << endl;									//socket descriptor (# of socket in GDT)
	cout << "Error information: " << WSAGetLastError() << endl << endl;	//error info
	//	//	//	//	//	//

	int r = listen(s, 5);

	while (true) {
		char buf[255], res[100], b[255], *Res;
		sockaddr_in remote_addr;
		int size = sizeof(remote_addr);
		SOCKET s2;
		s2 = accept(s, (struct sockaddr*)&remote_addr, &size);
		
		//Debug(socket info)//
		cout << "SOCKET descriptor: " << s << endl;									//socket descriptor (# of socket in GDT)
		cout << "Error information: " << WSAGetLastError() << endl << endl;	//error info

		while (recv(s2, b, sizeof(b), 0) != 0) 
		{
			int i = 0;
			for (unsigned j = 0; j <= strlen(b); j++)
				if (b[j] == 'a') i++;

			_itoa(i, res, 10);

			Res = new char[strlen(res) + 1];
			strcpy(Res, res);
			Res[strlen(res)] = '\0';


			//Посылает данные на соединенный сокет
			send(s2, Res, sizeof(Res) - 2, 0);
		}

		closesocket(s2);

	}

	WSACleanup();

}