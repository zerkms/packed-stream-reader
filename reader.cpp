#include "reader.hpp"
#include "header.hpp"

using namespace psr;

Reader::Reader()
    :
    is_open(false)
{

}

Reader::Reader(const std::string& output_filename, const std::string& output_map_filename)
{
}

void Reader::Open(const std::string& output_filename, const std::string& output_map_filename)
{
}

void Reader::Close()
{
    is_open = false;
}

Reader::~Reader()
{
    Close();
}