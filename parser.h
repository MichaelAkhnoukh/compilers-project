#ifndef COMPILERS_PROJECT_PARSER_H
#define COMPILERS_PROJECT_PARSER_H

#include "scanner.h"
#include <list>
short program(void);

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

#endif //COMPILERS_PROJECT_PARSER_H
