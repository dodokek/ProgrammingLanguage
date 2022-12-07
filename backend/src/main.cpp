#include "parser.h"
#include "tree_to_asm.h"

int main()
{
    TreeNode* root = GetGrammar ();

    DrawTree (root);

    PrintCmdsInFile (root);
}