#include <winsock2.h>
#include <iostream>


using namespace std;

int main()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);

	struct sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(1024);
	peer.sin_addr.s_addr = inet_addr("127.0.0.1");
	while (true)
	{
		SOCKET s_client;
		s_client = socket(AF_INET, SOCK_DGRAM, 0);
		int t;
		t = sizeof(peer);
		char buf[100], b1[100], b2[100];
		cout << "String: " << endl;
		cin.getline(buf, 100, '\n');
		sendto(s_client, buf, lstrlen(buf), 0, (struct sockaddr*) &peer, t);
		int rv1 = recvfrom(s_client, b1, lstrlen(b1), 0, (struct sockaddr*) &peer, &t);
		int rv2 = recvfrom(s_client, b2, lstrlen(b2), 0, (struct sockaddr*) &peer, &t);
		b1[rv1] = '\0';
		b2[rv2] = '\0';
		cout << "Changed string: " << b2 << "; ";
		cout << "Count: " << b1 << endl;

		closesocket(s_client);
	}
	WSACleanup();
	cout << endl;
	system("pause");
	return 0;
}

