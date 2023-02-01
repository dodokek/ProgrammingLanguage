#ifndef PARS_H
#define PARS_H


#include "dsl.h" 
#include "stringUtils.h"
#include "fileUtils.h"
#include "../../params.h"
#include "translitor.h"

//-----------------------------------------------

const int PREFIX_OFFSET = 1;

//---------------------------------------------

TreeNode* GetGrammar ();

TreeNode* GetStatement (Token token_array[], int* cur_token_id);

TreeNode* GetFunction (Token token_array[], int* cur_token_id);

TreeNode* GetFuncHeader (Token token_array[], int* cur_token_id);

TreeNode* GetParam (Token token_array[], int* cur_token_id);

TreeNode* GetIfElse (Token token_array[], int* cur_token_id);

TreeNode* GetCall (Token token_array[], int* cur_token_id);

TreeNode* GetWhile (Token token_array[], int* cur_token_id);

TreeNode* GetInOut (Token token_array[], int* cur_token_id);

TreeNode* GetVar (Token token_array[], int* cur_token_id);

TreeNode* GetRet (Token token_array[], int* cur_token_id);

TreeNode* GetExpression (Token token_array[], int* cur_token_id);

TreeNode* GetAddSub (Token token_array[], int* cur_token_id);

TreeNode* GetMlt (Token token_array[], int* cur_token_id);

TreeNode* GetPower (Token token_array[], int* cur_token_id);

TreeNode* GetSpecOperations (Token token_array[], int* cur_token_id);

TreeNode* GetNumOrName (Token token_array[], int* cur_token_id);

TreeNode* GetBracketExp (Token token_array[], int* cur_token_id);

TreeNode* CreateNode (Types type,           double dbl_val,
                      Options op_val,    const char* var_name,
                      TreeNode* left_child, TreeNode* right_child);

TreeNode* DestructTree (TreeNode* root);

bool isZero (double num);

bool isEqual (double num1, double num2);

void FillTokensArray (Token* token_array);

Token* CommandToToken (char* name);

Token* CreateToken (Types type, double dbl_val, Options operation);

void PrintTokens (Token token_array[]);

void RecPrintNode (TreeNode* cur_node, FILE* out_file);

void PrintTreeInFile (TreeNode* root);

void SkipSpaces (char** string);

void RecursDrawConnections (TreeNode* node, FILE* dot_file);

void InitGraphvisNode (TreeNode* node, FILE* dot_file); 

void DrawTree (TreeNode* root);

char* GetOpSign (Options op);


#endif
