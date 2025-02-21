#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

namespace web {

std::optional<std::string> read_file(std::string_view path) {

    std::ifstream file(path.data(), std::ios::ate); // ate moves pointer to end

    if (!file.is_open()) {
        return std::nullopt; // no file found
    }

    // Get filesize
    auto file_size = file.tellg(); // read file size with position of pointer
    std::string content(file_size, '\0'); // allocate needed space

    file.seekg(0); // move pointer to beginning

    file.read(content.data(), file_size); // write to cstring used by
                                          // std::string
    return content;
}

std::vector<std::string> index_public() {
    std::vector<std::string> files;
    std::string public_dir = "public";

    if (!std::filesystem::exists(public_dir) ||
        !std::filesystem::is_directory(public_dir)) {
        throw std::runtime_error("Directory 'public/' does not exist in "
                                 "current directory to serve files from.");
    }

    for (const auto &entry :
         std::filesystem::recursive_directory_iterator(public_dir)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().string());
        }
    }

    return files;
}

std::optional<std::string>
read_file_from_dir(std::string_view rel_path, std::string_view dir_name,
                   std::vector<std::string> dir_index) {

    std::string path = std::string(dir_name) + "/" + std::string(rel_path);

    auto file_it = std::find(dir_index.begin(), dir_index.end(), path);

    if (file_it == dir_index.end()) {
        return std::nullopt;
    }

    return read_file(path);
}

} // namespace web
