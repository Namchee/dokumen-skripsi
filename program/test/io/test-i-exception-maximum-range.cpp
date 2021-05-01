#include "io.h"
#include <cassert>
#include <stdexcept>

int main(int argc, char *argv[]) {
    try {
        Arguments params = read_arguments(argc, argv);

        throw std::logic_error("Should throw an error since range is negative.");
    } catch(std::invalid_argument const &err) {
        assert(err.what() == std::string("Jarak entitas maksimum harus merupakan bilangan positif."));
    }

    return 0;
}