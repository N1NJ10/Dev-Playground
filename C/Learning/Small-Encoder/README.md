# Small-Encoder

This is a small C project with a simple library/build layout. It demonstrates two ideas:

- XOR-based string obfuscation/deobfuscation.
- Base64 encoding and decoding.

The program builds a static library from helper source files, then links a small executable that exercises those functions.

## Files

- `Makefile`: builds object files, archives the helper code into a static library, links the final executable, and provides a `clean` target.

## Subdirectories

- `bin`: build output directory for the final executable. After running `make`, this folder is expected to contain the compiled `Smallencoder` program.
- `include`: contains the public header files used by the project.
  - `b64.h`: declares the Base64 encoding and decoding functions.
  - `crypto.h`: declares the XOR helper function used to modify a string in place.
- `lib`: build output directory for the static library archive. The Makefile generates `libcrypto.a` here.
- `obj`: build output directory for intermediate object files created during compilation.
- `src`: contains the source code for the program.
  - `Base64.c`: implements the Base64 encoder and decoder.
  - `crypto.c`: implements the XOR string helper declared in `crypto.h`.
  - `main.c`: demonstrates the workflow by obfuscating a sample string, restoring it, encoding it to Base64, and decoding it back.

## Build Flow

1. `src/crypto.c` and `src/Base64.c` are compiled into object files in `obj/`.
2. Those object files are archived into `lib/libcrypto.a`.
3. `src/main.c` is linked against that library to produce `bin/Smallencoder`.

## Purpose

This project is mainly a learning exercise showing how to:

- organize a small C project into `include`, `src`, `obj`, `lib`, and `bin` directories,
- separate declarations from implementations,
- create and link a static library,
- and test simple encoding/obfuscation helpers from a single executable.
