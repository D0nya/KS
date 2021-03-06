// Server.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <WinSock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

double fact(int);

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "RUS");

	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(1028);
	local.sin_addr.s_addr = htonl(INADDR_ANY);

	SOCKET s = socket(local.sin_family, SOCK_STREAM, 0);

	bind(s, (struct sockaddr*)&local, sizeof(local));

	cout << "SOCKET descriptor: " << s << endl;									//socket descriptor (# of socket in GDT)

	if (WSAGetLastError() != 0)
	cout << "Error information: " << WSAGetLastError() << endl << endl;	//error info

	int r = listen(s, 5);

	while (true) 
	{
		char res[255], tb[255], *Res;
		int m, n, i = 0;
		double tres;
		sockaddr_in remote_addr;
		int size = sizeof(remote_addr);
		SOCKET s2 = accept(s, (struct sockaddr*)&remote_addr, &size);
		
		cout << "SOCKET descriptor: " << s2 << endl;													//socket descriptor (# of socket in GDT)
		if(WSAGetLastError() != 0)
		cout << "Error information: " << WSAGetLastError() << endl << endl;	//error info

		while (recv(s2, tb, strlen(tb), 0) != 0) 
		{
			if (i == 0) 
			{
				m = atoi(tb);
				i++;
			}

			else if (i == 1)
			{
				n = atoi(tb);

				tres = fact(m) + fact(n);

				sprintf(res, "%.1f", tres);

				Res = (char*)malloc(strlen(res));
				strcpy(Res, res);

				send(s2, Res, strlen(Res) + 1, 0);
				if (WSAGetLastError() == 0) {
					cout << "Пакет успешно отправлен!\nРазмер пакета: " << strlen(Res) + 1 << " байт" << endl;
					i = 0;
				}
				else {
					cout << "Ошибка: " << WSAGetLastError() << endl;
					system("pause");
					return 0;
				}
			}
		}	
		closesocket(s2);
	}
	WSACleanup();
}

double fact(int a) {
	if (a < 0)
		return 0;
	if (a == 0)
		return 1;
	else {
		return a*fact(a - 1);
	}
}
