#include<stdio.h>
#include<iostream>
#include <winsock2.h>

using namespace std;

struct city
{
	char date[10];
	char code_and_name[20];
	char duration[20];
	char tariff[10];
	char city_number[20];
	char user_number[20];
}cities[6];

DWORD WINAPI ThreadFunc(LPVOID);
int numcl = 0;


void print()
{
	if (numcl) printf("%d client connected\n", numcl);
	else printf("No clients connected\n");
}

void init(city * c)
{
	strcpy(c[0].date, "12.01.2018");
	strcpy(c[1].date, "15.06.2018");
	strcpy(c[2].date, "30.12.2017");
	strcpy(c[3].date, "24.06.2018");
	strcpy(c[4].date, "02.08.2018");
	strcpy(c[5].date, "08.04.2018");
	
	strcpy(c[0].code_and_name, "8 0222 Mogilev");
	strcpy(c[1].code_and_name, "8 0232 Gomel");
	strcpy(c[2].code_and_name, "8 017 Minsk");
	strcpy(c[3].code_and_name, "8 0152 Grodno");
	strcpy(c[4].code_and_name, "8 0212 Vitebsk");
	strcpy(c[5].code_and_name, "8 0162 Brest");

	strcpy(c[0].duration, "20 min 25 sec" );
	strcpy(c[1].duration, "15 min 34 sec" );
	strcpy(c[2].duration, "57 min 23 sec\0" );
	strcpy(c[3].duration, "43 min 15 sec" );
	strcpy(c[4].duration, "1 h 03 min 20 sec");
	strcpy(c[5].duration, "34 min 0 sec");

	strcpy(c[0].tariff, "Bezlim");
	strcpy(c[1].tariff, "Lemon");
	strcpy(c[2].tariff, "Bezlim");
	strcpy(c[3].tariff, "Bezlim");
	strcpy(c[4].tariff, "Lemon");
	strcpy(c[5].tariff, "Lemon");

	strcpy(c[0].city_number, "+375 44 7723546");
	strcpy(c[1].city_number, "+375 29 6728996");
	strcpy(c[2].city_number, "+375 44 3423572");
	strcpy(c[3].city_number, "+375 29 7984644");
	strcpy(c[4].city_number, "+375 44 3323546");
	strcpy(c[5].city_number, "+375 29 7935586");

	strcpy(c[0].user_number, "+375 29 8475836");
	strcpy(c[1].user_number, "+375 44 5257469");
	strcpy(c[2].user_number, "+375 29 7746307");
	strcpy(c[3].user_number, "+375 44 8884632");
	strcpy(c[4].user_number, "+375 29 9940358");
	strcpy(c[5].user_number, "+375 44 7746265");

}

int main()
{
	setlocale(LC_ALL, "RUS");
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) { return 0; }

	init(cities);
	
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in local_addr;
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(1280);
	local_addr.sin_addr.s_addr = 0;
	bind(s, (sockaddr *)&local_addr, sizeof(local_addr));
	int c = listen(s, 1);
	cout << "Server is active" << endl;
	cout << endl;
	// извлекаем сообщение из очереди
	SOCKET client_socket;    // сокет для клиента
	sockaddr_in client_addr; // адрес клиента (заполняется системой)
	int client_addr_size = sizeof(client_addr);
	// цикл извлечения запросов на подключение из очереди
	while ((client_socket = accept(s, (sockaddr *)&client_addr, &client_addr_size)))
	{
		numcl++;
		print();
		char *ip = inet_ntoa(client_addr.sin_addr);
		cout << "Client "<< ip <<':'<< client_addr.sin_port << " connected" << endl;
		// вызов нового потока для обслуживания клиента
		DWORD thID;  //thID идентификатор типа DWORD
		CreateThread(NULL, NULL, ThreadFunc, &client_socket, NULL, &thID);
	}
	return 0;
}
 char *change_string(char const * string)
{
	 char* tmp;
	 tmp = new char[strlen(string) + 1];
	 char buf[100];
	 strcpy(tmp, string);
	 int i1 = 0;
	 int i2 = 0;
	 while (tmp[i1] != '\0')
	 {
		 if ( tmp[i1] != ' ' && tmp[i1] < '0' || tmp[i1]>'9')
		 {
			 buf[i2] = tmp[i1];
			 i2++;
		 }
		 i1++;
	 }
	 buf[i2] = '\0';
	 delete[] tmp;
	 return buf;
}

DWORD WINAPI ThreadFunc(LPVOID client_socket)
{

	SOCKET s2 = ((SOCKET *)client_socket)[0];
	char buf[256];
	char buf1[256];
	while (recv(s2, buf, sizeof(buf), 0))
	{
		cout << "City: " << buf << endl;
		int i;
		for (i = 0; i < 6; i++)
		{
			if (!strcmp(buf, change_string(cities[i].code_and_name)))
			{
				send(s2, cities[i].duration, strlen(cities[i].duration), 0);
				break;
			}
		}
		if(i>=6)
			send(s2, "City not found!", strlen("City not found!"), 0);
	
	}
	numcl--;
	print();
	closesocket(s2);
	return 0;
}
