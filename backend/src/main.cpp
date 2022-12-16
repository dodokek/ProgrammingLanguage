#include "parser_backend.h"

int main()
{
    TreeNode* root = GetGrammar ();

    DrawTree (root);

    PrintCmdsInFile (root);

    DestructTree (root);
}