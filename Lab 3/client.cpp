#include <iostream>
#include <WinSock2.h>
using namespace std;

int main()
{
	setlocale(LC_ALL, "");

	WORD wVersionRequested;
	WSADATA wsaData;
	int err, i;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) { return 0; }
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	// указание адреса и порта сервера
	sockaddr_in dest_addr;
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_port = htons(1280);
	dest_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	connect(s, (sockaddr *)&dest_addr, sizeof(dest_addr));
	char city[20];
	char buf[256];
	int choose;
	while (true)
	{
		cout << "√ород: ";
		cin >> city;
		send(s, city, strlen(city) + 1, 0);
		int end;
		end = recv(s, buf, sizeof(buf), 0);
		buf[end] = '\0';
		cout << buf;
		cout << endl;
		cout << "1-продолжить, 2-exit" << endl;
		cin >> choose;
		if (choose == 2)
				break;
	}
	closesocket(s);
}

