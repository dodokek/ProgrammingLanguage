
#include "stringUtils.h"
#include "fileUtils.h"
#include "parser_backend.h"

const char input_path[] = "../frontend/data/tree.txt";

// Gods forgive me for this global variable i am not govnocoder.
Variable VARIABLES_ARRAY[MAX_VARIABLES] = {};
int VARIABLES_AMOUNT = 0;
// Gods forgive me for this global variable i am not govnocoder.


TreeNode* CreateNode (Types type, double dbl_val, Options op_val, const char* var_name,
                      TreeNode* left_child, TreeNode* right_child)
{
    TreeNode* new_node = (TreeNode*) calloc (1, sizeof (TreeNode));
    if (!new_node) return nullptr;

    if      (type == NUM_T) new_node->value.dbl_val  = dbl_val;
    else if (type == VAR_T || type == NAME_T) new_node->value.var_name = var_name;
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

    return RecGetChild (TOKENS_DATA, NOT_FUNC);
}


TreeNode* RecGetChild (Token token_array[], int* cur_token_id, bool is_func_name)
{
    printf ("Now working with token type %d, operation %s, %d\n", CUR_TOKEN.type, GetOpSign (CUR_TOKEN.value.op_val), CUR_TOKEN.value.op_val);
    printf ("Token num %d: ", *cur_token_id);
    if (CUR_TOKEN.type == VAR_T)
    {
        printf ("Hehe name %s and %d\n", CUR_TOKEN.value.var_name, is_func_name);
        if (is_func_name)
        {
            const char* cur_name = CUR_TOKEN.value.var_name;
            NEXT_TOKEN;
            TreeNode* param_node = RecGetChild (TOKENS_DATA, NOT_FUNC);
            TreeNode* type_node  = RecGetChild (TOKENS_DATA, NOT_FUNC);
            return NAME_NODE (cur_name, param_node, type_node);
        }
        else 
        {
            ADD_TO_NAMETABLE;
            NEXT_TOKEN;
            return VAR_NODE (PREV_TOKEN.value.var_name, nullptr, nullptr);
        } 
    }
    else if (CUR_TOKEN.type == NUM_T)
    {
        printf ("Hell yeah, num %lg\n", CUR_TOKEN.value.dbl_val);

        NEXT_TOKEN;
        return DIGIT_NODE (PREV_TOKEN.value.dbl_val);
    }
    else if (CHECK_OP_T (TERMINATION_SYM))
    {
        printf ("End of tokens, returning\n");
        return nullptr;
    }
    else if (CHECK_OP_T (NIL))
    {
        NEXT_TOKEN;
        printf ("Skipping nil\n");
        return nullptr;
    }
    else 
    {
        Options cur_opt = CUR_TOKEN.value.op_val;
        printf ("Cur opt is %s\n", GetOpSign (cur_opt));
        TreeNode* left_child = nullptr;
        TreeNode* right_child = nullptr;
        
        NEXT_TOKEN;                     

        if (cur_opt == FUNC || cur_opt == CALL)
            left_child = RecGetChild (TOKENS_DATA, IS_FUNC);        
        else
            left_child = RecGetChild (TOKENS_DATA, NOT_FUNC);        

        right_child = RecGetChild (TOKENS_DATA, NOT_FUNC);       
        
        return OP_NODE (cur_opt, left_child, right_child);      
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

    printf ("%s\n", input);


    for (int i = 0; i <= input_len;)
    {
        SkipSpaces (input, &i);
        
        if (isalpha(input[i]))
        {
            printf ("Now at %c, ind %d out of %d\n", input[i], i, strlen(input)); // for dbg only

            char op_name[MAX_NAME_LEN] = "";

            int len = 0;
            sscanf (input + i, "%[^{} ]%n", op_name, &len);
            i += len;

            printf ("\n\tGot string %s\n", op_name);

            Options operation = GetOpType (op_name);
            TOP_TOKEN = CreateToken (OP_T, 0, operation, i); 
            tokens_amount++;
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


//--Tree to asm. Begin-----------------------------------------------


void PrintCmdsInFile (TreeNode* root)
{
    FILE* cmds_file = get_file ("data/cmds.asm", "w+");

    PRINT ("call main\nhlt\n\n");
    PRINT ("; let the chaos begin\n\n");

    PrintOperation (root, cmds_file);

    fclose (cmds_file);
}


void PrintOperation (TreeNode* cur_node, FILE* cmds_file)
{
    if (!cur_node) return;

    static int label_counter = 0;

    printf ("Now printing type %d, operation %s, dbl val: %lg, name ptr %p\n",
             cur_node->type, GetOpSign (cur_node->value.op_val), cur_node->value.dbl_val, cur_node->value.var_name);

    if (cur_node->type == OP_T)
    {
        printf ("Switch op_t: %d\n", cur_node->value.op_val);
        switch (cur_node->value.op_val)
        {
        case ST:
            PrintOperation (l_child);
            if (cur_node->right) PrintOperation (r_child);
            break;
        
        case FUNC:
            PRINT ("; function \n");
            PrintOperation (l_child);
            PrintOperation (r_child);
            break;

        case RET:
            PRINT ("ret\n");
            PRINT ("; end of func\n\n");
            break;

        case ADD:
            PrintOperation (l_child);
            PrintOperation (r_child);

            PRINT ("add\n");
            break;

        case SUB:
            PrintOperation (l_child);
            PrintOperation (r_child);

            PRINT ("sub\n");
            break;

        case MUL:
            PrintOperation (l_child);
            PrintOperation (r_child);

            PRINT ("mul\n");
            break;

        case DIV:
            PrintOperation (l_child);
            PrintOperation (r_child);

            PRINT ("div\n");
            break;

        case CALL:
            PRINT ("call %s\n", cur_node->left->value.var_name);
            break;

        case IS_EE:
            PrintOperation (l_child);
            PrintOperation (r_child);
            PRINT ("jne if_label%d\n\n", label_counter);

            break;
        
        case IS_NE:
            PrintOperation (l_child);
            PrintOperation (r_child);
            PRINT ("je if_label%d\n\n", label_counter);

            break;

        case IF:
            PRINT ("; if begin\n");
            PrintOperation (l_child);
            PrintOperation (r_child);

            break;

        case ELSE:
            PRINT ("; if false\n");
            PrintOperation (l_child);

            PRINT ("\nif_label%d:\n", label_counter);
            
            label_counter++;
            PRINT ("; if true\n");
            PrintOperation (r_child);

            break;

        case VAR:
            PrintOperation (r_child);
            PRINT ("; popping variable %s\n", cur_node->left->value.var_name);
            PRINT ("pop [%d]\n", GetVarIndx(cur_node->left->value.var_name));

            break;

        case IN:
            PRINT ("in \n");
            PRINT ("pop [%d] \n", GetVarIndx (cur_node->left->left->left->value.var_name));

            break;

        case OUT:
            PRINT ("push [%d] \n", GetVarIndx (cur_node->left->left->left->value.var_name));
            PRINT ("out \n");

            break;

        case SIN:
            PrintOperation (l_child);
            PRINT ("sin\n");
            break;

        case COS:
            PrintOperation (l_child);
            PRINT ("sin\n");
            break;

        case SQRT:
            PrintOperation (l_child);
            PRINT ("sin\n");
            break;

        case VOID:
            PRINT (";no return params\n");
            break;

        case TYPE:
            PRINT (";have to return something\n");
            break;

        default:
            printf ("Unknown command! %d\n", cur_node->value.op_val);
            break;
        }
    }
    else if (cur_node->type == NAME_T)
    {
        PRINT ("%s:\n", cur_node->value.var_name);
        // PrintOperation (r_child);
    }
    else if (cur_node->type == NUM_T)
    {
        PRINT ("push %lg\n", cur_node->value.dbl_val);
    }
    else if (cur_node->type == VAR_T)
    {
        PRINT ("; pushing variable %s\n", cur_node->value.var_name);
        PRINT ("push [%d]\n", GetVarIndx(cur_node->value.var_name));
    }
    else
    {
        printf ("Error while translating to asm, unknown command, type %d, op %d\n",
                cur_node->type, cur_node->value.op_val);
    }
    PRINT ("; ----------\n");

    return;
}


int GetVarIndx (const char* var_name)
{
    for (int cur_indx = 0; cur_indx < VARIABLES_AMOUNT; cur_indx++)
    {
        if (strcmp (var_name, VARIABLES_ARRAY[cur_indx].name) == 0)
            return VARIABLES_ARRAY[cur_indx].ram_indx;
    }

    printf ("Didn't found match fot %s in db\n", var_name);
    return 0;
}


//--Tree to asm. End-------------------------------------------------


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
    CMP (IN)
    CMP (SIN)
    CMP (COS)
    CMP (SQRT)
    CMP (VOID)
    CMP (TYPE)
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
    // printf ("Entering node type %d, name %p\n", node->type, node->value.var_name);
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
                "label=\" {Function name | Name: %s}\"] \n \n",
                node, node->value);

    else
    {
        __print ("Node%d[shape=record, width=0.2, style=\"filled\", color=\"red\", fillcolor=\"red\","
                "label=\" {Op type: %d | value: unknown type}\"] \n \n",
                node, node->type);
    }
    printf ("Exiting\n");

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
    SWITCH (COS, "cos")
    SWITCH (SIN, "sin")
    SWITCH (SQRT, "sqrt")
    SWITCH (VOID, "void")
    SWITCH (TYPE, "type")


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
