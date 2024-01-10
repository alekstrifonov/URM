#define DOCTEST_CONFIG_IMPLEMENT

#include "SparseArray.hpp"
#include "URM.hpp"
#include "doctest.h"
#include "tokenizer.hpp"
#include <iostream>

void compare(const SparseArray& a, const std::vector<unsigned int>& b) {
    std::size_t j = 0;
    for (std::size_t i = 0; i < b.size(); i++) {
        if (b[i] != 0) {
            CHECK(a.getValues()[j] == b[i]);
            ++j;
        }
    }
}

TEST_CASE("TEST SPARSE ARRAY BASIC FUNCTIONS") {
    std::vector<unsigned int> b = { 1, 0, 0, 5, 0, 4, 3 };

    SparseArray a(b);

    compare(a, b);
}

TEST_CASE("TEST ZERO AND INC") {
    SparseArray a;

    std::vector<unsigned int> b = { 1, 2, 3 };

    a.INC(0);
    a.INC(1);
    a.INC(1);
    a.INC(2);
    a.INC(2);
    a.INC(2);

    CHECK(a.size() == b.size());

    compare(a, b);

    a.ZERO(0);
    CHECK(a.size() != b.size());

    a.ZERO(1);
    a.ZERO(2);

    CHECK(a.size() == 0);
}

TEST_CASE("TEST MOVE") {
    std::vector<unsigned int> b = { 4, 1, 1, 1 };

    SparseArray a(b);

    b.push_back(4);

    a.MOVE(0, 4);

    compare(a, b);

    a.ZERO(0);
    a.MOVE(0, 4);

    CHECK(a.size() == 3);

    a.INC(1);
    a.MOVE(1, 2);

    std::vector<unsigned int> c = { 2, 2, 1 };

    compare(a, c);
}

TEST_CASE("TEST / SPARSE ARRAY FUNCTIONS") {
    std::vector<unsigned int> b = { 0, 2, 9, 0, 1, 3, 4, 5, 0, 2, 7 };

    SparseArray a(b);

    SUBCASE("TESTING /zero") {
        a.zero(3, 8);

        CHECK(a.size() == 4);

        std::vector<unsigned int> valueResult = { 2, 9, 2, 7 };
        std::vector<unsigned int> indexResult = { 1, 2, 9, 10 };

        for (std::size_t i = 0; i < a.size(); i++) {
            CHECK(a.getIndexes()[i] == indexResult[i]);
            CHECK(a.getValues()[i] == valueResult[i]);
        }

        a.zero(11, 13);
        CHECK(a.size() == 4);
    }

    SUBCASE("TESTING /set") {
        CHECK(a.size() == 8);

        a.set(4, 2);
        CHECK(a.size() == 8);
        CHECK(a.getValues()[2] == 2);

        a.set(3, 3);
        CHECK(a.size() == 9);
        std::vector<unsigned int> toCompare = { 2, 9, 3, 2, 3, 4, 5, 2, 7 };
        compare(a, toCompare);
    }

    SUBCASE("TESTING /copy") {
        std::vector<unsigned int> toCompare = { 2, 9, 2, 9, 4, 5, 2, 7 };
        a.copy(0, 3, 3);
        a.mem(0, 11);
        compare(a, toCompare);

        a.copy(0, 11, 11);
        CHECK(a.size() == 16);
    }

    SUBCASE("TESTING /mem") {
        CHECK(a.size() == 8);
        a.mem(0, 11);
    }
}

TEST_CASE("Test Basic Operators Tokenization") {
    std::istringstream is("ZERO 1\n INC 2\nMOVE 1 2\nJUMP 3\nJUMP 1 3 8\n");
    Tokenizer tokenizer(is);

    Tokenizer::Token token;

    is >> token;

    CHECK(token.type == Tokenizer::ZERO);
    CHECK(token.value.size() == 1);
    CHECK(token.value[0] == 1);

    is >> token;
    CHECK(token.type == Tokenizer::INC);
    CHECK(token.value.size() == 1);
    CHECK(token.value[0] == 2);

    is >> token;
    CHECK(token.type == Tokenizer::MOVE);
    CHECK(token.value.size() == 2);
    CHECK(token.value[0] == 1);
    CHECK(token.value[1] == 2);

    is >> token;
    CHECK(token.type == Tokenizer::JUMP);
    CHECK(token.value.size() == 1);
    CHECK(token.value[0] == 3);

    is >> token;
    CHECK(token.type == Tokenizer::IF_JUMP);
    CHECK(token.value.size() == 3);
    CHECK(token.value[0] == 1);
    CHECK(token.value[1] == 3);
    CHECK(token.value[2] == 8);
}

