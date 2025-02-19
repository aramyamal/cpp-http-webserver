#include <fstream>
#include <optional>
#include <string>

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

} // namespace web
