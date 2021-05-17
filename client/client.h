#pragma once

#pragma comment(lib, "ws2_32.lib")			//add ws2_32.lib
using namespace std;
class client {
public:
	client();
	~client();
	int Send(char* buffer, size_t length);
	int init_client(char* host_name, int port);
	int Recv(char* buffer, int length);
	int execute();
	void run(board& Board);
	SOCKADDR_IN addrSrv;
	SOCKET sockClt;
};

client::client()
{

}

client::~client()
{
	closesocket(sockClt);
	WSACleanup();
}

int client::init_client(char* host_name, int port)
{
	WORD	wVersionRequested;
	WSADATA wsaData;
	int		err, iLen;
	wVersionRequested = MAKEWORD(2, 2);//create 16bit data
	//(1)Load WinSock
	err = WSAStartup(wVersionRequested, &wsaData);	//load win socket
	if (err != 0)
	{
		cout << "Load WinSock Failed!";
		return -1;
	}
	//(2)create socket
	sockClt = socket(AF_INET, SOCK_STREAM, 0);
	if (sockClt == INVALID_SOCKET) {
		cout << "socket() fail:" << WSAGetLastError() << endl;
		return -2;
	}
	//(3)IP

	addrSrv.sin_family = AF_INET;
	addrSrv.sin_addr.s_addr = inet_addr(host_name);
	addrSrv.sin_port = htons(port);

	//(5)connect
	err = connect(sockClt, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));

	if (err == INVALID_SOCKET)
	{
		cout << "connect() fail" << WSAGetLastError() << endl;
		return -1;
	}

	char sendBuf[1024], hostname[100];
	if (gethostname(hostname, 100) != 0)	//get host name
		strcpy(hostname, "None");
	strcpy(sendBuf, hostname);
	strcat(sendBuf, " have connected to you!");
	this->Send(sendBuf, strlen(sendBuf) + 1);

	char recvBuf[1024] = "\0";
	iLen = this->Recv(recvBuf, 1024);

	if (iLen == 0)
		return -3;
	else if (iLen == SOCKET_ERROR) {
		cout << "recv() fail:" << WSAGetLastError() << endl;
		return -4;
	}
	else
	{
		recvBuf[iLen] = '\0';
		cout << recvBuf << endl;
	}
	return 0;
}

int client::Send(char* buffer, size_t length)
{
	return send(sockClt, buffer, length, 0);
}

int client::Recv(char* buffer, int length)
{
	return recv(sockClt, buffer, length, 0);

}

void client::run(board& Board)
{
	char buffer[20];
	while (true)
	{
		this->Recv(buffer, 10);
		buffer[2] = 0;
		int x = atoi(buffer);
		int y = atoi(&buffer[3]);
		Board.server_chess_moves(x, y);
		Board.display();
		char click;
		while (1) {
			click = _getch();

			if (Board.change(click))
			{
				Board.display();
				break;
			}
			else Board.display();
		}
		Board.display();
		sprintf(buffer, "%2d %2d", Board.cursor_x, Board.cursor_y);
		this->Send(buffer, 10);

	}
}