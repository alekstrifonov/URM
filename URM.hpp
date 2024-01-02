#pragma once
#include "tokenizer.hpp"
#include "SparseArray.hpp"

class URM
{
public:
    URM();
    URM(std::istream &);

    Tokenizer::Token getCurrentInstruction(std::istream& is);

    void loadFromFile(const std::string &fileName);
    void dialogue();

    void run(std::istream &is);
    void run(const std::string& fileName);

    void add(const std::string& fileName);

    void print() const;
    void evaluate(std::istream &);

private:
    void JUMP(const std::size_t, std::istream &is);
    void IF_JUMP(const std::size_t x, const std::size_t y, const std::size_t z, std::istream &is);

private:
    Tokenizer::Token currentInstruction;
    SparseArray memory;
    std::size_t JUMP_INCREMENT;
};