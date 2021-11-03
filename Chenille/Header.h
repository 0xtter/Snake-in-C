#pragma once

#define LARGEUR 30
#define LONGUEUR 20
#define NOMBRECASES LARGEUR*LONGUEUR
#define NOMBREPOMMES 10
#define TAILLEINITIALECHENILLE 5
#define TETECHENILLE 'x'
#define CORPSCHENILLE 'o'
#define POMME '@'

typedef struct QUEUE {
	int X;
	int Y;
}queue;


typedef struct POMMES {
	int X;
	int Y;
}pomme;



void ContourConsole() {
	for (int y = 0; y < LONGUEUR ;y++) {
		moveCursor(LARGEUR+1,y);
		plotChar((char)186);
	}
	for (int x = 0; x < LARGEUR+1; x++) {
		moveCursor(x, LONGUEUR);
		plotChar((char)205);
	}
	plotChar((char)188);
}

void InitialiserPommes(pomme P[]) {
	setWriteColor(RED);
	for (int i = 0; i < NOMBREPOMMES; i++) {
		int Fin = false;
		do { //Vérification que l'on ne pose pas un biscuit sur la même case qu'un autre
			P[i].X = rangedRand(0, LARGEUR);
			P[i].Y = rangedRand(0, LONGUEUR);
			Fin = true;
			for (int n = 0; n < NOMBREPOMMES; n++) if (n != i && P[n].X == P[i].X && P[n].Y == P[i].Y) Fin = false;
		} while (!Fin);
		moveCursor(P[i].X, P[i].Y);
		plotChar(POMME);

	}
}


void Afficher(queue Q[], int Size) {
	setWriteColor(GREEN);
	moveCursor(Q[0].X, Q[0].Y);
	plotChar(TETECHENILLE);
	moveCursor(Q[1].X, Q[1].Y);
	plotChar(CORPSCHENILLE);
}

void InitialiseQueue(queue Q[],int Size) {
	for (int i = 0; i < NOMBRECASES; i++) {
		Q[i].X = -1;
		Q[i].Y = -1;
	}
	setWriteColor(GREEN);
	for (int i = 0; i < Size;i++) {
		Q[i].X = (int)LARGEUR / 2-i;
		Q[i].Y = (int)LONGUEUR / 2;
		moveCursor(Q[i].X, Q[i].Y);
		if (i == 0) plotChar(TETECHENILLE);
		else plotChar(CORPSCHENILLE);
	}
}

unsigned char ChoixDirection(unsigned char Key, unsigned char Direction) {
	switch (Key) {
	case 'M':
		if (Direction != 'G')return 'D';
		else return Direction;
		break;
	case 'H':
		if (Direction != 'B')return 'H';
		else return Direction;
		break;
	case 'K':
		if (Direction != 'D')return 'G';
		else return Direction;
		break;
	case 'P':
		if (Direction != 'H')return 'B';
		else return Direction;
		break;
	default:
		return Direction;
	}
}


int DeplacementChenille(queue Q[], int Taille, unsigned char Direction, pomme P[]) {
	moveCursor(Q[Taille - 1].X, Q[Taille - 1].Y);
	plotChar(' ');

	int TaillePlusGrande = Taille;
	for (int i = 0; i < NOMBREPOMMES; i++) { //Vérification si on mange un biscuit
		if (P[i].X == Q[0].X && P[i].Y == Q[0].Y) {
			Q[Taille].X = Q[Taille - 1].X;
			Q[Taille].Y = Q[Taille - 1].Y;
			TaillePlusGrande = Taille + 1;
			bool Fin = true;
			do {
				P[i].X = rangedRand(0, LARGEUR);
				P[i].Y = rangedRand(0, LONGUEUR);
				Fin = true;
				for (int n = 1; n < Taille; n++) if (Q[n].X == P[i].X && Q[n].Y == P[i].Y) Fin = false;
				for (int n = 0; n < NOMBREPOMMES; n++) if (n != i && P[n].X == P[i].X && P[n].Y == P[i].Y) Fin = false;
			} while (!Fin);
			setWriteColor(RED);
			moveCursor(P[i].X, P[i].Y);
			plotChar(POMME);
		}
	}

	for (int i = Taille - 1; i > 0; i--) {
		Q[i].X = Q[i - 1].X;
		Q[i].Y = Q[i - 1].Y;
	}
	setWriteColor(GREEN);
	switch (Direction) {
	case 'D':
		Q[0].X = (LARGEUR + Q[0].X + 1) % LARGEUR;
		break;
	case 'H':
		Q[0].Y = (LONGUEUR + Q[0].Y - 1) % LONGUEUR;
		break;
	case 'B':
		Q[0].Y = (LONGUEUR + Q[0].Y + 1) % LONGUEUR;
		break;
	case 'G':
		Q[0].X = (LARGEUR + Q[0].X - 1) % LARGEUR;
		break;
	}
	return TaillePlusGrande;
}

bool CheckFin(queue Q[], int Taille) {
	for (int i = 1; i < Taille; i++) {
		if (Q[0].X == Q[i].X && Q[0].Y == Q[i].Y)return true;
	}
	return false;
}