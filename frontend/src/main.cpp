#include "parser.h"
#include "translitor.h"
#include <clocale>

int main()
{
    setlocale(LC_ALL, "Rus");
    
    TreeNode* root = GetGrammar ();

    DrawTree (root);

    PrintTreeInFile (root);
}