
#include "cli_base.h"
#include <algorithm>
#include <io.h>      // For Windows _isatty
#include <fcntl.h>   // For Windows file control

#ifdef _WIN32
    #include <windows.h>
    #include <io.h>
    #define isatty _isatty
    #define fileno _fileno
#else
    #include <unistd.h>
#endif

CLIBase::CLIBase(const std::string& toolName) : toolName(toolName) {}

int CLIBase::run(int argc, char* argv[]) {
    defineOptions();
    
    if (!parseArguments(argc, argv)) {
        return 1;
    }
    
    if (hasOption("help") || hasOption("h")) {
        showHelp();
        return 0;
    }
    
    return execute();
}

void CLIBase::addOption(const std::string& shortOpt, const std::string& longOpt, 
                       const std::string& description, bool hasValue) {
    Option opt;
    opt.shortOpt = shortOpt;
    opt.longOpt = longOpt;
    opt.description = description;
    opt.hasValue = hasValue;
    opt.present = false;
    
    size_t index = options.size();
    options.push_back(opt);
    
    if (!shortOpt.empty()) {
        optionMap[shortOpt] = index;
    }
    if (!longOpt.empty()) {
        optionMap[longOpt] = index;
    }
}

bool CLIBase::hasOption(const std::string& option) const {
    auto it = optionMap.find(option);
    return it != optionMap.end() && options[it->second].present;
}

std::string CLIBase::getOptionValue(const std::string& option) const {
    auto it = optionMap.find(option);
    if (it != optionMap.end() && options[it->second].present) {
        return options[it->second].value;
    }
    return "";
}

bool CLIBase::parseArguments(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        
        if (arg.starts_with("--")) {
            // Long option
            std::string optName = arg.substr(2);
            std::string value;
            
            size_t eqPos = optName.find('=');
            if (eqPos != std::string::npos) {
                value = optName.substr(eqPos + 1);
                optName = optName.substr(0, eqPos);
            }
            
            auto it = optionMap.find(optName);
            if (it == optionMap.end()) {
                writeError("Unknown option: --" + optName);
                return false;
            }
            
            Option& opt = options[it->second];
            opt.present = true;
            
            if (opt.hasValue) {
                if (value.empty() && i + 1 < argc && !std::string(argv[i + 1]).starts_with("-")) {
                    opt.value = argv[++i];
                } else if (!value.empty()) {
                    opt.value = value;
                } else {
                    writeError("Option --" + optName + " requires a value");
                    return false;
                }
            }
        } else if (arg.starts_with("-") && arg.length() > 1) {
            // Short option(s)
            for (size_t j = 1; j < arg.length(); ++j) {
                std::string optName(1, arg[j]);
                
                auto it = optionMap.find(optName);
                if (it == optionMap.end()) {
                    writeError("Unknown option: -" + optName);
                    return false;
                }
                
                Option& opt = options[it->second];
                opt.present = true;
                
                if (opt.hasValue) {
                    if (j + 1 < arg.length()) {
                        // Value is attached: -ovalue
                        opt.value = arg.substr(j + 1);
                        break;
                    } else if (i + 1 < argc && !std::string(argv[i + 1]).starts_with("-")) {
                        // Value is next argument: -o value
                        opt.value = argv[++i];
                        break;
                    } else {
                        writeError("Option -" + optName + " requires a value");
                        return false;
                    }
                }
            }
        } else {
            // Positional argument
            arguments.push_back(arg);
        }
    }
    
    return true;
}

void CLIBase::showHelp() const {
    std::cout << "Usage: " << toolName << " [OPTIONS] [ARGUMENTS]\n\n";
    std::cout << "Options:\n";
    
    for (const auto& opt : options) {
        std::cout << "  ";
        
        if (!opt.shortOpt.empty()) {
            std::cout << "-" << opt.shortOpt;
            if (!opt.longOpt.empty()) {
                std::cout << ", ";
            }
        }
        
        if (!opt.longOpt.empty()) {
            std::cout << "--" << opt.longOpt;
        }
        
        if (opt.hasValue) {
            std::cout << " VALUE";
        }
        
        std::cout << "\n    " << opt.description << "\n\n";
    }
    
    std::cout << "This tool supports piping:\n";
    std::cout << "  " << toolName << " | other-tool    # Pipe output to another tool\n";
    std::cout << "  other-tool | " << toolName << "    # Read input from another tool\n";
    std::cout << "  " << toolName << " > output.txt   # Redirect output to file\n\n";
}

std::string CLIBase::readFromStdin() {
    std::ostringstream buffer;
    std::string line;
    
    while (std::getline(std::cin, line)) {
        buffer << line << "\n";
    }
    
    return buffer.str();
}

void CLIBase::writeToStdout(const std::string& output) {
    std::cout << output;
    std::cout.flush();  // Ensure output is flushed for piping
}

void CLIBase::writeError(const std::string& error) {
    std::cerr << toolName << ": " << error << std::endl;
}

bool CLIBase::isInputPiped() const {
#ifdef _WIN32
    return !_isatty(_fileno(stdin));
#else
    return !isatty(fileno(stdin));
#endif
}

bool CLIBase::isOutputPiped() const {
#ifdef _WIN32
    return !_isatty(_fileno(stdout));
#else
    return !isatty(fileno(stdout));
#endif
}
