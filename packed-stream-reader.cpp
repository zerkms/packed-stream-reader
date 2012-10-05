#include <iostream>

#include "writer.hpp"

int main(int argc, char** argv)
{
    psr::Writer writer(64 * 1024);

    writer.Write("tmp/input", "tmp/output", "tmp/output.map");

	return 0;
}
