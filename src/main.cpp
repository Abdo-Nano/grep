#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <optional>



std::string highlightFoundPattern(const std::string &text, const std::string &sub) {
    std::string result;
    size_t pos = 0, found;

    // ANSI escape codes
    const std::string red = "\033[31m";   // red text
    const std::string reset = "\033[0m";  // reset to default

    while ((found = text.find(sub, pos)) != std::string::npos) {
        result += text.substr(pos, found - pos);   // normal text
        result += red + sub + reset;               // highlighted substring
        pos = found + sub.size();
    }
    result += text.substr(pos); // remaining text
    return result;
}


bool isPatternFound(const std::string& line , const std::string& pattern) {
    for (int i = 0 ;i < (int) line.size();) {
        if (line[i] == pattern[0]) {
            int j = 0;
            while ( j < (int) pattern.size() && line[i] == pattern[j]) {
                i++;
                j++;
            }
            if (j == pattern.size())
                return true;
        } else
            i++;
    }
    return false;
}

void printLines(const std::vector<std::string>& lines) {
    for (const std::string& line : lines)
        std::cout << line << std::endl;
}

std::optional<std::ifstream> openFile(std::filesystem::path& path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        return std::nullopt;
    }
    return file;
}

void grep(std::filesystem::path& path, const std::string& pattern) {
    std::optional<std::ifstream> file = openFile(path);

    std::string line;
    std::vector<std::string> lines;

    while (getline(file.value(), line)) {
        if (isPatternFound(line , pattern)) {
            std::string result = highlightFoundPattern(line , pattern);
            lines.push_back(result);
        }
    }

    printLines(lines);
    file->close();
}


int main(int argc , char* argv[]) {
    if (argc < 2) {
        std::cerr << "The arguments number isn't enough." << std::endl;
    } else {
        std::filesystem::path path{argv[1]};
        grep(path, argv[2]);
    }
    return 0;
}