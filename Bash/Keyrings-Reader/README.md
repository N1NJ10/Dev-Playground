# Keyrings-Reader

Brief manual for `Keyrings-Reader.sh`.

## What It Does

`Keyrings-Reader.sh` looks for `user` keys listed in `/proc/keys`, tries to dump their contents with `keyctl`, and saves successful results as local binary files.

## Requirements

- Linux system with `/proc/keys` available.
- `keyctl` installed and accessible in `PATH`.
- Enough privileges to read and dump the target keys.

## Basic Usage

Run the script from its directory:

```bash
chmod +x ./Keyrings-Reader.sh
./Keyrings-Reader.sh
```

Or run it with Bash directly:

```bash
bash ./Keyrings-Reader.sh
```

## Output

- Successful key dumps are written as `dump_<hexid>.bin`.
- The script prints a short text preview when the key content is readable.
- Empty or failed dump files are removed automatically.

## Notes

- The script only targets keys of type `user`.
- Failures usually mean permission issues, revoked keys, or empty key data.
- Dumped files may contain sensitive material, so handle them carefully.
