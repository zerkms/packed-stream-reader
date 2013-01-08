#ifndef HEADER_HPP_
#define HEADER_HPP_

#include <vector>
#include <string>

namespace psr {

    typedef std::vector<size_t> vector_blocks;
    typedef unsigned char data_type;
    typedef std::vector<data_type> data_vector;

    class Header
    {
    protected:
        std::vector<char> signature_;
        vector_blocks blocks_;
        size_t block_size_;

    public:
        Header();
        Header(data_vector map_binary);
        void set_block_size(size_t block_size);
        void add_block(size_t length);
        data_vector Generate() const;

    private:
        void Parse(std::vector<unsigned char> map_binary);
    };

}

#endif