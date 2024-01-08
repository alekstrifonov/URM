#pragma once
#include <fstream>
#include <sstream>

#include "SparseArray.hpp"
#include "tokenizer.hpp"

class URM {
public:
    URM();


    Tokenizer::Token getCurrentInstruction(std::istream& is);

    void loadFromFile(const std::string& fileName);
    void dialogue();

    void evaluate(std::istream&);

    void getInstructions();

private:
    void quote(const std::string& instruction);
    void run();
    void add(const std::string& fileName);

    void clearTempFile();

    void JUMP(const std::size_t);
    void IF_JUMP(const std::size_t x, const std::size_t y, const std::size_t z, std::istream& is);

private:
    Tokenizer::Token currentInstruction;
    SparseArray memory;
    std::size_t JUMP_INCREMENT;
    std::size_t numberOfInstructions;
    std::string tempFileName;
    std::ofstream outFile;
    std::ifstream inFile;
};