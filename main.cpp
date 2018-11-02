#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdarg>
#include <regex>

using namespace std;
typedef enum {
    START, INCOMMENT, INID, INASSIGN, INNUM, DONE
} States;
string ReservedKeywords[8] = {"if", "then", "else", "end", "repeat", "until", "read", "write"};
string SpecialSymbols[12] = {"+", "-", "*", "/", "=", "<", "(", ")", ";", ":=", "{", "}"};

int Scanner(char c) {
    static int state = START;
    bool save;
    switch (state) {
        case START:
            break;
        case INCOMMENT:
            break;
        case INID:
            break;
        case INASSIGN:
            break;
        case INNUM:
            break;
        case DONE:
            break;
    }


}

typedef struct {
    unsigned char state;
    unsigned char tokentype;
    unsigned char tokenvalue;

} jkj;

void get(const char *input) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; SpecialSymbols[i][j] != 0; j++) {
            for (int k = 0; input[k] != 0; k++) {
                if (input[k] == SpecialSymbols[i][j]) {

                }
            }
            printf("%c", SpecialSymbols[i][j]);
            fflush(stdout);
        }
    }
}

string *splitLine(string &line) {
//    line = regex_replace(line,regex("\\{.*\\}")," ");
    string *words = new string[100];
    char *buffer = new char[line.length() + 1];
    strcpy(buffer, line.c_str());
    char *wordContext;
    const char *wordSeparators = " +-*/=<();:=";
    char *word = strtok_r(buffer, wordSeparators, &wordContext);
    int i = 0;
    while (word) {
        words[i] = word;
        word = strtok_r(NULL, wordSeparators, &wordContext);
        i++;
    }
    delete[] buffer;
    return words;
}

//void getInput()
int main(int argc, char *argv[]) {
    ifstream inFile("./TinySample.txt");
    string str = "if < x   then     {  don't compute if x <=0}";
//    while (getline(inFile, str)) {
//
//    }
    string * words = splitLine(str);
    for (int i = 0; i < 10; ++i) {
        cout << words[i] << endl;
    }
}

