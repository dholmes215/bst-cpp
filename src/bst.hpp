// Copyright (C) 2019 David Holmes <dholmes@dholmes.us>. All rights reserved.

#ifndef BST_BST_HPP
#define BST_BST_HPP

#include <iostream>
#include <memory>

namespace bst {

using std::ostream;
using std::unique_ptr;

template <typename Key> struct node
{
    node(Key key) : key(key), left(nullptr), right(nullptr), p(nullptr) {}
    Key key;
    unique_ptr<node<Key>> left;
    unique_ptr<node<Key>> right;
    node<Key> * p;
};

template <typename Key>
void inorder_tree_walk(ostream & stream, const node<Key> * x)
{
    if (x != nullptr) {
        inorder_tree_walk(stream, x->left.get());
        stream << x->key << '\n';
        inorder_tree_walk(stream, x->right.get());
    }
}

template <typename Key>
const node<Key> * tree_search(const node<Key> * x, const Key k)
{
    if (x == nullptr || k == x->key) {
        return x;
    }
    if (k < x->k) {
        return tree_search(x->left.get(), k);
    } else {
        return tree_search(x->right.get(), k);
    }
}

} // namespace bst

#endif // BST_BST_HPP