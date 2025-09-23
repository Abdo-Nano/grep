#include <iostream>
#include "../include/grep.h"



/* ==== Whay I learned from this project ====
 *
- RAII resource management (automatic file closing)

- Efficient string searching using std::string::find

- Comprehensive error handling

- Configurable options (case Insensitive, line numbers, etc.)

- Recursive directory search

- Proper const correctness and modern C++ features

- Comprehensive Catch2 test suite

- Better command line interface

 */


int main(int argc , char* argv[]) {
    if (argc < 2) {
        std::cerr << "the arguments number isn't enough." << "\n";
    }
    if (argc < 3) {
        std::cerr << "usage: " << argv[0] << " <filename> <pattern>" << std::endl;
        std::cerr << "example: " << argv[0] << " file.txt \"search text\"" << std::endl;
        return 1;
    }

    std::filesystem::path path{argv[1]};
    if (!std::filesystem::exists(path)) {
        std::cerr << "the path is not found" << "\n";
        return 0;
    }
    if (std::filesystem::is_directory(path)) {
        std::cerr << "this is not a directory" << "\n";
        return 0;
    }
    std::string pattern {argv[2]};
    grep::grep(path , pattern);
    return 0;
}