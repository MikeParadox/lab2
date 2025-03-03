#ifndef LISTGTESTS_H
#define LISTGTESTS_H

#include "my_list.h"
#include <gtest/gtest.h>
#include <initializer_list>
#include <string>

TEST(Construction, DefaultConstruction)
{
    MyList<int> lst;
    ASSERT_EQ(lst.size(), 0);
}

TEST(Construction, InitListConstruction)
{
    MyList<int> lst{1, 2, 3};
    ASSERT_EQ(lst.size(), 3);
}

TEST(Construction, CopyConstruction)
{
    MyList<int> lst{1, -10};
    MyList<int> lst2{lst};
    ASSERT_EQ(lst2.size(), 2);
}

TEST(Construction, CopyConstructionIsNotShallow)
{
    MyList<int> lst{0, 1, 3};
    MyList<int> lst2{lst};
    lst.push_back(111);
    ASSERT_NE(lst.size(), lst2.size());
}

TEST(Assignment, CopyAssignment)
{
    MyList<int> lst{0, 1, 3};
    MyList<int> lst2;
    lst2 = lst;
    ASSERT_EQ(lst.size(), lst2.size());
}

TEST(Assignment, CopyAssignmentIsNotShallow)
{
    MyList<int> lst{0, 1, 3};
    MyList<int> lst2;
    lst2 = lst;
    lst.push_back(111);
    ASSERT_NE(lst.size(), lst2.size());
}

TEST(Empty, IsEmpty)
{
    MyList<int> lst;
    ASSERT_TRUE(lst.empty());
}

TEST(Empty, IsNotEmpty)
{
    MyList<int> lst{1};
    ASSERT_FALSE(lst.empty());
}

TEST(Size, Empty)
{
    MyList<int> lst;
    ASSERT_EQ(lst.size(), 0);
}

TEST(Size, NotEmpty)
{
    MyList<int> lst{1, 2, 3};
    ASSERT_EQ(lst.size(), 3);
}

TEST(Clear, EmptyList)
{
    MyList<int> lst;
    lst.clear();
    ASSERT_EQ(lst.size(), 0);
}

TEST(Clear, NotEmptyList)
{
    MyList<int> lst{2, 4, 0, 1};
    lst.clear();
    ASSERT_EQ(lst.size(), 0);
}

TEST(Insert, BeginEmpty)
{
    MyList<int> lst;
    lst.insert(lst.begin(), 2);
    ASSERT_EQ(*lst.begin(), 2);
}

TEST(Insert, BeginNotEmpty)
{
    MyList<int> lst{0, 1};
    lst.insert(lst.begin(), 2);
    ASSERT_EQ(*lst.begin(), 2);
}

TEST(Insert, EndEmpty)
{
    MyList<int> lst;
    lst.insert(lst.end(), 2);
    ASSERT_EQ(*lst.begin(), 2);
}

TEST(Insert, EndNotEmpty)
{
    MyList<int> lst{0, 1};
    lst.insert(lst.end(), 2);
    ASSERT_EQ(*(--lst.end()), 2);
}

TEST(Insert, NotInEnd)
{
    MyList<int> lst{1, 3, 5, 7};
    MyList<int> lst2{1, 3, 9, 5, 7};

    auto it{++lst.begin()};
    auto it2{++lst.begin()};
    ++it2;

    lst.insert(it, 0);
    lst2.insert(it2, 0);

    ASSERT_EQ(*(--it), 0);
    ASSERT_EQ(*(--it2), 0);
}

TEST(Erase, Begin)
{
    MyList<int> lst{1, 2};
    auto it = lst.erase(lst.begin());
    ASSERT_EQ(lst.size(), 1);
    ASSERT_EQ(*(lst.begin()), 2);
    ASSERT_EQ(*it, 2);
}

TEST(Erase, End)
{
    MyList<int> lst{1, 2};
    auto it = lst.erase(++lst.begin());
    ASSERT_EQ(lst.size(), 1);
    ASSERT_EQ(*(lst.begin()), 1);
}

