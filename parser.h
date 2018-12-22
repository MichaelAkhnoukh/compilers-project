#pragma once
#include<stdio.h>
#include<string>
#include<list>
#include"scanner.h"
using namespace std;
class TreeNode
{
public:
	tinyToken Token;
	TreeNode* Parent;
	list <TreeNode *>Children;
	TreeNode(tinyToken &T, TreeNode * p=NULL) :Token(T), Parent(p) {}
	//TreeNode() {}
	void InsertNode(TreeNode * Child) { Children.push_back(Child); }
	TreeNode* GetParent() { return Parent; }
};