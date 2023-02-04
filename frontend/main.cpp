#include "parser_frontend.h"
#include "translitor.h"
#include "write_on_disk.h"
#include <clocale>

int main()
{
    setlocale(LC_ALL, "Rus");
    
    TreeNode* root = GetGrammar ();

    DrawTree (root);

    PrintTreeInFile (root);

    DestructTree (root);
}