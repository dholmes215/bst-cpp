// Copyright (C) 2019 David Holmes <dholmes@dholmes.us>. All rights reserved.

#ifndef BST_BST_HPP
#define BST_BST_HPP

#include <iostream>
#include <iterator>
#include <memory>

namespace bst {

using std::make_unique;
using std::move;
using std::ostream;
using std::unique_ptr;

template <typename Key> struct node
{
    template <typename Key2> friend class multiset;

public:
    node(Key key) : k(key), l(nullptr), r(nullptr), p(nullptr) {}
    node(node<Key> &&) = delete; // TODO Add move constructor later to fix
                                 // children's parent pointers
    node<Key> & operator=(node<Key> &&) = delete; // TODO Ditto

    const Key & key() const { return k; }
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

private:
    Key k;
    unique_ptr<node<Key>> l;
    unique_ptr<node<Key>> r;
    node<Key> * p;
};

template <typename Key>
void inorder_tree_walk(ostream & stream, const node<Key> * x)
{
    if (x != nullptr) {
        inorder_tree_walk(stream, x->left());
        stream << x->key() << '\n';
        inorder_tree_walk(stream, x->right());
    }
}

template <typename Key>
const node<Key> * tree_search(const node<Key> * x, const Key k)
{
    if (x == nullptr || k == x->key()) {
        return x;
    }
    if (k < x->key()) {
        return tree_search(x->left(), k);
    } else {
        return tree_search(x->right(), k);
    }
}

template <typename Key>
const node<Key> * iterative_tree_search(const node<Key> * x, const Key k)
{
    while (x != nullptr && k != x->key()) {
        if (k < x->key()) {
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

template <typename Key> class iterator final
{
    template <typename Key2> friend class multiset;

public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = Key;
    using difference_type = int;
    using pointer = const Key *;
    using reference = const Key &;

    iterator() = default;
    iterator(const iterator & iter) = default;

    const Key & operator*() { return p->key(); }

    // Pre-increment
    iterator & operator++()
    {
        p = tree_successor(p);
        return *this;
    }

    // Post-increment
    iterator operator++(int)
    {
        auto out = *this;
        p = tree_successor(p);
        return out;
    }

    // XXX Making this a BidirectionalIterator would require making end()
    // decrementable, which would bean requiring it to point to an actual "end
    // node". This makes sense for a red-black tree, but every "empty" BST would
    // have to have that node as its root, adding one level to each BST. I'm
    // going to pass.

    // // Pre-decrement
    // iterator & operator--()
    // {
    //     p = tree_predecessor(p);
    //     return *this;
    // }

    // // Post-decrement
    // iterator operator--(int)
    // {
    //     auto out = *this;
    //     p = tree_predecessor(p);
    //     return out;
    // }

    bool operator==(const iterator<Key> rhs) const { return p == rhs.p; }
    bool operator!=(const iterator<Key> rhs) const { return p != rhs.p; }

private:
    iterator(const node<Key> * p) : p(p) {}
    const node<Key> * p;
};

template <typename Key> class multiset
{
    template <typename Key2> friend class iterator;

public:
    multiset() = default;
    void insert(const Key & key);
    iterator<Key> begin() { return iterator(tree_minimum(root.get())); }
    iterator<Key> end() { return iterator<Key>(nullptr); }

private:
    unique_ptr<node<Key>> root;
};

template <typename Key> void multiset<Key>::insert(const Key & key)
{
    node<Key> * y = nullptr;
    node<Key> * x = root.get();
    while (x != nullptr) {
        y = x;
        if (key < x->key()) {
            x = x->left();
        } else {
            x = x->right();
        }
    }
    if (y == nullptr) {
        root = make_unique<node<Key>>(key);
    } else {
        if (key < y->key()) {
            y->l = make_unique<node<Key>>(key);
            y->l->p = y;
        } else {
            y->r = make_unique<node<Key>>(key);
            y->r->p = y;
        }
    }
}

} // namespace bst

#endif // BST_BST_HPP