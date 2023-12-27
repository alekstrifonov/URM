#include "SparseArray.hpp"
#include <iostream>
#include <cassert>

SparseArray::SparseArray()
{
    indexArray = {}; // initialize as empty
    valueArray = {};
}

bool SparseArray::isInIndexArray(const std::size_t position) const
{
    if (position > indexArray.back())
    {
        return false;
    }
    else
    {
        for (std::size_t i = 0; i < indexArray.size(); i++)
        {
            if (indexArray[i] == position)
            {
                return true;
            }
        }
    }

    return false;
}

std::size_t SparseArray::getPositionIndex(const std::size_t position) const
{
    assert(isInIndexArray(position));
    std::size_t result = 0;

    for (std::size_t i = 0; i < indexArray.size(); i++)
    {
        if (indexArray[i] == position) // assert ensures us that function will always return a value
        {
            result = i;
        }
    }
    return result;
}

std::size_t SparseArray::size() const
{
    assert(valueArray.size() == indexArray.size());

    return valueArray.size();
}

void SparseArray::ZERO(const std::size_t position)
{
    if (!isInIndexArray(position))
    {
        return;
    }

    const std::size_t indexToRemove = getPositionIndex(position);

    indexArray.erase(indexArray.begin() + indexToRemove);
    valueArray.erase(valueArray.begin() + indexToRemove);
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
    if (!isInIndexArray(x))
    {
        ZERO(y);

        return;
    }

    if (isInIndexArray(y))
    {
        valueArray[getPositionIndex(y)] = valueArray[getPositionIndex(x)];
        return;
    }
    else
    {
        for (std::size_t i = 0; i < valueArray[getPositionIndex(x)]; i++)
        {
            INC(y);
        }
    }
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

const std::vector<unsigned int> SparseArray::getValues() const
{
    return valueArray;
}
const std::vector<unsigned int> SparseArray::getIndexes() const
{
    return indexArray;
}