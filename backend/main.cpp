#include "parser_backend.h"

int main()
{
    TreeNode* root = GetGrammar ();

    // SimplifyTree (root);

    // DrawTree (root);

    PrintCmdsInFile (root);

    // TreeToOriginalLang (root);

    DestructTree (root);
}