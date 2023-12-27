#define DOCTEST_CONFIG_IMPLEMENT

#include <iostream>
#include "doctest.h"
#include "SparseArray.hpp"

void compare(const SparseArray &a, const std::vector<unsigned int> &b)
{
    std::size_t j = 0;
    for (std::size_t i = 0; i < b.size(); i++)
    {
        if (b[i] != 0)
        {
            CHECK(a.getValues()[j] == b[i]);
            ++j;
        }
    }
}

TEST_CASE("TEST SPARSE ARRAY BASIC FUNCTIONS")
{
    SparseArray a;

    std::vector<unsigned int> b = {1, 0, 0, 5, 0, 4, 3};

    a.add(b);

    compare(a, b);
}

TEST_CASE("TEST ZERO AND INC")
{
    SparseArray a;

    std::vector<unsigned int> b = {1, 2, 3};

    a.INC(0);
    a.INC(1);
    a.INC(1);
    a.INC(2);
    a.INC(2);
    a.INC(2);

    CHECK(a.size() == b.size());

    compare(a,b);

    a.ZERO(0);
    CHECK(a.size() != b.size());

    a.ZERO(1);
    a.ZERO(2);

    CHECK(a.size() == 0);
}

TEST_CASE("TEST MOVE")
{
    SparseArray a;

    std::vector<unsigned int> b = {4, 1, 1, 1};

    a.add(b);
    b.push_back(4);

    a.MOVE(0, 4);

    compare(a, b);

    a.ZERO(0);
    a.MOVE(0, 4);

    CHECK(a.size() == 3);

    a.INC(1);
    a.MOVE(1, 2);

    std::vector<unsigned int> c = {2, 2, 1};

    compare(a, c);
}

int main()
{
    doctest::Context().run();
}