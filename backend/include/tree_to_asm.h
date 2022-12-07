#ifndef TREE_ASM_H
#define TREE_ASM_H

#include "fileUtils.h"
#include "stringUtils.h"
#include "parser.h"

#define PRINT(...) fprintf (cmds_file, __VA_ARGS__)


void PrintCmdsInFile (TreeNode* root);

void PrintOperation (TreeNode* cur_node, FILE* cmds_file);

#endif