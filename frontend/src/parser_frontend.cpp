#include "parser_frontend.h"
#include "stringUtils.h"
#include "fileUtils.h"

const char input_path[] = "data/input.txt";

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
    printf ("St: Now at operation %d\n", CUR_TOKEN.value.op_val);

    if (CUR_TOKEN.value.op_val == TERMINATION_SYM) return nullptr;
    if (CUR_TOKEN.value.op_val == SEMI_COL)
    {
        NEXT_TOKEN; 
        return GetStatement (TOKENS_DATA);
    }
    if (CUR_TOKEN.value.op_val == CLOSE_BR)
    {
        NEXT_TOKEN;
        return nullptr;
    }

    TreeNode* left_child = GetFunction (TOKENS_DATA);
    TreeNode* next_statement = GetStatement (TOKENS_DATA);

    return OP_NODE (ST, left_child, next_statement);
}


TreeNode* GetFunction (Token token_array[], int *cur_token_id)
{
    printf("%d: ", *cur_token_id);
    printf("Function: Now at %d\n", CUR_TOKEN.value.op_val);

    if (CHECK_OP_T (FUNC))
    {
        NEXT_TOKEN;

        TreeNode* header_node = GetFuncHeader (TOKENS_DATA);
        TreeNode* body_node   = GetStatement (TOKENS_DATA);
    
        return OP_NODE (FUNC, header_node, body_node);
    }
    else
    {
        return GetIfElse (TOKENS_DATA);
    }
}


TreeNode* GetFuncHeader (Token token_array[], int *cur_token_id)
{
    printf("%d: ", *cur_token_id);
    printf("Function header: Now at %d\n", CUR_TOKEN.value.op_val);

    TreeNode* name_node  = GetNumOrName (TOKENS_DATA);
    name_node->type = NAME_T;

    TreeNode* param_node = GetParam (TOKENS_DATA);

    name_node->left = param_node;

    return name_node;
}


TreeNode* GetParam (Token token_array[], int *cur_token_id)
{
    printf("%d: ", *cur_token_id);
    printf("Param: Now at %d\n", CUR_TOKEN.value.op_val);

    if (CHECK_OP_T (OPEN_BR)) NEXT_TOKEN;
    if (CUR_TOKEN.value.op_val == CLOSE_BR)
    {
        printf ("Exiting params.\n");
        NEXT_TOKEN;
        return nullptr;
    }

    TreeNode* param_node = GetVar (TOKENS_DATA);
    TreeNode* next_param_node = GetParam (TOKENS_DATA);

    return OP_NODE (PARAM, param_node, next_param_node);
}


TreeNode* GetIfElse (Token token_array[], int *cur_token_id)
{
    printf("%d: ", *cur_token_id);
    printf("If: Now at %d\n", CUR_TOKEN.value.op_val);

    if (CHECK_OP_T (IF))
    {
        printf ("I suck dicks\n");

        NEXT_TOKEN;

        TreeNode* condition = GetExpression (TOKENS_DATA);
        TreeNode* if_body   = GetStatement (TOKENS_DATA);

        if (CUR_TOKEN.value.op_val != ELSE)
        {
            printf ("Something wrong in if/else syntax\n");
            return nullptr;
        }

        NEXT_TOKEN;

        TreeNode* else_body = GetStatement (TOKENS_DATA);
        
        return OP_NODE (IF, condition, OP_NODE (ELSE, if_body, else_body));
    }
    else
    {
        return GetWhile (TOKENS_DATA);
    }
}


TreeNode* GetWhile (Token token_array[], int* cur_token_id)
{
    printf("%d: ", *cur_token_id);
    printf("While: Now at %d\n", CUR_TOKEN.value.op_val);

    if (CHECK_OP_T (WHILE))
    {
        NEXT_TOKEN;

        TreeNode* condition    = GetExpression (TOKENS_DATA);
        TreeNode* while_body   = GetStatement (TOKENS_DATA);
        
        return OP_NODE (WHILE, condition, while_body);
    }
    else
    {
        return GetRet (TOKENS_DATA);
    }
}


TreeNode* GetRet (Token token_array[], int* cur_token_id)
{
    printf ("%d: ", *cur_token_id);
    printf ("Return: Now at %d\n", CUR_TOKEN.value.op_val);

    if (CHECK_OP_T (RET))
    {
        NEXT_TOKEN;

        return OP_NODE (RET, nullptr, nullptr);
    }
    else 
    {
        return GetCall (TOKENS_DATA);
    }
}


