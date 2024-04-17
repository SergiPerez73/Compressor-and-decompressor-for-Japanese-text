# Compressor and decompressor for Japanese text

## Description

This compressor allows you to compress files with Japanese text to divide their size in memory by 2. Afterwards, you can decompress the generated file to get the original text back. 

## Motivation

Normally, each Japanese symbol (either a kanji or a hiragana or katakana character) occupies 3 bytes. In other words, 24 bits are being used to store these characters in memory, even though 12 bits would be sufficient, since there are no more than 4096 (2^12) Japanese characters in use today. This code makes it possible to compress the size of files containing only Japanese characters so that they take up half the memory space.

## Code execution

This folder has 2 C++ programs to be compiled: compressor.cc and decompressor.cc. You can compile them in linux with the command `make`. You can also delete the executables by writing `make clear`. Then you can start using the executables with the next commands.
To compress a file:
```bash
./compressor <input_file> <compressed_file>
```
To decompress a compressed file:
```bash
./decompressor <compressed_file> <decompressed_file>
```
The you don't need to have the output files in the folder because the program will generate them automatically with the name you entered.

## Example

This folder contains a file named input_example.txt wich has text in japanese that can be compressed (and afterwards decompressed).

## Author

Sergi Perez
