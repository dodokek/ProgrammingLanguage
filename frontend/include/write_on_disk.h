#ifndef DISK_H
#define DISK_H

#include "parser_frontend.h"

void PrintTreeInFile (TreeNode* root);

void RecPrintNode (TreeNode* cur_node, FILE* out_file);

#endif