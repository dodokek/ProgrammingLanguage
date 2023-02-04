#ifndef TREEASM_H
#define TREEASM_H

#include "parser_backend.h"
#include "dsl.h"


void PrintCmdsInFile (TreeNode* root);

void PrintOperation (TreeNode* cur_node, FILE* cmds_file, Stack* namespace_offset);

int GetVariablePos (int namespace_pointer, char** _namespace, int* var_amount,
                    const char var_name[], Stack* namespace_offset);

int InsertVarInNamespace (int namespace_pointer, char** _namespace,
                          int* var_amount, const char var_name[]);

#endif
