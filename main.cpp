#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
typedef enum{START,INCOMMENT,INID,INASSIGN,DONE}States;
unsigned char ReservedKeywords [][8]={"if","then","else","end","repeat","until","read","write"};
unsigned char SpecialSymbols [][10]={"+","-","*","/","=","<","(",")",";",":="};
int Scanner(){
	static int current_state=START;
	switch (current_state){
	case START:
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
	for(int i=0;i<10;i++){
		for(int j=0;SpecialSymbols[i][j]!=0;j++){
			printf("%c",SpecialSymbols[i][j]);
			fflush(stdout);
		}
		printf("\n");
	}
    ifstream inFile("./test");
	string str;
	while (getline(inFile,str)){
		cout << str << endl;
	}

}

