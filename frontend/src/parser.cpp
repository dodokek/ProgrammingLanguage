
#include "parser.h"
#include "stringUtils.h"
#include "fileUtils.h"

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

/*
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



//-------Parser->Lecsical analysis----------------------------------


void FillTokensArray (Token* token_array)
{
    FILE* input_file = get_file ("data/input.txt", "r");
    char* input = GetTextBuffer(input_file);
    fclose (input_file);

    char* cur_ptr = input;
    int tokens_amount = 0;

    while (true)
    {
        SkipSpaces (&cur_ptr);
        if (*cur_ptr == '\0' || *(cur_ptr - 1) == '\0')
        {
            token_array[tokens_amount] = *(CreateToken (OP_T, 0, TERMINATION_SYM));
            break;
        }
        else if (isdigit (*cur_ptr))
        {
            int len = 0;
            double num = 0;
            sscanf (cur_ptr, "%lg%n", &num, &len);
            cur_ptr += len;

            token_array[tokens_amount] = *(CreateToken (NUM_T, num, UNKNOWN));
        }
        else if (*cur_ptr == '^')
        {
            cur_ptr += VAR_OFFSET;

            token_array[tokens_amount] = *(CreateToken (VAR_T, 0, UNKNOWN));  
            
            int len = 0;
            sscanf (cur_ptr, "%s%n", token_array[tokens_amount].value.var_name, &len);
            token_array[tokens_amount].value.var_name = TranslitString (token_array[tokens_amount].value.var_name, len);

            tokens_amount++;
            cur_ptr += len;

        }
        else
        {
            int len = 0;
            char command[MAX_NAME_LEN] = "";
            sscanf (cur_ptr, "%s%n", command, &len);

            char* translit_cmd = TranslitString (command, len);
            token_array[tokens_amount] = *(CommandToToken (translit_cmd)); 

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
    printf ("====Creating token with type %d and op val %d %s====\n", type, operation, GetOpSign (operation));

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
    while (token_array[i].value.op_val != TERMINATION_SYM)
    {
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
}


void SkipSpaces (char** string)
{
    while (strchr (" \n\t\r ", **string))
        (*string)++;
}


#define SWITCH(op, return_statement)   \
    case op:                            \
        return return_statement;        \

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
    SWITCH (OPEN_BR, "Enter zone")
    SWITCH (CLOSE_BR, "Exit zone")

    default:
        return "?";
    }
} 


//-------Parser->Lecsical analysis----------------------------------


//--Parser.End-----------------------------------------------------


//------Dump--------------------------------------------------------

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

