#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdarg>
#include <regex>
#include<cstdio>

#define NUM_RESERVED_KEYWORDS 8
#define NUM_SPECIAL_SYMBOLS 11
#define MAX_TOKENS_NUMBER 100
using namespace std;

typedef enum {
    START, INCOMMENT, INID, INOPERATION, INNUM, DONE, ERROR
} States;

typedef struct {
    string tokenValue;
    string tokenType;
} tinyToken;

string ReservedKeywords[NUM_RESERVED_KEYWORDS] = {"if", "then", "else", "end", "repeat", "until", "read", "write"};

char SpecialSymbols[NUM_SPECIAL_SYMBOLS] = {'+', '-', '*', '/', '<', '>', '(', ')', ';', ':', '='};

string SpecialSymbolsTokens[NUM_SPECIAL_SYMBOLS] = {"Addition", "Subtraction", "Multiply", "Division", "LessThan",
                                                    "GreaterThan", "OpenBracket", "CloseBracket", "EOL", "Assignment",
                                                    "Comparison"};

bool isReserved(string &s);

int isValidSymbole(char &c);

string *getWords(string line);

void addToken(const string &type, string &value);

tinyToken *tokens = new tinyToken[MAX_TOKENS_NUMBER];

//TODO modifiy Scanner function to return array of tokens
void Scanner(string line) {
    static int state = START;
    int index = 0;
    string tokenType = "", tokenValue = "";
    int j = 0;
    string *s = getWords(line);
    while (line[index] != NULL) {
        switch (state) {
            case START:
                //As long As we have white spaces do nothing
                while (line[index] != NULL && (line[index] == ' ' || line[index] == '\t'))
                    index++;
                //indicates comment beginning
                if (line[index] == '{') {
                    state = INCOMMENT;
                }
                    //indicates that we have either reserved keyword or identifier
                else if (isalpha(line[index]))
                    state = INID;
                    //indicates that we have most segnificant bit of a number
                else if (isdigit(line[index]))
                    state = INNUM;
                    //indicates that we have operation like :=, +, -
                else if (line[index] == '}')
                    index++;
                else if (isValidSymbole(line[index]) != -1)
                    state = INOPERATION;
                else
                    state = ERROR;
                break;
                //Ready and Finalized
            case INCOMMENT:
                while (line[index] != NULL && line.length() >= 1 && line[index] != '}')
                    index++;
                if (line[index] == '}')
                    state = START;
                break;
            case INID: {
                cout << *(s + j) << ",";
                if (isReserved(s[j])) {
                    cout << "Keyword" << endl;
                } else {
                    cout << "Identifier" << endl;
                }
                j++;
                while (isalpha(line[index]) || isdigit(line[index]))
                    index++;
                state = START;
                break;
            }
                //Ready To print
            case INOPERATION: {
                tokenType = "";
                tokenValue = "";
                bool compoundOP = false;
                if (isValidSymbole(line[index]) > 0) {
//                    cout << line[index];
                    tokenValue = line[index];
                    if (line[index] == ':' || line[index] == '<' || line[index] == '>') {
                        if (line[index + 1] == '=') {
                            compoundOP = true;
//                            cout << '=';
                            tokenValue += '=';
                        }
                    }
//                    cout << ',' << SpecialSymbolsTokens[isValidSymbole(line[index])] << endl;
                    tokenType = SpecialSymbolsTokens[isValidSymbole(line[index])];
                    addToken(tokenType, tokenValue);
                }
                (compoundOP) ? index += 2 : index++;
                state = START;
                break;
            }
                //Ready to print
            case INNUM:
                tokenType = "number";
                tokenValue = "";
                //Accept floating point numbers ignoring a second decimal point if exists
                bool isFloat = false;
                while (line[index] != NULL && (isdigit(line[index]) || (line[index] == '.') && isFloat == false)) {
                    if (line[index] == '.') {
                        isFloat = true;
                    }
                    tokenValue += line[index++];
                    //don't do double icrementation if cout is enabled
                    //don't forget to increment the index after removing the cout
//                    cout << line[index++];
                }
                addToken(tokenType, tokenValue);
//                cout << ",number\n";
                state = START;
                break;
                //TODO DONE state
                //TODO ERROR state
        }
    }
    delete[] s;
}


string *getWords(string line) {
    line = regex_replace(line, regex("\\{.*\\}"), "");
    line = regex_replace(line, regex("[ \\t]+$"), "");
    string *words = new string[line.length()];
    char *buffer = new char[line.length() + 1];
    strcpy(buffer, line.c_str());
    char *wordContext;
    const char *wordSeparators = " +-=<();:=*";
    char *word = strtok_r(buffer, wordSeparators, &wordContext);
    int i = 0;
    while (word) {
        if (!isdigit(word[0]) && isValidSymbole(word[0]) == -1) {
            words[i] = word;
            i++;
        }
        word = strtok_r(NULL, wordSeparators, &wordContext);
    }
    delete[] buffer;
    return words;
}

bool isReserved(string &s) {
    for (int i = 0; i < NUM_RESERVED_KEYWORDS; ++i) {
        if (ReservedKeywords[i] == s) {
            return true;
        }
    }
    return false;
}

//checks if the symbol is valid
//return -1 in case of not valid
//return the position of the symbols token if valid
int isValidSymbole(char &c) {
    for (int i = 0; i < NUM_SPECIAL_SYMBOLS; ++i) {
        if (SpecialSymbols[i] == c) {
            return i;
        }
    }
    return -1;
}

void addToken(const string &type, string &value) {
    static int tokenIndex = 0;
    static int size = MAX_TOKENS_NUMBER;
    tokens[tokenIndex].tokenType = type;
    tokens[tokenIndex].tokenValue = value;
    tokenIndex++;
    //Automatically resize the tokens array if its full
    if (tokenIndex >= size) {
        size = size * 2;
        tinyToken *temp = new tinyToken[size];
        copy(tokens, tokens + (size / 2), temp);
        delete[] tokens;
        tokens = new tinyToken[size * 2];
        copy(temp, temp + (size / 2), tokens);
        delete[] temp;
    }
}

int main(int argc, char *argv[]) {
//    freopen("output.txt","w",stdout);
    ifstream inFile("./TinySample.txt");
    string str;
    while (getline(inFile, str)) {
        Scanner(str);
    }
//    cout << "\nEnter 'q' to exit:";
//    while (getchar() != 'q');
    //cin.ignore();
    delete[] tokens;
}