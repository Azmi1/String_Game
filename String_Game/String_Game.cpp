#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include "Libs/PerlinNoise.h"
#include "Libs/rlutil.h"

using namespace std;

class player {
public:
	int x;
	int y;
};

double get_map(int seed, int, int x, int y);

void Load_Map(int, int, player);

/*int main() {
	int a = 1;
	while (1) {
		if (kbhit()){
			a = getch();
		}
		cout << 1;
		if (a == '0')
			break;
	}
}
*/
int main()
{
	int seed, sensitivity;
	cout << "Vnesi seed: ";
	cin >> seed;
	cout << "Vnesi sensitivity: ";
	cin >> sensitivity;
	bool Game = true, Input_Buffer = false; int izbira, x, yr;
	player Pl;
	Pl.x = 0;
	Pl.y = 0;
	Load_Map(seed, sensitivity, Pl);
	while (Game == true) {
		if (kbhit() && Input_Buffer == false) {
			Input_Buffer = true;
			char input = getch();
			if (input == 's')
				Pl.y += 1;
			else if (input == 'w')
				Pl.y -= 1;
			if (input == 'd')
				Pl.x += 1;
			else if (input == 'a')
				Pl.x -= 1;
			system("CLS");
			Load_Map(seed, sensitivity, Pl);
			rlutil::setColor(7);
			cout << endl;
			rlutil::setColor(7);
		}
		else {
			Input_Buffer = false;

		}
		/*
		cout << "Izberi med opcijami: " << endl;
		cout << "1.) Premik" << endl;
		cout << "9.) Konec" << endl;
		cout << "Vpisi izbiro: ";
		cin >> izbira;
		switch (izbira) {
		case 1:
			cout << "Vpisi premik po x osi: ";
			cin >> x;															
			cout << "Vpisi premik po y osi: ";
			cin >> y;
			Pl.x += x;
			Pl.y += y;
			break;
		case 9:
			Game = false;
			break;
		}
		*/
	}
	return 0;
}

double get_map(int seed, int sensitivity, int x, int y) {
	siv::PerlinNoise pn(seed);
	double x1 = (double)x / ((double)sensitivity);
	double y1 = (double)y / ((double)sensitivity);

	double n = pn.noise(10 * x1, 10 * y1, 0.8);
	return n;
}

void Load_Map(int seed, int sensitivity,player Pl) {
	cout << (char)201;
	for (int i = 0; i < 64; i++) {
		cout << (char)205;
	}
	cout << (char)187 << endl; 
	int Velikost_Ekrana = 64;
	int zacetna_verednost = Pl.x -32;
	int visina = Pl.y + 16;

	int j = 0;
	double n;
	for (int i = Pl.y - 16; i < visina; i++) {
		cout << (char)186;
		for (int j = zacetna_verednost; j < Pl.x + 32; j++) {
			n = get_map(seed, sensitivity, j, i);
			if (Pl.x == j && Pl.y == i) {
				rlutil::setColor(4);
				cout << 'P';
			}
			else if(n < 0.2){
				rlutil::setColor(1);
				cout << (char)176;
			}
			else if (n < 0.3) {
				rlutil::setColor(7);
				cout << 'M';
			}
			else{
				rlutil::setColor(2);
				cout << 'O';
			}
		}
		rlutil::setColor(7);
		cout << (char)186;
		cout << endl;
	}
	cout << (char)200;
	for (int i = 0; i < 64; i++) {
		cout << (char)205;
	}
	cout << (char)188 << endl;
}


/*int visina = 64;
//if((visina/2)*debelina >)
int steps = 32;
int j = (Pl.x + Pl.y * debelina) - 32 + (debelina * (Pl.y - steps));
if (j < 0)
	j = 0;
int oj = j;
cout << j << endl;
for (int i = 0; i < 64; i++) {
	for (; j < oj + 64 ; j++) {
		if (j < 0)
			j = 0;
		if (Pl.x + Pl.y * debelina == j) {
			rlutil::setColor(4);
			cout << 'P';
		}
		else {
			if (p[j] == 'O')
				rlutil::setColor(2);
			else if (p[j] == (char)176)
				rlutil::setColor(1);
			else if (p[j] == 'M')
				rlutil::setColor(7);
			cout << p[j];
		}

	}
	rlutil::setColor(7);
	cout << (char)186 << endl << (char)186;
	steps -= 1;
	j = (Pl.x + Pl.y * debelina) - 32 - (debelina * (Pl.y - steps));
	oj = j;
	}*/
