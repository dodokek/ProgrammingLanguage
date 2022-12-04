#ifndef DSL_H
#define DSL_H

#define DL GetDerivative (cur_node->left, print_in_pdf)
#define DR GetDerivative (cur_node->right, print_in_pdf)
#define CL CopyNode (cur_node->left)
#define CR CopyNode (cur_node->right)
#define GET_DIGIT(num) CreateDigitNode (num)

#define ADD(L, R) CreateNode (OPERATION_T, 0, ADD, nullptr, L, R)
#define SUB(L, R) CreateNode (OPERATION_T, 0, SUB, nullptr, L, R)
#define MUL(L, R) CreateNode (OPERATION_T, 0, MUL, nullptr, L, R)
#define DIV(L, R) CreateNode (OPERATION_T, 0, DIV, nullptr, L, R)
#define POW(L, R) CreateNode (OPERATION_T, 0, POW,  nullptr,  L, R)

#define INIT_PARAMSOPERATION_T, 0, UNKNOWN, nullptr, nullptr, nullptr
#define VAR_PARAMS(V)  VAR_T, 0, UNKNOWN, #V, nullptr, nullptr

#define _print(...) fprintf (out_file, __VA_ARGS__)

//--Simplifier

#define _SimplifyTree(X) while(SimplifyTree(X)) 

#define L_DBL cur_node->left->value.dbl_val
#define R_DBL cur_node->right->value.dbl_val

#define L_TYPE cur_node->left->type
#define R_TYPE cur_node->right->type

#define L_VAR cur_node->left->value.var_name
#define R_VAR cur_node->right->value.var_name

#define CUR_OP cur_node->value.op_val
#define CUR_T  cur_node->type

//--Tokenizer

#define CUR_TOKEN token_array[*cur_token_id]
#define PREV_TOKEN token_array[*cur_token_id - 1]

#define TOP_TOKEN token_array[tokens_amount]

#define OP_PARAMS(X)OPERATION_T, 0, X, i

//-----------

#endif