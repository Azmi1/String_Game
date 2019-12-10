#include <iostream>
#include "Libs/PerlinNoise.h"
#include "Libs/rlutil.h"

using namespace std;

string get_map(){
	int velikost, seed, debelina, sirina; string map;
	cout << "Vnesi velikost mape: ";
	cin >> velikost;
	cout << "Vnesi seed: ";
	cin >> seed;
	siv::PerlinNoise pn(seed);
	for (int i = 0; i < velikost; i++) { // y;
		sirina = 0;
		for (int j = 0; j < velikost; j++) {
			double x = (double)j / ((double)velikost);
			double y = (double)i / ((double)velikost);
			
			double n = pn.noise(10 * x, 10 * y, 0.8);
			
			if (n < 0.2) {
				rlutil::setColor(1);
				cout << "X";
			}
			else {
				rlutil::setColor(2);
				cout << "O";
			}
			map += n;
			sirina += 1;
		}
	cout << endl;
	}
	return map;
}