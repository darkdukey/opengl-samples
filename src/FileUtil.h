#pragma once

#include <vector>
#include <string>

namespace NT {

namespace FileUtil {

std::string getFileName(const std::string& path);
std::string getExtension(const std::string& path);
bool exists(const std::string& fileName);
std::string readFile(const std::string& filename);
bool loadFile(const std::string& filename, std::vector<unsigned char>& data);
std::string join(const std::string& a, const std::string& b);
inline char separator() {
#ifdef _WIN32
    return '\\';
#else
    return '/';
#endif
}
}  // namespace FileUtil

}  // namespace NT
