#ifndef WRITER_HPP_
#define WRITER_HPP_

#include <string>
#include <fstream>

#include "header.hpp"

namespace psr {

    class Writer
    {
    private:
        std::string output_filename, output_map_filename;
        std::ofstream output;
        size_t block_size;
        
        std::string writing_buffer;
        size_t writing_buffer_length;

        Header header;

    public:
        Writer(const std::string& output_filename, const std::string& output_map_filename, size_t blockSize);
        ~Writer();

    public:
        Writer& Write(const char* s, size_t n);
    private:
        void Flush(bool force = false);
        size_t Flush(size_t length);
        void WriteHeader() const;
    };

}

#endif