# CUE
Tiny BIN/CUE parsing and loading library written in C

## Usage
Sample code is included in the main.c file.

Please note that we assume file references inside the CUE sheet are relative to the path the CUE file is being loaded from.
i.e. a file named `bar.bin` referenced from `/foo/bar.cue` will be loaded from `/foo/bar.bin`.
