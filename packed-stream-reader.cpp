#include <iostream>
#include <fstream>

#include "writer.hpp"

int main(int argc, char** argv)
{
    psr::Writer writer(64 * 1024);
    writer.Open("tmp/output", "tmp/output.map");

    std::ifstream input("tmp/input");
    
    std::string tmp;
    while (std::getline(input, tmp)) {
        writer.Write(tmp.c_str(), tmp.length());
    }

	return 0;
}
