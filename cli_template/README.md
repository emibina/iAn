
# CLI Tools Template

A template for creating chainable C++ command-line tools for Windows PowerShell.

## Features

- **Proper pipe support**: Tools can read from stdin and write to stdout
- **Option parsing**: Support for short (-h) and long (--help) options
- **Chainable**: Use `tool1 | tool2` to chain tools together
- **Windows compatible**: Works with PowerShell redirection (`>`, `|`)
- **Extensible**: Easy to add new tools using the base class

## Building

```bash
# Using the build script
build.bat

# Or manually
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
```

## Usage Examples

```powershell
# Basic usage
.\tool1.exe --number 3
.\tool2.exe --help

# Piping between tools
.\tool1.exe --number 5 | .\tool2.exe --uppercase

# Filtering and counting
.\tool1.exe --number 10 | .\tool2.exe --filter "Line [2-4]" --count

# Save to file
.\tool1.exe --number 5 | .\tool2.exe --sort > output.txt

# Complex chain
.\tool1.exe --prefix "Data" --number 8 | .\tool2.exe --filter "Data [1-3]" --uppercase | .\tool2.exe --sort
```

## Adding New Tools

1. Create a new directory: `mkdir tool3`
2. Create `tool3/main.cpp` inheriting from `CLIBase`
3. Add the executable to `CMakeLists.txt`
4. Implement `defineOptions()` and `execute()` methods

## Architecture

- `CLIBase`: Base class handling argument parsing, help generation, and I/O
- Tools inherit from `CLIBase` and implement specific functionality
- Proper stdin/stdout handling enables seamless piping
- Cross-platform compatibility (Windows focus, but portable)