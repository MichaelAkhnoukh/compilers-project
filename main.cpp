#include <iostream>
#include "scanner.h"
#include <cstdio>

int main(int argc, char *argv[]) {
	//    freopen("output.txt", "w", stdout);
	ifstream inFile("./TinySample.txt");
	Scanner(inFile);
	inFile.close();
	int i = 0;
	while (tokens[i].next) {
		cout << tokens[i].tokenValue << " , ";
		cout << tokens[i].tokenType << endl;
		i++;
	}
	//    cout << "\nEnter 'q' to exit:";
	//    while (getchar() != 'q');
	//cin.ignore();
	delete[] tokens;
}