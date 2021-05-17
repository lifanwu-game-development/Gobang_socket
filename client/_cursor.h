#pragma once
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
void gotoxy(short x, short y) {
	COORD coord = { 2 * x,y };
	SetConsoleCursorPosition(handle, coord);
}
void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(handle, &cursor_info);
}

