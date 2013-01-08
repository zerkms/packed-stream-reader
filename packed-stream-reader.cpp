#include <iostream>
#include <sstream>
#include <fstream>

#include "writer.hpp"
#include "header.hpp"

void test_header();

int main(int argc, char** argv)
{
    test_header();
    return 0;

    psr::Writer writer(64 * 1024);
    writer.Open("tmp/output", "tmp/output.map");

    std::ifstream input("tmp/input");
    
    std::string tmp;
    while (std::getline(input, tmp)) {
        writer.Write(tmp.c_str(), tmp.length());
    }

	return 0;
}

void test_header()
{
    std::ifstream map("tmp/output.map", std::ios::binary);

    std::vector<unsigned char> map_binary((std::istreambuf_iterator<char>(map)), std::istreambuf_iterator<char>());
    //std::getline(map, map_binary);




    psr::Header h(map_binary);

    

    

    map.close();
}