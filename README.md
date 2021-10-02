## VtfParser

This repository is a program that I write to transform the ".vtf" file generate
by transvalor forge to ".csv" file.

## Installation

Just use g++ to compile all ".cpp" file in the repository.

```shell
$ g++ *.cpp -o VtfParser
```

## Usage

1. Transform only *one* vtf file (the file name must contain .vtf):
  ```shell
  $ VtfParser <vtf filename>
  ```
2. Use the `find` command to generate file names folder, and recursively
   transform all vtf files in the folder:
  ```shell
  $ find . -type f -name "*.vtf" > vtfFiles
  $ ./VtfParser < vtfFiles
  ```
