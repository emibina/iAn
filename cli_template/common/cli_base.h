
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <map>

class CLIBase
{
public:
	CLIBase(const std::string& toolName);
	virtual ~CLIBase() = default;

	// Main entry point for the tool
	int run(int argc, char* argv[]);

protected:
	// Override these in derived classes
	virtual void defineOptions() = 0;
	virtual int execute() = 0;
	virtual void showHelp() const;

	// Utility methods for derived classes
	void addOption(const std::string& shortOpt, const std::string& longOpt,
		const std::string& description, bool hasValue);
	bool hasOption(const std::string& option) const;
	std::string getOptionValue(const std::string& option) const;
	std::vector<std::string> getArguments() const { return arguments; }

	// Input/Output utilities
	std::string readFromStdin();
	void writeToStdout(const std::string& output);
	void writeError(const std::string& error);

	// Check if input is coming from pipe
	bool isInputPiped() const;
	bool isOutputPiped() const;

private:
	struct Option
	{
		std::string shortOpt;
		std::string longOpt;
		std::string description;
		bool hasValue;
		std::string value;
		bool present;
	};

	std::string toolName;
	std::vector<Option> options;
	std::vector<std::string> arguments;
	std::map<std::string, size_t> optionMap;

	bool parseArguments(int argc, char* argv[]);
};
