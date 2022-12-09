#include "translitor.h"

char* translit_string (const char* src, size_t size)
{
    char* rus_string = (char*) calloc (size * 4, sizeof (char));
    char* begin_ptr  = rus_string;

    while (*src != '\0')
    {
        switch (*src)
        {
            case USELESS2:
                break;
            case USELESS1:
                break;
            case ARUS:
                *rus_string = 'a';
                rus_string++;
                break;
            case BRUS:
                *rus_string = 'b';
                rus_string++;
                break;
            case VRUS:
                *rus_string = 'v';
                rus_string++;
                break;
            case GRUS:
                *rus_string = 'g';
                rus_string++;
                break;
            case DRUS:
                *rus_string = 'd';
                rus_string++;
                break;
            case ERUS:
                *rus_string = 'e';
                rus_string++;
                break;
            case ZHRUS:
                *rus_string = 'z';
                rus_string++;
                *rus_string = 'h';
                rus_string++;
                break;
            case ZRUS:
                *rus_string = 'z';
                rus_string++;
                break;
            case IRUS:
                *rus_string = 'i';
                rus_string++;
                break;
            case YIRUS:
                *rus_string = 'i';
                rus_string++;
                break;
            case KRUS:
                *rus_string = 'k';
                rus_string++;
                break;
            case LRUS:
                *rus_string = 'l';
                rus_string++;
                break;
            case MRUS:
                *rus_string = 'm';
                rus_string++;
                break;
            case NRUS:
                *rus_string = 'n';
                rus_string++;
                break;
            case ORUS:
                *rus_string = 'o';
                rus_string++;
                break;
            case PRUS:
                *rus_string = 'p';
                rus_string++;
                break;
            case RRUS:
                *rus_string = 'r';
                rus_string++;
                break;
            case SRUS:
                *rus_string = 's';
                rus_string++;
                break;
            case TRUS:
                *rus_string = 't';
                rus_string++;
                break;
            case URUS:
                *rus_string = 'u';
                rus_string++;
                break;
            case FRUS:
                *rus_string = 'f';
                rus_string++;
                break;
            case HRUS:
                *rus_string = 'k';
                rus_string++;
                *rus_string = 'h';
                rus_string++;
                break;
            case TSRUS:
                *rus_string = 't';
                rus_string++;
                *rus_string = 's';
                rus_string++;
                break;
            case CHRUS:
                *rus_string = 'c';
                rus_string++;
                *rus_string = 'h';
                rus_string++;
                break;
            case SHRUS:
                *rus_string = 's';
                rus_string++;
                *rus_string = 'h';
                rus_string++;
                break;
            case SHCHRUS:
                *rus_string = 's';
                rus_string++;
                *rus_string = 'h';
                rus_string++;
                *rus_string = 'c';
                rus_string++;
                *rus_string = 'h';
                rus_string++;
                break;
            case IERUS:
                *rus_string = 'i';
                rus_string++;
                *rus_string = 'e';
                rus_string++;
                break;
            case YRUS:
                *rus_string = 'y';
                rus_string++;
                break;
            case QRUS:
                *rus_string = '\'';
                rus_string++;
                break;
            case EERUS:
                *rus_string = 'e';
                rus_string++;
                break;
            case IURUS:
                *rus_string = 'i';
                rus_string++;
                *rus_string = 'u';
                rus_string++;
                break;
            case IARUS:
                *rus_string = 'i';
                rus_string++;
                *rus_string = 'a';
                rus_string++;
                break;
            case ABRUS:
                *rus_string = 'a';
                rus_string++;
                break;
            case BBRUS:
                *rus_string = 'b';
                rus_string++;
                break;
            case VBRUS:
                *rus_string = 'v';
                rus_string++;
                break;
            case GBRUS:
                *rus_string = 'g';
                rus_string++;
                break;
            case DBRUS:
                *rus_string = 'd';
                rus_string++;
                break;
            case EBRUS:
                *rus_string = 'e';
                rus_string++;
                break;
            case ZHBRUS:
                *rus_string = 'z';
                rus_string++;
                *rus_string = 'h';
                rus_string++;
                break;
            case ZBRUS:
                *rus_string = 'z';
                rus_string++;
                break;
            case IBRUS:
                *rus_string = 'i';
                rus_string++;
                break;
            case YIBRUS:
                *rus_string = 'i';
                rus_string++;
                break;
            case KBRUS:
                *rus_string = 'k';
                rus_string++;
                break;
            case LBRUS:
                *rus_string = 'l';
                rus_string++;
                break;
            case MBRUS:
                *rus_string = 'm';
                rus_string++;
                break;
            case NBRUS:
                *rus_string = 'n';
                rus_string++;
                break;
            case OBRUS:
                *rus_string = 'o';
                rus_string++;
                break;
            case PBRUS:
                *rus_string = 'p';
                rus_string++;
                break;
            case RBRUS:
                *rus_string = 'r';
                rus_string++;
                break;
            case SBRUS:
                *rus_string = 's';
                rus_string++;
                break;
            case TBRUS:
                *rus_string = 't';
                rus_string++;
                break;
            case UBRUS:
                *rus_string = 'u';
                rus_string++;
                break;
            case FBRUS:
                *rus_string = 'f';
                rus_string++;
                break;
            case HBRUS:
                *rus_string = 'k';
                rus_string++;
                *rus_string = 'h';
                rus_string++;
                break;
            case TSBRUS:
                *rus_string = 't';
                rus_string++;
                *rus_string = 's';
                rus_string++;
                break;
            case CHBRUS:
                *rus_string = 'c';
                rus_string++;
                *rus_string = 'h';
                rus_string++;
                break;
            case SHBRUS:
                *rus_string = 's';
                rus_string++;
                *rus_string = 'h';
                rus_string++;
                break;
            case SHCHBRUS:
                *rus_string = 's';
                rus_string++;
                *rus_string = 'h';
                rus_string++;
                *rus_string = 'c';
                rus_string++;
                *rus_string = 'h';
                rus_string++;
                break;
            case IEBRUS:
                *rus_string = 'i';
                rus_string++;
                *rus_string = 'e';
                rus_string++;
                break;
            case YBRUS:
                *rus_string = 'y';
                rus_string++;
                break;
            case QBRUS:
                *rus_string = '\'';
                rus_string++;
                break;
            case EEBRUS:
                *rus_string = 'e';
                rus_string++;
                break;
            case IUBRUS:
                *rus_string = 'i';
                rus_string++;
                *rus_string = 'u';
                rus_string++;
                break;
            case IABRUS:
                *rus_string = 'i';
                rus_string++;
                *rus_string = 'a';
                rus_string++;
                break;
            default:
                *rus_string = *src;
                rus_string++;
                break;
        }
        printf ("Now i got %c\n", *(rus_string-1));
        src++;
        printf ("Src: %d\n", *src);
    }

    *rus_string = '\0';

    return begin_ptr;
}
