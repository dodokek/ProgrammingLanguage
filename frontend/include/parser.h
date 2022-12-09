#ifndef PARS_H
#define PARS_H


#include "dsl.h" 
#include "stringUtils.h"
#include "fileUtils.h"
#include "../../params.h"

//-----------------------------------------------

const char input_path[] = "data/input.txt";

//---------------------------------------------

char* GetInputLine ();

TreeNode* GetGrammar ();

TreeNode* GetStatement (Token token_array[], int* cur_token_id);

TreeNode* GetFunction (Token token_array[], int* cur_token_id);

TreeNode* GetFuncHeader (Token token_array[], int* cur_token_id);

TreeNode* GetParam (Token token_array[], int* cur_token_id);

TreeNode* GetIf (Token token_array[], int* cur_token_id);

TreeNode* GetElse (Token token_array[], int* cur_token_id);

TreeNode* GetCall (Token token_array[], int* cur_token_id);

TreeNode* GetVar (Token token_array[], int* cur_token_id);

TreeNode* GetName (Token token_array[], int* cur_token_id);

TreeNode* GetRet (Token token_array[], int* cur_token_id);

TreeNode* GetExpression (Token token_array[], int* cur_token_id);

TreeNode* GetAddSub (Token token_array[], int* cur_token_id);

TreeNode* GetMlt (Token token_array[], int* cur_token_id);

TreeNode* GetPower (Token token_array[], int* cur_token_id);

TreeNode* GetNumOrVar (Token token_array[], int* cur_token_id);

TreeNode* GetBracketExp (Token token_array[], int* cur_token_id);

void SkipSpaces (char* string, int* i);

TreeNode* GetMltreeRoot ();

TreeNode* CreateNode (Types type,           double dbl_val,
                      Options op_val,    const char* var_name,
                      TreeNode* left_child, TreeNode* right_child);

TreeNode* BuildTree (FILE* tree_info);

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

#endif
