#ifndef WRITER_HPP_
#define WRITER_HPP_

#include <string>

namespace psr {

    class Writer
    {
    private:
        std::string input_filename, output_filename;
        size_t block_size;

    public:
        Writer(size_t blockSize);
        void Write(const std::string& input_filename, const std::string& output_filename, const std::string& output_map_filename);
    };

}

#endif