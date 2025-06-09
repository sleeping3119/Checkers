#include <iostream>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include <conio.h>


#define v 12
#define h 12
#define blue 1
#define green 2
#define red 4
#define yellow 14
#define white 15

using namespace std;
struct position {
	int r, c;
};

char** init(int&, int&, string, string[]);
int turnChange(int);
bool isHorizental(position sc, position dc);
bool isVertical(position sc, position dc);
bool isDiagnal(position sc, position dc);
void gt(int, int);
void drawLD(position, position);
void setClr(int);
void circle(int, int, int);
void drawL(position, position);
void printBoard(char**, int);
void drawRD(position, position);
void printTurn(string[], int);
bool checkSelectPiece(position, int, int, char**);
void selectPiece(int, position&, position&, int, char**);
void prompt(int, string, int, int);

bool wincondition(int dim, char** B) {
	int c1{}, c2{};
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
		{
			if (islower(B[i][j]))
				c1 += 1;
			else if (isupper(B[i][j]))
				c2 += 1;
		}
	if (c1 == 0) {
		prompt(green, "Player 2 has won the game", 2, dim);
			return false;
	}
	else if (c2 == 0) {
		prompt(green, "Player 1 has won the game", 2, dim);
			return false;
	}
	return true;


}
position centre(position f, position t) {
	position c{};
	if (f.r == t.r)
	{
		c.r = f.r;
		if (t.c > f.c) c.c = f.c + 1;
		else c.c = t.c + 1;
	}
	else if (f.c == t.c)
	{
		c.r = f.r;
		if (t.r > f.r) c.r = f.r + 1;
		else c.r = t.r + 1;
	}
	else
	{
		if (t.r > f.r) c.r = f.r + 1;
		else if (t.r < f.r) c.r = t.r + 1;
		if (t.c > f.c) c.c = f.c + 1;
		else if (t.c < f.c) c.c = t.c + 1;
	}
	return c;
}
void printscore(string names[], int dim, char** B) {
	int score[2];
	int total = 12;
	int c1{}, c2{};
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++)
		{
			if (islower(B[i][j]))
				c1 += 1;
			else if (isupper(B[i][j]))
				c2 += 1;
		}

	score[0] = total - c1;
	score[1] = total - c2;
	gt(dim, dim * h + 8);
	cout << "Green Score " << names[1] << "= " << score[1];
	gt(dim + 1, dim * h + 8);
	cout << "Red Score " << names[0] << "= " << score[0];
	prompt(blue, " \b", -8, dim);
}
bool isLegal(position f, position& t, int dim, int turn, char** B) {
	position c{};
	if (t.r <0 || t.r>dim || t.c < 0 || t.c >dim) {
		prompt(red, "Wrong destination, please select piece again: ", 0, dim);
		return false;
	}
	if (isDiagnal(f, t) && ((abs(f.c - f.r) == 1) || (abs(f.c - f.r) == 3))) {
		prompt(red, "You can not move diagnaly here, please select piece again: ", 0, dim);
		return false;
	}
	if (B[t.r][t.c] != '-') {
		prompt(red, "Landing on pieces is not valid, you can jump opponent pieces, slct peice again", 0, dim);
		return false;
	}
	if ((abs(t.r - f.r)) == 1 || (abs(t.c - f.c)) == 1) {
		return true;
	}
	else if ((abs(t.r - f.r)) == 2 || (abs(t.c - f.c)) == 2) {

		c = centre(f, t);
		if (turn && islower(B[c.r][c.c])) {
			B[c.r][c.c] = '-';

			return true;
		}
		if (!turn && isupper(B[c.r][c.c])) {
			B[c.r][c.c] = '-';
			return true;
		}
	}
	prompt(red, "Wrong destination dude, please select piece again ", 0, dim);
	return false;
}
int selectMove(position f, position& t, int dim, int turn, char** B) {

	prompt(green, "Please select position: ", -2, dim);
	cin >> t.r >> t.c;
	t.r--, t.c--;
	if (!isLegal(f, t, dim, turn, B)) {
		selectPiece(turn, f, t, dim, B); return 0;
	}
	prompt(red, " \b", 0, dim);
	return 1;
}
void updateB(char** B, position a, position b) {
	char ch = B[a.r][a.c];
	B[a.r][a.c] = '-';
	B[b.r][b.c] = ch;
}




