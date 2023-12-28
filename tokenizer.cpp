#include "tokenizer.hpp"

void clear(std::istream &in)
{
    char next = in.peek();

    while (isspace(in.peek()))
    {
        in.get();
        next = in.peek();
    }
}

std::vector<unsigned int> getValues(std::istream &in)
{
    std::vector<unsigned int> values;

    char next = in.peek();
    assert(isdigit(next));

    while (isdigit(next))
    {
        unsigned int value;
        in >> value;
        values.push_back(value);

        while (isspace(in.peek()))
        {
            in.get();
        }

        next = in.peek();        
    }

    return values;
}

Tokenizer::Tokenizer(std::istream &_in) : in(_in) {}

std::istream &operator>>(std::istream &in, Tokenizer::Token &t)
{
    std::string keyword;

    in >> keyword;

    if (keyword == "ZERO")
    {
        t.type = Tokenizer::ZERO;
        clear(in);

        t.value = getValues(in);

        assert(t.value.size() == 1);
    }
    else if (keyword == "INC")
    {
        t.type = Tokenizer::INC;
        clear(in);

        t.value = getValues(in);

        assert(t.value.size() == 1);
    }
    else if (keyword == "MOVE")
    {
        t.type = Tokenizer::MOVE;
        clear(in);

        t.value = getValues(in);

        assert(t.value.size() == 2);
    }
    else if (keyword == "JUMP")
    {
        clear(in);
        t.value = getValues(in);

        if (t.value.size() == 1)
        {
            t.type = Tokenizer::JUMP;
        }
        else
        {
            t.type = Tokenizer::IF_JUMP;
        }
    }
    else if (keyword == "/zero")
    {
        t.type = Tokenizer::RANGE_ZERO;
        clear(in);

        t.value = getValues(in);

        assert(t.value.size() == 2);
    }
    else if (t.keyword == "/set")
    {
        t.type = Tokenizer::SET;
        clear(in);

        t.value = getValues(in);

        assert(t.value.size() == 2);
    }
    else if (t.keyword == "/copy")
    {
        t.type = Tokenizer::COPY;
        clear(in);

        t.value = getValues(in);

        assert(t.value.size() == 3);
    }
    else if (keyword == "/mem")
    {
        t.type = Tokenizer::MEM;
        clear(in);

        t.value = getValues(in);

        assert(t.value.size() == 2);
    }
    else if (keyword == "/load")
    {
        t.type = Tokenizer::LOAD;
        clear(in);

        in >> t.keyword;
    }
    else if (keyword == "/run")
    {
        t.type = Tokenizer::RUN;
        clear(in);
    }
    else if (keyword == "/add")
    {
        t.type = Tokenizer::ADD;
        clear(in);

        in >> t.keyword;
    }
    else if (keyword == "/quote")
    {
        t.type = Tokenizer::QUOTE;
        clear(in);

        std::getline(in, t.keyword);
    }
    else if (keyword == "/code")
    {
        t.type = Tokenizer::CODE;
    }
    else if (keyword == "/comment")
    {
        t.type = Tokenizer::COMMENT;
    }
    else
    {
        std::cout << "Wrong input" << std::endl; // will need to handle exceptions better in the future
    }

    return in;
}