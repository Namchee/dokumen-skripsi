#include "io.h"
#include <filesystem>
#include <cassert>

int main(int argc, char *argv[]) {
    Parameters params = read_arguments(argc, argv);

    assert(params.source == "seq_eth");
    assert(params.entity_count == 3);
    assert(params.time_interval == 10);
    assert(params.range == 0.15);
    assert(params.cosine_similarity == 1.0);
    assert(params.path == (std::filesystem::current_path() / "abc").string());

    return 0;
}