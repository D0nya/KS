// Client.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <WinSock2.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

void sendPack(char[255], SOCKET);

int main() {

	setlocale(LC_ALL, "RUS");

	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	struct sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(1028);
	//т.к. клиент и сервер на одном компьютере,
	// пишем адрес 127.0.0.1
	peer.sin_addr.s_addr = inet_addr("127.0.0.1");

	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);

	connect(s, (struct sockaddr*) &peer, sizeof(peer));

	char buf1[255], buf2[255], b[255];

	cout << "Введите 2 числа: " << endl;
	cout << "\tm: "; cin >> buf1;
	cout << "\tn: "; cin >> buf2;

	sendPack(buf1, s);
	sendPack(buf2, s);

	if (recv(s, b, strlen(b), 0) != 0) 
	{
		cout << b << endl;
	}

	closesocket(s);

	WSACleanup();

	system("pause");
	return 0;
}

void sendPack(char pak[255], SOCKET s) 
{
	char *line;
	line = (char*)malloc(strlen(pak));
	strcpy(line, pak);
	send(s, line, strlen(line), 0);
	if (WSAGetLastError() == 0) {
		cout << "Пакет успешно отправлен!\nРазмер пакета: " << strlen(line) + 1 << " байт" << endl << endl;
	}
	else {
		cout << "Ошибка: " << WSAGetLastError() << endl;
	}
}