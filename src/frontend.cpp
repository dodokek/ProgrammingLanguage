#ifndef FRONTEND_H
#define FRONTEND_H

#include "stringUtils.h"
#include "fileUtils.h"
#include "frontend.h"

TreeNode* CreateNode (Types type, double dbl_val, Options op_val, const char* var_name,
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

    TreeNode* root = GetStatement(TOKENS_DATA); 

    if (CUR_TOKEN.value.op_val == TERMINATION_SYM)
        printf ("G: Got termination symbol, ending\n");
    else
        printf ("!!! Compilation error, cur Token: Type: %d, Dbl value: %lg. Line number %d. Op type: %d\n",
               CUR_TOKEN.type, CUR_TOKEN.value.dbl_val, CUR_TOKEN.line_number, CUR_TOKEN.value.op_val);

    return root;
}


TreeNode* GetStatement (Token token_array[], int* cur_token_id)
{
    if (CHECK_OP_T (ST))
    {
        *cur_token_id += 1;
        return OP_NODE (ST, GetFunction (TOKENS_DATA), GetStatement (TOKENS_DATA));
    }
    else 
    {
        *cur_token_id += 1;
        return GetFunction (TOKENS_DATA);
    }
}


TreeNode* GetFunction (Token token_array[], int* cur_token_id)
{
    if (CHECK_OP_T (FUNC))
    {
        *cur_token_id += 1;
        return OP_NODE (FUNC, GetFuncName (TOKENS_DATA), GetStatement (TOKENS_DATA));
    }
    else {
        return GetVar ();
    }
}


TreeNode* GetFuncName (Token token_array[], int* cur_token_id)
{
    return 0; // delete this shit
}


TreeNode* GetParam (Token token_array[], int* cur_token_id)
{
    return 0;
}


TreeNode* GetVar (Token token_array[], int* cur_token_id)
{
    return OP_NODE(VAR, GetName (TOKENS_DATA), GetNumber (TOKENS_DATA));
}


TreeNode* GetExpression (Token token_array[], int* cur_token_id)
{
    TreeNode* top_operation_node = GetMlt (TOKENS_DATA);

    while (CUR_TOKEN.value.op_val == ADD || CUR_TOKEN.value.op_val == SUB)
    {
        Options last_op = CUR_TOKEN.value.op_val;
        *cur_token_id += 1;

        TreeNode* right_node = GetMlt (TOKENS_DATA);

        if (last_op == ADD)
            top_operation_node = ADD (top_operation_node, right_node);
        else
            top_operation_node = SUB (top_operation_node, right_node);
    }   

    return top_operation_node;
}


TreeNode* GetMlt (Token token_array[], int* cur_token_id)
{
    TreeNode* top_operation_node = GetPower (TOKENS_DATA);

    while (CUR_TOKEN.value.op_val == MUL || CUR_TOKEN.value.op_val == DIV)
    {
        Options last_op = CUR_TOKEN.value.op_val;
        *cur_token_id += 1;

        TreeNode* right_node = GetPower (TOKENS_DATA);

        if (last_op == MUL)
            top_operation_node = MUL (top_operation_node, right_node);
        else
            top_operation_node = DIV (top_operation_node, right_node);
    }       

    return top_operation_node;
}


TreeNode* GetPower (Token token_array[], int* cur_token_id)
{
    TreeNode* top_operation_node = GetBracketExp (TOKENS_DATA);

    while (CUR_TOKEN.value.op_val == POW)
    {
        *cur_token_id += 1;

        TreeNode* right_node = GetBracketExp (TOKENS_DATA);
        top_operation_node = POW (top_operation_node, right_node);
    }       

    return top_operation_node;
}


