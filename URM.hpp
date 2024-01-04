#pragma once
#include "tokenizer.hpp"
#include "SparseArray.hpp"
#include <fstream>

class URM
{
public:
    URM();
    ~URM();

    Tokenizer::Token getCurrentInstruction(std::istream &is);

    void loadFromFile(const std::string &fileName);
    void dialogue();

    void print() const;
    void evaluate(std::istream &);

private:
    void run();
    void add(const std::string &fileName);
    
    void clearTempFile();

    void JUMP(const std::size_t, std::istream &is);
    void IF_JUMP(const std::size_t x, const std::size_t y, const std::size_t z, std::istream &is);

private:
    Tokenizer::Token currentInstruction;
    SparseArray memory;
    std::size_t JUMP_INCREMENT;
    std::size_t numberOfInstructions;
    std::string tempFileName;
    std::ofstream outFile;
    std::ifstream inFile;
};