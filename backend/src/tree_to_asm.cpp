#include "tree_to_asm.h"
#include "dsl.h"


void PrintCmdsInFile (TreeNode* root)
{
    FILE* cmds_file = get_file ("data/cmds.asm", "w+");

    PrintOperation (root, cmds_file);

    fclose (cmds_file);
}


void PrintOperation (TreeNode* cur_node, FILE* cmds_file)
{
    static int label_counter = 0;

    printf ("Now printing type %d, operation %s, dbl val: %lg, name ptr %p\n",
             cur_node->type, GetOpSign (cur_node->value.op_val), cur_node->value.dbl_val, cur_node->value.var_name);

    if (cur_node->type == OP_T)
    {
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
        
        case IF:
            PRINT ("; if begin\n");
            PrintOperation (l_child);
            PrintOperation (r_child);

            break;

        case ELSE:
            PRINT ("; if true\n");
            PrintOperation (l_child);

            PRINT ("\nif_label%d:\n", label_counter);
            
            label_counter++;
            PRINT ("; if false\n");
            PrintOperation (r_child);

            break;

        case VAR:
            PRINT ("push %lg\n", cur_node->right->value.dbl_val);
            PRINT ("pop [%d]\n", *(cur_node->left->value.var_name));

            break;

        default:
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
        PRINT ("; pushing variable %c\n", *(cur_node->value.var_name));
        PRINT ("push [%d]\n", *(cur_node->value.var_name));
    }
    else
    {
        printf ("Error while translating to asm, unknown command, type %d, op %d\n",
                cur_node->type, cur_node->value.op_val);
    }

    return;
}