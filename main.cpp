#define DOCTEST_CONFIG_IMPLEMENT

#include <iostream>
#include "doctest.h"

TEST_CASE("Test Doctest")
{
    CHECK(1 == 1);
}

int main()
{
    doctest::Context().run();
}