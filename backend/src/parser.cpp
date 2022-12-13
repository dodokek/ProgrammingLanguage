
#include "stringUtils.h"
#include "fileUtils.h"
#include "parser.h"

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

    return node;
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
        NEXT_TOKEN;
        TreeNode* tmp_node = GetFunction (TOKENS_DATA);
        return OP_NODE (ST, tmp_node, GetStatement (TOKENS_DATA));
    }
    else if (CHECK_OP_T (NIL))
    {
        NEXT_TOKEN;
        return nullptr;
    }
    else 
    {
        return GetFunction (TOKENS_DATA);
    }
}


TreeNode* GetFunction (Token token_array[], int* cur_token_id)
{
    if (CHECK_OP_T (FUNC))
    {
        NEXT_TOKEN;

        TreeNode* functction_header = GetFuncHeader (TOKENS_DATA); 
        TreeNode* functction_body   = GetStatement (TOKENS_DATA); 

        return OP_NODE (FUNC, functction_header, functction_body);
    }
    else 
    {
        return GetIf (TOKENS_DATA);
    }
}


TreeNode* GetFuncHeader (Token token_array[], int* cur_token_id)
{
    if (CUR_TOKEN.type != VAR_T)
        printf ("===Error missing function name===\n");

    TreeNode* func_name_node = GetNumOrVar (TOKENS_DATA);
    func_name_node->type = NAME_T;

    printf ("Got name %s\n", func_name_node->value.var_name);

    func_name_node->left = GetParam (TOKENS_DATA);

    return func_name_node;
}


TreeNode* GetParam (Token token_array[], int* cur_token_id)
{
    if (CHECK_OP_T (PARAM))
    {
        NEXT_TOKEN;
        
        TreeNode* param_node = OP_NODE (PARAM, nullptr, nullptr);

        param_node->left  = GetVar (TOKENS_DATA);
        param_node->right = GetParam (TOKENS_DATA);

        return param_node;
    }
    else if (CHECK_OP_T (NIL))
    {
        NEXT_TOKEN;

        return nullptr;
    }
    else
    {
        printf ("===Error. Undefined parametr sequence===\n");
        return nullptr;
    }

}


TreeNode* GetIf (Token token_array[], int* cur_token_id)
{
    if (CHECK_OP_T (IF))
    {
        // printf ("Hey hey\n");
        NEXT_TOKEN;

        TreeNode* statement = GetStatement (TOKENS_DATA);
        TreeNode* else_node = GetElse (TOKENS_DATA);

        return OP_NODE (IF, statement, else_node);
    }
    else 
    {
        return GetCall (TOKENS_DATA);
    }
}


TreeNode* GetElse (Token token_array[], int* cur_token_id)
{
    if (CHECK_OP_T (ELSE))
    {
        NEXT_TOKEN;
        TreeNode* left_statement = GetStatement (TOKENS_DATA);
        TreeNode* right_statement = GetStatement (TOKENS_DATA);

        return OP_NODE (ELSE, left_statement, right_statement);
    }
    else
    {
        printf ("===Error, couldn't match else for any if before.===\n");
        return nullptr;
    }
}


TreeNode* GetCall (Token token_array[], int* cur_token_id)
{
    if (CHECK_OP_T (CALL))
    {
        NEXT_TOKEN;

        TreeNode* function_header_node = GetFuncHeader (TOKENS_DATA);

        return OP_NODE (CALL, function_header_node, nullptr);
    }
    else
    {
        return GetVar (TOKENS_DATA);
    }
}


TreeNode* GetVar (Token token_array[], int* cur_token_id)
{
    if (CHECK_OP_T (VAR))
    {
        printf ("%d: ", *cur_token_id);
        printf ("Var: Now at %d %d\n", CUR_TOKEN.value.op_val, __LINE__);

        NEXT_TOKEN;
        TreeNode* var_name_node  = GetNumOrVar (TOKENS_DATA);
        TreeNode* equated_st_node = GetExpression (TOKENS_DATA);

        return OP_NODE(VAR, var_name_node, equated_st_node);
    }
    else 
    {
        return GetRet (TOKENS_DATA);
    }
}


TreeNode* GetRet (Token token_array[], int* cur_token_id)
{
    if (CHECK_OP_T (RET))
    {
        NEXT_TOKEN;
        return OP_NODE (RET, nullptr, nullptr);
    }
    else 
    {
        return GetExpression (TOKENS_DATA);
    }
}


