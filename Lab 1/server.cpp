#include <winsock2.h>
#include <iostream>


using namespace std;

int count_String(char* str)
{
	int res = 0;
	while (*str != '\0')
	{
		if (*str <='9' && *str>'0' && *str % 3 == 0)
			res++;
		str++;
	}
	
	return res;
}

void main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(1280);
	local.sin_addr.s_addr = inet_addr("127.0.0.1");

	SOCKET s_server = socket(AF_INET, SOCK_STREAM, 0);

	int c = bind(s_server, (struct sockaddr*)&local, sizeof(local));
	int r = listen(s_server, 1);

	cout << "Server on" << endl;
	while (true)
	{
		char b[255];
		char buf[255];
		char* res;
		sockaddr_in remote_addr;
		int size = sizeof(remote_addr);
		SOCKET s_client;
		s_client = accept(s_server, (struct sockaddr*)&remote_addr, &size);
		cout << &remote_addr << " connected"<<endl;
		while (recv(s_client, b, sizeof(b), 0) != 0)
		{
			cout << "String: " << b;
			int Res = count_String(b);
			_itoa(Res, buf, 10);
			res = new char[strlen(buf)];
			res = buf;
			send(s_client, res, sizeof(res), 0);
		}
	}
	closesocket(s_server);
	WSACleanup();
}


