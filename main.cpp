#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
typedef enum{START,INCOMMENT,INID,INASSIGN,INNUM,DONE}States;
string ReservedKeywords [8]={"if","then","else","end","repeat","until","read","write"};
string SpecialSymbols [12]={"+","-","*","/","=","<","(",")",";",":=","{","}"};
typedef struct {

};
int Scanner(char c){
	static int state=START;
	bool save;
	switch (state){
	case START:
		if (isdigit(c))
			state = INNUM;
		else if (isalpha(c))
			state = INID;
		else if (c == ':')
			state = INASSIGN;
		else if ((c == ' ') || (c == '\t') || (c == '\n'))
			save = false;
		else if (c == '{')
		{ save = false;
			state = INCOMMENT;
		}
		else
		{ state = DONE;
			switch (c)
			{ case EOF:
					save = false;
					currentToken = ENDFILE;
					break;
				case '=':
					currentToken = EQ;
					break;
				case '<':
					currentToken = LT;
					break;
				case '+':
					currentToken = PLUS;
					break;
				case '-':
					currentToken = MINUS;
					break;
				case '*':
					currentToken = TIMES;
					break;
				case '/':
					currentToken = OVER;
					break;
				case '(':
					currentToken = LPAREN;
					break;
				case ')':
					currentToken = RPAREN;
					break;
				case ';':
					currentToken = SEMI;
					break;
				default:
					currentToken = ERROR;
					break;
			}
		}
		break;
	case INCOMMENT:
		break;
	case INID:
		break;
	case INASSIGN:
		break;
	case DONE:
		break;
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

				}
			}
			printf("%c",SpecialSymbols[i][j]);
			fflush(stdout);
		}
	}
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
		cout << str << endl;
		if(str==""){
			cout << "new line" << endl;
		}

	}

}

