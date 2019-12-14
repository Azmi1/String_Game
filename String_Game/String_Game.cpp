#include <iostream>
#include <stdlib.h>
#include "Libs/PerlinNoise.h"
#include "Libs/rlutil.h"

using namespace std;

class player {
public:
	int x;
	int y;
};

string get_map(int velikost, int seed);

void Load_Map(string, int, int, player);

int main()
{
	int velikost, seed;
	cout << "Vnesi velikost mape: ";
	cin >> velikost;
	cout << "Vnesi seed: ";
	cin >> seed;
	string p= get_map(velikost, seed);
	bool Game = true; int debelina = velikost, st = p.length(), sirina = debelina, izbira, x, y;
	player Pl;
	Pl.x = 0;
	Pl.y = 0;
	while (Game == true) {
		rlutil::setColor(7);
		Load_Map(p, velikost, st, Pl);
		cout << endl;
		rlutil::setColor(7);
		cout << "Izberi med opcijami: " << endl;
		cout << "1.) Premik" << endl;
		cout << "9.) Konec" << endl;
		cout << "Vpisi izbiro: ";
		cin >> izbira;
		switch (izbira) {
		case 1:
			cout << "Vpisi premik po x osi: ";
			cin >> x;
			while (Pl.x + x >= debelina || Pl.x + x < 0) {
				cout << "Premik po x osi prevelik ali premajhen" << endl;
				cout << "Maksimalen premik(v desno): " << debelina - 1 - Pl.x << endl;
				cout << "Minimalen premik(v levo): " << Pl.x << endl;
				cout << "Vpisi premik po x osi: ";
				cin >> x;
			}																			
			cout << "Vpisi premik po y osi: ";
			cin >> y;
			while (Pl.y + y > sirina - 1 || Pl.y + y < 0) {
				cout << "Premik po y osi prevelik ali premajhen" << endl;
				cout << "Maksimalen premik(na gor): " << -Pl.y << endl;
				cout << "Minimalen premik(na dol): " << (sirina - Pl.y) - 1 << endl;
				cout << "Vpisi premik po y osi: ";
				cin >> y;
			}
			Pl.x += x;
			Pl.y += y;
			break;
		case 9:
			Game = false;
			break;
		}
	}
	return 0;
}

string get_map(int velikost, int seed) {
	string map;
	siv::PerlinNoise pn(seed);
	for (int i = 0; i < velikost; i++) { // y;
		for (int j = 0; j < velikost; j++) {
			double x = (double)j / ((double)velikost);
			double y = (double)i / ((double)velikost);

			double n = pn.noise(10 * x, 10 * y, 0.8);

			if (n < 0.01) {
				rlutil::setColor(1);
				cout << (char)176;
				map += (char)176;
			}
			else if (n < 0.16) {
				rlutil::setColor(7);
				cout << 'M';
				map += "M";
			}
			else {
				rlutil::setColor(2);
				cout << 'O';
				map += "O";
			}
		}
		cout << endl;
	}
	return map;
}

void Load_Map(string p, int velikost, int st, player Pl) {
	cout << (char)201;
	for (int i = 0; i < 64; i++) {
		cout << (char)205;
	}
	cout << (char)187 << endl; 
	cout << (char)186;
	int Velikost_Ekrana = 64;
	int zacetna_verednost = (Pl.x + Pl.y * velikost) - (32 + 32 * velikost);
	int koncna_vrednost = (Pl.x + Pl.y * velikost) + (32 + 32 * velikost);
	if (zacetna_verednost < 0) {
		zacetna_verednost = 0;
	}
	int j = 0;
	for (int i = zacetna_verednost; i <= koncna_vrednost; i++) {
			cout << p[i];
		if (i - (zacetna_verednost + (velikost * j)) == 63) {
			j++;
			i += velikost - Velikost_Ekrana;
			cout << (char)186 << endl << (char)186;
		}
	}
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