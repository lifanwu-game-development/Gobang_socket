#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include<Windows.h>
#include<winsock2.h> 
#include<conio.h>
#include<stdio.h>
#include <iostream>
#include <string.h>

#include"_cursor.h"
#include"chessboard.h"
#include"client.h"



board Board;

int main()
{

	Board.init_board();
	client a;
	char ip[20] = "127.0.0.1";
	scanf("%s", ip);
	a.init_client(ip, 8000);
	HideCursor();
	a.run(Board);

}