int main()
{
	int score[2]{};
	int turn, dim;
	position from{}, to{};
	char** B = nullptr;
	string names[2]{};
	B = init(dim, turn, "load.txt", names);
	printBoard(B, dim);
	do {
		printTurn(names, turn);
		selectPiece(turn, from, to, dim, B);
		updateB(B, from, to);
		printBoard(B, dim);
		printscore(names, dim, B);
		turn = turnChange(turn);
	} while (wincondition(dim, B));

}
char** init(int& dim, int& turn, string a, string name[]) {

	ifstream rdr(a);
	cout << "Enter First player name :";
	cin >> name[0];
	cout << "Enter Second player name :";
	cin >> name[1];
	srand((unsigned)time(0));
	turn = abs(rand() % 2);
	/*if (!rdr) {
		cout << "txt file not found";
		exit(_getch());
	}*/
	rdr >> dim;
	char** B = new char* [dim] {};
	for (int i = 0; i < dim; i++) {
		B[i] = new char[dim];
		for (int j = 0; j < dim; j++) {
			rdr >> B[i][j];
		}
	}
	return B;
}
int turnChange(int t) {
	t = (t + 1) % 2;
	return t;
}
bool isHorizental(position sc, position dc) {
	if (sc.r == dc.r) return true;
	return false;
}
bool isVertical(position sc, position dc) {
	if (sc.c == dc.c) return true;
	return false;
}
bool isDiagnal(position sc, position dc) {
	if (abs(sc.c - dc.c) == abs(sc.r - dc.r)) return true;
	return false;
}
void gt(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void drawLD(position from, position to)
{
	for (int i = from.r, j = from.c; i < to.r; i++, j--)
	{
		gt(i, j); cout << char(-37);
	}

}
void setClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
void circle(int r, int c, int clr) {
	setClr(clr);
	c = c - 3;
	gt(r - 3, c);
	cout << "   * ";
	gt(r - 2, c);
	cout << " *****";
	gt(r - 1, c);
	cout << "*******";
	gt(r, c);
	cout << "*******";
	gt(r + 1, c);
	cout << " *****";
	gt(r + 2, c);
	cout << "   * ";

}
void drawL(position a, position b) {
	char ch = -37;
	if (a.r == b.r)
		for (int i = a.c; i < b.c; i++) {
			gt(a.r, i); cout << ch;
		}
	else
		for (int i = a.r; i < b.r; i++) {
			gt(i, a.c); cout << ch;
		}

}
void drawRD(position from, position to)
{
	for (int i = from.r, j = from.c; i < to.r; i++, j++)
	{
		gt(i, j); cout << char(-37);
	}

}
void printBoard(char** B, int dim) {
	int start = 6;
	int len = h * (dim - 1) + start;
	int hlen = (h * (dim - 1) / 2) + start;
	int height = v * (dim - 1) + start;
	int hheight = (v * (dim - 1)) / 2 + start;
	//print space first 
	system("cls");

	position a{}; a.c = start, a.r = start;
	position b{}; b.r = len, b.c = height;
	setClr(yellow);
	drawRD(a, b);
	a.r = hheight, a.c = start;
	b.r = height, b.c = hlen;
	drawRD(a, b);
	a.r = start, a.c = hlen;
	b.r = hheight, b.c = len;
	drawRD(a, b);


	a.r = start, a.c = len;
	b.r = height, b.c = start;
	drawLD(a, b);
	a.r = start, a.c = hlen;
	b.r = hheight, b.c = start;
	drawLD(a, b);
	a.r = hheight, a.c = len;
	b.r = height, b.c = hlen;
	drawLD(a, b);

	setClr(blue);
	for (int i = 0; i < dim; i++)
	{
		a.r = start, a.c = i * h + start;
		b.r = height, b.c = i * h + start;
		drawL(a, b);
		a.r = i * v + start, a.c = start;
		b.r = i * v + start, b.c = len;
		drawL(a, b);
	}
	//drawDiagnal(b,a);
	for (int i = 0; i < dim; i++) {
		for (int j = 0; j < dim; j++)
		{
			gt(i * v + start, j * h + start);
			if (islower(B[i][j]))
				circle(i * v + start, j * h + start, green);
			else if (isupper(B[i][j]))
				circle(i * v + start, j * h + start, red);
			else
				cout << "*";
		}
	}
	//drawing line
	setClr(white);

}
void prompt(int col, string sent, int i, int dim) {
	gt(dim * h + 6 + i, 0);
	cout << "                                                                         ";
	gt(dim * h + 6 + i, 0);
	setClr(col); cout << sent; setClr(15);
}
void printTurn(string names[], int turn) {
	string word{};
	if (turn) word = "Red";
	else word = "Green";
	setClr(green);
	cout << "\n\n\nIt is " << names[turn] << "'s (" << word << ") turn\n";
	setClr(white);
}
bool checkSelectPiece(position from, int turn, int dim, char** B) {
	if (dim < from.r || dim < from.c || from.c < 0 || from.r < 0)
	{
		prompt(red, "Out of range!!! please enter again", 0, dim);
		return false;
	}
	if (turn == 0 && islower(B[from.r][from.c]))
		return true;
	else if (turn == 1 && isupper(B[from.r][from.c]))
		return true;
	prompt(red, "Wrong input !!! please enter again", 0, dim);
	return false;
}
void selectPiece(int turn, position& from, position& to, int dim, char** B) {
	do {
		prompt(green, "Please select your piece: ", -2, dim);
		cin >> from.r >> from.c;
		from.r--, from.c--;
	} while (!checkSelectPiece(from, turn, dim, B));
	prompt(red, " \b", 0, dim);
	selectMove(from, to, dim, turn, B);
}

