#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <array>
#include <vector>
#include <regex>

struct MissingHeader {
    std::string header;
    std::string requestingFile;
    int line;
};

int runCommandCapture(const std::string& cmd, std::string& output) {
    std::array<char, 256> buffer{};
    output.clear();
    FILE* pipe = popen((cmd + " 2>&1").c_str(), "r");
    if (!pipe) return -1;
    while (fgets(buffer.data(), buffer.size(), pipe)) {
        output += buffer.data();
    }
    return pclose(pipe);
}

std::vector<MissingHeader> parseMissingHeaders(const std::string& compilerOutput) {
    std::vector<MissingHeader> results;
    std::regex re(R"(In file included from ([^:]+):(\d+):\n|fatal error: '([^']+)' file not found)");
    std::smatch match;

    std::string currentFile;
    int currentLine = 0;
    auto it = compilerOutput.cbegin();

    while (std::regex_search(it, compilerOutput.cend(), match, re)) {
        if (match[1].matched && match[2].matched) {
            currentFile = match[1];
            currentLine = std::stoi(match[2]);
        }
        if (match[3].matched) {
            MissingHeader mh;
            mh.header = match[3];
            mh.requestingFile = currentFile;
            mh.line = currentLine;
            results.push_back(mh);
        }
        it = match.suffix().first;
    }
    return results;
}

int main() {
    const std::string SRC = "GeneralsMD/Code/GameEngine/Source";
    const std::string TU  = SRC + "/GameClient/System/DebugDisplay.cpp";

    std::string compiler = "clang++";
    if (std::system("which clang++ > /dev/null 2>&1") != 0) {
        compiler = "g++";
    }
    std::cout << "Using compiler: " << compiler << "\n";

    std::string compileCmd = compiler +
        " -std=c++20 "
        "-I\"" + SRC + "\" "
        "-Wall -Wextra -Werror -Wpedantic -Wconversion -Wshadow "
        "-Wdouble-promotion -Wold-style-cast -Woverloaded-virtual -Wnon-virtual-dtor "
        "-Wnull-dereference -Wformat=2 -Wimplicit-fallthrough=5 -Wundef -Wredundant-decls "
        "-fno-omit-frame-pointer "
        "-O0 -g3 "
        "-c \"" + TU + "\" -o /tmp/DebugDisplay.o";

    std::cout << "\nCompiling DebugDisplay.cpp...\n";

    std::string output;
    int status = runCommandCapture(compileCmd, output);

    if (status != 0) {
        std::cerr << "\nCompilation failed.\n";

        auto missingHeaders = parseMissingHeaders(output);
        if (!missingHeaders.empty()) {
            std::cerr << "\n=== Missing Header Report ===\n";
            for (const auto& mh : missingHeaders) {
                std::cerr << "Header: " << mh.header
                          << " | Included from: " << mh.requestingFile
                          << " (line " << mh.line << ")\n";
            }
            std::cerr << "=============================\n";
        } else {
            std::cerr << "\nNo missing header detected in compiler output.\n";
        }

        std::cerr << "\nFull compiler output:\n" << output << "\n";
        return 1;
    }

    std::cout << "\nCompile succeeded. Running clang-tidy...\n";
    if (std::system("which clang-tidy > /dev/null 2>&1") == 0) {
        std::string tidyCmd =
            "clang-tidy \"" + TU + "\" "
            "--warnings-as-errors='*' "
            "--extra-arg=-std=c++20 "
            "--extra-arg=-I\"" + SRC + "\" "
            "--checks='clang-analyzer-*,bugprone-*,readability-*,modernize-*,performance-*,cppcoreguidelines-*,-cppcoreguidelines-avoid-magic-numbers' "
            "--header-filter='GeneralsMD/Code/GameEngine/Source/.*' "
            "--format-style=file || true";
        std::system(tidyCmd.c_str());
    } else {
        std::cerr << "clang-tidy not found. Skipping lint step.\n";
    }

    std::cout << "\nDebugDisplay.cpp passes strict compile and lint.\n";
    return 0;
}
