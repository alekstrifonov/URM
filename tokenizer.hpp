#pragma once
#include <fstream>
#include <iostream>
#include <string>

class Tokenizer {
public:
    enum Tokens {
        ZERO, INC, MOVE, IF_JUMP, JUMP, RANGE_ZERO, SET, COPY, MEM, LOAD, RUN, ADD, QUOTE, CODE, COMMENT, END
    };

    struct Token {
        Tokens type;
        std::string keyword;
        std::vector<std::size_t> value; // vector since not all functions are unitary

        bool operator==(const Token&);
    };

    Tokenizer(std::istream&);

private:
    std::istream& in;
};

std::istream& operator>>(std::istream&, Tokenizer::Token&);