#ifndef BACK_H
#define BACK_H

#include "dsl.h" 
#include "stringUtils.h"
#include "fileUtils.h"
#include "../../params.h"


//-----------------------------------------------

const char input_path[] = "../frontend/data/tree.txt";

//-----------------------------------------------


void PrintCmdsInFile (TreeNode* root);

void PrintOperation (TreeNode* cur_node, FILE* cmds_file);

int GetVarIndx (const char* var_name);

char* GetInputLine ();

TreeNode* GetGrammar ();

TreeNode* RecGetChild (Token token_array[], int* cur_token_id);

TreeNode* GetStatement (Token token_array[], int* cur_token_id);

TreeNode* GetFunction (Token token_array[], int* cur_token_id);

TreeNode* GetFuncHeader (Token token_array[], int* cur_token_id);

TreeNode* GetParam (Token token_array[], int* cur_token_id);

TreeNode* GetIf (Token token_array[], int* cur_token_id);

TreeNode* GetElse (Token token_array[], int* cur_token_id);

TreeNode* GetCall (Token token_array[], int* cur_token_id);

TreeNode* GetInOut (Token token_array[], int* cur_token_id);

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

TreeNode* TransformNode (TreeNode* node, Types type, double dbl_val, const char* var_name);

TreeNode* CopyNode (TreeNode* node_to_cpy);

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

#define PRINT(...) fprintf (cmds_file, __VA_ARGS__)

#endif