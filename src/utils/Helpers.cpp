#include <random>
#include <experimental/filesystem>
#include <fstream>

namespace fs = std::experimental::filesystem;


fs::path create_temporary_directory(unsigned long long max_tries = 1000){
    auto tmp_dir = fs::temp_directory_path();
    unsigned long long i = 0;
    std::random_device dev;
    std::mt19937 prng(dev());
    std::uniform_int_distribution<uint64_t> rand(0);
    fs::path path;
    while (true) {
        std::stringstream ss;
        ss << std::hex << rand(prng);
        path = tmp_dir / ss.str();
        // true if the directory was created.
        if (fs::create_directory(path)) {
            break;
        }
        if (i == max_tries) {
            throw std::runtime_error("could not find non-existing directory");
        }
        i++;
    }
    return path;
}

std::string write_to_temp(std::string filename, const void *data, int size){
    auto path = (create_temporary_directory() / fs::path(filename)).string();

    std::ofstream stream(path, std::ios::binary);
    stream.write((const char *)data, size);
    stream.close();

    return path;
}

std::string replace_all(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}
