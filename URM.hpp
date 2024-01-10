#pragma once
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "SparseArray.hpp"
#include "tokenizer.hpp"

class URM {
public:
    URM();
    ~URM();

    Tokenizer::Token getCurrentInstruction(std::istream& is);

    void loadFromFile(const std::string& fileName);
    void dialogue();

    void evaluate();

    void getInstructions();

private:
    void quote(const std::string& instruction);
    void run();
    void add(const std::string& fileName);
    void jumpEval(std::size_t&);

    void clearTempFile();

    void JUMP(const std::size_t);
    void IF_JUMP(const std::size_t x, const std::size_t y, const std::size_t z);

private:
    Tokenizer::Token currentInstruction;
    SparseArray memory;
    std::size_t numberOfInstructions;
    std::string tempFileName;
    std::ofstream outFile;
    std::ifstream inFile;
};