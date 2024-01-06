#pragma once
#include <map>
#include <vector>

class SparseArray {
   public:
    SparseArray();

    std::size_t size() const;
    SparseArray(std::vector<unsigned int> x);

    bool equal(const std::size_t x, const std::size_t y);

    const std::vector<unsigned int> getValues() const;
    const std::vector<std::size_t> getIndexes() const;
    void clear();

   public:
    void ZERO(const std::size_t position);
    void INC(const std::size_t position);
    void MOVE(const std::size_t x, const std::size_t y);

    void zero(const std::size_t begin, const std::size_t end);
    void set(const std::size_t position, unsigned int newValue);
    void copy(const std::size_t begin, const std::size_t end, const std::size_t ammountToCopy);
    void mem(const std::size_t begin, const std::size_t end);

   private:
    bool isInIndexArray(const std::size_t position) const;

    void changeValue(const std::size_t position, unsigned int value);

    private:
    std::map<std::size_t, unsigned int> memory;
};
