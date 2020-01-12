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

string get_map(int, int, int);

void Load_Map(string, int, player);

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
	int seed, sensitivity, velikost = 100;
	cout << "Vnesi seed: ";
	cin >> seed;
	cout << "Vnesi sensitivity: ";
	cin >> sensitivity;
	string map = get_map(seed, sensitivity, velikost);
	bool Game = true, Input_Buffer = false;
	player Pl;
	Pl.x = 0;
	Pl.y = 0;
	system("CLS");
	Load_Map(map, velikost, Pl);
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
			//system("CLS");
			for (int i = 0; i < 10; i++)
				cout << endl;
			Load_Map(map, velikost, Pl);
			rlutil::setColor(7);
			cout << endl;
			rlutil::setColor(7);
		}
		else {
			Input_Buffer = false;

		}
	}
	return 0;
}

string get_map(int seed, int sensitivity, int velikost) {
	siv::PerlinNoise pn(seed);
	string map;
	for (int y = 0; y < velikost; y++) {
		for (int x = 0; x < velikost; x++) {
			double x1 = (double)x / ((double)sensitivity);
			double y1 = (double)y / ((double)sensitivity);

			double n = pn.noise(10 * x1, 10 * y1, 0.8);
			if (n < 0.2)
				map += (char)176;
			else if (n < 0.3)
				map += 'M';
			else
				map += 'O';
		}
	}
	return map;
}

void Load_Map(string map, int velikost, player Pl) {
	cout << (char)201;
	for (int i = 0; i < 64; i++) {
		cout << (char)205;
	}
	cout << (char)187 << endl;
	int x = Pl.x-32;
	int y = Pl.y-32;
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	for (; y < Pl.y + 16; y++) { // y
		cout << (char)186;
		int x = Pl.x - 32;
		if (x < 0)
			x = 0;
		for (; x < Pl.x + 32; x++) { // x
			int naslov = x + y * velikost;
			if (naslov >= velikost * velikost + 1)
				break;
			if (Pl.x + Pl.y * velikost == naslov) {
				rlutil::setColor(4);
				cout << 'P';
			}
			else {
				if (map[naslov] == 'O')
					rlutil::setColor(2);
				else if (map[naslov] == (char)176)
					rlutil::setColor(1);
				else if (map[naslov] == 'M')
					rlutil::setColor(7);
				//printf("%c",map[naslov]);
				cout << map[naslov];
			}
		}
		rlutil::setColor(7);
		cout << (char)186 << endl;
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
