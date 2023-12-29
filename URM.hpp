#pragma once
#include "tokenizer.hpp"
#include "SparseArray.hpp"

class URM
{
public:
    URM();
    URM(const Tokenizer::Token& t);

    void loadFromFile(std::ifstream& is);
    void dialogue();

    void print() const;

private:
    void evaluate();

private:
    Tokenizer::Token currentInstruction;
    SparseArray memory;
};