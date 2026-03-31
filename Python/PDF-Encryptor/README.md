# PDF-Encryptor

Brief manual for `PDF-Encryptor.py`.

## What It Does

`PDF-Encryptor.py` reads an input PDF, copies its pages into a new file, and applies password protection using the `pypdf` library.

## Requirements

- Python 3
- `pypdf` installed

Install the dependency with:

```bash
pip install pypdf
```

## Basic Usage

Run the script with an input PDF and a password:

```bash
python3 ./PDF-Encryptor.py input.pdf MyPassword123
```

Set a custom output file:

```bash
python3 ./PDF-Encryptor.py input.pdf MyPassword123 -o protected.pdf
```

## Output

- If `-o` is not provided, the script creates a file named like `input_protected.pdf`.
- On success, it prints the saved output path.

## Notes

- The script stops with an error if the input PDF does not exist.
- Any processing failure is reported to `stderr`.
- Keep in mind that the password will appear in shell history if passed directly on the command line.
