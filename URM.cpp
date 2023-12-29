#include "URM.hpp"

URM::URM() = default;

URM::URM(const Tokenizer::Token &t)
{
    currentInstruction.type = t.type;
    currentInstruction.keyword = t.keyword;
    currentInstruction.value = t.value;
}

void URM::loadFromFile(std::ifstream &is)
{
}

void URM::dialogue()
{
}

void URM::print() const
{
}

void URM::evaluate()
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
        /* code */
        break;

    case Tokenizer::IF_JUMP:
        /* code */
        break;
    case Tokenizer::RANGE_ZERO:
        /* code */
        break;

    case Tokenizer::SET:
        /* code */
        break;
    case Tokenizer::COPY:
        /* code */
        break;

    case Tokenizer::MEM:
        /* code */
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
        /* code */
        break;

    default:
        break;
    }
}