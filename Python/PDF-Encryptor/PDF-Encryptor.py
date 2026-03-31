#!/usr/bin/env python3
"""
Protect a PDF file with a password.
Don't Forget to pip install pypdf

Usage:
    python PDF-Encryptor.py <input_pdf> <password>
"""

import sys
import os
import argparse
from pypdf import PdfReader, PdfWriter


def protect_pdf(input_path: str, password: str, output_path: str = None) -> str:
    if not os.path.isfile(input_path):
        raise FileNotFoundError(f"Input file not found: {input_path}")

    if output_path is None:
        base, ext = os.path.splitext(input_path)
        output_path = f"{base}_protected{ext}"

    reader = PdfReader(input_path)
    writer = PdfWriter()

    for page in reader.pages:
        writer.add_page(page)

    writer.encrypt(user_password=password, owner_password=None, use_128bit=True)

    with open(output_path, "wb") as out_file:
        writer.write(out_file)

    return output_path


def main():
    parser = argparse.ArgumentParser(
        description="Protect a PDF file with a password."
    )
    parser.add_argument("input_pdf", help="Path to the input PDF file")
    parser.add_argument("password", help="Password to protect the PDF")
    parser.add_argument(
        "-o", "--output", help="Output file path (optional)", default=None
    )

    args = parser.parse_args()

    try:
        output_file = protect_pdf(args.input_pdf, args.password, args.output)
        print(f"Success! Protected PDF saved as: {output_file}")
    except FileNotFoundError as e:
        print(f"Error: {e}", file=sys.stderr)
        sys.exit(1)
    except Exception as e:
        print(f"An error occurred while processing the PDF: {e}", file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()