TEST_CASE("Test From File") {
    std::ifstream is("test.txt");

    Tokenizer tokenizer(is); // Create tokenizer using file stream

    Tokenizer::Token token;

    is >> token;
    CHECK(token.type == Tokenizer::ZERO);
    CHECK(token.value.size() == 1);
    CHECK(token.value[0] == 1);

    is >> token;
    CHECK(token.type == Tokenizer::INC);
    CHECK(token.value.size() == 1);
    CHECK(token.value[0] == 2);

    is >> token;
    CHECK(token.type == Tokenizer::MOVE);
    CHECK(token.value.size() == 2);
    CHECK(token.value[0] == 1);
    CHECK(token.value[1] == 2);

    is >> token;
    CHECK(token.type == Tokenizer::JUMP);
    CHECK(token.value.size() == 1);
    CHECK(token.value[0] == 3);
    is >> token;

    CHECK(token.type == Tokenizer::IF_JUMP);
    CHECK(token.value.size() == 3);
    CHECK(token.value[0] == 1);
    CHECK(token.value[1] == 3);
    CHECK(token.value[2] == 8);

    is >> token;
    CHECK(token.type == Tokenizer::RANGE_ZERO);
    CHECK(token.value.size() == 2);
    CHECK(token.value[0] == 1);
    CHECK(token.value[1] == 5);

    is >> token;
    CHECK(token.type == Tokenizer::SET);
    CHECK(token.value.size() == 2);
    CHECK(token.value[0] == 2);
    CHECK(token.value[1] == 4);

    is >> token;
    CHECK(token.type == Tokenizer::MEM);
    CHECK(token.value.size() == 2);
    CHECK(token.value[0] == 1);
    CHECK(token.value[1] == 2);

    is >> token;
    CHECK(token.type == Tokenizer::COMMENT);
    CHECK(token.keyword == "This is a comment");

    is >> token;
    CHECK(token.type == Tokenizer::LOAD);
    CHECK(token.keyword == "fib.urm");

    is >> token;
    CHECK(token.type == Tokenizer::RUN);

    is >> token;
    CHECK(token.type == Tokenizer::ADD);
    CHECK(token.keyword == "rand.urm");

    is >> token;
    CHECK(token.type == Tokenizer::QUOTE);
    CHECK(token.keyword == "SET 2 3");

    is >> token;
    CHECK(token.type == Tokenizer::CODE);

    is >> token;
    CHECK(token.type == Tokenizer::COMMENT);
    CHECK(token.keyword == "This is a comment");

    is.close();
}

TEST_CASE("TEST URM BASIC FUNCTIONALITY") {
    std::ifstream is("temp.urm");

    URM a;

    CHECK(a.getCurrentInstruction(is).type == Tokenizer::LOAD);
    a.evaluate();

    CHECK(a.getCurrentInstruction(is).type == Tokenizer::INC);
    a.evaluate();

    CHECK(a.getCurrentInstruction(is).type == Tokenizer::RUN);
    a.evaluate();

    std::ifstream loadedFile("sample.urm");
    a.getInstructions();
    std::ifstream instructionsFile("CODE.urm");

    Tokenizer loadedTokenizer(loadedFile);
    Tokenizer instructionTokenizer(instructionsFile);

    Tokenizer::Token loadedToken;
    Tokenizer::Token instructionToken;

    while (!loadedFile.eof()) {
        loadedFile >> loadedToken;
        instructionsFile >> instructionToken;

        CHECK(loadedToken == instructionToken);
    }

    loadedFile.close();

    std::ifstream addedFile("shrek.urm");
    Tokenizer addedTokenizer(addedFile);

    Tokenizer::Token addedToken;

    while (!addedFile.eof()) {
        addedFile >> addedToken;
        instructionsFile >> instructionToken;

        CHECK(addedToken == instructionToken);
    }

    addedFile.close();
}

int main() {
    doctest::Context().run();

    URM a;
    a.dialogue();
}