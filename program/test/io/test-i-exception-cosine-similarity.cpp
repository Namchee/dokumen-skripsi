#include "io.h"
#include <cassert>
#include <stdexcept>

int main(int argc, char *argv[]) {
    try {
        Arguments params = read_arguments(argc, argv);

        throw std::logic_error("Should throw an error since cosine_similarity is out of range.");
    } catch(std::invalid_argument const &err) {
        assert(err.what() == std::string("Nilai cosine similarity yang valid berkisar antara [-1, 1]."));
    }

    return 0;
}