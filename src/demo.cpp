// Copyright (C) 2019 David Holmes <dholmes@dholmes.us>. All rights reserved.

#include "bst.hpp"

#include <cstddef>
#include <iostream>

using namespace bst;

using std::int8_t;
using std::ostream;

template <typename Key>
void print_node(ostream & out, const node<Key> * node, int8_t indent)
{
    if (node) {
        out << std::string(indent * 2, ' ') << node->key() << '\n';
        print_node(out, node->left(), indent + 1);
        print_node(out, node->right(), indent + 1);
    }
}

using I32Node = node<int32_t>;
const unique_ptr<I32Node> example12_1_a = [] {
    auto example12_1_a = make_unique<I32Node>(5);
    example12_1_a->add_left(3);
    example12_1_a->left()->add_left(2);
    example12_1_a->left()->add_right(5);
    example12_1_a->add_right(7);
    example12_1_a->right()->add_right(8);
    return example12_1_a;
}();

int main(int /*argc*/, char ** /*argv*/)
{
    print_node(std::cout, example12_1_a.get(), 0);
    return 0;
}
