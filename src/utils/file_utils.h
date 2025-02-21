#pragma once

#include <optional>
#include <string>
#include <vector>
namespace web {

std::optional<std::string> read_file(std::string_view path);

std::vector<std::string> index_public();

std::optional<std::string>
read_file_from_dir(std::string_view rel_path, std::string_view dir_name,
                   std::vector<std::string> dir_index);
} // namespace web
