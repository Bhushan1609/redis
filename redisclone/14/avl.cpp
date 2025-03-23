// avl.cpp
#include "avl.h"
#include<bits/stdc++.h>
// Initialize an AVLNode
void avl_init(AVLNode *node) {
  node->depth = 1;
  node->cnt = 1;
  node->left = node->right = node->parent = nullptr;
}

// Update depth and cnt for a node
void avl_update(AVLNode *node) {
  node->depth = 1 + std::max(avl_height(node->left), avl_height(node->right));
  node->cnt = 1 + avl_cnt(node->left) + avl_cnt(node->right);
}

// Left rotation
AVLNode *avl_rotate_left(AVLNode *node) {
  AVLNode *new_root = node->right;
  if (new_root->left) {
    new_root->left->parent = node;
  }
  node->right = new_root->left;
  new_root->left = node;
  new_root->parent = node->parent;
  node->parent = new_root;
  avl_update(node);
  avl_update(new_root);
  return new_root;
}

// Right rotation
AVLNode *avl_rotate_right(AVLNode *node) {
  AVLNode *new_root = node->left;
  if (new_root->right) {
    new_root->right->parent = node;
  }
  node->left = new_root->right;
  new_root->right = node;
  new_root->parent = node->parent;
  node->parent = new_root;
  avl_update(node);
  avl_update(new_root);
  return new_root;
}

// Rest of your existing avl.cpp code (avl_fix, avl_del, avl_offset)...