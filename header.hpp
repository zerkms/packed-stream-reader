#ifndef HEADER_HPP_
#define HEADER_HPP_

#include <vector>
#include <string>

namespace psr {

    class Header
    {
    protected:
        std::vector<char> signature_;
        std::vector<size_t> blocks_;
        size_t block_size_;

    public:
        Header();
        void set_block_size(size_t block_size);
        void add_block(size_t length);
        std::string Generate() const;
    };

}

#endif