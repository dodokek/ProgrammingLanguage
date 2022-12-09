#include "translitor.h"

char* TranslitString (const char* src, size_t size)
{
    char* translit = (char*) calloc (size * 4, sizeof (char));
    char* begin_ptr  = translit;

    while (*src != '\0')
    {
        switch (*src)
        {
            case USELESS2:
                break;
            case USELESS1:
                break;
            case ARUS:
                *translit = 'a';
                translit++;
                break;
            case BRUS:
                *translit = 'b';
                translit++;
                break;
            case VRUS:
                *translit = 'v';
                translit++;
                break;
            case GRUS:
                *translit = 'g';
                translit++;
                break;
            case DRUS:
                *translit = 'd';
                translit++;
                break;
            case ERUS:
                *translit = 'e';
                translit++;
                break;
            case ZHRUS:
                *translit = 'z';
                translit++;
                *translit = 'h';
                translit++;
                break;
            case ZRUS:
                *translit = 'z';
                translit++;
                break;
            case IRUS:
                *translit = 'i';
                translit++;
                break;
            case YIRUS:
                *translit = 'i';
                translit++;
                break;
            case KRUS:
                *translit = 'k';
                translit++;
                break;
            case LRUS:
                *translit = 'l';
                translit++;
                break;
            case MRUS:
                *translit = 'm';
                translit++;
                break;
            case NRUS:
                *translit = 'n';
                translit++;
                break;
            case ORUS:
                *translit = 'o';
                translit++;
                break;
            case PRUS:
                *translit = 'p';
                translit++;
                break;
            case RRUS:
                *translit = 'r';
                translit++;
                break;
            case SRUS:
                *translit = 's';
                translit++;
                break;
            case TRUS:
                *translit = 't';
                translit++;
                break;
            case URUS:
                *translit = 'u';
                translit++;
                break;
            case FRUS:
                *translit = 'f';
                translit++;
                break;
            case HRUS:
                *translit = 'k';
                translit++;
                *translit = 'h';
                translit++;
                break;
            case TSRUS:
                *translit = 't';
                translit++;
                *translit = 's';
                translit++;
                break;
            case CHRUS:
                *translit = 'c';
                translit++;
                *translit = 'h';
                translit++;
                break;
            case SHRUS:
                *translit = 's';
                translit++;
                *translit = 'h';
                translit++;
                break;
            case SHCHRUS:
                *translit = 's';
                translit++;
                *translit = 'h';
                translit++;
                *translit = 'c';
                translit++;
                *translit = 'h';
                translit++;
                break;
            case IERUS:
                *translit = 'i';
                translit++;
                *translit = 'e';
                translit++;
                break;
            case YRUS:
                *translit = 'y';
                translit++;
                break;
            case QRUS:
                *translit = '\'';
                translit++;
                break;
            case EERUS:
                *translit = 'e';
                translit++;
                break;
            case IURUS:
                *translit = 'i';
                translit++;
                *translit = 'u';
                translit++;
                break;
            case IARUS:
                *translit = 'i';
                translit++;
                *translit = 'a';
                translit++;
                break;
            case ABRUS:
                *translit = 'a';
                translit++;
                break;
            case BBRUS:
                *translit = 'b';
                translit++;
                break;
            case VBRUS:
                *translit = 'v';
                translit++;
                break;
            case GBRUS:
                *translit = 'g';
                translit++;
                break;
            case DBRUS:
                *translit = 'd';
                translit++;
                break;
            case EBRUS:
                *translit = 'e';
                translit++;
                break;
            case ZHBRUS:
                *translit = 'z';
                translit++;
                *translit = 'h';
                translit++;
                break;
            case ZBRUS:
                *translit = 'z';
                translit++;
                break;
            case IBRUS:
                *translit = 'i';
                translit++;
                break;
            case YIBRUS:
                *translit = 'i';
                translit++;
                break;
            case KBRUS:
                *translit = 'k';
                translit++;
                break;
            case LBRUS:
                *translit = 'l';
                translit++;
                break;
            case MBRUS:
                *translit = 'm';
                translit++;
                break;
            case NBRUS:
                *translit = 'n';
                translit++;
                break;
            case OBRUS:
                *translit = 'o';
                translit++;
                break;
            case PBRUS:
                *translit = 'p';
                translit++;
                break;
            case RBRUS:
                *translit = 'r';
                translit++;
                break;
            case SBRUS:
                *translit = 's';
                translit++;
                break;
            case TBRUS:
                *translit = 't';
                translit++;
                break;
            case UBRUS:
                *translit = 'u';
                translit++;
                break;
            case FBRUS:
                *translit = 'f';
                translit++;
                break;
            case HBRUS:
                *translit = 'k';
                translit++;
                *translit = 'h';
                translit++;
                break;
            case TSBRUS:
                *translit = 't';
                translit++;
                *translit = 's';
                translit++;
                break;
            case CHBRUS:
                *translit = 'c';
                translit++;
                *translit = 'h';
                translit++;
                break;
            case SHBRUS:
                *translit = 's';
                translit++;
                *translit = 'h';
                translit++;
                break;
            case SHCHBRUS:
                *translit = 's';
                translit++;
                *translit = 'h';
                translit++;
                *translit = 'c';
                translit++;
                *translit = 'h';
                translit++;
                break;
            case IEBRUS:
                *translit = 'i';
                translit++;
                *translit = 'e';
                translit++;
                break;
            case YBRUS:
                *translit = 'y';
                translit++;
                break;
            case QBRUS:
                *translit = '\'';
                translit++;
                break;
            case EEBRUS:
                *translit = 'e';
                translit++;
                break;
            case IUBRUS:
                *translit = 'i';
                translit++;
                *translit = 'u';
                translit++;
                break;
            case IABRUS:
                *translit = 'i';
                translit++;
                *translit = 'a';
                translit++;
                break;
            default:
                *translit = *src;
                translit++;
                break;
        }
        // printf ("Now i got %c\n", *(translit-1));
        src++;
        // printf ("Src: %d\n", *src);
    }

    *translit = '\0';

    return begin_ptr;
}
