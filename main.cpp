#include <iostream>
#include "scanner.h"
#include <cstdio>

int main(int argc, char *argv[]) {
//    freopen("output.txt", "w", stdout);
    ifstream inFile("./TinySample.txt");
    Scanner(inFile);
    inFile.close();

    tinyToken *next = get_root_token();
    while (next) {
        cout << next->tokenValue << "," << next->tokenType << endl;
        next = next->next;
    }
//    cout << "\nEnter 'q' to exit:";
//    while (getchar() != 'q');
    //cin.ignore();
}