#ifndef FRONTEND_H
#define FRONTEND_H

#include "stringUtils.h"
#include "fileUtils.h"
#include "backend.h"

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
    printf ("%d: ", *cur_token_id);

    printf ("St: Now at %d\n", CUR_TOKEN.value.op_val);

    if (CHECK_OP_T (ST))
    {
        *cur_token_id += 1;
        TreeNode* tmp_node = GetVar (TOKENS_DATA);
        return OP_NODE (ST, tmp_node, GetStatement (TOKENS_DATA));
    }
    else if (CHECK_OP_T (NIL))
    {
        *cur_token_id += 1;
        return nullptr;
    }
    else 
    {
        *cur_token_id += 1;
        return GetVar (TOKENS_DATA);
    }
}


TreeNode* GetVar (Token token_array[], int* cur_token_id)
{
    printf ("%d: ", *cur_token_id);
    printf ("Var: Now at %d %d\n", CUR_TOKEN.value.op_val, __LINE__);

    *cur_token_id += 1;
    TreeNode* tmp_node = GetName (TOKENS_DATA);
    return OP_NODE(VAR, tmp_node, GetExpression (TOKENS_DATA));
}


TreeNode* GetFunction (Token token_array[], int* cur_token_id)
{
    // if (CHECK_OP_T (FUNC))
    // {
    //     *cur_token_id += 1;
    //     return OP_NODE (FUNC, GetFuncName (TOKENS_DATA), GetStatement (TOKENS_DATA));
    // }
    // else {
    //     return GetVar ();
    // }
}


TreeNode* GetFuncName (Token token_array[], int* cur_token_id)
{
    return 0; // delete this shit
}


TreeNode* GetParam (Token token_array[], int* cur_token_id)
{
    return 0;
}


TreeNode* GetName (Token token_array[], int* cur_token_id)
{
    printf ("%d: ", *cur_token_id);
    printf ("Name: Now at name %s %d\n", CUR_TOKEN.value.var_name, CUR_TOKEN.type);


    if (CUR_TOKEN.type == VAR_T)
    {
        *cur_token_id += 1;
        return NAME_NODE (PREV_TOKEN.value.var_name, nullptr, nullptr);;
    }
    
    return 0;
}


TreeNode* GetExpression (Token token_array[], int* cur_token_id)
{

    if (CHECK_OP_T (ADD) || CHECK_OP_T (SUB))
    {
        *cur_token_id += 1;

        TreeNode* left_node = GetMlt (TOKENS_DATA);
        TreeNode* right_node = GetMlt (TOKENS_DATA);

        if (CUR_TOKEN.value.op_val == ADD)
            return ADD (left_node, right_node);
        else
            return SUB (left_node, right_node);
    }
    else 
    {
        *cur_token_id += 1;

        return GetMlt (TOKENS_DATA);
    }

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
    printf ("%d: ", *cur_token_id);

    printf ("Getting number %lg, type %d\n", CUR_TOKEN.value.dbl_val, CUR_TOKEN.type);

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
        else if (input[i] == '{' || input[i] == '}')
        {
            printf ("Skipping %c\n", input[i]);
            i++;
        }
        else if (input[i] == '\0')
        {
            TOP_TOKEN = CreateToken (OP_T, 0, TERMINATION_SYM, i);
            i++;
            tokens_amount++;    
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

//------Dump

#define __print(...) fprintf (dot_file, __VA_ARGS__)

void DrawTree (TreeNode* root)
{
    assert (root != nullptr);

    static int img_counter = 0;

    FILE* dot_file = get_file ("data/graph.dot", "w+");
    
    // Writing header info
    const char header[] = R"(
    digraph g {
        dpi      = 200;
        fontname = "Comic Sans MS";
        fontsize = 20;
        rankdir   =  TB;
        edge [color = darkgrey, arrowhead = onormal, arrowsize = 1, penwidth = 1.2]
        graph[fillcolor = lightgreen, ranksep = 1.3, nodesep = 0.5,
        style = "rounded, filled",color = green, penwidth = 2]

    )";

    
    __print (header);

    InitGraphvisNode (root, dot_file);

    RecursDrawConnections (root, dot_file);

    __print ("}\n");
    
    // Executing dotfile and printing an image

    printf ("Closing the dot file");
    fclose (dot_file);

    char src[MAX_SRC_LEN] = "";

    sprintf (src, "dot -Tpng data/graph.dot -o data/pretty_tree%d.png", img_counter);

    system (src);

    img_counter++;

    return;
}


void InitGraphvisNode (TreeNode* node, FILE* dot_file)   // Recursivly initialises every node 
{
    assert (node != nullptr);

    if (node->type == NUM_T)
        __print ("Node%p[shape=record, width=0.2, style=\"filled\", color=\"red\", fillcolor=\"#DB8E21\","
                "label=\" {Type: number | value: %lg}\"] \n \n",
                node, node->value.dbl_val);

    else if (node->type == OP_T)
        __print ("Node%p[shape=record, width=0.2, style=\"filled\", color=\"red\", fillcolor=\"#DBB585\","
                "label=\" {Type: operation | value: %s}\"] \n \n",
                node, GetOpSign(node->value.op_val));

    else if (node->type == VAR_T)
        __print ("Node%p[shape=record, width=0.2, style=\"filled\", color=\"red\", fillcolor=\"#19DB27\","
                "label=\" {Type: variable | value: %s}\"] \n \n",
                node, node->value);

    else
    {
        __print ("Node%d[shape=record, width=0.2, style=\"filled\", color=\"red\", fillcolor=\"red\","
                "label=\" {Op type: %d | value: unknown type}\"] \n \n",
                node, node->type);
    }

    if (node->left) InitGraphvisNode (node->left, dot_file);
    if (node->right) InitGraphvisNode (node->right, dot_file);

    return;
}


char* GetOpSign (Options op)
{
    switch (op)
    {
    case ADD:
        return "+";

    case SUB:
        return "-";

    case DIV:
        return "/";

    case MUL:
        return "\\cdot";

    case POW:
        return "^";

    case ST:
        return "Statement";

    case VAR:
        return "Var";

    case NIL:
        return "Null node";

    default:
        return "?";
    }
} 


void RecursDrawConnections (TreeNode* node, FILE* dot_file)
{
    assert (node != nullptr);

    if (node->left)
    {
        __print ("Node%p->Node%p\n", node, node->left);
        RecursDrawConnections (node->left, dot_file);
    } 
    if (node->right)
    {
        __print ("Node%p->Node%p\n", node, node->right);
        RecursDrawConnections (node->right, dot_file);
    } 

    return;
}


#undef __print



#endif