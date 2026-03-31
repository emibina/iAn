
#include "../common/cli_base.h"
#include <random>

class Tool1 : public CLIBase {
public:
    Tool1() : CLIBase("tool1") {}
    
protected:
    void defineOptions() override {
        addOption("h", "help", "Show this help message", false);
        addOption("n", "number", "Number of lines to generate", true);
        addOption("p", "prefix", "Prefix for each line", true);
        addOption("v", "verbose", "Verbose output", false);
    }
    
    int execute() override {
        int numLines = 5; // default
        std::string prefix = "Line";
        
        if (hasOption("number")) {
            try {
                numLines = std::stoi(getOptionValue("number"));
            } catch (const std::exception&) {
                writeError("Invalid number specified");
                return 1;
            }
        }
        
        if (hasOption("prefix")) {
            prefix = getOptionValue("prefix");
        }
        
        if (hasOption("verbose")) {
            writeError("Generating " + std::to_string(numLines) + " lines with prefix '" + prefix + "'");
        }
        
        // Check if we should read from stdin
        if (isInputPiped()) {
            std::string input = readFromStdin();
            if (hasOption("verbose")) {
                writeError("Processing input from pipe: " + std::to_string(input.length()) + " characters");
            }
            
            // Process the input (simple example: add prefix to each line)
            std::istringstream iss(input);
            std::string line;
            while (std::getline(iss, line)) {
                if (!line.empty()) {
                    writeToStdout(prefix + ": " + line + "\n");
                }
            }
        } else {
            // Generate new content
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dis(1000, 9999);
            
            for (int i = 1; i <= numLines; ++i) {
                std::string output = prefix + " " + std::to_string(i) + 
                                   " (ID: " + std::to_string(dis(gen)) + ")\n";
                writeToStdout(output);
            }
        }
        
        return 0;
    }
};

int main(int argc, char* argv[]) {
    Tool1 tool;
    return tool.run(argc, argv);
}
