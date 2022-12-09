#ifndef PARAMS_H
#define PARAMS_H
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

#endif
