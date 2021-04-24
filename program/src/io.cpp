#include "io.h"
#include "eval.h"
#include "utils.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <iterator>
#include <filesystem>
#include <stdexcept>
#include <argparse/argparse.hpp>

/**
 * Parse user inputs from command-line arguments.
 * 
 * @param argc arguments count
 * @param argv actual arguments
 * 
 * @return list of parsed arguments.
 */
Parameters read_arguments(int argc, char *argv[]) {
    argparse::ArgumentParser program("rombongan");

    program.add_argument("data")
        .help("Nama berkas text dari sumber data yang ingin digunakan")
        .required();

    program.add_argument("fps")
        .help("Jumlah frame per detik")
        .required()
        .action([](const std::string &value) { return std::stod(value); });

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
        .help("Direktori sumber data lintasan. Relatif terhadap direktori saat ini.")
        .default_value(
            (std::filesystem::current_path() / "data")
                .make_preferred()
                .string()
        )
        .action([](const std::string &value) {
            return (std::filesystem::current_path() / value)
                .make_preferred()
                .string();
        });

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
        throw std::invalid_argument(
            "Jumlah entitas minimum harus lebih besar dari 1."
        );
    }

    auto time_interval = program.get<int>("time_interval");

    if (time_interval < 2) {
        throw std::invalid_argument(
            "Durasi pergerakan bersama harus lebih besar dari 1."
        );
    }

    auto range = program.get<double>("range");

    if (range <= 0.0f) {
        throw std::invalid_argument(
            "Jarak entitas maksimum harus merupakan bilangan positif."
        );
    }

    auto cosine_similarity = program.get<double>("cosine_similarity");

    if (cosine_similarity < -1.0f || cosine_similarity > 1.0f) {
        throw std::invalid_argument(
            "Nilai cosine similarity yang valid berkisar antara [-1, 1]."
        );
    }

    auto fps = program.get<double>("fps");

    if (fps < 1.0f) {
        throw std::invalid_argument(
            "Nilai frame per second minimum yang dapat diproses adalah 1 frame per sekon"
        );
    }

    auto path = program.get<std::string>("--path");

    Parameters p;

    p.source = data;
    p.entity_count = entity_count;
    p.time_interval = time_interval;
    p.range = range;
    p.cosine_similarity = cosine_similarity;
    p.path = path;
    p.fps = fps;

    return p;
}

/**
 * Write rombongan identification result into a text file.
 * 
 * @param result rombongan identification result
 * @param params arguments passed to the program
 * @param score predicition score
 */
void write_result(
    const std::vector<Rombongan>& result,
    const Parameters& params,
    const Score& score
) {
    std::ofstream file_stream;

    std::filesystem::path dir_path = 
        (std::filesystem::current_path() / "data" / "output")
        .make_preferred();

    if (!std::filesystem::exists(dir_path)) {
        std::filesystem::create_directory(dir_path);
        std::filesystem::permissions(
            dir_path,
            std::filesystem::perms::owner_all |
            std::filesystem::perms::group_all |
            std::filesystem::perms::others_read,
            std::filesystem::perm_options::add
        );
    }

    auto now = get_current_time();
    auto output_filename = params.source + "-" + std::to_string(now);

    auto [precision, recall, f1_score] = score;

    auto output_filepath = (dir_path / output_filename)
        .make_preferred()
        .replace_extension(".txt");
    
    file_stream.open(
        output_filepath,
        std::ofstream::out | std::ofstream::trunc
    );

    if (file_stream.is_open()) {
        // write the parameters in csv-like format
        file_stream << "data, m, k, r, theta" << std::endl;
        file_stream << params.source << ", ";
        file_stream << params.entity_count << ", ";
        file_stream << params.time_interval << ", ";
        file_stream << params.range << ", ";
        file_stream << params.cosine_similarity;
        file_stream << std::endl << std::endl;

        std::streamsize ss = std::cout.precision();

        file_stream << "precision, recall, f1_score" << std::endl;
        file_stream << std::setprecision(2);
        file_stream << precision << ", ";
        file_stream << recall << ", ";
        file_stream << f1_score;
        file_stream << std::endl << std::endl;

        file_stream << std::setprecision(ss);

        // initialize csv-like header for identification result
        file_stream << "members, duration" << std::endl;

        for (Rombongan group: result) {
            std::vector<unsigned int> members = group.members;
            std::vector<std::pair<double, double> > duration = group.duration;

            for (size_t i = 0; i < members.size(); i++) {
                if (i > 0) {
                    file_stream << " ";
                }

                file_stream << members[i];
            }

            file_stream << ", ";

            for (size_t i = 0; i < duration.size(); i++) {
                if (i > 0) {
                    file_stream << " ";
                }

                file_stream << duration[i].first << "-" << duration[i].second;
            }

            file_stream << std::endl;
        }

        file_stream.close();

        std::cout << "Successfully written identification result to ";
        std::cout << output_filename << ".txt" << std::endl;
    } else {
        throw std::runtime_error(
            "Failed to open output stream due to lack of permissions."
        );
    }
}
