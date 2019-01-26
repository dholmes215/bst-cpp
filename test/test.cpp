// Copyright (C) 2019 David Holmes <dholmes@dholmes.us>. All rights reserved.

#include "bst.hpp"

#include "gtest/gtest.h"

#include <cstdint>
#include <sstream>

using namespace bst;
using namespace std;

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

const unique_ptr<I32Node> example12_1_b = [] {
    auto example12_1_b = make_unique<I32Node>(2);
    example12_1_b->add_right(3);
    example12_1_b->right()->add_right(7);
    example12_1_b->right()->right()->add_left(5);
    example12_1_b->right()->right()->left()->add_left(5);
    example12_1_b->right()->right()->add_right(8);
    return example12_1_b;
}();

const string example12_1StrExpected{"2\n3\n5\n5\n7\n8\n"};

const unique_ptr<I32Node> example12_2 = [] {
    auto example12_2 = make_unique<I32Node>(15);
    example12_2->add_left(6);
    example12_2->left()->add_left(3);
    example12_2->left()->left()->add_left(2);
    example12_2->left()->left()->add_right(4);
    example12_2->left()->add_right(7);
    example12_2->left()->right()->add_right(13);
    example12_2->left()->right()->right()->add_left(9);
    example12_2->add_right(18);
    example12_2->right()->add_left(17);
    example12_2->right()->add_right(20);
    return example12_2;
}();

const string example12_2StrExpected{"2\n3\n4\n6\n7\n9\n13\n15\n17\n18\n20\n"};

TEST(InorderTreeWalkTest, Example12_1_a)
{
    stringstream ss;
    inorder_tree_walk(ss, example12_1_a.get());
    string str{istreambuf_iterator<char>(ss), {}};

    ASSERT_EQ(str, example12_1StrExpected);
}

TEST(InorderTreeWalkTest, Example12_1_b)
{
    stringstream ss;
    inorder_tree_walk(ss, example12_1_b.get());
    string str{istreambuf_iterator<char>(ss), {}};

    ASSERT_EQ(str, example12_1StrExpected);
}

TEST(InorderTreeWalkTest, Example12_2)
{
    stringstream ss;
    inorder_tree_walk(ss, example12_2.get());
    string str{istreambuf_iterator<char>(ss), {}};

    ASSERT_EQ(str, example12_2StrExpected);
}

TEST(TreeSearchTest, Example12_2)
{
    auto search = [&](const auto key) {
        return tree_search(example12_2.get(), key);
    };
    ASSERT_EQ(search(1), nullptr);
    ASSERT_EQ(search(2)->key, 2);
    ASSERT_EQ(search(6)->key, 6);
    ASSERT_EQ(search(9)->key, 9);
    ASSERT_EQ(search(10), nullptr);
    ASSERT_EQ(search(20)->key, 20);
    ASSERT_EQ(search(21), nullptr);
}

TEST(IterativeTreeSearchTest, Example12_2)
{
    auto search = [&](const auto key) {
        return iterative_tree_search(example12_2.get(), key);
    };
    ASSERT_EQ(search(1), nullptr);
    ASSERT_EQ(search(2)->key, 2);
    ASSERT_EQ(search(6)->key, 6);
    ASSERT_EQ(search(9)->key, 9);
    ASSERT_EQ(search(10), nullptr);
    ASSERT_EQ(search(20)->key, 20);
    ASSERT_EQ(search(21), nullptr);
}

TEST(TreeMinimumTest, Example12_2)
{
    auto min = tree_minimum(example12_2.get());
    ASSERT_EQ(min->key, 2);
}

TEST(TreeMaximumTest, Example12_2)
{
    auto max = tree_maximum(example12_2.get());
    ASSERT_EQ(max->key, 20);
}

TEST(TreeSuccessorTest, Example12_2)
{
    auto x = tree_minimum(example12_2.get());
    x = tree_successor(x);
    ASSERT_EQ(x->key, 3);
    x = tree_successor(x);
    ASSERT_EQ(x->key, 4);
    x = tree_successor(x);
    ASSERT_EQ(x->key, 6);
    x = tree_successor(x);
    ASSERT_EQ(x->key, 7);
    x = tree_successor(x);
    ASSERT_EQ(x->key, 9);
    x = tree_successor(x);
    ASSERT_EQ(x->key, 13);
    x = tree_successor(x);
    ASSERT_EQ(x->key, 15);
    x = tree_successor(x);
    ASSERT_EQ(x->key, 17);
    x = tree_successor(x);
    ASSERT_EQ(x->key, 18);
    x = tree_successor(x);
    ASSERT_EQ(x->key, 20);
    x = tree_successor(x);
    ASSERT_EQ(x, nullptr);
}

TEST(TreePredecessorTest, Example12_2)
{
    auto x = tree_maximum(example12_2.get());
    x = tree_predecessor(x);
    ASSERT_EQ(x->key, 18);
    x = tree_predecessor(x);
    ASSERT_EQ(x->key, 17);
    x = tree_predecessor(x);
    ASSERT_EQ(x->key, 15);
    x = tree_predecessor(x);
    ASSERT_EQ(x->key, 13);
    x = tree_predecessor(x);
    ASSERT_EQ(x->key, 9);
    x = tree_predecessor(x);
    ASSERT_EQ(x->key, 7);
    x = tree_predecessor(x);
    ASSERT_EQ(x->key, 6);
    x = tree_predecessor(x);
    ASSERT_EQ(x->key, 4);
    x = tree_predecessor(x);
    ASSERT_EQ(x->key, 3);
    x = tree_predecessor(x);
    ASSERT_EQ(x->key, 2);
    x = tree_predecessor(x);
    ASSERT_EQ(x, nullptr);
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
