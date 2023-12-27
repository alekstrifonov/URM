#define DOCTEST_CONFIG_IMPLEMENT

#include <iostream>
#include "doctest.h"
#include "SparseArray.hpp"

TEST_CASE("TEST SPARSE ARRAY BASIC FUNCTIONS")
{
    SparseArray a;

    std::vector<unsigned int> b = {1, 0, 0, 5, 0, 4, 3};

    a.add(b);
    std::size_t j = 0;

    for (std::size_t i = 0; i < b.size(); ++i)
    {
        if (b[i] != 0)
        {
            CHECK(b[i] == a.getValues()[j]);
            CHECK(i == a.getIndexes()[j]);
            ++j;
        }
    }
}

TEST_CASE("TEST URM INSTRUCTIONS")
{
    SparseArray a;

    std::vector<unsigned int> b = {1,2,3};

    a.INC(0);
    a.INC(1);
    a.INC(1);
    a.INC(2);
    a.INC(2);
    a.INC(2);

    CHECK(a.size() ==  b.size());

    for (std::size_t i = 0; i < a.size(); i++)
    {
        CHECK(a.getValues()[i] == b[i]);
        CHECK(a.getIndexes()[i] == i);
    }
    
    a.ZERO(0);
    CHECK(a.size() != b.size());

    a.ZERO(1);
    a.ZERO(2);

    CHECK(a.size() == 0);
}

int main()
{
    doctest::Context().run();
}