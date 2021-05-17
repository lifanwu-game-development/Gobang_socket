#pragma once
#pragma once
#define LENGTH 20
#define WIDTH 20
class board {
public:
	board()
	{

	}

	void init_board()
	{
		int i, j;
		for (i = 0; i < LENGTH; i++)
			for (j = 0; j < WIDTH; j++)
				_board[i][j] = 0;
	}

	void display();


	bool server_chess_moves(int x, int y)
	{
		if (_board[x][y])return false;
		else
		{
			_board[x][y] = 'x';
			return true;
		}
	}

	bool client_chess_moves(int x, int y)
	{
		if (_board[x][y])return false;
		else
		{
			_board[x][y] = 'o';
			return true;
		}
	}

	bool change(char click)
	{
		switch (click) {
		case 'w': {
			if (this->cursor_y == 0);
			else this->cursor_y--;
			break;
		}

		case 's': {
			if (this->cursor_y == WIDTH - 1);
			else this->cursor_y++;
			break;
		}

		case 'a': {
			if (this->cursor_x == 0);
			else this->cursor_x--;
			break;
		}

		case 'd': {
			if (this->cursor_x == LENGTH - 1);
			else this->cursor_x++;
			break;
		}
		case 13: {
			return this->client_chess_moves(this->cursor_x, this->cursor_y);
			break;
		}
		}
		return false;
	}
public:
	char _board[LENGTH][WIDTH];
	int cursor_x, cursor_y;
};


void board::display()
{
	system("cls");
	gotoxy(0, 0);
	int i, j;
	for (i = 0; i < LENGTH; i++)
	{

		for (j = 0; j < WIDTH; j++)
		{
			gotoxy(i, j);
			printf("%c ", _board[i][j]);
		}

	}
	gotoxy(cursor_x, cursor_y);
	printf("กั");
}