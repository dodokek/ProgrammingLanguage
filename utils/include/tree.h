#include "../../params.h"
#include "stdlib.h"

struct TreeNode
{
    Types type; 
    
    TreeNode* parent;

    TreeNode* left;
    TreeNode* right;

    Values value;
};


TreeNode* CreateNode (Types type, double dbl_val, Options op_val, const char* var_name,
                      TreeNode* left_child, TreeNode* right_child);

TreeNode* DestructTree (TreeNode* root);

TreeNode* TransformNode (TreeNode* node, Types type, double dbl_val, const char* var_name);