TreeNode* GetCall (Token token_array[], int* cur_token_id)
{
    printf ("%d: ", *cur_token_id);
    printf ("Call: Now at %d\n", CUR_TOKEN.value.op_val);

    if (CHECK_OP_T (CALL))
    {
        NEXT_TOKEN;
        TreeNode* func_name_node = GetNumOrName (TOKENS_DATA);
        func_name_node->type = NAME_SHORT_T;

        return OP_NODE (CALL, func_name_node, nullptr);
    }
    else 
    {
        return GetInOut (TOKENS_DATA);
    }
}


TreeNode* GetInOut (Token token_array[], int* cur_token_id)
{
    printf ("%d: ", *cur_token_id);
    printf ("InOut: Now at %d\n", CUR_TOKEN.value.op_val);

    if (CHECK_OP_T (IN))
    {
        NEXT_TOKEN;
        TreeNode* param_node = GetParam(TOKENS_DATA);

        return OP_NODE (IN, param_node, nullptr);
    }
    else if (CHECK_OP_T (OUT))
    {
        NEXT_TOKEN;
        TreeNode* param_node = GetParam(TOKENS_DATA);

        return OP_NODE (OUT, param_node, nullptr);
    }
    else 
    {
        return GetVar (TOKENS_DATA);
    }
}


TreeNode* GetVar (Token token_array[], int* cur_token_id)
{
    printf ("%d: ", *cur_token_id);
    printf ("Var: Now at %d\n", CUR_TOKEN.value.op_val);

    if (CHECK_OP_T (VAR))
    {
        NEXT_TOKEN;
        TreeNode* name_node = GetVar (TOKENS_DATA);
        TreeNode* val_node  = GetExpression (TOKENS_DATA);

        return OP_NODE (VAR, name_node, val_node);
    }
    else 
    {
        return GetSpecOperations (TOKENS_DATA);
    }
}


TreeNode* GetExpression (Token token_array[], int* cur_token_id)
{
    printf ("%d: ", *cur_token_id);
    printf ("Epxression: Now at %d\n", CUR_TOKEN.value.op_val);

    TreeNode* left_expression = GetAddSub (TOKENS_DATA);

    if (
        CUR_TOKEN.value.op_val == EQ    ||
        CUR_TOKEN.value.op_val == IS_EE ||
        CUR_TOKEN.value.op_val == IS_GE ||
        CUR_TOKEN.value.op_val == IS_BE ||
        CUR_TOKEN.value.op_val == IS_GT ||
        CUR_TOKEN.value.op_val == IS_BT ||
        CUR_TOKEN.value.op_val == IS_NE
       ) 
    {
        Options operation =  CUR_TOKEN.value.op_val;
        
        NEXT_TOKEN;
        TreeNode* right_expression = GetAddSub (TOKENS_DATA);
    
        return OP_NODE (operation, left_expression, right_expression);
    }

    return left_expression;
}


TreeNode* GetAddSub (Token token_array[], int* cur_token_id)
{
    printf ("%d: ", *cur_token_id);
    printf ("Add Sub: Now at %d\n", CUR_TOKEN.value.op_val);

    TreeNode* top_operation_node = GetMlt (token_array, cur_token_id);

    while (CUR_TOKEN.value.op_val == ADD || CUR_TOKEN.value.op_val == SUB)
    {
        Options last_op = CUR_TOKEN.value.op_val;
        NEXT_TOKEN;

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
        Options last_op = CUR_TOKEN.value.op_val;
        NEXT_TOKEN;

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
        NEXT_TOKEN;

        TreeNode* right_node = GetBracketExp (token_array, cur_token_id);
        top_operation_node = POW (top_operation_node, right_node);
    }       

    return top_operation_node;
}


TreeNode* GetBracketExp (Token token_array[], int* cur_token_id)
{ 
    if (CUR_TOKEN.value.op_val == OPEN_BR)
    {
        NEXT_TOKEN;
        TreeNode* sub_node = GetExpression (token_array, cur_token_id);

        if (CUR_TOKEN.value.op_val == CLOSE_BR)
        {
            NEXT_TOKEN;
            return sub_node;
        }
        else 
        {
            printf ("Wrong brackets sequence\n");  
        }        
    }
    else
    {
        return GetSpecOperations (token_array, cur_token_id);
    }
}


