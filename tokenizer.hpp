#pragma once
#include <string>
#include <iostream>

class Tokenizer
{
public:
    enum Tokens
    {
        ZERO, INC, MOVE, IF_JUMP, JUMP, RANGE_ZERO, SET, COPY, MEM, LOAD, RUN, ADD, QUOTE, CODE, COMMENT
    };

    struct Token
    {
        Tokens type;
        std::string keyword;
        std::vector<unsigned int> value;//vector since not all functions are unitary
    };

    Tokenizer(std::istream &);

    Token getNextToken();
    Token peekToken();

private:
    std::istream &in;
    Token *peeked;
};

std::istream &operator>>(std::istream &, Tokenizer::Token &);
std::ostream &operator<<(std::ostream &, Tokenizer::Token &);