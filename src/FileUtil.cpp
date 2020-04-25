#include "FileUtil.h"

#include <fstream>
#include <iterator>

#include "Debug.h"

using namespace std;

namespace NT {

string FileUtil::getExtension(const string& s) {
    return s.substr(s.find_first_of('.') + 1);
}

string FileUtil::getFileName(const string& s) {
    // Remove directory if present.
    // Do this before extension removal incase directory has a period character.
    const size_t last_slash_idx = s.find_last_of("\\/");
    if (string::npos != last_slash_idx) {
        return s.substr(last_slash_idx + 1);
    }

    return ("");
}

bool FileUtil::exists(const string& fileName) {
    ifstream infile(fileName);
    return infile.good();
}

string FileUtil::readFile(const string& filename) {
    string buffer;
    ifstream file(filename, ios::ate | ios::binary);

    if (!file.is_open()) {
        LOG(error) << "failed to open file:" << filename;
        return buffer;
    }

    size_t fileSize = (size_t)file.tellg();
    buffer.resize(fileSize);
    file.seekg(0);
    file.read(&buffer[0], fileSize);
    file.close();

    return buffer;
}

bool FileUtil::loadFile(const string& filename, vector<unsigned char>& data) {
    // open the file:
    ifstream file(filename, ios::binary);
    if (!file.is_open()) {
        LOG(error) << "fail to open file: " << filename;
        return false;
    }
    // Stop eating new lines in binary mode!!!
    file.unsetf(ios::skipws);
    // get its size:
    streampos fileSize;

    file.seekg(0, ios::end);
    fileSize = file.tellg();
    file.seekg(0, ios::beg);

    // reserve capacity
    data.reserve(fileSize);
    // read the data:
    data.insert(data.begin(), istream_iterator<unsigned char>(file), istream_iterator<unsigned char>());

    return true;
}

string FileUtil::join(const string& a, const string& b) {
    string res;
    if (a.back() != separator()) {
        res = a + separator() + b;
    } else {
        res = a + b;
    }

    return res;
}

}  // namespace NT
