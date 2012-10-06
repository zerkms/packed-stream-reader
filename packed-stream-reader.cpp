#include <iostream>

#include "writer.hpp"

int main(int argc, char** argv)
{
    psr::Writer writer("tmp/output", "tmp/output.map", 64 * 1024);

    writer.Write("tmp/input", 9);

	return 0;
}
