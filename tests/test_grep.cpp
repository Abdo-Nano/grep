#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_string.hpp>
#include <catch2/matchers/catch_matchers_vector.hpp>
#include <sstream>
#include <fstream>
#include <filesystem>
#include "../include/grep.h"

// using namespace Catch::Matchers;

TEST_CASE("highlightFoundPattern function", "[highlight]") {
    SECTION("Highlights single occurrence") {
        std::string result = grep::highlightFoundPattern("hello world", "world");
        REQUIRE(result.find("\033[31mworld\033[0m") != std::string::npos);
        REQUIRE(result.find("hello ") != std::string::npos);
    }
}

TEST_CASE("isPatternFound function", "[matching]") {
    SECTION("Finds exact matches") {
        REQUIRE(grep::isPatternFound("hello world", "world"));
        REQUIRE_FALSE(grep::isPatternFound("hello world", "nonexistent"));
    }
}

TEST_CASE("isPatternFoundCaseInsensitive function", "[matching][case_insensitive]") {
    SECTION("Finds case insensitive matches") {
        REQUIRE(grep::isPatternFoundCaseInsensitive("Hello World", "hello"));
        REQUIRE_FALSE(grep::isPatternFoundCaseInsensitive("hello world", "nonexistent"));
    }
}

TEST_CASE("printLines function", "[output]") {
    SECTION("Prints multiple lines correctly") {
        std::vector<std::string> lines = {"line1", "line2", "line3"};
        std::stringstream output;

        grep::printLines(lines, output);

        REQUIRE(output.str() == "line1\nline2\nline3\n");
    }

    SECTION("Handles empty vector") {
        std::vector<std::string> lines;
        std::stringstream output;

        grep::printLines(lines, output);

        REQUIRE(output.str().empty());
    }
}

TEST_CASE("openFile function", "[file][io]") {
    SECTION("Successfully opens existing file") {
        const std::string test_filename = "file.txt";

        {
            std::ofstream test_file(test_filename);
            test_file << "test content\n";
        }

        std::filesystem::path path{test_filename};
        auto result = grep::openFile(path);

        REQUIRE(result.has_value());
        REQUIRE(result.value().is_open());

        std::remove(test_filename.c_str());
    }
}

TEST_CASE("grep function integration", "[grep][integration]") {
    SECTION("Finds and highlights matches in file") {
        const std::string test_filename = "file.txt";

        {
            std::ofstream test_file(test_filename);
            test_file << "hello world\n";
            test_file << "goodbye world\n";
            test_file << "hello again\n";
        }

        std::stringstream output;
        std::filesystem::path path{test_filename};

        auto old_cout_buf = std::cout.rdbuf(output.rdbuf());
        grep::grep(path, "hello");
        std::cout.rdbuf(old_cout_buf);

        std::string result = output.str();
        REQUIRE(result.find("hello world") != std::string::npos);
        REQUIRE(result.find("hello again") != std::string::npos);
        REQUIRE(result.find("goodbye world") == std::string::npos);

        std::remove(test_filename.c_str());
    }
}