TEST(Erase, Inside)
{
    MyList<int> lst{1, 2, 3, 4};
    auto it = lst.erase(++lst.begin());
    ++it;
    ASSERT_EQ(lst.size(), 3);
}

TEST(EraseRange, BeginMiddle)
{
    MyList<int> lst{1, 2, 3, 4, 5};
    auto first = lst.begin();
    auto last = --lst.end();
    lst.erase(first, last);
    ASSERT_EQ(*lst.begin(), 5);
    ASSERT_EQ(lst.size(), 1);
}

TEST(EraseRange, MiddleMiddle)
{
    MyList<int> lst{1, 2, 3, 4, 5};
    auto first = ++lst.begin();
    auto last = --lst.end();
    lst.erase(first, last);
    ASSERT_EQ(*lst.begin(), 1);
    ASSERT_EQ(lst.size(), 2);
}

TEST(EraseRange, MiddleEnd)
{
    MyList<int> lst{1, 2, 3, 4, 5};
    auto first = ++lst.begin();
    auto last = lst.end();
    lst.erase(first, last);
    ASSERT_EQ(*lst.begin(), 1);
    ASSERT_EQ(lst.size(), 1);
}

TEST(PushBack, EmptyList)
{
    MyList<int> lst;
    lst.push_back(1);
    ASSERT_EQ(*lst.begin(), 1);
    ASSERT_EQ(lst.size(), 1);
}

TEST(PushBack, NotEmptyList)
{
    MyList<int> lst{1, 2, 3};
    lst.push_back(4);
    ASSERT_EQ(lst.size(), 4);
    ASSERT_EQ(*(--lst.end()), 4);
}

TEST(PopBack, OneNode)
{
    MyList<int> lst{1};
    lst.pop_back();
    ASSERT_TRUE(lst.empty());
}

TEST(PopBack, SeveralNodes)
{
    MyList<int> lst{1, 2, 3};
    auto size = lst.size();
    lst.pop_back();
    ASSERT_EQ(lst.size(), size - 1);
}

TEST(PushFront, EmptyList)
{
    MyList<int> lst;
    lst.push_front(0);
    ASSERT_EQ(lst.size(), 1);
    ASSERT_EQ(*lst.begin(), 0);
}

TEST(PushFront, NotEmptyList)
{
    MyList<int> lst{1, 2};
    lst.push_front(0);
    ASSERT_EQ(lst.size(), 3);
    ASSERT_EQ(*lst.begin(), 0);
}

TEST(PopFront, OneNode)
{
    MyList<int> lst{0};
    auto size = lst.size();
    lst.pop_front();
    ASSERT_TRUE(lst.empty());
}

TEST(PopFront, SeveralNodes)
{
    MyList<int> lst{1, 2, 3, 4};
    auto size = lst.size();
    lst.pop_front();
    ASSERT_EQ(lst.size(), --size);
    ASSERT_EQ(*lst.begin(), 2);
}

TEST(Reverse, OneNode)
{
    MyList<int> lst{1};
    MyList<int> reversed_lst{1};
    lst.reverse();

    auto it = lst.begin();
    auto r_it = reversed_lst.begin();

    for (; it != lst.end(); ++it, ++r_it) ASSERT_EQ(*it, *r_it);
}

TEST(Reverse, EvenNumNodes)
{
    MyList<int> lst{0, 1, 2, 3};
    MyList<int> reversed_lst{3, 2, 1, 0};
    lst.reverse();

    auto it = lst.begin();
    auto r_it = reversed_lst.begin();

    for (; it != lst.end(); ++it, ++r_it) ASSERT_EQ(*it, *r_it);
}

TEST(CountPositive, ZeroPos)
{
    MyList<int> lst{0};
    ASSERT_EQ(lst.count_positive(), 0);
}

TEST(CountPositive, OnePos)
{
    MyList<int> lst{1};
    ASSERT_EQ(lst.count_positive(), 1);
}

TEST(CountPositive, SeveralPos)
{
    MyList<int> lst{-1, 0, 1, 2, 3};
    ASSERT_EQ(lst.count_positive(), 3);
}


#endif
