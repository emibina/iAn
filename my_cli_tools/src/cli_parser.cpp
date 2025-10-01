#include "cli_parser.h"
#include <iostream>

CLIParser::CLIParser(int argc, char* argv[]) : argc(argc), argv(argv) {}

bool CLIParser::parse() {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg.size() > 1 && arg.substr(0, 1) == "-") {
            std::string option_name = arg.substr(1);
            if (i + 1 < argc && argv[i + 1][0] != '-') {
                options[option_name] = argv[i + 1];
                i++; // Skip the next argument
            } else {
                options[option_name] = ""; // Flag option
            }
        } else {
            positional_args.push_back(arg);
        }
    }
    return true;
}

bool CLIParser::has_option(const std::string& option) const {
    return options.count(option);
}

std::string CLIParser::get_option_value(const std::string& option) const {
    if (has_option(option)) {
        return options.at(option);
    }
    return "";
}