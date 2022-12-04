#ifndef FRONTEND_H
#define FRONTEND_H

#include "stringUtils.h"
#include "fileUtils.h"
#include "frontend.h"

TreeNode* CreateNode (Types type, double dbl_val, Operations op_val, const char* var_name,
                      TreeNode* left_child, TreeNode* right_child)
{
    // printf ("Creating node with type %d\n", type);

    TreeNode* new_node = (TreeNode*) calloc (1, sizeof (TreeNode));
    if (!new_node) return nullptr;

    if      (type == NUM_T) new_node->value.dbl_val  = dbl_val;
    else if (type == VAR_T) new_node->value.var_name = var_name;
    else if (type == OP_T)  new_node->value.op_val   = op_val;
    
    new_node->left   = left_child;
    new_node->right  = right_child;
    new_node->parent = nullptr;
    new_node->type   = type;

    return new_node;
}


TreeNode* CopyNode (TreeNode* node_to_cpy)
{
    TreeNode* new_node = (TreeNode*) calloc (1, sizeof (TreeNode));
    if (!new_node) return nullptr;

    *new_node = *node_to_cpy;

    return new_node;
}


TreeNode* CreateDigitNode (double dbl_val)
{
    TreeNode* new_node = (TreeNode*) calloc (1, sizeof (TreeNode));
    if (!new_node) return nullptr;

    new_node->value.dbl_val  = dbl_val;
    
    new_node->left   = nullptr;
    new_node->right  = nullptr;
    new_node->parent = nullptr;
    new_node->type   = NUM_T;

    return new_node;
}


TreeNode* TransformNode (TreeNode* node, Types type, double dbl_val, const char* var_name)
{
    node->type = type;
    
    if (type == NUM_T)
        node->value.dbl_val = dbl_val;
    else
        node->value.var_name = var_name;

    if (node->left)  free (node->left);
    if (node->right) free (node->right);

    node->left = nullptr;
    node->right = nullptr;

}


TreeNode* DestructTree (TreeNode* root)
{
    if (root->left)  DestructTree (root->left);
    if (root->right) DestructTree (root->right);

    root->value.var_name = nullptr;
    
    free (root);
    root = nullptr;

    return root;
}


//---<Parser>-------------------------------------------


TreeNode* GetGrammar () 
{
    Token token_array[MAX_TOKENS];
    FillTokensArray (token_array);
    PrintTokens (token_array);

    int token_id = 0;
    int* cur_token_id = &token_id;

    TreeNode* root = GetExpression(token_array, cur_token_id); 

    if (CUR_TOKEN.value.op_val == TERMINATION_SYM)
        printf ("G: Got termination symbol, ending\n");
    else
        printf ("!!! Compilation error, cur Token: Type: %d, Dbl value: %lg. Line number %d. Op type: %d\n",
               CUR_TOKEN.type, CUR_TOKEN.value.dbl_val, CUR_TOKEN.line_number, CUR_TOKEN.value.op_val);

    return root;
}


TreeNode* GetExpression (Token token_array[], int* cur_token_id)
{
    TreeNode* top_operation_node = GetMlt (token_array, cur_token_id);

    while (CUR_TOKEN.value.op_val == ADD || CUR_TOKEN.value.op_val == SUB)
    {
        Operations last_op = CUR_TOKEN.value.op_val;
        *cur_token_id += 1;

        TreeNode* right_node = GetMlt (token_array, cur_token_id);

        if (last_op == ADD)
            top_operation_node = ADD (top_operation_node, right_node);
        else
            top_operation_node = SUB (top_operation_node, right_node);
    }   

    return top_operation_node;
}


TreeNode* GetMlt (Token token_array[], int* cur_token_id)
{
    TreeNode* top_operation_node = GetPower (token_array, cur_token_id);

    while (CUR_TOKEN.value.op_val == MUL || CUR_TOKEN.value.op_val == DIV)
    {
        Operations last_op = CUR_TOKEN.value.op_val;
        *cur_token_id += 1;

        TreeNode* right_node = GetPower (token_array, cur_token_id);

        if (last_op == MUL)
            top_operation_node = MUL (top_operation_node, right_node);
        else
            top_operation_node = DIV (top_operation_node, right_node);
    }       

    return top_operation_node;
}


TreeNode* GetPower (Token token_array[], int* cur_token_id)
{
    TreeNode* top_operation_node = GetBracketExp (token_array, cur_token_id);

    while (CUR_TOKEN.value.op_val == POW)
    {
        *cur_token_id += 1;

        TreeNode* right_node = GetBracketExp (token_array, cur_token_id);
        top_operation_node = POW (top_operation_node, right_node);
    }       

    return top_operation_node;
}


TreeNode* GetBracketExp (Token token_array[], int* cur_token_id)
{
    
    if (CUR_TOKEN.value.op_val == OPEN_BR)
    {
        *cur_token_id += 1;
        TreeNode* sub_node = GetExpression (token_array, cur_token_id);

        if (CUR_TOKEN.value.op_val == CLOSE_BR)
        {
            *cur_token_id += 1;
            return sub_node;
        }
        else 
        {
            printf ("Wrong brackets sequence\n");  
        }        
    }

    else if (CUR_TOKEN.type == OP_T)
    {
        Operations cur_op = CUR_TOKEN.value.op_val;

        *cur_token_id += 2; // Skipping operation + bracket
        TreeNode* sub_node = GetExpression (token_array, cur_token_id);

        if (CUR_TOKEN.value.op_val == CLOSE_BR)
        {
            *cur_token_id += 1;
            return GetOperationNode (sub_node, cur_op);
        }
        else 
        {
            printf ("Wrong brackets sequence\n");  
        }
    }
    else
    {
        return GetNumber (token_array, cur_token_id);
    }
}