TreeNode* GetSpecOperations (Token token_array[], int* cur_token_id)
{
    if (CHECK_OP_T (SIN))
    {
        NEXT_TOKEN;
        return OP_NODE (SIN, GetBracketExp (TOKENS_DATA), nullptr);
    }
    else if (CHECK_OP_T (COS))
    {
        NEXT_TOKEN;
        return OP_NODE (COS, GetBracketExp (TOKENS_DATA), nullptr);
    }
    else if (CHECK_OP_T (SQRT))
    {
        NEXT_TOKEN;
        return OP_NODE (SQRT, GetBracketExp (TOKENS_DATA), nullptr);
    }
    else 
    {
        return GetNumOrName (TOKENS_DATA);
    }
    
}


TreeNode* GetNumOrName (Token token_array[], int* cur_token_id)
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
        printf ("Didn't find any nums or vars, returning null\n");
        return nullptr;
    }
}


//-------Parser->Lecsical analysis----------------------------------


void FillTokensArray (Token* token_array)
{
    FILE* input_file = get_file ("data/input.txt", "r");
    char* input = GetTextBuffer(input_file);
    fclose (input_file);

    char* cur_ptr = input;
    int tokens_amount = 0;
    int len = 0;

    while (true)
    {
        SkipSpaces (&cur_ptr);
        if (*cur_ptr == '\0' || *(cur_ptr - 1) == '\0')
        {
            TOP_TOKEN = *(CreateToken (OP_T, 0, TERMINATION_SYM));
            break;
        }
        else if (isdigit (*cur_ptr))
        {
            double num = 0;
            sscanf (cur_ptr, "%lg%n", &num, &len);
            cur_ptr += len;

            TOP_TOKEN = *(CreateToken (NUM_T, num, UNKNOWN));
            tokens_amount++;
        }
        else if (*cur_ptr == '^')
        {
            cur_ptr += VAR_OFFSET; // skips the ^_^: prefix in variables

            TOP_TOKEN = *(CreateToken (VAR_T, 0, UNKNOWN));  
            
            sscanf (cur_ptr, "%s%n", TOP_TOKEN.value.var_name, &len);
            TOP_TOKEN.value.var_name = TranslitString (TOP_TOKEN.value.var_name, len);

            tokens_amount++;
            cur_ptr += len;
        }
        else
        {
            char command[MAX_NAME_LEN] = "";
            sscanf (cur_ptr, "%s%n", command, &len);
            printf ("Scanned string %s\n", command);
            char* translit_cmd = TranslitString (command, len);
            TOP_TOKEN = *(CommandToToken (translit_cmd)); 

            tokens_amount++;
            cur_ptr += len;
        }
    }

    free (input);
}


#define CMD(cmd_code, cmd_name)                   \
    if (strcmp (cmd_name, name) == 0)             \
    {                                             \
        return CreateToken (OP_T, 0, cmd_code);   \
    } else                                        \


Token* CommandToToken (char* name)
{
    // CodeGen--------------
    #include "dictionary.h"
    // ---------------------
    {
        printf ("Could not find name %s in database.\n", name);
        return nullptr;
    }

}


#undef CMD


Token* CreateToken (Types type, double dbl_val, Options operation)
{
    static int token_counter = 0;

    printf ("===%d: Creating token with type %d and op val %d, op name: %s. dbl val: %lg====\n", token_counter, type, operation, GetOpSign (operation), dbl_val);
    token_counter++;

    Token* new_token = (Token*) calloc (1, sizeof (Token));

    if      (type == NUM_T) new_token->value.dbl_val  = dbl_val;
    else if (type == VAR_T) new_token->value.var_name = (char*) calloc (MAX_TOKEN_LEN, sizeof (char));
    else if (type == OP_T)  new_token->value.op_val = operation;
    
    new_token->type = type;

    return new_token;
}


void PrintTokens (Token* token_array)
{
    int i = 0;
    while (token_array[i].value.op_val != TERMINATION_SYM || token_array[i].type != OP_T)
    {
        printf ("%d: ", i);
        printf ("\tToken: %s, code: %d\n", 
                GetOpSign (token_array[i].value.op_val),
                token_array[i].value.op_val
                );

        if (token_array[i].type == VAR_T)
        {
            printf ("\t\tIt's name is %s\n", token_array[i].value.var_name);
        }
        if (token_array[i].type == NUM_T)
        {
            printf ("\t\tIt's value is %lg\n", token_array[i].value.dbl_val);
        }
        i++;
    }
    printf ("----End of tokenizer----\n\n");
}


void SkipSpaces (char** string)
{
    while (strchr (" \n\t\r ", **string))
        (*string)++;
}


