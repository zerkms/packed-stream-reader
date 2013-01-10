#include "header.hpp"

#include <iostream>

using namespace psr;

Header::Header()
{
    signature_.push_back('P');
    signature_.push_back('S');
    signature_.push_back('R');
}

Header::Header(std::vector<unsigned char> map_binary)
{
    signature_.push_back('P');
    signature_.push_back('S');
    signature_.push_back('R');

    std::vector<char>::const_iterator
        it = signature_.begin(),
        ite = signature_.end();

    for (int index = 0; it != ite; ++it) {
        if (*it != map_binary.at(index++)) {
            throw "signature is incorrect";
        }
    }

    Parse(map_binary);
}

void Header::set_block_size(size_t block_size)
{
    block_size_ = block_size;
}

data_vector Header::Generate() const
{
    size_t blocks_count = blocks_.size();

    data_vector result;
    size_t total_count = signature_.size() + sizeof(block_size_) + sizeof(blocks_count) + blocks_count * sizeof(vector_block_size_type);

    result.reserve(total_count);

    std::vector<char>::const_iterator
        it = signature_.begin(),
        ite = signature_.end();

    for (; it != ite; ++it) {
        result.push_back(*it);
    }
    
    // block size
    std::copy(
        reinterpret_cast<const data_type *>(&block_size_),
        reinterpret_cast<const data_type *>(&block_size_) + sizeof(block_size_),
        std::back_inserter(result)
    );

    // blocks count
    std::copy(
        reinterpret_cast<data_type *>(&blocks_count),
        reinterpret_cast<data_type *>(&blocks_count) + sizeof(blocks_count),
        std::back_inserter(result)
    );

    // blocks
    std::vector<vector_block_size_type>::const_iterator
        it2 = blocks_.begin(),
        ite2 = blocks_.end();

    for (; it2 != ite2; ++it2) {
        vector_block_size_type block_size = *it2;
        
        std::copy(
            reinterpret_cast<data_type *>(&block_size),
            reinterpret_cast<data_type *>(&block_size) + sizeof(block_size),
            std::back_inserter(result)
        );
    }

    return result;
}

void Header::add_block(size_t length)
{
    blocks_.push_back(length);
}

void Header::Parse(const data_vector& map_binary)
{
    size_t offset = signature_.size();

    data_vector::const_iterator
        it = map_binary.begin() + offset,
        ite = it + sizeof(block_size_);

    std::copy(it, ite, (data_type *)&block_size_);

    size_t blocks_count = 0;

    it = ite;
    ite += sizeof(blocks_count);

    std::copy(it, ite, (data_type *)&blocks_count);

    while (blocks_count--) {
        it = ite;
        ite += sizeof(vector_blocks::value_type);

        vector_blocks::value_type tmp;
        std::copy(it, ite, (data_type *)&tmp);

        blocks_.push_back(tmp);
    }
}