#include "writer.hpp"
#include "header.hpp"

#include <iostream>
#include <fstream>
#include "zlib.h"

using namespace psr;

Writer::Writer(const std::string& output_filename, const std::string& output_map_filename, size_t block_size)
    :
    output_filename(output_filename),
    output_map_filename(output_map_filename),
    block_size(block_size),
    writing_buffer(""),
    writing_buffer_length(0),
    header()
{
    header.set_block_size(block_size);

    output.open(output_filename);
    if (!output.good()) {
        throw "the output file is bad";
    }
}

Writer::~Writer()
{
    Flush(true);
    WriteHeader();

    output.close();
}

Writer& Writer::Write(const char* src, size_t length)
{
    writing_buffer.append(src, length);
    writing_buffer_length += length;
    
    Flush();

    return *this;
}

void Writer::Flush(bool force)
{
    if (writing_buffer_length >= block_size) {
        while (writing_buffer_length >= block_size) {
            header.add_block(Flush(block_size));
            writing_buffer_length -= block_size;
        }
    }

    if (force && writing_buffer_length > 0) {
        header.add_block(Flush(writing_buffer_length));
        writing_buffer_length -= writing_buffer_length;
    }
}

size_t Writer::Flush(const size_t length)
{
    Bytef *compressed_chunk = new Bytef[length];

    uLongf compressed_block_size = length;
    std::string chunk = writing_buffer.substr(0, compressed_block_size);
    compress(compressed_chunk, &compressed_block_size, (Bytef *)chunk.c_str(), length);

    output.write((char *)compressed_chunk, compressed_block_size);

    writing_buffer = writing_buffer.substr(length);

    delete[] compressed_chunk;

    return compressed_block_size;
}

void Writer::WriteHeader() const
{
    std::ofstream output_map(output_map_filename);
    if (!output_map.good()) {
        throw "the output map file is bad";
    }

    output_map << header.Generate();

    output_map.close();
}
