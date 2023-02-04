#ifndef BACK_H
#define BACK_H

#include "dsl.h" 
#include "../../utils/include/fileUtils.h"
#include "../../utils/include/stack.h"
#include "../../utils/include/stringUtils.h"
#include "../../utils/include/tree.h"
#include "../../params.h"
#include "tree_to_asm.h"
#include "reverse.h"


//-----------------------------------------------

//-----------------------------------------------

enum IsFunc
{
    NOT_FUNC,
    IS_FUNC,
};



char* GetInputLine ();

TreeNode* GetGrammar ();

void SkipSpaces (char* string, int* i);

TreeNode* CreateNode (Types type,           double dbl_val,
                      Options op_val,    const char* var_name,
                      TreeNode* left_child, TreeNode* right_child);

TreeNode* DestructTree (TreeNode* root);

Options GetOpType (char str[]);

bool isZero (double num);

bool isEqual (double num1, double num2);

TreeNode* GetOperationNode (TreeNode* child_node, Options op);

void FillTokensArray (Token* token_array);

Token CreateToken (Types type, double dbl_val, Options operation, int line_number);

void PrintTokens (Token token_array[]);

void RecursDrawConnections (TreeNode* node, FILE* dot_file);

void InitGraphvisNode (TreeNode* node, FILE* dot_file); 

void DrawTree (TreeNode* root);

char* GetOpSign (Options op);

int SimplifyTree (TreeNode* cur_node);

TreeNode* RecGetChild (Token token_array[], int* cur_token_id, bool is_func_name);

void PutTabs (FILE* file, int amount);

#define PRINT(...) fprintf (cmds_file, __VA_ARGS__)

#endif