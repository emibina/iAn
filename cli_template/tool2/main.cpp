
#include "../common/cli_base.h"
#include <algorithm>
#include <regex>

class Tool2 : public CLIBase {
public:
    Tool2() : CLIBase("tool2") {}
    
protected:
    void defineOptions() override {
        addOption("h", "help", "Show this help message", false);
        addOption("u", "uppercase", "Convert to uppercase", false);
        addOption("c", "count", "Count lines/words/characters", false);
        addOption("f", "filter", "Filter lines containing pattern", true);
        addOption("s", "sort", "Sort lines", false);
        addOption("v", "verbose", "Verbose output", false);
    }
    
    int execute() override {
        std::string input;
        
        // Always try to read from stdin first (for piping support)
        if (isInputPiped() || !getArguments().empty()) {
            if (isInputPiped()) {
                input = readFromStdin();
            } else {
                // If no pipe, treat first argument as input
                auto args = getArguments();
                if (!args.empty()) {
                    input = args[0] + "\n";
                }
            }
            
            if (input.empty()) {
                writeError("No input provided");
                return 1;
            }
            
            // Process the input
            std::vector<std::string> lines;
            std::istringstream iss(input);
            std::string line;
            
            while (std::getline(iss, line)) {
                if (!line.empty()) {
                    lines.push_back(line);
                }
            }
            
            if (hasOption("verbose")) {
                writeError("Processing " + std::to_string(lines.size()) + " lines");
            }
            
            // Apply filters
            if (hasOption("filter")) {
                std::string pattern = getOptionValue("filter");
                std::regex filterRegex(pattern);
                
                lines.erase(std::remove_if(lines.begin(), lines.end(),
                    [&](const std::string& line) {
                        return !std::regex_search(line, filterRegex);
                    }), lines.end());
                
                if (hasOption("verbose")) {
                    writeError("After filtering: " + std::to_string(lines.size()) + " lines");
                }
            }
            
            // Apply transformations
            if (hasOption("uppercase")) {
                for (auto& line : lines) {
                    std::transform(line.begin(), line.end(), line.begin(), ::toupper);
                }
            }
            
            if (hasOption("sort")) {
                std::sort(lines.begin(), lines.end());
            }
            
            // Output results
            if (hasOption("count")) {
                int totalChars = 0;
                int totalWords = 0;
                
                for (const auto& line : lines) {
                    totalChars += line.length();
                    // Simple word counting
                    std::istringstream wordStream(line);
                    std::string word;
                    while (wordStream >> word) {
                        totalWords++;
                    }
                }
                
                writeToStdout("Lines: " + std::to_string(lines.size()) + "\n");
                writeToStdout("Words: " + std::to_string(totalWords) + "\n");
                writeToStdout("Characters: " + std::to_string(totalChars) + "\n");
            } else {
                for (const auto& line : lines) {
                    writeToStdout(line + "\n");
                }
            }
        } else {
            writeError("No input provided. Use --help for usage information.");
            return 1;
        }
        
        return 0;
    }
};

int main(int argc, char* argv[]) {
    Tool2 tool;
    return tool.run(argc, argv);
}
