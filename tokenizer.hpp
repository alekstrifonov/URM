#pragma once
#include <string>
#include <iostream>

class Tokenizer
{
public:
    enum Tokens
    {
        INSTRUCTION,
        COMMAND,
        OPERAND
    };

    struct Token
    {
        Tokens type;
        std::string keyword;
        unsigned int value;
    };

    Tokenizer(std::istream &);

    Token getNextToken();
    Token peekToken();

private:
    std::istream &in;
    Token *peeked;
};

std::istream& operator>>(std::istream&, Tokenizer::Token&);
std::ostream& operator<<(std::ostream&, Tokenizer::Token&);