TreeNode* GetExpression (Token token_array[], int* cur_token_id)
{
    printf ("%d: \n", *cur_token_id);

    if(
        CUR_TOKEN.value.op_val != EQ    &&
        CUR_TOKEN.value.op_val != IS_EE &&
        CUR_TOKEN.value.op_val != IS_GE &&
        CUR_TOKEN.value.op_val != IS_BE &&
        CUR_TOKEN.value.op_val != IS_GT &&
        CUR_TOKEN.value.op_val != IS_BT &&
        CUR_TOKEN.value.op_val != IS_NE
    ) return GetAddSub (TOKENS_DATA);
    else if (CUR_TOKEN.value.op_val == NIL)
    {
        NEXT_TOKEN;
        return nullptr;
    }
    else 
    {
        Options cur_op = CUR_TOKEN.value.op_val;    

        NEXT_TOKEN;

        TreeNode* left_node  = GetExpression (TOKENS_DATA);
        TreeNode* right_node = GetExpression (TOKENS_DATA);

        return OP_NODE (cur_op, left_node, right_node);
    }
}


TreeNode* GetAddSub (Token token_array[], int* cur_token_id)
{
    printf ("%d: add/sub \n", *cur_token_id);


    if (CHECK_OP_T (ADD) || CHECK_OP_T (SUB))
    {
        Options cur_option = CUR_TOKEN.value.op_val;

        NEXT_TOKEN;

        TreeNode* left_node  = GetExpression (TOKENS_DATA);
        TreeNode* right_node = GetExpression (TOKENS_DATA);

        if (cur_option == ADD)
            return ADD (left_node, right_node);
        else
            return SUB (left_node, right_node);
    }
    else 
    {
        return GetMlt (TOKENS_DATA);
    }
}



TreeNode* GetMlt (Token token_array[], int* cur_token_id)
{
    printf ("%d: mlt/div \n", *cur_token_id);

    if (CHECK_OP_T (MUL) || CHECK_OP_T (DIV))
    {
        Options cur_option = CUR_TOKEN.value.op_val;

        NEXT_TOKEN;

        TreeNode* left_node =  GetExpression (TOKENS_DATA);
        TreeNode* right_node = GetExpression (TOKENS_DATA);

        if (cur_option == MUL)
            return MUL (left_node, right_node);
        else
            return DIV (left_node, right_node);
    }
    else 
    {
        return GetPower (TOKENS_DATA);
    }
}


TreeNode* GetPower (Token token_array[], int* cur_token_id)
{
    if (CHECK_OP_T (POW))
    {
        NEXT_TOKEN;

        TreeNode* left_node =  GetExpression (TOKENS_DATA);
        TreeNode* right_node = GetExpression (TOKENS_DATA);
        
        return POW (left_node, right_node);    
    }
    else 
    {
        return GetNumOrVar (TOKENS_DATA);
    }
}


TreeNode* GetNumOrVar (Token token_array[], int* cur_token_id)
{
    printf ("%d: ", *cur_token_id);

    printf ("Getting number %lg, type %d\n", CUR_TOKEN.value.dbl_val, CUR_TOKEN.type);

    if      (CUR_TOKEN.type == NUM_T)
    {
        NEXT_TOKEN;
        return DIGIT_NODE (PREV_TOKEN.value.dbl_val);
    }
    else if (CUR_TOKEN.type == VAR_T)
    {
        NEXT_TOKEN;
        return CreateNode (VAR_T, 0, UNKNOWN, PREV_TOKEN.value.var_name, nullptr, nullptr);
    }
    else 
    {
        NEXT_TOKEN;
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
    while (isspace(string[*i])) (*i)++;
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
        printf ("Token %d. Type: %d, Dbl value: %lg. Line number %d. Op type: %d, name ptr %p\n", i,
               token_array[i].type, token_array[i].value.dbl_val, token_array[i].line_number, token_array[i].value.op_val, token_array[i].value.var_name);

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
    CMP (IS_EE)
    CMP (IS_GE)
    CMP (IS_BE)
    CMP (IS_GT)
    CMP (IS_BT)
    CMP (IS_NE)
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

    printf ("Closing the dot file\n\n");
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

    else if (node->type == NAME_T)
        __print ("Node%p[shape=record, width=0.2, style=\"filled\", color=\"red\", fillcolor=\"#19DB27\","
                "label=\" {Function name |Name: %s}\"] \n \n",
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


#define SWITCH(op, return_statement)   \
    case op:                            \
        return #op;        \

char* GetOpSign (Options op)
{
    switch (op)
    {
    SWITCH (ADD, "+")
    SWITCH (SUB, "-")
    SWITCH (DIV, "/")
    SWITCH (MUL, "*")
    SWITCH (POW, "^")
    SWITCH (IS_EE, "==")
    SWITCH (IS_GE, "IS_GE") // Graphvis sucks, it doesnt let to write >
    SWITCH (IS_BE, "IS_BE")
    SWITCH (IS_GT, "IS_GT")
    SWITCH (IS_BT, "IS_BT")
    SWITCH (IS_NE, "!=")
    SWITCH (ST, "Statement")
    SWITCH (VAR, "Var")
    SWITCH (NIL, "null node")
    SWITCH (EQ, "=")
    SWITCH (IF, "if")
    SWITCH (ELSE, "else")
    SWITCH (PARAM, "Parametr")
    SWITCH (FUNC, "Function declaration")
    SWITCH (CALL, "Function call")
    SWITCH (RET, "Return of function")

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
