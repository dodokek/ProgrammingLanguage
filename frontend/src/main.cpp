#include "parser.h"
#include "translitor.h"
#include <clocale>

int main()
{
    setlocale(LC_ALL, "Rus");
    
    // Token token_array[MAX_TOKENS] = {};

    // FillTokensArray (token_array);

    // PrintTokens (token_array);

    FILE* input = get_file ("data/input.txt", "r");

    char* buffer = GetTextBuffer (input);

    char* translit = translit_string (buffer, strlen (buffer));
    printf ("%d\n", strlen (buffer));
    printf ("%d\n", strlen (translit));
    printf (translit);

    free (buffer);
}