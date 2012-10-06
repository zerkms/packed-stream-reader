#include <iostream>
#include <fstream>

#include "writer.hpp"

int main(int argc, char** argv)
{
    psr::Writer writer("tmp/output", "tmp/output.map", 64 * 1024);

    std::ifstream input("tmp/input");
    
    std::string tmp;
    while (std::getline(input, tmp)) {
        writer.Write(tmp.c_str(), tmp.length());
    }

	return 0;
}
