#include "SparseArray.hpp"
#include <iostream>
#include <cassert>

SparseArray::SparseArray()
{
    indexArray = {}; // initialize as empty
    valueArray = {};
}

SparseArray::SparseArray(const std::vector<unsigned int> x)
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

bool SparseArray::equal(const std::size_t x, const std::size_t y) //helper function for URM's IF_JUMP
{
    if (!isInIndexArray(x))
    {
        if (!isInIndexArray(y))
        {
            return true; //both are zero
        }
        return false; //x == 0, y != 0
    }

    if (!isInIndexArray(y))
    {
        return false; //x != 0, y == 0
    }
    
    return valueArray[getPositionIndex(x)] == valueArray[getPositionIndex(y)];
}

void SparseArray::clear()
{
    indexArray.clear();
    indexArray.shrink_to_fit(); //ensure capacity is at zero
    valueArray.clear();
    valueArray.shrink_to_fit();
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

    set(y, valueArray[getPositionIndex(x)]);
}

void SparseArray::zero(const std::size_t begin, const std::size_t end)
{
    if (begin > end)
    {
        std::cerr << "INVALID RANGE GIVEN: " << begin << " IS LARGER THAN: " << end;
    }

    if (end < indexArray[0] || begin > indexArray.back())
    {
        return; // the range to nullify is already zero
    }

    std::size_t beginIndex = 0;
    std::size_t endIndex = 0;

    for (std::size_t i = 0; i < indexArray.size(); i++)
    {
        if (indexArray[i] >= begin && beginIndex == 0)
        {
            beginIndex = i;
        }

        if (indexArray[i] <= end)
        {

            endIndex = i + 1; // erase removes elemets in the range [first, last) - to erase last we need to increment it by 1
        }
    }

    indexArray.erase(indexArray.begin() + beginIndex, indexArray.begin() + endIndex);
    valueArray.erase(valueArray.begin() + beginIndex, valueArray.begin() + endIndex);
}

void SparseArray::set(const std::size_t position, unsigned int newValue)
{
    if(newValue == 0)
    {
        ZERO(position);
    }

    if (isInIndexArray(position))
    {
        valueArray[getPositionIndex(position)] = newValue;
        return;
    }

    if (position > indexArray.back())
    {
       indexArray.push_back(position);
       valueArray.push_back(newValue);

       return;
    }
    
    for (std::size_t i = 0; i < indexArray.size(); i++)
    {
        if (position < indexArray[i])
        {
            indexArray.insert(indexArray.begin() + i, position);
            valueArray.insert(valueArray.begin() + i, newValue);

            return;
        }
    }
}

void SparseArray::copy(const std::size_t begin, const std::size_t end, const std::size_t ammountToCopy)
{
    for (std::size_t i = 0; i < ammountToCopy; i++)
    {
        MOVE(begin + i, end + i);
    }
    
}

void SparseArray::mem(const std::size_t begin, const std::size_t end)
{
    for (std::size_t i = 0; i < end; i++)
    {
        if (isInIndexArray(begin + i))
        {
            std::cout << valueArray[getPositionIndex(begin + i)] << " ";
        } else {
            std::cout << 0 << " ";
        }
    }
    std::cout << std::endl;
}

const std::vector<unsigned int> SparseArray::getValues() const
{
    return valueArray;
}
const std::vector<unsigned int> SparseArray::getIndexes() const
{
    return indexArray;
}