#include <iostream>
#include <string>
#include <fstream>

using namespace std;
string delSymbol(string str, char symbol);
string selPath();
int** drawing(int** matrix, int N);



int main() {

	string path, inpath;
	bool fstate(true);
	cout << "Output path: ";
	path = selPath();
	cout << "Input path: ";
	inpath = selPath();
	int side;
	
	ifstream ipath(inpath);
	if (ipath.is_open()) {
		string frow;
		int rcount(0);
		while (getline(ipath, frow)) {
			if (!frow.empty())
			rcount++;
		}
		if (rcount>0) {
			ifstream ipath1(inpath);
			while (getline(ipath1, frow)) {
				if (!frow.empty()) {
					if (frow.find('.') != frow.npos || frow.find(',') != frow.npos) {
						cout << "Value must be integer" << endl;
						fstate = false;
						break;
					}
					try {
						side = stoi(frow);
					}
					catch (exception) {
						cout << "Invalid value" << endl;
						fstate = false;
						break;
					}
					if (side < 1) {
						cout << "Value must be positive" << endl;
						fstate = false;
						break;
					}
					break;
				}
			}
		}
		else {
			fstate = false;
		}

	}
	else {
		fstate = false;
	}
	if (!fstate) {
		cout << "An error occured while getting values from a file." << endl;
		string inconsole;
		while (true) {

			cout << "Enter matrix side: " << endl;
			cin >> inconsole;
			
			if (inconsole.find('.') != inconsole.npos || inconsole.find(',') != inconsole.npos) {
				cout << "Value must be integer" << endl;
				continue;
			}
			try {
				side = stoi(inconsole);
			}
			catch (exception) {
				cout << "Invalid value" << endl;
				continue;
			}
			if (side < 1) {
				cout << "Value must be positive" << endl;
				continue;
			}
			break;
		}
	}
	int** matrix = new int*[side];
	for (int i = 0; i < side; i++) {
		matrix[i] = new int[side];
	}
	matrix = drawing(matrix, side);
	ofstream out(path);
	for (int f = 0; f < side; f++) {
		for (int g = 0; g < side; g++) {

			cout << matrix[f][g]<<" ";
			out << matrix[f][g] << " ";

		}
		cout << endl;
		out << endl;
	}

	system("pause");
	return 0;

}

string delSymbol(string str, char symbol) {

	int length = str.length();
	string newstr;
	
	for (int k = 0; k < length; k++) {

		if (str[k] != symbol) {
			newstr.append(1, str[k]);
		}

	}
	
	return newstr;
}
string selPath() {

	string ipath;
	while (true) {

		cout << "Enter path to the file:" << endl;
		cin >> ipath;
		cout << endl;

		int n = ipath.length();
		for (int i = 0; i < n; i++) {

			if (ipath[i] == '\\') {
				ipath[i] = '/';
			}

		}
		ipath = delSymbol(ipath, '\"');
		ipath = delSymbol(ipath, ' ');


		int n1 = ipath.length();
		if (n1<4||(ipath[n1 - 1] != 't' && ipath[n1 - 2] != 'x' && ipath[n1 - 3] != 't' && ipath[n1 - 4] != '.')) {
			cout << "File must be .txt" << endl;
		}
		else {
			break;
		}

	}


	return ipath;
}
int** drawing(int** matrix, int N) {
	int y;
	if (N % 2 == 0)y = N / 2;
	if (N % 2 == 1)y = N / 2 + 1;

	for (int temp = 0; temp < y; temp++) {

		for (int k = 0; k < N; k++) {
				
			for (int u = 0; u < N; u++) {

				if ((k == 0 + temp && u == 0 + temp) || (k == 0 + temp && u == N - 1 - temp) || (k == N - 1 - temp && u == 0 + temp) || (k == N - 1 - temp && u == N - 1 - temp) || (k == 0 + temp && u > 0 + temp && u < N - 1 - temp) || (k == N - 1 - temp && u > 0 + temp && u < N - 1 - temp) || (k > 0 + temp && k < N - 1 - temp && u == 0 + temp) || (k > 0 + temp && k < N - 1 - temp && u == N - 1 - temp)) {
					matrix[u][k] = temp + 1;
				}

			}

		}
	}

	return matrix;
}