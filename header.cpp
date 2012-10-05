#include "header.hpp"

using namespace psr;

Header::Header()
{
    signature_.push_back('P');
    signature_.push_back('S');
    signature_.push_back('R');
}

void Header::set_block_size(size_t block_size)
{
    block_size_ = block_size;
}

std::string Header::Generate() const
{
    std::string result;

    std::vector<char>::const_iterator
        it = signature_.begin(),
        ite = signature_.end();

    for (; it != ite; ++it) {
        result += *it;
    }

    // block size
    result.append((char *)&block_size_, sizeof(block_size_));

    // blocks count
    size_t blocks_count(blocks_.size());
    result.append((char *)&blocks_count, sizeof(blocks_count));

    // blocks
    std::vector<size_t>::const_iterator
        it2 = blocks_.begin(),
        ite2 = blocks_.end();

    for (; it2 != ite2; ++it2) {
        result.append((char *)&(*it2), sizeof(*it2));
    }

    return result;
}

void Header::add_block(size_t length)
{
    blocks_.push_back(length);
}