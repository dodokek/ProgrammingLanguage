#include "include/tree_to_asm.h"

//--Tree to asm. Begin-----------------------------------------------


void PrintCmdsInFile (TreeNode* root)
{
    FILE* cmds_file = get_file ("data/cmds.asm", "w+");
    Stack namespace_offset = {};
    StackCtor (&namespace_offset, MAX_NAMESPACES);
    StackPush (&namespace_offset, 0);

    PRINT ("call main \nhlt\n\n");
    PRINT ("; let the chaos begin\n\n");

    PrintOperation (root, cmds_file, &namespace_offset);

    PRINT ("; goodbye\nend\n");


    printf ("Successfully closing asm file\n");
    fclose (cmds_file);
}


void PrintOperation (TreeNode* cur_node, FILE* cmds_file, Stack* namespace_offset)
{
    if (!cur_node) return;

    static int label_counter = 0;
    static Options previous_option = UNKNOWN;
    static char** _namespace = (char**) calloc (MAX_VARIABLES * MAX_NAMESPACES, sizeof (char*));
    static int    namespace_pointer = 0;
    
    int vars_before = StackPop (namespace_offset);
    StackPush (namespace_offset, vars_before);

    if (cur_node->type == OP_T)
    {
        printf ("Switch op_t: %s\n", GetOpSign(cur_node->value.op_val));
        int cur_label_num = -1;
     
        switch (cur_node->value.op_val)
        {
        case ST:
            PrintOperation (l_child);
            if (cur_node->right) PrintOperation (r_child);
            break;
        
        case FUNC:
            for (int i = 0; i < vars_before; i++)
                _namespace[i] = nullptr;
            
            StackPush (namespace_offset, 0);
            namespace_pointer += MAX_VARIABLES;

            PRINT ("; function \n");
            PrintOperation (l_child);
            PRINT ("push rcx \n");
            PrintOperation (r_child);


            StackPop (namespace_offset);
            namespace_pointer -= MAX_VARIABLES;

            break;

        case RET:
            PRINT ("pop rcx\n");
            previous_option = RET;
            PrintOperation (l_child);
            PRINT ("push rcx\n");


            PRINT ("ret\n");
            PRINT ("; end of func\n\n");
            break;

        case ADD:
            PrintOperation (l_child);
            PrintOperation (r_child);

            PRINT ("add\n");
            break;

        case SUB:
            PrintOperation (r_child);
            PrintOperation (l_child);

            PRINT ("sub\n");
            break;

        case MUL:
            PrintOperation (l_child);
            PrintOperation (r_child);

            PRINT ("mul\n");
            break;

        case DIV:
            PrintOperation (r_child);
            PrintOperation (l_child);

            PRINT ("div\n");
            break;

        case CALL:
            previous_option = CALL;
            PrintOperation (r_child);

            PRINT ("; switching namespace\npush %d\npush rax\nadd\npop rax\n", vars_before + 1);
            PRINT ("; calling func\ncall %s\n", cur_node->left->value.var_name);
            
            PRINT ("; switching namespace\npush %d\npush rax\nsub\npop rax\n", vars_before + 1);
            
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

        case IS_BT:
            PrintOperation (r_child);
            PrintOperation (l_child);
            PRINT ("jae if_label%d\n\n", label_counter);

            break;

        case IF:
            PRINT ("; if begin\n");
            PrintOperation (l_child);
            PrintOperation (r_child);

            break;

        case ELSE:
            cur_label_num = label_counter;
            label_counter++;
            
            PRINT ("; if true\n");
            PrintOperation (l_child);
            PRINT ("jmp else_label%d\n", cur_label_num);

            PRINT ("\nif_label%d:\n", cur_label_num);
            PRINT ("; if false\n");
            PrintOperation (r_child);

            PRINT ("\nelse_label%d:\n", cur_label_num);
            break;

        case VAR:
            GetVariablePos (namespace_pointer,_namespace, &vars_before, cur_node->left->value.var_name, namespace_offset); 

            PrintOperation (r_child);
            PRINT ("; popping variable %s\n", cur_node->left->value.var_name);
            PRINT ("pop [%d+rax]\n", GET_VAR_POS (cur_node->left->value.var_name));

            break;

        case IN:
            previous_option = IN;
            PrintOperation (l_child);

            break;

        case OUT:
            previous_option = OUT;
            PrintOperation (l_child);

            break;

        case PARAM:

            GET_VAR_POS (cur_node->left->value.var_name);
            if (previous_option == IN)
            {
                PRINT ("; getting variable %s\n", cur_node->left->value.var_name);
                PRINT ("in\n");
                PRINT ("pop [%d+rax] \n", GET_VAR_POS (cur_node->left->value.var_name));
            }
            else if (previous_option == OUT)
            {
                PRINT ("; printing variable %s\n", cur_node->left->value.var_name);
                PRINT ("push [%d+rax] \n", GET_VAR_POS (cur_node->left->value.var_name));
                PRINT ("out\n");
            }
            else if (previous_option == CALL)
            {
                PRINT ("; pushing function call param: %s\n", cur_node->left->value.var_name);
                PRINT ("push [%d+rax]\n", GET_VAR_POS (cur_node->left->value.var_name));
            }
            else if (previous_option == FUNC)
            {
                GET_VAR_POS (cur_node->left->value.var_name);
                
                PRINT ("; poping function argument: %s\n", cur_node->left->value.var_name);
                PRINT ("pop [%d+rax]\n", GET_VAR_POS (cur_node->left->value.var_name));
            }
            else if (previous_option == RET)
            {
                PRINT ("; returning the value from var: %s\n", cur_node->left->value.var_name);
                PRINT ("push [%d+rax]\n", GET_VAR_POS (cur_node->left->value.var_name));
            }

            if (cur_node->right) PrintOperation (r_child);

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
            PRINT ("sqr\n");
            break;

        case VOID:
            PRINT (";no return params\n");
            break;

        case TYPE:
            PRINT (";have to return something\n");
            break;

        default:
            printf ("\n\nUnknown command! %d\n\n", cur_node->value.op_val);
            break;
        }
    }
    else if (cur_node->type == NAME_T)
    {
        PRINT ("%s:\n", cur_node->value.var_name);
        PRINT ("pop rcx \n");

        previous_option = FUNC;
        PrintOperation (l_child);
    }
    else if (cur_node->type == NUM_T)
    {
        PRINT ("push %lg\n", cur_node->value.dbl_val);
    }
    else if (cur_node->type == VAR_T)
    {
        GetVariablePos (namespace_pointer, _namespace, &vars_before, cur_node->value.var_name, namespace_offset);
        
        PRINT ("; pushing variable %s\n", cur_node->value.var_name);
        PRINT ("push [%d+rax]\n",
                GetVariablePos (namespace_pointer, _namespace, &vars_before, cur_node->value.var_name, namespace_offset));
    }
    else
    {
        printf ("Error while translating to asm, unknown command, type %d, op %d\n",
                cur_node->type, cur_node->value.op_val);
    }

    return;
}


int GetVariablePos (int namespace_pointer, char** _namespace, int* var_amount,
                    const char var_name[], Stack* namespace_offset)
{
    for (int cur_indx = namespace_pointer; cur_indx < *var_amount + namespace_pointer; cur_indx++)
    {
        printf ("\tNow cmpring %s and %s\n",_namespace[cur_indx], var_name);
        if (strcmp ( _namespace[cur_indx], var_name ) == 0)
            return cur_indx - namespace_pointer;
    }

    InsertVarInNamespace (namespace_pointer, _namespace, var_amount, var_name);

    StackPop  (namespace_offset);
    StackPush (namespace_offset, *var_amount);

    printf ("Adding new variable to namespace: %s\n", var_name);
    return -1;
}


int InsertVarInNamespace (int namespace_pointer, char** _namespace,
                          int* var_amount, const char var_name[])
{
    _namespace[*var_amount + namespace_pointer] = (char*) var_name;
    (*var_amount)++;
    for (int i = namespace_pointer; i < *var_amount + namespace_pointer; i++)
    {
        printf ("\tName:%s...\n", _namespace[i]);
    }
    return 0;
}


//--Tree to asm. End-------------------------------------------------
