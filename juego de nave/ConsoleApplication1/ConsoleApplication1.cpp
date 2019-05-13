#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include<Windows.h>
#include <conio.h>
#include<corecrt_wconio.h>
#include<list>
#define TECLA_ARRIBA 72
#define TECLA_ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77

using namespace std;




void gotoxy(int x, int y) {
	HANDLE iCon;
	iCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(iCon, dwPos);

}

void ocultarcursor() {
	HANDLE iCon;
	iCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO  cci;
	cci.dwSize = 50;
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(iCon, &cci);

}

class NAVE 
{
public:
	//NAVE{}; ();
	//~NAVE{}; ();
	NAVE(int _x, int _y,int _corazones,int _vidas) : x(_x), y(_y), corazones(_corazones),vidas (_vidas) {}
	//NAVE(int _x, int _y, int _corazones) : x(_x), y(_y){}
	int X() { return x; }
	int Y() { return y; }
	void COR() { corazones--; }
	void pintar();
	void borrar();
	void mover();
	void pintar_corazones();
	void morir();
	int VID() { return vidas; }
private:
	int x, y;
	int corazones;
	int vidas;
};

void NAVE::pintar() {
	gotoxy(x, y); printf("  %c", 202);
	gotoxy(x, y+1); printf(" %c%c%c", 47,207,92);
	gotoxy(x, y+2); printf(" %c%c%c", 118,118,118);

}
void NAVE::borrar() {
	gotoxy(x, y); printf("      ");
	gotoxy(x, y + 1); printf("      ");
	gotoxy(x, y + 2); printf("      ");

}
void NAVE::mover(){
	int kbhit(void);
	if (kbhit()) {
			char tecla = _getch();


			borrar();

			if (tecla == IZQUIERDA && x>3) {
				x--;
			}
			if (tecla == DERECHA && x+5<77) {
				x++;
			}
			if (tecla == 72 && y>4 )y--;
			if (tecla == 80 && y+3<29)y++;
			pintar();
			pintar_corazones();

	}

}
//NAVE::NAVE(int _x, int _y): x(_x),y(_y) {
	//x = _x;
	//y = _Y;
//}
void pintar_limites() {
	for (int i = 2; i < 78;i++) {
		gotoxy(i, 3); printf("%c", 205);
		gotoxy(i, 29); printf("%c", 205);
	}
	for (int i = 4; i < 29; i++) {
		gotoxy(2, i); printf("%C", 186);
		gotoxy(77, i); printf("%c", 186);
	}
	gotoxy(2, 3); printf("%c", 201);
	gotoxy(2,29 ); printf("%c", 200);
	gotoxy(77, 3); printf("%c", 187);
	gotoxy(77,29 ); printf("%c", 188);
}

void NAVE::pintar_corazones() {
	gotoxy(50, 2); printf("vidas %d", vidas);
	gotoxy(64, 2); printf("salud");
	gotoxy(70, 2); printf("     ");
	for (int i = 0; i < corazones; i++) {

		gotoxy(70 + i, 2); printf("%c", 3);
	}



}
void NAVE::morir() {
	if (corazones == 0) {
		borrar();
		gotoxy(x, y); printf("  **  ");
		gotoxy(x, y + 1); printf(" **** ");
		gotoxy(x, y + 2); printf("  **  ");
		Sleep(200);
		borrar();
		gotoxy(x, y);     printf("* ** *");
		gotoxy(x, y + 1); printf(" **** ");
		gotoxy(x, y + 2); printf("* ** *");
		Sleep(200);
		borrar();
		vidas--;
		corazones = 3;
		pintar_corazones();
		pintar();

	}
}

class AST
{
public:
	AST(int _x, int _y) : x (_x), y(_y) {}
	void pintar();
	void mover();
	void choque(class NAVE &N);
	int X() { return x; }
	int Y() { return y; }
private:
	int x, y;
};

void AST::pintar() {
	gotoxy(x, y); printf("%c", 184);
}
void AST::mover() {
	gotoxy(x, y); printf(" ");
	y++;
	if (y > 28) {
		x = rand() % 71 + 4;
		y = 4;
	}
	pintar();

}

void AST::choque(class NAVE &N)
{
	if (x >= N.X() && x < N.X() + 4 && y >= N.Y() && y <= N.Y() + 2) {

		N.COR();
		N.borrar();
		N.pintar();
		N.pintar_corazones();
		x = rand() % 71 + 4;
		y = 4;
	}
};
class BALA
{
public:
	BALA(int _x,int _y): x(_x),y(_y){}
	int X() { return x; }
	int Y() { return y; }
	void mover();
	bool fuera();
private:
	int x, y;
};

void BALA::mover() {
	gotoxy(x, y); printf(" ");
	
		y--;
	gotoxy(x, y); printf("*");
	
}

bool BALA::fuera() {

	if (y == 4)return true;
	return false;
}

int main()
{
	ocultarcursor();

	pintar_limites();
	NAVE N(37, 26, 3,3);
	N.pintar();
	N.pintar_corazones();
	//AST ast1(10, 4), ast2(4, 7), ast3(15, 10);
	list <AST*> A;
	list <AST*>::iterator itA;
	for (int i = 0; i < 5;i++) {
		A.push_back(new AST(rand() % 75 + 3,rand()%5+4));

	}
	list<BALA*> B;
	list<BALA*>::iterator it;
	bool game_over = false;
	int puntos = 0;
	while (!game_over) {
		gotoxy(4, 2); printf("puntos %d", puntos);
		int kbhit(void);
		if (kbhit()) {
			char tecla = _getch();
			if (tecla == 'a') {
				B.push_back(new BALA(N.X() + 2, N.Y() - 1));
			}

			}
		for (it = B.begin(); it != B.end();) {
			(*it)->mover();
			if ((*it)->fuera()) {
				gotoxy((*it)->X(), (*it)->Y()); printf(" ");
				delete(*it);
				it = B.erase(it);
			}
			else
			{
				it++;
			}
		}
		
		for (itA = A.begin();itA != A.end() ;itA++){
			(*itA)->mover();
			(*itA)->choque(N);

		}
		for (itA = A.begin(); itA != A.end(); itA++) {
			for (it = B.begin(); it != B.end(); ) {
				if ((*itA)->X() == (*it)->X() && ((*itA)->Y() + 1 == (*it)->Y() || (*itA)->Y() == (*it)->Y())) {
					gotoxy((*it)->X(), (*it)->Y()); printf(" ");
					delete(*it);
					it = B.erase(it);
					A.push_back(new AST(rand() % 75 + 3, 4));
					gotoxy((*itA)->X(), (*itA)->Y()); printf(" ");
					delete(*itA);
					itA = A.erase(itA);
					puntos += 5;

				}
				else
				{
					it++;
				}

			}

		}
		//ast1.mover(); ast1.choque(N);
		//ast2.mover(); ast2.choque(N);
		//ast3.mover(); ast3.choque(N);
		if (N.VID() == 0) game_over = true;
		N.morir();
		N.mover();
		Sleep(20);
	}


	return 0;
} 
