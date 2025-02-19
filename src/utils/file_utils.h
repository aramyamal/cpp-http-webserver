#pragma once
#include <optional>
#include <string>
namespace web {

std::optional<std::string> read_file(std::string_view path);

} // namespace web