TreeNode* GetNumber (Token token_array[], int* cur_token_id)
{
    if      (CUR_TOKEN.type == NUM_T)
    {
        *cur_token_id += 1;
        return CreateDigitNode (PREV_TOKEN.value.dbl_val);
    }

    else if (CUR_TOKEN.type == VAR_T)
    {
        *cur_token_id += 1;
        return CreateNode (VAR_T, 0, UNKNOWN, PREV_TOKEN.value.var_name, nullptr, nullptr);
    }
    else 
    {
        *cur_token_id += 1;
        printf ("Unexpected token, returning null\n");
        return nullptr;
    }
}


TreeNode* GetOperationNode (TreeNode* child_node, Operations op)
{
    switch (op)
    {
    case SIN:
        return SIN (nullptr, child_node);
    
    case COS:
        return COS (nullptr, child_node);

    case LN:
        return LN (nullptr, child_node);
    
    default:
        printf ("While GetMlting operation nodes, error occured: %d\n", op);
        break;
    }

    return 0;
}


char* GetInputLine ()
{
    char* buffer = (char*) calloc (MAX_SRC_LEN, sizeof (char));

    FILE* input_file = get_file ("data/input.txt", "r");

    fgets (buffer, MAX_SRC_LEN, input_file);

    fclose (input_file);

    return buffer;   
}


//-------Parser->Lecsical analysis----------------------------------

void FillTokensArray (Token* token_array)
{
    char* input = GetInputLine();
    int tokens_amount = 0;
    int input_len = (int) strlen(input);

    for (int i = 0; i <= input_len;)
    {
        SkipSpaces (input, &i);

        if (isalpha(input[i]))
        {
            char* tmp_line = (input + i);
            while (isalpha (*tmp_line)) tmp_line++;

            if (*tmp_line == '(')
            {
                char op_name[100] = "";
                
                int len = 0;
                sscanf (input + i, "%[^( ]%n", op_name, &len);
                i += len;
                
                Operations operation = GetOpType (op_name);
                TOP_TOKEN = CreateToken (OP_T, 0, operation, i); 
                tokens_amount++;
            }   
            else // variable handler
            {
                TOP_TOKEN = CreateToken (VAR_T, 0, UNKNOWN, i);

                int len = 0;
                sscanf (input + i, "%[^+-*/() ]%n", TOP_TOKEN.value.var_name, &len);
                i += len;

                printf ("Working with var, its len: %d, String %s\n", len, input + i);
                tokens_amount++;
            }
        }
        else if (isdigit (input[i]))
        {
            printf ("Proccessing digit %c\n", input[i]);

            double num = 0;

            int len;
            sscanf (input + i, "%lg%n", &num, &len);
            i += len;

            TOP_TOKEN = CreateToken (NUM_T, num, UNKNOWN, i);
            tokens_amount++;

        }
        else
        {
            printf ("Proccessing operation %c\n", input[i]);

            Operations operation = UNKNOWN;
            operation = GetOpType (input + i);
            printf ("Input: %c, Op type: %d\n", input[i], operation);
        
            TOP_TOKEN = CreateToken (OP_PARAMS(operation));
            
            tokens_amount++;
            i++;
        }
    } 
}


void SkipSpaces (char* string, int* i)
{
    while (isspace (string[*i])) (*i)++;
}


Token CreateToken (Types type, double dbl_val, Operations op_t, int line_number)
{
    printf ("====Creating token with type %d and op val %d====\n", type, op_t);

    Token* new_token = (Token*) calloc (1, sizeof (Token));

    if      (type == NUM_T) new_token->value.dbl_val  = dbl_val;
    else if (type == VAR_T) new_token->value.var_name = (char*) calloc (MAX_TOKEN_LEN, sizeof (char));
    else if (type == OP_T)  new_token->value.op_val   = op_t;
    
    new_token->type = type;
    new_token->line_number = line_number;

    return *new_token;
}


void PrintTokens (Token* token_array)
{
    int i = 0;
    while (token_array[i].value.op_val != TERMINATION_SYM)
    {
        printf ("Token. Type: %d, Dbl value: %lg. Line number %d. Op type: %d\n",
               token_array[i].type, token_array[i].value.dbl_val, token_array[i].line_number, token_array[i].value.op_val);

        i++;
    }
}


//-------Parser->Lecsical analysis----------------------------------


//--Parser.End---------------------------------------------------


#define CMP(operation) strcmp (str, #operation) == 0

Operations GetOpType (char str[])
{    
    if      (str[0] == '+') return ADD;
    else if (str[0] == '-') return SUB;
    else if (str[0] == '*') return MUL;
    else if (str[0] == '/') return DIV;
    else if (str[0] == '^') return POW;
    else if (str[0] == '(') return OPEN_BR;
    else if (str[0] == ')') return CLOSE_BR;
    else if (str[0] == '\0') return TERMINATION_SYM;
    else if (CMP (sin)) return SIN;
    else if (CMP (cos)) return COS;
    else if (CMP (tg))  return TG;
    else if (CMP (ctg)) return CTG;
    else if (CMP (ln)) return LN;
    else if (CMP (arccos)) return ARCCOS;
    else if (CMP (arcsin)) return ARCSIN;


    else return UNKNOWN;
}

#undef CMP



#endif