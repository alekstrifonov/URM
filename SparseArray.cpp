#include "SparseArray.hpp"
#include <iostream>
#include <cassert>

SparseArray::SparseArray()
{
    indexArray = {}; // initialize as empty
    valueArray = {};
}

std::size_t SparseArray::size()
{
    assert(valueArray.size() == indexArray.size());

    return valueArray.size();
}

void SparseArray::ZERO(const std::size_t position)
{
    if (position > indexArray.back()) // highest index is last - element in position is already zero
    {
        return;
    }

    for (std::size_t i = 0; i < indexArray.size(); i++)
    {
        if (indexArray[i] == position) // if element matches a position in our indexes - we need to remove it from the arrays since it's zero
        {
            indexArray.erase(indexArray.begin() + i);
            valueArray.erase(valueArray.begin() + i);

            return;
        }
    }
}

void SparseArray::INC(const std::size_t position)
{
    if (indexArray.empty())
    {
        indexArray.push_back(position);
        valueArray.push_back(1);

        return;
    }

    if (position > indexArray.back())
    {
        indexArray.push_back(position);
        valueArray.push_back(1);

        return;
    }

    for (std::size_t i = 0; i < indexArray.size(); i++)
    {
        if (indexArray[i] == position)
        {
            valueArray[i]++;
            return;
        }
        else if (position < indexArray[i])
        {
            indexArray.insert(indexArray.begin() + i, position);
            valueArray.insert(valueArray.begin() + i, 1);

            return;
        }
    }
}

void SparseArray::MOVE(const std::size_t x, const std::size_t y)
{
}

void SparseArray::zero(const std::size_t begin, const std::size_t end)
{
}
void SparseArray::set(unsigned int y, const std::size_t x)
{
}

void SparseArray::add(const std::vector<unsigned int> x)
{
    for (std::size_t i = 0; i < x.size(); i++)
    {
        if (x[i] != 0)
        {
            valueArray.push_back(x[i]);
            indexArray.push_back(i);
        }
    }
}

const std::vector<unsigned int> SparseArray::getValues()
{
    return valueArray;
}
const std::vector<unsigned int> SparseArray::getIndexes()
{
    return indexArray;
}