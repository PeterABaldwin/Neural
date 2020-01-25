#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <cstdlib>

using namespace std;

FILE *stream;

int mainm() {
	//random training sets for XOR -- tow inputs and one output

	string in;
	//std::ofstream out("/trainingData.txt");
	freopen_s( &stream, "trainingData.txt", "w", stdout);
	//freopen_s("trainingData.txt", "w", stdout);
	cout << endl << "topology: 2 4 1" << endl;

	for (int i = 2000; i >= 0; --i) {
		int n1 = (int)(2.0 * rand() / double(RAND_MAX));
		int n2 = (int)(2.0 * rand() / double(RAND_MAX));
		int t = n1 ^ n2;
		cout << "in: " << n1 << ".0 " << n2 << ".0" << endl;
		cout << "out: " << t << ".0" << endl;
	}

	return 0;
}
