// Copyright (C) 2019 David Holmes <dholmes@dholmes.us>. All rights reserved.

#include "bst.hpp"

#include "gtest/gtest.h"

#include <cstdint>
#include <sstream>

using namespace bst;
using namespace std;

using U32Node = node<uint32_t>;

const U32Node example12_1_a = [] {
    U32Node example12_1_a{5};
    example12_1_a.left = make_unique<U32Node>(3);
    example12_1_a.left->left = make_unique<U32Node>(2);
    example12_1_a.left->right = make_unique<U32Node>(5);
    example12_1_a.right = make_unique<U32Node>(7);
    example12_1_a.right->right = make_unique<U32Node>(8);
    return example12_1_a;
}();

const U32Node example12_1_b = [] {
    U32Node example12_1_b{2};
    example12_1_b.right = make_unique<U32Node>(3);
    example12_1_b.right->right = make_unique<U32Node>(7);
    example12_1_b.right->right->left = make_unique<U32Node>(5);
    example12_1_b.right->right->left->left = make_unique<U32Node>(5);
    example12_1_b.right->right->right = make_unique<U32Node>(8);
    return example12_1_b;
}();

const string example12_1StrExpected{"2\n3\n5\n5\n7\n8\n"};

const U32Node example12_2 = [] {
    U32Node example12_2{15};
    example12_2.left = make_unique<U32Node>(6);
    example12_2.left->left = make_unique<U32Node>(3);
    example12_2.left->left->left = make_unique<U32Node>(2);
    example12_2.left->left->right = make_unique<U32Node>(4);
    example12_2.left->right = make_unique<U32Node>(7);
    example12_2.left->right->right = make_unique<U32Node>(13);
    example12_2.left->right->right->left = make_unique<U32Node>(9);
    example12_2.right = make_unique<U32Node>(18);
    example12_2.right->left = make_unique<U32Node>(17);
    example12_2.right->right = make_unique<U32Node>(20);
    return example12_2;
}();

const string example12_2StrExpected{"2\n3\n4\n6\n7\n9\n13\n15\n17\n18\n20\n"};

TEST(InorderTreeWalkTest, Example12_1_a)
{
    stringstream ss;
    inorder_tree_walk(ss, &example12_1_a);
    string str{istreambuf_iterator<char>(ss), {}};

    ASSERT_EQ(str, example12_1StrExpected);
}

TEST(InorderTreeWalkTest, Example12_1_b)
{
    stringstream ss;
    inorder_tree_walk(ss, &example12_1_b);
    string str{istreambuf_iterator<char>(ss), {}};

    ASSERT_EQ(str, example12_1StrExpected);
}

TEST(InorderTreeWalkTest, Example12_2)
{
    stringstream ss;
    inorder_tree_walk(ss, &example12_2);
    string str{istreambuf_iterator<char>(ss), {}};

    ASSERT_EQ(str, example12_2StrExpected);
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
