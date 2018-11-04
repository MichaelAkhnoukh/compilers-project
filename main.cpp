#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdarg>
#include <regex>
#include<cstdio>

#define NUM_RESERVED_KEYWORDS 8
#define NUM_SPECIAL_SYMBOLS 10

using namespace std;

typedef enum{START,INCOMMENT,INID,INOPERATION,INNUM,DONE}States;
string ReservedKeywords [NUM_RESERVED_KEYWORDS]={"if","then","else","end","repeat","until","read","write"};
char SpecialSymbols[NUM_SPECIAL_SYMBOLS]={'+','-','*','/','<','(',')',';',':','='};
string SpecialSymbolsTokens[NUM_SPECIAL_SYMBOLS] = { "Addition","Subtraction","Multiply","Division","LessThan","OpenPrackrt","ClosePracket","EOL","Assignment","Comparison" };

bool isReserved(string& s);
string *getWords(string &line);

void Scanner(string line){
	static int state=START;
	int index = 0;
	while(line[index]!=NULL){
		switch (state) {
		case START:
			//As long As we have white spaces do nothing
			while (line[index] != NULL && ( line[index] == ' ' || line[index] == '\t'))
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
			else
				state = INOPERATION;
			break;

		//Ready and Finalized
		case INCOMMENT:
			while (line[index]!=NULL&&line.length()>=1&&line[index] != '}')
				index++;
			if (line[index] == '}')
				//line = regex_replace(line, regex("\\{.*\\}"), " ");
				state = START;
			break;
		case INID:
			//Call Michael's Function
			while (isalpha(line[index]))
				index++;
			state = START;
			break;
		//Ready To print
		case INOPERATION:
		{int i;
		bool isAssignment = false;
		for (i = 0; i < 10; i++) {
			//the assignment operator has : & = (2 char in the string)
			if (line[index] == SpecialSymbols[i]) {
				index++;
				if (SpecialSymbols[i] == ':') {
					index++;
					isAssignment = true;
				}
				break;
			}

		}
		(isAssignment) ? cout << SpecialSymbols[i] << "=,Assignment\n" : cout << SpecialSymbols[i] << "," << SpecialSymbolsTokens[i] << endl;
		state = START;
		break; }
		//Ready to print
		case INNUM:
			while (line[index]!=NULL&&isdigit(line[index]))
				cout << line[index++];
			cout << ",number\n";
			state = START;
			break;
		}
			
			
	}
}


string *getWords(string &line) {
//    line = regex_replace(line,regex("\\{.*\\}")," ");
    string *words = new string[100];
    char *buffer = new char[line.length() + 1];
    strcpy(buffer, line.c_str());
    char *wordContext;
    const char *wordSeparators = " +-=<();:=";
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

bool isReserved(string& s){
    for (int i = 0; i < NUM_RESERVED_KEYWORDS; ++i) {
        if (ReservedKeywords[i] == s) {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]){
   ifstream inFile("./TinySample.txt");
	string str;
	while (getline(inFile,str)){
		Scanner(str);
		}
	cout << "\nEnter 'q' to exit:";
	while (getchar() != 'q');
		//cin.ignore();
}