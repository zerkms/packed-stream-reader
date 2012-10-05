#include "writer.hpp"
#include "header.hpp"

#include <iostream>
#include <fstream>
#include "zlib.h"

using namespace psr;

Writer::Writer(size_t block_size)
    :
    block_size(block_size)
{
}

void Writer::Write(const std::string& input_filename, const std::string& output_filename, const std::string& output_map_filename)
{
    Header header;
    header.set_block_size(block_size);

    std::ifstream input(input_filename);

    if (!input.good()) {
        throw "the input file is bad";
    }

    std::ofstream output(output_filename);

    if (!output.good()) {
        throw "the output file is bad";
    }

    char *chunk = new char[block_size];
    Bytef *compressed_chunk = new Bytef[block_size];

    while (!input.eof()) {
        uLongf compressed_block_size = block_size;

        input.read(chunk, block_size);
        compress(compressed_chunk, &compressed_block_size, (Bytef *)chunk, block_size);
        header.add_block(compressed_block_size);
        output.write((char *)compressed_chunk, compressed_block_size);
    }

    input.close();
    output.close();

    delete[] chunk;
    delete[] compressed_chunk;

    std::ofstream output_map(output_map_filename);

    if (!output_map.good()) {
        throw "the output map file is bad";
    }

    std::string map(header.Generate());

    output_map.write(map.c_str(), map.size());

    output_map.close();
}