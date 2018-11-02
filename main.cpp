#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdarg>
#include <regex>

using namespace std;

typedef enum{START,INCOMMENT,INID,INOPERATION,INNUM,DONE}States;
string ReservedKeywords [8]={"if","then","else","end","repeat","until","read","write"};
char SpecialSymbols[10]={'+','-','*','/','=','<','(',')',';',':'};
string SpecialSymbolsTokens[10] = { "Addition","Subtraction","Multiply","Division","LessThan","OpenPrackrt","ClosePracket","EOL","Assignment" };


int Scanner(string line){
	static int state=START;
	int index = 0;
	bool save;
	while(line[index]!=NULL){
		switch (state) {
		case START:
			//As long As we have white spaces do nothing
			while (line[index] != NULL && ((line[index] == ' ') || (line[index] == '\t')))
				index++;
			//indicates comment beginning
			if (line[index] == '{')
				state = INCOMMENT;
			//indicates that we have either reserved keyword or identifier
			else if (isalpha(line[index]))
				state = INID;
			//indicates that we have most segnificant bit of a number
			else if (isdigit(line[index]))
				state = INNUM;
			//indicates that we have operation like :=, +, - 
			else
				state = INOPERATION;
			break;
		case INCOMMENT:
			while (line[index] != NULL&&line[index] != '}')
				index++;
			if (line[index] == '}')
				state = START;
			break;
		case INID:
			//Call Michael's Function
			break;
		case INOPERATION:
			for (int i = 0; i < 10; i++) {
				i++;
				//the assignment operator has : & = (2 char in the string)
				if (line[index] == SpecialSymbols[i] && SpecialSymbols[i] == ':')
					i++;
			}
			state = START;
			break;
		}
			
			
	}
}

typedef struct{
	unsigned char state;
	unsigned char tokentype;
	unsigned char tokenvalue;

}jkj;
void get(const char *input){
	for(int i=0;i<10;i++){
		for(int j=0;SpecialSymbols[i][j]!=0;j++){
			for(int k=0;input[k]!=0;k++){
				if(input[k]==SpecialSymbols[i][j]){

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
int main(int argc, char *argv[]){
//	for(int i=0;i<10;i++){
//		for(int j=0;SpecialSymbols[i][j]!=0;j++){
//			printf("%c",SpecialSymbols[i][j]);
//			fflush(stdout);
//		}
//		printf("\n");
//	}
    ifstream inFile("./TinySample.txt");
	string str;
	while (getline(inFile,str)){
		Scanner(str);
		}



}