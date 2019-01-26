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
    node(Key key) : key(key), l(nullptr), r(nullptr), p(nullptr) {}
    node(node<Key> &&) = delete; // TODO Add move constructor later to fix
                                 // children's parent pointers
    node<Key> & operator=(node<Key> &&) = delete; // TODO Ditto

    node * left() const { return l.get(); }
    node * right() const { return r.get(); }
    node * parent() const { return p; }

    node * add_left(Key key)
    {
        l = make_unique<node>(key);
        l->p = this;
        return l.get();
    }

    node * add_right(Key key)
    {
        r = make_unique<node>(key);
        r->p = this;
        return l.get();
    }

    Key key;

private:
    unique_ptr<node<Key>> l;
    unique_ptr<node<Key>> r;
    node<Key> * p;
};

template <typename Key>
void inorder_tree_walk(ostream & stream, const node<Key> * x)
{
    if (x != nullptr) {
        inorder_tree_walk(stream, x->left());
        stream << x->key << '\n';
        inorder_tree_walk(stream, x->right());
    }
}

template <typename Key>
const node<Key> * tree_search(const node<Key> * x, const Key k)
{
    if (x == nullptr || k == x->key) {
        return x;
    }
    if (k < x->key) {
        return tree_search(x->left(), k);
    } else {
        return tree_search(x->right(), k);
    }
}

template <typename Key>
const node<Key> * iterative_tree_search(const node<Key> * x, const Key k)
{
    while (x != nullptr && k != x->key) {
        if (k < x->key) {
            x = x->left();
        } else {
            x = x->right();
        }
    }

    return x;
}

template <typename Key> const node<Key> * tree_minimum(const node<Key> * x)
{
    while (x->left()) {
        x = x->left();
    }
    return x;
}

template <typename Key> const node<Key> * tree_maximum(const node<Key> * x)
{
    while (x->right()) {
        x = x->right();
    }
    return x;
}

template <typename Key> const node<Key> * tree_successor(const node<Key> * x)
{
    if (x->right()) {
        return tree_minimum(x->right());
    }
    auto y = x->parent();
    while (y && x == y->right()) {
        x = y;
        y = y->parent();
    }
    return y;
}

template <typename Key> const node<Key> * tree_predecessor(const node<Key> * x)
{
    if (x->left()) {
        return tree_maximum(x->left());
    }
    auto y = x->parent();
    while (y && x == y->left()) {
        x = y;
        y = y->parent();
    }
    return y;
}

} // namespace bst

#endif // BST_BST_HPP