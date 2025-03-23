// avl.h
#pragma once
#include <cstdint>

struct AVLNode {
  uint32_t depth = 0;     // Depth of the subtree
  uint32_t cnt = 0;       // Number of nodes in the subtree
  AVLNode *left = nullptr;
  AVLNode *right = nullptr;
  AVLNode *parent = nullptr;
};

// Macros to access AVLNode properties
#define avl_cnt(node) ((node) ? (node)->cnt : 0)
#define avl_height(node) ((node) ? (node)->depth : 0)

// Function declarations
void avl_init(AVLNode *node);
void avl_update(AVLNode *node);
AVLNode *avl_rotate_left(AVLNode *node);
AVLNode *avl_rotate_right(AVLNode *node);
AVLNode *avl_fix(AVLNode *node);
AVLNode *avl_del(AVLNode *node);
AVLNode *avl_offset(AVLNode *node, int64_t offset);