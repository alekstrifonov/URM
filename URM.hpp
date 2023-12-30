#pragma once
#include "tokenizer.hpp"
#include "SparseArray.hpp"

class URM
{
public:
    URM();
    URM(const Tokenizer::Token& t);


    void loadFromFile(const std::string&  fileName);
    void dialogue();

    void print() const;
    void evaluate(std::istream&);

private:
    void JUMP(const std::size_t, std::istream& is);
    void IF_JUMP(const std::size_t x, const std::size_t y, const std::size_t z, std::istream& is);

private:
    Tokenizer::Token currentInstruction;
    SparseArray memory;
};