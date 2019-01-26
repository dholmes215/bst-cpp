// Copyright (C) 2019 David Holmes <dholmes@dholmes.us>. All rights reserved.

#ifndef BST_BST_HPP
#define BST_BST_HPP

#include <iostream>
#include <memory>

namespace bst {

using std::make_unique;
using std::ostream;
using std::unique_ptr;

template <typename Key> struct node
{
    node(Key key) : key(key), left(nullptr), right(nullptr), p(nullptr) {}
    node(node<Key> &&) = delete; // TODO Add move constructor later to fix
                                 // children's parent pointers
    node<Key> & operator=(node<Key> &&) = delete; // TODO Ditto

    node * add_left(Key key)
    {
        left = make_unique<node>(key);
        left->p = this;
        return left.get();
    }

    node * add_right(Key key)
    {
        right = make_unique<node>(key);
        right->p = this;
        return left.get();
    }

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
    if (k < x->key) {
        return tree_search(x->left.get(), k);
    } else {
        return tree_search(x->right.get(), k);
    }
}

template <typename Key>
const node<Key> * iterative_tree_search(const node<Key> * x, const Key k)
{
    while (x != nullptr && k != x->key) {
        if (k < x->key) {
            x = x->left.get();
        } else {
            x = x->right.get();
        }
    }

    return x;
}

template <typename Key> const node<Key> * tree_minimum(const node<Key> * x)
{
    while (x->left) {
        x = x->left.get();
    }
    return x;
}

template <typename Key> const node<Key> * tree_maximum(const node<Key> * x)
{
    while (x->right) {
        x = x->right.get();
    }
    return x;
}

template <typename Key> const node<Key> * tree_successor(const node<Key> * x)
{
    if (x->right) {
        return tree_minimum(x->right.get());
    }
    auto y = x->p;
    while (y && x == y->right.get()) {
        x = y;
        y = y->p;
    }
    return y;
}

} // namespace bst

#endif // BST_BST_HPP