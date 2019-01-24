// Copyright (C) 2019 David Holmes <dholmes@dholmes.us>. All rights reserved.

#include "bst.hpp"

#include "gtest/gtest.h"

#include <cstdint>
#include <sstream>

using namespace bst;
using namespace std;

using U32Node = node<uint32_t>;

const U32Node exampleA = [] {
    U32Node exampleA{5};
    exampleA.left = make_unique<U32Node>(3);
    exampleA.left->left = make_unique<U32Node>(2);
    exampleA.left->right = make_unique<U32Node>(5);
    exampleA.right = make_unique<U32Node>(7);
    exampleA.right->right = make_unique<U32Node>(8);
    return exampleA;
}();

const U32Node exampleB = [] {
    U32Node exampleA{2};
    exampleA.right = make_unique<U32Node>(3);
    exampleA.right->right = make_unique<U32Node>(7);
    exampleA.right->right->left = make_unique<U32Node>(5);
    exampleA.right->right->left->left = make_unique<U32Node>(5);
    exampleA.right->right->right = make_unique<U32Node>(8);
    return exampleA;
}();

const string exampleStrExpected{"2\n3\n5\n5\n7\n8\n"};

TEST(InorderTreeWalkTest, ExampleA) {
    stringstream ss;
    inorder_tree_walk(ss, &exampleA);
    string exampleAStr{istreambuf_iterator<char>(ss), {}};
    ASSERT_EQ(exampleAStr, exampleStrExpected);
}

TEST(InorderTreeWalkTest, ExampleB) {
    stringstream ss;
    inorder_tree_walk(ss, &exampleB);
    string exampleBStr{istreambuf_iterator<char>(ss), {}};
    ASSERT_EQ(exampleBStr, exampleStrExpected);
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
