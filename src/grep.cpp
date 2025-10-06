//
// Created by abdo on 9/23/25.
//

#include "../include/grep.h"
#include <iostream>
#include <ostream>
#include <string>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <fstream>
#include <optional>


namespace grep {

    std::string highlightFoundPattern(const std::string &text, const std::string &sub) {
        std::string result;
        size_t pos = 0, found;

        const std::string red = "\033[31m";
        const std::string reset = "\033[0m";

        while ((found = text.find(sub, pos)) != std::string::npos) {
            result += text.substr(pos, found - pos);
            result += red + sub + reset;
            pos = found + sub.size();
        }
        result += text.substr(pos);
        return result;
    }

    bool isPatternFound(const std::string& line , const std::string& pattern) {
        return line.find(pattern) != std::string::npos;
    }

    void printLines(const std::vector<std::string>& lines, std::ostream& output) {
        for (const std::string& line : lines)
            std::cout << line << "\n";
    }

    bool isPatternFoundCaseInsensitive(const std::string& line , const std::string& pattern) {
        auto it = std::search(
            line.begin() , line.end(),
            pattern.begin() , pattern.end(),
            [] (char a , char b) {return std::tolower(a) == std::tolower(b);}
            );

        return it != line.end();
    }

    std::optional<std::ifstream> openFile(const std::filesystem::path& path) {
        std::ifstream file {path};
        if (!file.is_open())
            return std::nullopt;
        return std::move(file);
    }

   void grep(const std::filesystem::path& path, const std::string& pattern){
        if (auto file = openFile(path)) {
            std::string line;
            std::vector<std::string> lines;

            while (getline(file.value(), line)) {
                if (isPatternFound(line , pattern)) {
                    std::string result = highlightFoundPattern(line , pattern);
                    lines.push_back(result);
                }
            }
            printLines(lines);
        }
    }
}