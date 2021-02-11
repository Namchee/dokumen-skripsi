#include "io.h"
#include <iostream>
#include <filesystem>
#include <stdexcept>
#include <argparse/argparse.hpp>

/**
 * Parse command-line arguments.
 * 
 * @param argc arguments count
 * @param argv actual arguments
 * 
 * @return list of parsed arguments.
 */
Parameters parseArguments(int argc, char *argv[]) {
    argparse::ArgumentParser program("rombongan");

    program.add_argument("data")
        .help("Nama berkas text dari sumber data yang ingin digunakan")
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

    program.add_argument("-p", "--path")
        .help("Absolute path menuju direktori sumber data lintasan.")
        .default_value(std::string("./../data"));

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error &err) {
        std::cout << err.what() << "\n";
        std::cout << program;
        exit(0);
    }

    auto data = program.get<std::string>("data");
    auto entity_count = program.get<int>("entity_count");

    if (entity_count < 2) {
        throw std::invalid_argument("Jumlah entitas minimum harus lebih besar dari 1.");
    }

    auto time_interval = program.get<int>("time_interval");

    if (time_interval < 2) {
        throw std::invalid_argument("Durasi pergerakan bersama harus lebih besar dari 1.");
    }

    auto range = program.get<double>("range");

    if (range <= 0.0f) {
        throw std::invalid_argument("Jarak entitas maksimum harus merupakan bilangan positif.");
    }

    auto cosine_similarity = program.get<double>("cosine_similarity");

    if (cosine_similarity < -1.0f || cosine_similarity > 1.0f) {
        throw std::invalid_argument("Nilai cosine similarity yang valid berkisar antara [-1, 1].");
    }

    auto path = program.get<std::string>("--path");

    Parameters p;

    p.source = data;
    p.entity_count = entity_count;
    p.time_interval = time_interval;
    p.range = range;
    p.cosine_similarity = cosine_similarity;
    p.path = path;

    return p;
}
