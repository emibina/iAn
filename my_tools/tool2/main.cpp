#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#if defined(_WIN32) || defined(_WIN64)
#include <io.h>
#define isatty _isatty
#define fileno _fileno
#else
#include <unistd.h>
#endif

std::vector<std::string> split(const std::string& input, char delimiter = ' ') {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string item;
    while (std::getline(ss, item, delimiter)) {
        if (!item.empty()) tokens.push_back(item);
    }
    return tokens;
}

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv + 1, argv + argc);

    bool hasPipeInput = !isatty(fileno(stdin));
    std::vector<std::string> pipedInput;
    if (hasPipeInput) {
        std::string line;
        while (std::getline(std::cin, line)) {
            if (!line.empty()) pipedInput.push_back(line);
        }
    }

    if (!args.empty()) {
        std::cout << "[tool] Arguments:\n";
        for (auto& a : args) std::cout << " - " << a << "\n";
    }

    if (!pipedInput.empty()) {
        std::cout << "[tool] Piped input:\n";
        for (auto& l : pipedInput) std::cout << " > " << l << "\n";
    }

	std::cout << "tool2";

    return 0;
}
