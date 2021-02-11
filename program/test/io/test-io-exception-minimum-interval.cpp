#include "io.h"
#include <cassert>
#include <iostream>

int main(int argc, char *argv[]) {
    try {
        Parameters params = parseArguments(argc, argv);

        throw std::logic_error("Should throw an error since time_interval is less than 2.");
    } catch(std::invalid_argument const &err) {
        assert(err.what() == std::string("Durasi pergerakan bersama harus lebih besar dari 1."));
    }

    return 0;
}