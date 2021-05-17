#pragma once



using namespace std;

#pragma comment(lib, "ws2_32.lib")			//add ws2_32.lib

class server {
public:
	server();
	~server();
	int init_server(int port);
	int Send(char* buffer, size_t length);
	int Recv(char* buffer, size_t length);
	SOCKET sockSrv;
	SOCKET sockConn;
	void run(board& Board);
};

server::server()
{

}

server::~server()
{
	//(10)close server sock
	closesocket(sockSrv);
	//(11)clean up winsock
	WSACleanup();
	//(9)close connected sock
	closesocket(sockConn);

}

int server::init_server(int port)
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
	sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	if (sockSrv == INVALID_SOCKET) {
		cout << "socket() fail:" << WSAGetLastError() << endl;
		return -2;
	}
	//(3)server IP
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_addr.s_addr = htonl(INADDR_ANY);//Auto IP, byte sequence change
	addrSrv.sin_port = htons(port);
	//(4)bind
	err = bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (err != 0)
	{

		cout << "bind()fail" << WSAGetLastError() << endl;
		return -3;
	}
	//
//(5)listen
	err = listen(sockSrv, 5);
	if (err != 0)
	{

		cout << "listen()fail" << WSAGetLastError() << endl;
		return -4;
	}
	cout << "Server waitting...:" << endl;
	//(6)client ip
	SOCKADDR_IN addrClt;
	int len = sizeof(SOCKADDR);
	//(7)accept
	sockConn = accept(sockSrv, (SOCKADDR*)&addrClt, &len);
	char sendBuf[1024], hostname[100];
	if (gethostname(hostname, 100) != 0)	//get host name
		strcpy(hostname, "None");
	sprintf(sendBuf, "Welecome %s connected to %s!", inet_ntoa(addrClt.sin_addr), hostname);
	//(8)send recv
	this->Send(sendBuf, strlen(sendBuf) + 1);
	char recvBuf[1024] = "\0";
	iLen = Recv(recvBuf, 1024);

	recvBuf[iLen] = '\0';
	cout << recvBuf << endl;
}

void server::run(board& Board)
{
	char buffer[20];
	while (true)
	{
		char click;
		while (1) {
			click = _getch();
			if (Board.change(click))
			{
				Board.display();
				break;
			}
			Board.display();

		}
		Board.display();
		sprintf(buffer, "%2d %2d", Board.cursor_x, Board.cursor_y);
		this->Send(buffer, 10);
		this->Recv(buffer, 10);
		buffer[2] = 0;
		int x = atoi(buffer);
		int y = atoi(&buffer[3]);
		Board.client_chess_moves(x, y);
		Board.display();
	}


}

int server::Send(char* buffer, size_t length)
{
	return send(sockConn, buffer, length, 0);
}

int server::Recv(char* buffer, size_t length)
{
	return recv(sockConn, buffer, length, 0);
}