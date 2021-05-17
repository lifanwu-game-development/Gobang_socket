#pragma once
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
#include"server.h"
board Board;
int main(int argc, char* argv[])
{
	Board.init_board();
	server a;
	a.init_server(8000);
	HideCursor();
	a.run(Board);
}