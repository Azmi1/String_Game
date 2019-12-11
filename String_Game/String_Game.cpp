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

void Load_Map(string p, int debelina, int st, player Pl);

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

			if (n < 0.01)
				map += (char)176;
			else if (n < 0.16)
				map += "M";
			else
				map += "O";
		}
		cout << endl;
	}
	return map;
}

void Load_Map(string p, int debelina, int st, player Pl) {
	cout << (char)201;
	for (int i = 0; i < 64; i++) {
		cout << (char)205;
	}
	cout << (char)187 << endl;
	cout << (char)186;
	int zgornja_meja = Pl.x - 32 - (debelina * 32);
	if (zgornja_meja < 0)
		zgornja_meja = 0;
	int spodnja_meja = Pl.x + 32 + (debelina * 32);
	if (spodnja_meja > st)
		spodnja_meja = st;
	for (int i = zgornja_meja; i < spodnja_meja; i++) {
		if (i % 32 == 0 && i != 0) {
			rlutil::setColor(7);
			cout << (char)186 << endl << (char)186;
			i += -64 + debelina;
		}
		if (Pl.x + Pl.y * debelina == i) {
			rlutil::setColor(4);
			cout << 'P';
		}
		else {
			if (p[i] == 'O')
				rlutil::setColor(2);
			else if (p[i] == (char)176)
				rlutil::setColor(1);
			else if (p[i] == 'M')
				rlutil::setColor(7);
			cout << p[i];
		}
	}

}