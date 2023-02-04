#ifndef PARAMS_H
#define PARAMS_H


enum Sizes
{
    MAX_IMG_SRC_LEN = 100,
    STACK_INIT_CAP = 5,
    MAX_NAME_LEN = 200,
    MAX_SRC_LEN = 20000,
    MAX_VAR_LEN = 20,
    MAX_VARIABLES = 20,
    MAX_TOKEN_LEN = 400,
    MAX_TOKENS = 500,
    MAX_NAMESPACES = 20,
};


enum Types
{
    NUM_T,
    VAR_T,
    OP_T,
    SPEC_T,
    NAME_T,
    NAME_SHORT_T,
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
    SQRT,
    SIN,
    COS,

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

    OUT,
    IN,

    // Only for tokenizer
    OPEN_BR,
    CLOSE_BR,
    TERMINATION_SYM,
    SEMI_COL,

    // Some other stuff
    VOID,
    TYPE,
};

const double ACCURACY = 0.000001;

//---------------------------------------------


union Values
{
    double dbl_val;
    Options op_val;
    const char* var_name;
};


struct Token
{
    Types type;
    Values value;

    int line_number;
};


struct Variable
{
    int ram_indx;
    const char* name;
};


//----------------------------------------------------------

#endif
