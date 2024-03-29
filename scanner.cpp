#include "scanner.h"
#include <iostream>

using namespace std;
string ReservedKeywords[NUM_RESERVED_KEYWORDS] = {"if", "then", "else", "end", "repeat", "until", "read", "write"};
char SpecialSymbols[NUM_SPECIAL_SYMBOLS] = {'+', '-', '*', '/', '<', '>', '(', ')', ';', ':', '='};
string SpecialSymbolsTokens[NUM_SPECIAL_SYMBOLS] = {"Addition", "Subtraction", "Multiply", "Division", "LessThan",
                                                    "GreaterThan", "OpenBracket", "CloseBracket", "EOL", "Assignment",
                                                    "Comparison"};
tinyToken *rootToken = NULL;
tinyToken *next_token;

state Scanner(ifstream &inFile) {
    string line;
    tinyToken *head = new tinyToken;
    while (getline(inFile, line)) {
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
                    else if (isdigit(line[index]) ||
                             (line[index] == '-' && (head->tokenValue == ":=" || head->tokenValue == "=") &&
                              isdigit(line[index + 1])))
                        state = INNUM;
                        //indicates that we have operation like :=, +, -
                    else if (line[index] == '}')
                        index++;
                    else if (isValidSymbole(line[index]) != -1)
                        state = INOPERATION;
                    else
                        return ERROR;
                    break;
                    //Ready and Finalized
                case INCOMMENT:
                    while (line[index] != NULL && line.length() >= 1 && line[index] != '}')
                        index++;
                    if (line[index] == '}')
                        state = START;
                    break;
                case INID: {
                    tokenType = "";
                    tokenValue = *(s + j);
                    if (isReserved(s[j])) {
                        tokenType = s[j];
                    } else {
                        tokenType = "identifier";
                    }
                    head = addToken(head, tokenType, tokenValue);
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
                    if (isValidSymbole(line[index]) != -1) {
                        tokenValue = line[index];
                        if (line[index] == ':' || line[index] == '<' || line[index] == '>') {
                            if (line[index + 1] == '=') {
                                compoundOP = true;
                                tokenValue += '=';
                            }
                        }
                        tokenType = SpecialSymbolsTokens[isValidSymbole(line[index])];
                        head = addToken(head, tokenType, tokenValue);
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
                    bool isNegative = false;
                    while (line[index] != NULL &&
                           (isdigit(line[index]) || ((line[index] == '.') && isFloat == false) || line[index] == '-')) {
                        if (line[index] == '.') {
                            isFloat = true;
                        }
                        tokenValue += line[index++];
                        //don't do double incrementation if cout is enabled
                        //don't forget to increment the index after removing the cout
                    }
                    head = addToken(head, tokenType, tokenValue);
                    state = START;
                    break;
                    //TODO DONE state
                    //TODO ERROR state
            }
        }
        delete[] s;
    }
//    string eof = "EOF";
//    addToken(head,eof,eof);
    next_token = rootToken;
    return DONE;
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

tinyToken *addToken(tinyToken *head, const string &type, string &value) {

    if (rootToken == NULL) {
        rootToken = head;
    }

    tinyToken *token = new tinyToken;
    token->tokenType = type;
    token->tokenValue = value;
    head->next = token;

    return token;
}

tinyToken *get_root_token() {
    return rootToken->next;
}

tinyToken *get_next_token() {
    tinyToken *temp = next_token;
    next_token = next_token->next;
    return temp;
}

void set_next_token(tinyToken *t) {
    next_token = t;
}