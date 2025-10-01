#include <iostream>
#include <fstream>
#include <string>
#include "cli_parser.h"

// The core logic of your tool goes here
void run_tool(const std::string& input, const std::string& output_file) {
    std::string result = "Processed: " + input;
    
    if (!output_file.empty()) {
        std::ofstream outfile(output_file);
        if (outfile.is_open()) {
            outfile << result << std::endl;
            std::cout << "Results saved to " << output_file << std::endl;
            outfile.close();
        } else {
            std::cerr << "Error: Could not open file " << output_file << " for writing." << std::endl;
        }
    } else {
        std::cout << result << std::endl;
    }
}

int main(int argc, char* argv[]) {
    CLIParser parser(argc, argv);
    if (!parser.parse()) {
        std::cerr << "Error parsing command line arguments." << std::endl;
        return 1;
    }

    // Help message
    if (parser.has_option("h") || parser.has_option("help")) {
        std::cout << "Usage: ./tool1 -i <input> [-o <output_file>]" << std::endl;
        return 0;
    }

    // Get input and output file from arguments
    std::string input = parser.get_option_value("i");
    std::string output_file = parser.get_option_value("o");

    if (input.empty()) {
        std::cerr << "Error: -i (input) is a required argument." << std::endl;
        return 1;
    }

    run_tool(input, output_file);

    return 0;
}