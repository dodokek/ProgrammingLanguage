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

    printf ("Now printing type %d, operation %s, dbl val: %lg\n",
             cur_node->type, GetOpSign (cur_node->value.op_val), cur_node->value.dbl_val);

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
            PRINT ("RET\n");
            break;

        case ADD:
            PrintOperation (l_child);
            PrintOperation (r_child);

            PRINT ("ADD\n");
            break;

        case IS_EE:
            PrintOperation (l_child);
            PrintOperation (r_child);
            PRINT ("JNE if_label%d\n", label_counter);

            break;
        
        case IF:
            PrintOperation (l_child);
            PrintOperation (r_child);

            break;

        case ELSE:
            PrintOperation (l_child);
            PRINT ("if_label%d:\n", label_counter);
            label_counter++;
            PrintOperation (r_child);

            break;

        default:
            break;
        }
    }
    else if (cur_node->type == NAME_T)
    {
        PRINT ("%s:\n", cur_node->value.var_name);
        PrintOperation (r_child);
    }
    else if (cur_node->type == NUM_T)
    {
        PRINT ("PUSH %lg\n", cur_node->value.dbl_val);
    }
    else
    {
        printf ("Error while translating to asm, unknown command, type %d, op %d\n",
                cur_node->type, cur_node->value.op_val);
    }

    return;
}