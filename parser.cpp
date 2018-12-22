#include "stdio.h"

//#include "scanner.h"
#include"parser.h"

short stmt_sequence();
short match(const char* ch);
short identifier();
short comparison_op();
short factor();
short add_op();
short mul_op();

short term() {
	while (factor()) {
		if (!mul_op())
			return 0;
	}
	return 1;
}

short exp() {
	while (simple_exp()) {
		if (!comparison_op() || !simple_exp())
			return 0;
	}
	return 1;
}

short simple_exp() {
	while (term()) {
		if (!add_op())
			return 0;
	}
	return 1;
}



void printnexttoken() {
	token* temp = get_next_token();
	printf("## Next Token is : %s\n", temp->value);
	set_next_token(temp);
}

void printError(const char* instead) {
	token* temp = get_next_token();
	printf("## Syntax error in this token : %s\n", temp->value);
	printf("! expected %s instead\n", instead);
	set_next_token(temp);
}

short comparison_op() {
	if (match("<") || match(">"))
		return 1;
	return 0;
}

short mul_op() {
	if (match("*"))
		return 1;
	else if (match("/"))
		return 1;
	return 0;
}

short add_op() {
	if (match("+"))
		return 1;
	else if(match("-"))
		return 1;
	return 0;
}
//uses the linked list
short match(const char* ch) {
	tokens* temp = get_next_token();
	if (!strcmp(temp->value, ch)) {
		return 1;
	}
	set_next_token(temp);
	return 0;
}
//uses the linked list
short number() {
	token* temp = get_next_token();
	if (temp->type == NUMBER) {
		return 1;
	}
	set_next_token(temp);
	return 0;
}

short factor() {
	if (match("(") && exp() && match(")"))
		return 1;
	else if (number())
		return 1;
	else if (identifier())
		return 1;
	return 0;
}
//uses the linked list
short end_of_file() {
	tokens* temp = get_next_token();
	if (temp->type == _EOF) {
		set_next_token(temp);
		return 1;
	}
	set_next_token(temp);
	return 0;
}
//uses the linked list
short assig_op() {
	token* temp = get_next_token();
	if (temp->type == ASSIG_OP) {
		return 1;
	}
	set_next_token(temp);
	return 0;
}

short assign_stmt() {
	if (identifier() && assig_op() && exp()) {
		return 1;
	}
	return 0;
}

short if_stmt() {
	if ((match("if") && exp() && match("then") && stmt_sequence() && match("end")));
	else if (match("if") && exp() && match("then") && stmt_sequence() && match("else") && stmt_sequence() && match("end"));
	return 0;
}

short repeat_stmt(TreeNode *Parent) {
	if (match("repeat") && factor() && match("until") && factor()) {
		return 1;
	}
	return 0;
}

short identifier(TreeNode *Parent) {
	token* temp = Parent->Token.next;
	if (temp->type == IDENTIFIER) {
		return 1;
	}
	set_next_token(temp);
	return 0;
}

short read_stmt(TreeNode *Parent) {
	if (match("read") && identifier()) {
		return 1;
	}
	return 0;
}

short write_stmt(TreeNode *Parent) {
	if (match("write") && identifier(Parent)) {
		return 1;
	}
	return 0;
}

short statement(TreeNode *Parent) {
	if (if_stmt(Parent) || repeat_stmt(Parent) || assign_stmt(Parent) || read_stmt(Parent) || write_stmt(Parent)) {
		return 1;
	}
	else if (end_of_file()) {
		return 0;
	}
	printError("statment");
	return 0;
}

short stmt_sequence(TreeNode *Parent) {
	while (statement(Parent)) {
		//match not yet checked
		if (!match(";"))// the char is not a ;
			break;
	}
	//Not yet done as there is conflict between your implementation and his
	if (end_of_file())
		return 1;
	return 0;
}

TreeNode* program(tinyToken &obj) {
	TreeNode *Root=new TreeNode(obj);
	stmt_sequence(Root);
	return Root;
}

