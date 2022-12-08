#include "parser.h"

int main()
{
    Token token_array[MAX_TOKENS] = {};

    FillTokensArray (token_array);

    PrintTokens (token_array);

    // TreeNode* root = GetGrammar ();

    // DrawTree (root);

}