# Console Program: Command Reader

## Description

This is a simple console program written in C++ that reads a series of commands from a text file and displays each command on the console. The program processes each line in the input file as a separate command and outputs it to the console.

## Features

- Reads commands from a text file.
- Outputs each command line to the console.
- Includes error handling for file opening issues.

## Usage

1. **Input File**: Prepare a text file (e.g., `input.txt`) containing commands. Each line in the file should represent a single command.

Example of `input.txt`:
```
command1
command2
command3
```
2. **Running the Program**: Run the executable from the command line and pass the path of the text file as an argument.

## Build Instructions
Use CMake to build:
- Generate build files:
```bash
mkdir build
cd build
cmake ..
```
- Compile:
```bash
cmake --build .
```
## Software High Level Design
### Class Diagram
![HighLevelClassDiagram](https://github.com/user-attachments/assets/66adee1e-b378-4242-99a4-ca3dd83c9c47)

### Sequence Diagram
![HighLevelSequenceDiagram](https://github.com/user-attachments/assets/fa9e0b0a-9e7e-4a0c-a0c0-fe4d9fb19851)
