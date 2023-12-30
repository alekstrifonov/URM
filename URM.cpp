#include "URM.hpp"

URM::URM() = default;

URM::URM(const Tokenizer::Token &t)
{
    currentInstruction.type = t.type;
    currentInstruction.keyword = t.keyword;
    currentInstruction.value = t.value;
}

void URM::JUMP(const std::size_t instructionNumber, std::istream &is)
{
    for (std::size_t i = 0; i < instructionNumber; i++)
    {
        is >> currentInstruction;
    }
}

void URM::IF_JUMP(const std::size_t x, const std::size_t y, const std::size_t z, std::istream &is)
{
    if (memory.equal(x, y))
    {
        JUMP(z, is);
    }
}

void URM::loadFromFile(const std::string& fileName)
{
    memory.clear();

    std::ifstream is(fileName);
    Tokenizer tokenizer(is);

    is >> currentInstruction;
}

void URM::dialogue()
{
}

void URM::print() const
{
}

void URM::evaluate(std::istream& is)
{
    switch (currentInstruction.type)
    {
    case Tokenizer::ZERO:
        memory.ZERO(currentInstruction.value[0]);
        break;

    case Tokenizer::INC:
        memory.INC(currentInstruction.value[0]);
        break;

    case Tokenizer::MOVE:
        memory.MOVE(currentInstruction.value[0], currentInstruction.value[1]);
        break;

    case Tokenizer::JUMP:
        JUMP(currentInstruction.value[0], is);
        break;

    case Tokenizer::IF_JUMP:
        IF_JUMP(currentInstruction.value[0], currentInstruction.value[1], currentInstruction.value[2], is);
        break;

    case Tokenizer::RANGE_ZERO:
        memory.zero(currentInstruction.value[0], currentInstruction.value[1]);
        break;

    case Tokenizer::SET:
        memory.set(currentInstruction.value[0], currentInstruction.value[1]);
        break;
    case Tokenizer::COPY:
        memory.copy(currentInstruction.value[0], currentInstruction.value[1], currentInstruction.value[2]);
        break;

    case Tokenizer::MEM:
        memory.mem(currentInstruction.value[0], currentInstruction.value[1]);
        break;
    case Tokenizer::LOAD:
        /* code */
        break;

    case Tokenizer::RUN:
        /* code */
        break;
    case Tokenizer::ADD:
        /* code */
        break;

    case Tokenizer::QUOTE:
        /* code */
        break;
    case Tokenizer::CODE:
        /* code */
        break;
    case Tokenizer::COMMENT:
        //is >> currentInstruction;
        break;

    default:
        break;
    }
}