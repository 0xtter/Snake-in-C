#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <stdbool.h>
#include "ConsoleTools.h"
#include <locale.h>
#include "Header.h"

/***********************************/
//	Thomas Desrumeaux CSI3
/***********************************/

int main() {
	queue Chenille[NOMBRECASES];
	pomme Biscuits[NOMBREPOMMES];
	unsigned char Direction = 'D';
	int Taille = TAILLEINITIALECHENILLE;
	bool Fin = false;


	openConsole();
	clearScreen();
	setWriteColor(WHITE);
	ContourConsole();

	InitialiserPommes(Biscuits);
	InitialiseQueue(Chenille, TAILLEINITIALECHENILLE);


	while (!Fin) {
		if (_kbhit()) if (_getch() == 224) Direction = ChoixDirection(_getch(), Direction);
		Taille = DeplacementChenille(Chenille, Taille, Direction, Biscuits);
		Fin = CheckFin(Chenille, Taille);
		Afficher(Chenille, Taille);
		moveCursor(0, 0);
		Sleep(100);

	}
	moveCursor(0, LONGUEUR + 1);
	setWriteColor(RED);
	printf("\nPERDU!\n\n");
	Sleep(1000);
	closeConsole();
}