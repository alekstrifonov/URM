#pragma once
#include <vector>

class SparseArray
{
public:
    SparseArray();

    std::size_t size() const;

    void ZERO(const std::size_t position);
    void INC(const std::size_t position);
    void MOVE(const std::size_t x, const std::size_t y);

    void zero(const std::size_t begin, const std::size_t end);
    void set(unsigned int y, const std::size_t x);

    void add(std::vector<unsigned int> x);

    const std::vector<unsigned int> getValues() const;
    const std::vector<unsigned int> getIndexes() const;

private:
    bool isInIndexArray(const std::size_t position) const;
    std::size_t getPositionIndex(const std::size_t position) const;

private:
    std::vector<unsigned int> indexArray;
    std::vector<unsigned int> valueArray;
};
