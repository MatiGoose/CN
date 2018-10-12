#include <winsock2.h>
#include <iostream>


using namespace std;

struct info
{
	char b[200];
	char count = 0;
};

info change_string(info str)
{
	str.count = 0;
	if (strlen(str.b) % 4 == 0)
	{
		char buf[200];
		int index = 0;
		int index2 = 0;

		while (str.b[index] != '\0')
		{
			if (str.b[index] > '0' && str.b[index] <= '9')
			{
				int i = 0;
				char b[200];
				while (str.b[index] >= '0' && str.b[index] <= '9' && str.b[index] != '\0')
				{
					b[i] = str.b[index];
					index++;
					i++;	
				}
				b[i] = '\0';
				int value = atoi(b);
				if (value % 4 == 0)
				{
					value /= 4;
					_itoa(value, b, 10);
					i = 0;
					str.count++;
					while (b[i] != '\0')
					{
						buf[index2] = b[i];
						i++;
						index2++;
					}
				}
				else
				{
					i = 0;
					while (b[i] != '\0')
					{
						buf[index2] = b[i];
						i++;
						index2++;
					}
				}
			}
			else
			{
				buf[index2] = str.b[index];
				index2++;
				index++;
			}
		}
		buf[index2] = '\0';
		strcpy(str.b, buf);
	}
	return str;
}

void main(void)
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(1024);
	local.sin_addr.s_addr = 0;
	SOCKET s_server;
	s_server = socket(AF_INET, SOCK_DGRAM, 0);
	bind(s_server, (struct sockaddr*) &local, sizeof(local));
	info b;
	int l;
	l = sizeof(local);
	while (true)
	{
		int rv = recvfrom(s_server, b.b, lstrlen(b.b), 0, (SOCKADDR*)&local, &l);
		cout << "Server on" << endl;
		b.b[rv] = '\0';
		cout << "String:" << b.b << endl;
		b = change_string(b);
		char count[200];
		_itoa(b.count, count, 10);
		sendto(s_server, count, lstrlen(count), 0, (SOCKADDR*)&local, l);
		sendto(s_server, b.b, lstrlen(b.b), 0, (SOCKADDR*)&local, l);
	}
	closesocket(s_server);
	WSACleanup();
	system("pause");
}


