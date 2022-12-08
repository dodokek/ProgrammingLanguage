#ifndef DSL_H
#define DSL_H

#define DL GetDerivative (cur_node->left, print_in_pdf)
#define DR GetDerivative (cur_node->right, print_in_pdf)
#define CL CopyNode (cur_node->left)
#define CR CopyNode (cur_node->right)

#define DIGIT_NODE(num) CreateNode (NUM_T, num, UNKNOWN, nullptr, nullptr, nullptr)
#define OP_NODE(op, l, r) CreateNode (OP_T, 0, op, nullptr, l, r)
#define NAME_NODE(name, l, r) CreateNode (NAME_T, 0, UNKNOWN, name, l, r)

#define ADD(L, R) CreateNode (OP_T, 0, ADD, nullptr, L, R)
#define SUB(L, R) CreateNode (OP_T, 0, SUB, nullptr, L, R)
#define MUL(L, R) CreateNode (OP_T, 0, MUL, nullptr, L, R)
#define DIV(L, R) CreateNode (OP_T, 0, DIV, nullptr, L, R)
#define POW(L, R) CreateNode (OP_T, 0, POW,  nullptr,  L, R)
#define EQ(L, R) CreateNode (OP_T, 0, EQ,  nullptr,  L, R)


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

#define OP_PARAMS(X) OP_T, 0, X, i

//-----------Syntax Analyser Stuff

#define TOKENS_DATA token_array, cur_token_id

#define CHECK_OP_T(op) CUR_TOKEN.type == OP_T && CUR_TOKEN.value.op_val == op

#define NEXT_TOKEN *cur_token_id += 1

//--------------------------------

//----Tree to asm-----------------

#define l_child cur_node->left, cmds_file
#define r_child cur_node->right, cmds_file


//----Tree to asm-----------------



#endif