TreeNode* GetBracketExp (Token token_array[], int* cur_token_id)
{
    
    if (CUR_TOKEN.value.op_val == OPEN_BR)
    {
        *cur_token_id += 1;
        TreeNode* sub_node = GetExpression (TOKENS_DATA);

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

    else if (CUR_TOKEN.type ==OP_T)
    {
        Options cur_op = CUR_TOKEN.value.op_val;

        *cur_token_id += 2; // Skipping operation + bracket
        TreeNode* sub_node = GetExpression (TOKENS_DATA);

        if (CUR_TOKEN.value.op_val == CLOSE_BR)
        {
            *cur_token_id += 1;
            // return GetOperationNode (sub_node, cur_op);
            return 0;
        }
        else 
        {
            printf ("Wrong brackets sequence\n");  
        }
    }
    else
    {
        return GetNumber (TOKENS_DATA);
    }
}


TreeNode* GetNumber (Token token_array[], int* cur_token_id)
{
    if      (CUR_TOKEN.type == NUM_T)
    {
        *cur_token_id += 1;
        return DIGIT_NODE (PREV_TOKEN.value.dbl_val);
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


char* GetInputLine ()
{
    char* buffer = (char*) calloc (MAX_SRC_LEN, sizeof (char));

    FILE* input_file = get_file (input_path, "r");

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
            printf ("Now at %c\n", input[i]);

            char op_name[MAX_NAME_LEN] = "";

            int len = 0;
            sscanf (input + i, "%[^{} ]%n", op_name, &len);
            i += len;

            Options operation = GetOpType (op_name);
            TOP_TOKEN = CreateToken (OP_T, 0, operation, i); 
            tokens_amount++;

            // {
            // if (*tmp_line == '(')
            // {
            //     char op_name[100] = "";
            //
            //     int len = 0;
            //     sscanf (input + i, "%[^( ]%n", op_name, &len);
            //     i += len;
            //    
            //     Options operation = GetOpType (op_name);
            //     TOP_TOKEN = CreateToken (OP_T, 0, operation, i); 
            //     tokens_amount++;
            // }   
            // else // variable handler
            // {
            //     TOP_TOKEN = CreateToken (VAR_T, 0, UNKNOWN, i);
            //
            //     int len = 0;
            //     sscanf (input + i, "%[^+-*/() ]%n", TOP_TOKEN.value.var_name, &len);
            //     i += len;
            //
            //     printf ("Working with var, its len: %d, String %s\n", len, input + i);
            //     tokens_amount++;
            // }
            // }
        }
        else if (input[i] == '"')
        {
            i++;
            printf ("Now at %c\n", input[i]);

            TOP_TOKEN = CreateToken (VAR_T, 0, UNKNOWN, i); 

            int len = 0;
            sscanf (input + i, "%[^\" ]%n", TOP_TOKEN.value.var_name, &len);
            i += len;

            if (input[i] == '"')
            {
                printf ("Skipping fucker\n");
                i++;
            }

            tokens_amount++;
        } 
        else if (isdigit (input[i]))
        {
            printf ("Now at %c\n", input[i]);

            printf ("Proccessing digit %c\n", input[i]);

            double num = 0;

            int len;
            sscanf (input + i, "%lg%n", &num, &len);
            i += len;

            TOP_TOKEN = CreateToken (NUM_T, num, UNKNOWN, i);
            tokens_amount++;
        }
        else if (input[i] == '{' || input[i] == '}' || input[i] == '\0')
        {
            printf ("Skipping %c\n", input[i]);
            i++;
        }
        else
        {
            printf ("Now at %c\n", input[i]);

            printf ("======== Could not match pattern %s, %d ========== \n", input + i, i);
        }
    } 
}


void SkipSpaces (char* string, int* i)
{
    while (isspace (string[*i])) (*i)++;
}


Token CreateToken (Types type, double dbl_val, Options operation, int line_number)
{
    printf ("====Creating token with type %d and op val %d====\n", type, operation);

    Token* new_token = (Token*) calloc (1, sizeof (Token));

    if      (type == NUM_T) new_token->value.dbl_val  = dbl_val;
    else if (type == VAR_T) new_token->value.var_name = (char*) calloc (MAX_TOKEN_LEN, sizeof (char));
    else if (type == OP_T)  new_token->value.op_val = operation;
    
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


#define CMP(operation)                                        \
    if (strcmp (str, #operation) == 0) {return operation;}    \
    else 

Options GetOpType (char str[])
{    
    CMP (ADD)
    CMP (SUB)
    CMP (DIV)
    CMP (MUL)
    CMP (POW)
    CMP (AND)
    CMP (OR)
    CMP (EQ)
    CMP (ST)
    CMP (IF)
    CMP (ELSE)
    CMP (NIL)
    CMP (VAR)
    CMP (WHILE)
    CMP (FUNC)
    CMP (RET)
    CMP (CALL)
    CMP (PARAM)
    if (*str == '{')      return OPEN_BR;
    else if (*str == '}') return CLOSE_BR;
    else if (*str == '\0') return TERMINATION_SYM;
    {
        return UNKNOWN;
    }
}

#undef CMP



#endif