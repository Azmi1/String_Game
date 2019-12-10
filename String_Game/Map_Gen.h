#pragma once
#include <iostream>
#include "Libs/PerlinNoise.h"
#include "Libs/rlutil.h"

using namespace std;
string get_map(int velikost, int seed);

string get_map(int velikost, int seed) {
	string map;
	siv::PerlinNoise pn(seed);
	for (int i = 0; i < velikost; i++) { // y;
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
		}
		cout << endl;
	}
	return map;
}