# SAPCompiler (sapcmp)

## About
Simple CLI to compile a custom assembly language for a Ben Eater inspired 8-bit SAP (Simple As Possible) CPU. 

## Usage
```
sapcmp [--input=IN_FILE] [--output=OUT_FILE] [--base=ARG_BASE] [--display] [--verbose=V_LEVEL] [--help]
```

| Command           | Description        |
|:------------------:| ---------------------------------------- |
|  `-i`, `--input [IN_FILE]  ` | Input file |
|  `-o`, `--output [OUT_FILE ` | Output file (default: sapcmp_output.txt) |
|  `-b`, `--base [ARG_BASE]   ` | Infile argument base (default: 2) |
|  `-d`, `--display    ` | Display conversion |
|  `-v`, `--verbose [V_LEVEL]` | Verbose (0,1) (default: 0) |
|  `-h`, `--help       ` | Print usage |


Input file must be formatted as follows
```
[KEYWORD_0] [ARG_0]
[KEYWORD_1] [ARG_1]
...
[KEYWORD_N] [ARG_N]
```
where `N` is the maximum number of words the processors memory can store.

## Examples
*Example files can be found in SAPCompiler/examples*

### Example 1
Compile `testBase2-1.txt` to `sapcmp_output.txt` with no display.
```
$ sapcmp -i testBase2-1.txt
```

### Example 2
Compile `testBase2-2.txt` to `customOutput.txt` with result displayed.
```
$ sapcmp -i testBase2-2.txt -o customOutput.txt -d
```

### Example 3
Compile testBase16.txt to default output file, no display.
```
$ sapcmp -i testBase16.txt -b 16
```

### Example 4
Compile testBase10.txt to default output file with display.
```
$ sapcmp -i testBase10.txt -db 10
```

## Setup
Known to compile sucessfully with `g++` version 8.1.0. Likely works with other c++ compilers.

Clone repository and compile using:
```
g++ src/*.cpp -o build/sapcmp.exe
```

Add `/build` to system path.

## Contributors
Ben Graham, <ben.n.graham@icloud.com>
