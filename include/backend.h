#ifndef FRONT_H
#define FRONT_H

#include "dsl.h" 
#include "stringUtils.h"
#include "fileUtils.h"

//-----------------------------------------------


enum Sizes
{
    MAX_IMG_SRC_LEN = 100,
    STACK_INIT_CAP = 5,
    MAX_NAME_LEN = 100,
    MAX_SRC_LEN = 500,
    MAX_VARIABLES = 10,
    MAX_TOKEN_LEN = 10,
    MAX_TOKENS = 200,
};


enum Types
{
    NUM_T,
    VAR_T,
    OP_T,
    SPEC_T,
    NAME_T,
};


enum Options
{
    UNKNOWN,
    ADD,
    SUB,
    DIV,
    MUL,
    POW,
    AND,
    OR,
    EQ,

    // Comparison
    IS_EE,
    IS_GE,
    IS_BE,
    IS_GT,
    IS_BT,
    IS_NE,
    
    // Special nodes 
    ST,
    IF,
    ELSE,
    NIL,
    VAR,
    WHILE,
    FUNC,
    RET,
    CALL,
    PARAM,

    // Only for tokenizer
    OPEN_BR,
    CLOSE_BR,
    TERMINATION_SYM,
};

const double ACCURACY = 0.000001;

const char input_path[] = "data/input.txt";

//---------------------------------------------


union Values
{
    double dbl_val;
    Options op_val;
    const char* var_name;
};


struct TreeNode
{
    Types type; 
    
    TreeNode* parent;

    TreeNode* left;
    TreeNode* right;

    Values value;
};


struct Token
{
    Types type;
    Values value;

    int line_number;
};


//----------------------------------------------------------


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

#endif