#include "stdio.h"
#include "parser.h"
#include <iostream>
#include <cstring>

using namespace std;

short stmt_sequence();
short match(const string ch);
short identifier();
short comparison_op();
short factor();
short add_op();
short mul_op();
short end_of_file();

TreeNode root();

short term(){
    while(factor()){
        if(!mul_op())
            return 0;
    }
    return 1;
}

short simple_exp(){
    while(term()){
        if(!add_op())
            return 0;
    }
    return 1;
}

short exp (){
    while(simple_exp()){
        if(!comparison_op() || !simple_exp())
            return 0;
    }
    return 1;
}

void printnexttoken(){
    tinyToken* temp = get_next_token();
//    printf("## Next Token is : %s\n",temp->tokenValue);
    cout << "## Next Token is : " << temp->tokenValue << endl;
    set_next_token(temp);
}

void printError(const char* instead){
    tinyToken* temp = get_next_token();
//    printf("## Syntax error in this token : %s\n",temp->tokenValue);
    cout << "## Syntax error in this token : " << temp->tokenValue << endl;
    cout << "! expected" << instead << " instead" << endl;
//    printf("! expected %s instead\n",instead);
    set_next_token(temp);
}

short comparison_op(){
    if (match("<") || match(">"))
        return 1;
    return 0;
}

short mul_op(){
    if (match("*") || match("/"))
        return 1;
    return 0;
}

short add_op(){
    if (match("+") || match("-"))
        return 1;
    return 0;
}

short match(const string ch){
    if(!end_of_file()){
        tinyToken* temp = get_next_token();
//        cout << temp->tokenValue << endl;
        if(temp->tokenValue != ch){
            return 1;
        }
        set_next_token(temp);
    }
    return 0;
}

short number(){
    tinyToken* temp = get_next_token();
    if(temp->tokenType=="number"){
        return 1;
    }
    set_next_token(temp);
    return 0;
}

short factor(){
    if (match("(") && exp() && match(")"))
        return 1;
    else if(number())
        return 1;
    else if(identifier())
        return 1;
    return 0;
}

short end_of_file(){
    tinyToken* temp = get_next_token();
    if(temp->tokenType == "EOF"){
        set_next_token(temp);
        return 1;
    }
    set_next_token(temp);
    return 0;
}

short assig_op(){
    tinyToken* temp = get_next_token();
    if(temp->tokenType=="Assignment"){
        return 1;
    }
    set_next_token(temp);
    return 0;
}

short assign_stmt(){
    if(factor() && assig_op() && factor()) {
        return 1;
    }
    return 0;
}

short if_stmt(){
    return 0;
}

short repeat_stmt(){
    if(match("repeat") && factor() && match("until") && factor()){
        return 1;
    }
    return 0;
}

short identifier(){
    tinyToken* temp = get_next_token();
    if(temp->tokenType=="Identifier"){
        return 1;
    }
    set_next_token(temp);
    return 0;
}

short read_stmt(){
    if(match("read") && identifier()){
        return 1;
    }
    return 0;
}

short write_stmt(){
    if(match("write") && identifier()){
        return 1;
    }
    return 0;
}

short statement(){
    if(assign_stmt()||repeat_stmt()||if_stmt()||read_stmt()||write_stmt()){
        return 1;
    }
    else if(end_of_file()){
        return 0;
    }
    printError("statment");
    return 0;
}

short stmt_sequence(){
    while(statement()){
        if(!match(";")) { // the char is not a ;
            break;
        }
    }
    if(end_of_file())
        return 1;
    return 0;
}

short program(void){
    return stmt_sequence();
}