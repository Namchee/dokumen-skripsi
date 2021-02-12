#include "io.h"
#include <iostream>

int main(int argc, char *argv[]) {
    Parameters args = parseArguments(argc, argv);

    std::cout << args.path << std::endl;

    return 0;
}