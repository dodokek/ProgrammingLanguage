#include "parser_frontend.h"
#include "translitor.h"
#include <clocale>

int main()
{
    setlocale(LC_ALL, "Rus");
    
    TreeNode* root = GetGrammar ();

    DrawTree (root);

    TreeToOriginalLang (root);

    PrintTreeInFile (root);

    DestructTree (root);
}