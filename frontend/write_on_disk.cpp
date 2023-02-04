#include "include/write_on_disk.h"

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
        if (cur_node->left)
        {
            PRINT ("\"%s\"", cur_node->value.var_name);
            RecPrintNode (cur_node->left, out_file);
            PRINT ("{ TYPE }");
        }
        else
        { 
            PRINT ("\"%s\" { NIL } { VOID } ", cur_node->value.var_name);
        }
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

//--- Write on disk. End---------------------------------------------
