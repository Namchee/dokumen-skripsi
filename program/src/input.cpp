#include "input.h"
#include <iostream>
#include <filesystem>
#include <argparse/argparse.hpp>

/**
 * Parse command-line arguments.
 * 
 * @param argc arguments count
 * @param argv actual arguments
 * 
 * @return list of parsed arguments.
 */
Options parseArguments(int argc, char *argv[]) {
    argparse::ArgumentParser program("rombongan");

    program.add_argument("data")
        .help("Nama berkas dari sumber data yang ingin digunakan")
        .required();

    program.add_argument("entity_count")
        .help("Jumlah entitas minimum anggota rombongan")
        .required()
        .action([](const std::string &value) { return std::stoi(value); });
    
    program.add_argument("time_interval")
        .help("Interval waktu minimum pergerakan bersama secara konsekutif")
        .required()
        .action([](const std::string &value) { return std::stoi(value); });

    program.add_argument("range")
        .help("Jarak dynamic time warping maksimum antar anggota rombongan")
        .required()
        .action([](const std::string &value) { return std::stod(value); });

    program.add_argument("cosine_similarity")
        .help("Nilai cosine similarity minimum antar anggota rombongan")
        .required()
        .action([](const std::string &value) { return std::stod(value); });

    program.add_argument("path")
        .help("Direktori sumber data lintasan, relatif dari direktori saat ini")
        .default_value("./../data")
        .action([](const std::string &value) {
            return std::filesystem::current_path().string() + value;
        }
    );

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error &err) {
        std::cout << err.what() << "\n";
        std::cout << program;
        exit(0);
    }

    auto data = program.get<std::string>("data");
    auto entity_count = program.get<int>("entity_count");
    auto time_interval = program.get<int>("time_interval");
    auto range = program.get<double>("range");
    auto cosine_similarity = program.get<double>("cosine_similarity");
    auto path = program.get<std::string>("path");

    return {
        data,
        entity_count,
        time_interval,
        range,
        cosine_similarity,
        path
    };
}