#define SWITCH(op, return_statement)    \
    case op:                            \
        return #op;                     \    


char* GetOpSign (Options op)
{
    switch (op)
    {
    SWITCH (ADD, "ADD")
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
    SWITCH (OPEN_BR, "Enter zone")
    SWITCH (CLOSE_BR, "Exit zone")
    SWITCH (TERMINATION_SYM, "Termination symbol")
    SWITCH (WHILE, "While")
    SWITCH (SEMI_COL, "semi col")
    SWITCH (IN, "Input")
    SWITCH (OUT, "Output")
    SWITCH (SIN, "Output")
    SWITCH (COS, "Output")
    SWITCH (SQRT, "Output")

    default:
        return "?";
    }
} 


//-------Parser->Lecsical analysis----------------------------------
//--Parser.End-----------------------------------------------------


//--Write on disk. Begin-------------------------------------------

#define PRINT(...) fprintf (out_file, __VA_ARGS__)

void PrintTreeInFile (TreeNode* root)
{
    FILE* out_file = get_file ("data/tree.txt", "w+");

    RecPrintNode (root, out_file);

    fclose (out_file);
    printf ("Closing out file successfully\n");
}


void RecPrintNode (TreeNode* cur_node, FILE* out_file)
{
    printf ("Printing node type: %d with op type: %d\n",
             cur_node->type, cur_node->value.op_val);

    PRINT (" { ");

    if      (cur_node->type == NUM_T) PRINT ("%lg", cur_node->value.dbl_val);
    else if (cur_node->type == NAME_T)
    {
        PRINT ("\"%s\" { NIL } { VOID } ", cur_node->value.var_name);
    }
    else if (cur_node->type == NAME_SHORT_T)
    {
        PRINT ("\"%s\" { NIL } { NIL } ", cur_node->value.var_name);
    }
    else if (cur_node->type == VAR_T)
    {
        PRINT ("\"%s\"", cur_node->value.var_name);
        if (cur_node->left) RecPrintNode (cur_node->left, out_file);
    }
    else
    {
        PRINT (" %s ", GetOpSign (cur_node->value.op_val));   
    
        if (cur_node->left) RecPrintNode (cur_node->left, out_file);
        else PRINT (" { NIL } ");

        if (cur_node->right) RecPrintNode (cur_node->right, out_file);
        else PRINT (" { NIL } ");
    }


    PRINT (" } ");
}

//--Write on disk. End---------------------------------------------

//--Tree to original language. Begin---------------------------------------------


void TreeToOriginalLang (TreeNode* root)
{
    FILE* out_file = get_file ("data/reverse.txt", "w+");

    RecToOrigin (root, out_file);
}


void RecToOrigin (TreeNode* cur_node, FILE* out_file)
{
    if (cur_node->type == VAR_T  ||
        cur_node->type == NAME_T ||
        cur_node->type == NAME_SHORT_T )
    {
        PRINT (" ^_^:%s ", cur_node->value.var_name);
    }   
    else if (cur_node->type == NUM_T)
    {
        PRINT (" %lg ", cur_node->value.dbl_val);
    }
    else
    {
        #define CMD(code, name)                                             \
        case code:                                                          \
            if (cur_node->left) RecPrintNode (cur_node->left, out_file);    \
            PRINT (" %s ", name);                                           \
            if (cur_node->right) RecPrintNode (cur_node->right, out_file);  \
            break;                                                          \

        switch (cur_node->value.op_val)
        {
        case ST:
            if (cur_node->left) RecPrintNode (cur_node->left, out_file);
            PRINT ("\n ?????? \n");
            if (cur_node->right) RecPrintNode (cur_node->right, out_file);
            break;
       
        // ---------------Codegen--------------

        // #include "../include/dictionary.h"
        // CMD(IS_EE, "pakhnet_znakomo")

        // ---------------Codegen--------------

        default:
            break;
        }

        #undef CMD
    }
}


#undef PRINT


//--Tree to original language. End---------------------------------------------

//------Dump. Begin--------------------------------------------------------

#define __print(...) fprintf (dot_file, __VA_ARGS__)

void DrawTree (TreeNode* root)
{
    assert (root != nullptr);

    static int img_counter = 0;

    FILE* dot_file = get_file ("data/graph.dot", "w+");
    
    // Writing header info
    const char header[] = R"(
    digraph g {
        bgcolor="lightblue";
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

    else if (node->type == NAME_T || node->type == NAME_SHORT_T)
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

