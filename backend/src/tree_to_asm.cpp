#include "tree_to_asm.h"


void PrintCmdsInFile (TreeNode* root)
{
    FILE* cmds_file = get_file ("data/cmds.asm", "w+");

    PrintOperation (root, cmds_file);

    fclose (cmds_file);
}


void PrintOperation (TreeNode* cur_node, FILE* cmds_file)
{
    if (cur_node->type == OP_T)
    {
        switch (cur_node->value.op_val)
        {
        case ADD:
            PrintOperation (cur_node->left, cmds_file);
            PrintOperation (cur_node->right, cmds_file);

            PRINT ("ADD\n");
            break;
        
        default:
            break;
        }

    }
    else if (cur_node->type == NUM_T)
    {
        PRINT ("%lg\n", cur_node->value.dbl_val);
    }
    else
    {
        printf ("Error while translating to asm, unknown command, type %d, op %d\n",
                cur_node->type, cur_node->value.op_val);
    }
}