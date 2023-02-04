#ifndef REV_H
#define REV_H

#include "parser_backend.h"
#include "dsl.h"

void TreeToOriginalLang (TreeNode* root);

void RecToOrigin (TreeNode* cur_node, FILE* out_file);

#endif