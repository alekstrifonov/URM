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

    void clearTempFile();

    void JUMP(const std::size_t instructionNumber);
    void IF_JUMP(const std::size_t x, const std::size_t y, const std::size_t z);

    bool isInstruction() const;
    void updateNumInstrucitons(const std::string& line);

    void refreshFile(std::streampos);
    void updateJump(std::string& input, size_t increment) const;

private:
    Tokenizer::Token currentInstruction;
    SparseArray memory;
    std::size_t numberOfInstructions;
    std::size_t jumpIncrement;
    std::string tempFileName;
    std::ofstream outFile;
    std::ifstream inFile;
};