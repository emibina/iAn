#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#include <string>
#include <vector>
#include <map>

class CLIParser {
public:
    CLIParser(int argc, char* argv[]);
    bool has_option(const std::string& option) const;
    std::string get_option_value(const std::string& option) const;
    bool parse();

private:
    int argc;
    char** argv;
    std::map<std::string, std::string> options;
    std::vector<std::string> positional_args;
};

#endif // CLI_PARSER_H