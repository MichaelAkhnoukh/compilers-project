#ifndef COMPILERS_PROJECT_SCANNER_H
#define COMPILERS_PROJECT_SCANNER_H

#include <string>
#include <regex>
#include <fstream>

#define NUM_RESERVED_KEYWORDS 8
#define NUM_SPECIAL_SYMBOLS 11

using namespace std;

typedef enum {
    START, INCOMMENT, INID, INOPERATION, INNUM, DONE, ERROR
} state;

typedef struct tinyToken {
    string tokenValue;
    string tokenType;
    struct tinyToken *next = NULL;
} tinyToken;

bool isReserved(string &s);

int isValidSymbole(char &c);

string *getWords(string line);

tinyToken *addToken(tinyToken *head,const string &type, string &value);

state Scanner(ifstream &inFile);

tinyToken *get_root_token();

extern string ReservedKeywords[NUM_RESERVED_KEYWORDS];

extern char SpecialSymbols[NUM_SPECIAL_SYMBOLS];

extern string SpecialSymbolsTokens[NUM_SPECIAL_SYMBOLS];

#endif //COMPILERS_PROJECT_SCANNER_H
