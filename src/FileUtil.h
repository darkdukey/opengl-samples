#pragma once

#include <vector>

namespace NT {

namespace FileUtil {

std::string getFileName(const std::string& path);
std::string getExtension(const std::string& path);
bool exists(const std::string& fileName);
std::string readFile(const std::string& filename);
bool loadFile(const std::string& filename, std::vector<unsigned char>& data);
}  // namespace FileUtil

}  // namespace NT
