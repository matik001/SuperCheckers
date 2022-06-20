#ifndef CHECKERSAI_HELPERS_H
#define CHECKERSAI_HELPERS_H

#include <cstdlib>
#include <fstream>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

const long long INF_PATH = (long long)1e18;




fs::path create_temporary_directory(unsigned long long max_tries = 1000);
std::string write_to_temp(std::string filename, const void *data, int size);

std::string replace_all(std::string str, const std::string& from, const std::string& to);


#endif //CHECKERSAI_HELPERS_H
