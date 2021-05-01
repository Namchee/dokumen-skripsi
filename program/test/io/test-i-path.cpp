#include "io.h"
#include <filesystem>
#include <cassert>

int main(int argc, char *argv[]) {
    Arguments params = read_arguments(argc, argv);

    assert(params.source == "seq_eth");
    assert(params.entities == 3);
    assert(params.interval == 10);
    assert(params.range == 0.15);
    assert(params.angle == 1.0);
    assert(params.path == (std::filesystem::current_path() / "abc").string());

    return 0;
}