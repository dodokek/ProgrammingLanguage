#include "include/reverse.h"

//--- Tree to original language. Begin---------------------------------------------

#define PRINT(...) fprintf (out_file, __VA_ARGS__)

void TreeToOriginalLang (TreeNode* root)
{
    FILE* out_file = get_file ("data/reverse.txt", "w+");

    RecToOrigin (root, out_file);

    close_file (out_file, "reverse.txt");
}


#define OPR(op, translation)                     \
    case op:                                     \
            TRANSLATE_OP (translation);          \
            break;


void RecToOrigin (TreeNode* cur_node, FILE* out_file)
{
    static int global_offset = 0;

    printf ("Translating. type %d. name %d. val %d.\n",
             cur_node->type, cur_node->value.var_name, cur_node->value.dbl_val);


    if (   cur_node->type == VAR_T 
        || cur_node->type == NAME_SHORT_T
        || cur_node->type == NAME_T )
    {
        PRINT (">%s ", cur_node->value.var_name);
        if (cur_node->type == NAME_T)
        {    
            PRINT ("( ");
            TO_ORIGIN (cur_node, left);
            PRINT (") ");
        }
    }   
    else if (cur_node->type == NUM_T)
    {
        PRINT (" %lg ", cur_node->value.dbl_val);
    }
    else
    {   
        if (cur_node->value.op_val != ST && 
            cur_node->value.op_val != PARAM)
        {
            PutTabs (out_file, global_offset);
        }

        switch (cur_node->value.op_val)
        {
        case ST:
            TO_ORIGIN (cur_node, left);
            PRINT (" мяу\n");
            TO_ORIGIN (cur_node, right);
            break;
    
        case IF:

            PRINT ("куда_епта ");
            
            TO_ORIGIN (cur_node, left);
            PRINT ("\n");
            
            global_offset++;
            TO_ORIGIN (cur_node->right, left); // printing if body due to standart
            global_offset--;
            PutTabs (out_file, global_offset);
            PRINT ("валим\n\n");

            TO_ORIGIN (cur_node, right);
            break;

        case ELSE:
            global_offset++;
            PRINT ("ай_ладно\n");
            TO_ORIGIN (cur_node, right);
            global_offset--;
            PutTabs (out_file, global_offset);
            PRINT ("валим\n\n");
            break;

        case CALL:
            PRINT ("кис_кис ");
            TO_ORIGIN (cur_node, left);
            PRINT ("( ");
            TO_ORIGIN (cur_node, right);
            PRINT (") ");
            break;

        case RET:
            PRINT ("лее_куда_прешь ");
            PRINT ("( ");
            TO_ORIGIN (cur_node, left);
            PRINT (") ");
            break;

        case FUNC:
            global_offset++;

            PRINT ("комната_единички ");
            
            TO_ORIGIN (cur_node, left);
            PRINT ("\n");
            TO_ORIGIN (cur_node, right);
            
            PRINT ("валим\n\n");

            global_offset--;
            break;

        case IN:
            PRINT ("слизнуть ( ");
        
            TO_ORIGIN (cur_node, left);

            PRINT ( ") " );
            break;

        case OUT:
            PRINT ("буэээ ( ");
            TO_ORIGIN (cur_node, left);
            PRINT ( ") " ); 
            break;

        case VAR:
            PRINT ("нюх_нюх ");
            TO_ORIGIN (cur_node, left);
            TO_ORIGIN (cur_node, right);

            break;

        OPR (PARAM, "");
        OPR (ADD, "сожрать ");
        OPR (SUB, "кусь_за_жопу ");
        OPR (MUL, "мяя ");
        OPR (DIV, "миюяяяяу ");
        OPR (EQ,  "= ");
        OPR (IS_EE, "пахнет_знакомо ");
        OPR (IS_NE, "пахнет_незнакомо ");
        OPR (CLOSE_BR, "все ");

        default:
            break;
        }
    }
}


void PutTabs (FILE* file, int amount)
{
    for (int i = 0; i < amount; i++)
    {
        fprintf (file, "\t");
    }
}


#undef PRINT


//--Tree to original language. End---------------------------------------------
