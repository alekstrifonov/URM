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
    if (currentInstruction.type == Tokenizer::ZERO)
    {
        memory.ZERO(currentInstruction.value[0]);
    } else if (currentInstruction.type == Tokenizer::INC)
    {
        memory.INC(currentInstruction.value[0]);
    }
    
    
}