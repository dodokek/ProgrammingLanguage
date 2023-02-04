#include "parser_backend.h"

const char input_path[] = "../frontend/data/tree.txt";  


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
    else if (CHECK_OP_T (VOID))
    {
        NEXT_TOKEN;
        printf ("Skipping nil\n");
        return nullptr;
    }
    else if (CHECK_OP_T (TYPE))
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


int SimplifyTree (TreeNode* cur_node)
{
    assert (cur_node != nullptr);

    int simpl_amount = 0;

    if (cur_node->left)  simpl_amount  += SimplifyTree (cur_node->left);
    if (cur_node->right) simpl_amount  += SimplifyTree (cur_node->right);
    
    if (!cur_node->left || !cur_node->right) return 0;

    if (CUR_T == OP_T && L_TYPE != OP_T && R_TYPE != OP_T)
    {
        if (CUR_OP == MUL)
        {
            if      (isZero (L_DBL) && L_TYPE == NUM_T)
            {
                printf ("Simplifying <Zero> case left\n");

                TransformNode (cur_node, NUM_T, 0, nullptr);
                return 1;
            }

            else if (isZero (R_DBL) && R_TYPE == NUM_T)
            {
                printf ("Simplifying <Zero> case right\n");

                TransformNode (cur_node, NUM_T, 0, nullptr);
                return 1;
            }

            else if (isEqual (R_DBL, 1))
            {
                printf ("Simplifying <one> case right\n");

                if (L_TYPE == NUM_T)
                {
                    TransformNode (cur_node, NUM_T, L_DBL, nullptr);
                    return 1;
                }
                if (L_TYPE == VAR_T)
                {    
                    TransformNode (cur_node, VAR_T, 0, L_VAR);
                    return 1;
                }
            }

            else if (isEqual (L_DBL, 1))
            {
                printf ("Simplifying <one> case left\n");
                if (R_TYPE == NUM_T)
                {
                    TransformNode (cur_node, NUM_T, R_DBL, nullptr);
                    return 1;
                }
                if (R_TYPE == VAR_T)
                {   
                    TransformNode (cur_node, VAR_T, 0, R_VAR);
                    return 1;
                }
            }
        }
        
        if (L_TYPE == NUM_T && R_TYPE == NUM_T)
        {
            if (CUR_OP == ADD)
            {
                printf ("Oh, two numbers, ADD!\n");
                TransformNode (cur_node, NUM_T, L_DBL + R_DBL, nullptr);
                return 1;
            }
            else if (CUR_OP == MUL)
            {
                printf ("Oh, two numbers, MUL!\n");
                TransformNode (cur_node, NUM_T, L_DBL * R_DBL, nullptr);
                return 1;
            }
            else if (CUR_OP == SUB)
            {
                printf ("Oh, two numbers, MUL!\n");
                TransformNode (cur_node, NUM_T, L_DBL - R_DBL, nullptr);
                return 1;
            }
            else if (CUR_OP == DIV)
            {
                printf ("Oh, two numbers, MUL!\n");
                TransformNode (cur_node, NUM_T, L_DBL / R_DBL, nullptr);
                return 1;
            }
        }
    }

    return simpl_amount;
}


bool isZero (double num)
{
    printf ("recieved num %lg\n", num);
    if (abs(num) <= ACCURACY) return true;

    return false;
}


bool isEqual (double num1, double num2)
{
    return (abs (num1 - num2) < ACCURACY) ? 1 : 0;
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
        else if (isdigit (input[i]) || input[i] == '-')
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
    while (string[*i] == '\n' || string[*i] == ' ' || string[*i] == '\r') (*i)++;
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
    CMP (OUT)
    CMP (SIN)
    CMP (COS)
    CMP (SQRT)
    CMP (VOID)
    CMP (TYPE)
    if (*str == '{')      return OPEN_BR;
    else if (*str == '}') return CLOSE_BR;
    else if (*str == '\0') return TERMINATION_SYM;
    {
        printf ("======Error, now suck type!====\n");
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


char* GetInputLine ()
{
    char* buffer = (char*) calloc (MAX_SRC_LEN, sizeof (char));
    FILE* input_file = get_file (input_path, "r");
    
    fseek (input_file, 0L, SEEK_END);
    int file_len = ftell (input_file);
    fseek (input_file, 0L, SEEK_SET);

    fread (buffer, sizeof(char), file_len, input_file);
    
    fclose (input_file);
    return buffer;   
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
    // printf ("Exiting\n");

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
