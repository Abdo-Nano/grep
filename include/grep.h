//
// Created by abdo on 9/23/25.
//

#ifndef GREPCLI_GREP_H
#define GREPCLI_GREP_H
#include <string>
#include <vector>
#include <filesystem>
#include <optional>
#include <iostream>



namespace grep {
    std::string highlightFoundPattern(const std::string &text, const std::string &sub);
    bool isPatternFound(const std::string& line, const std::string& pattern);
    bool isPatternFoundCaseInsensitive(const std::string& line , const std::string& pattern);
    std::optional<std::ifstream> openFile(const std::filesystem::path& path);
    void printLines(const std::vector<std::string>& lines, std::ostream& output = std::cout);
    void grep(const std::filesystem::path& path, const std::string& pattern);
}


#endif //GREPCLI_GREP_H