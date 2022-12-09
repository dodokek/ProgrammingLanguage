#include "parser.h"
#include "translitor.h"
#include <clocale>

int main()
{
    setlocale(LC_ALL, "Rus");
    
    Token token_array[MAX_TOKENS] = {};
    FillTokensArray (token_array);
    PrintTokens (token_array);
}