#include "SparseArray.hpp"

#include <cassert>
#include <iostream>

using iter = std::map<std::size_t, unsigned int>::const_iterator;

SparseArray::SparseArray() {
    assert(memory.empty());
}

SparseArray::SparseArray(const std::vector<unsigned int> x) {
    for (std::size_t i = 0; i < x.size(); i++) {
        if (x[i] != 0) {
            memory[i] = x[i];
        }
    }
}

bool SparseArray::isInIndexArray(const std::size_t position) const {

    if (memory.empty()) {
        return false;
    }

    iter end = memory.end();
    --end;

    if (position > end->first) {
        return false;
    }
    else {
        for (iter i = memory.begin(); i != memory.end(); ++i) {
            if (position == i->first) {
                return true;
            }
        }
    }

    return false;
}

std::size_t SparseArray::size() const {
    return memory.size();
}

bool SparseArray::equal(const std::size_t x, const std::size_t y) {// helper function for URM's IF_JUMP

    if (!isInIndexArray(x)) {
        if (!isInIndexArray(y)) {
            return true; // both are zero
        }
        return false; // x == 0, y != 0
    }

    if (!isInIndexArray(y)) {
        return false; // x != 0, y == 0
    }

    return memory[x] == memory[y];
}

void SparseArray::clear() {
    memory.clear();
}

void SparseArray::ZERO(const std::size_t position) {
    if (memory.empty()) //nothing to delete
    {
        return;
    }

    if (!isInIndexArray(position)) {
        return;
    }

    memory.erase(position);
}

void SparseArray::INC(const std::size_t position) {
    if (memory.empty()) {
        memory[position] = 1;
        return;
    }

    memory[position]++;
}

void SparseArray::MOVE(const std::size_t x, const std::size_t y) {
    if (!isInIndexArray(x)) {
        ZERO(y);

        return;
    }

    memory[y] = memory[x];
}

void SparseArray::zero(const std::size_t begin, const std::size_t end) {
    if (begin > end) {
        std::cerr << "INVALID RANGE GIVEN: " << begin
            << " IS LARGER THAN: " << end;
    }

    iter temp = memory.end();
    --temp;

    if (end < memory.begin()->first || begin > temp->first) {
        return; // the range to nullify is already zero
    }

    iter beginIndex = memory.end();
    iter endIndex = memory.end();

    for (iter i = memory.begin(); i != memory.end(); ++i) {
        if (i->first >= begin && beginIndex == memory.end()) {
            beginIndex = i;
        }

        if (i->first <= end) {
            endIndex = i;
        }
        else {
            break;
        }
    }

    memory.erase(beginIndex, ++endIndex); // erase removes elemets in the range [first, last)
}

void SparseArray::set(const std::size_t position, unsigned int newValue) {
    if (newValue == 0) {
        ZERO(position);
    }

    memory[position] = newValue;
}

void SparseArray::copy(const std::size_t begin, const std::size_t end, const std::size_t ammountToCopy) {
    for (std::size_t i = 0; i < ammountToCopy; i++) {
        MOVE(begin + i, end + i);
    }
}

void SparseArray::mem(const std::size_t begin, const std::size_t end) {
    for (std::size_t i = 0; i < end; i++) {
        if (isInIndexArray(begin + i)) {
            std::cout << memory[begin + i] << " ";
        }
        else {
            std::cout << 0 << " ";
        }
    }
    std::cout << std::endl;
}

const std::vector<unsigned int> SparseArray::getValues() const {
    std::vector<unsigned int> result = {};

    for (iter i = memory.begin(); i != memory.end(); ++i) {
        result.push_back(i->second);
    }

    return result;
}

const std::vector<std::size_t> SparseArray::getIndexes() const {
    std::vector<std::size_t> result = {};

    for (iter i = memory.begin(); i != memory.end(); ++i) {
        result.push_back(i->first);
    }

    return result;
}