#!/usr/bin/env bash

# 1) Figure out which C file to compile:
if [ -z "$1" ]; then
  read -p "Enter the C source filename (with or without .c): " INPUT
else
  INPUT="$1"
fi

# 2) Normalize: if user typed “foo” → “foo.c”
if [[ "$INPUT" == *.c ]]; then
  SRC="$INPUT"
else
  SRC="$INPUT.c"
fi

# 3) Check that the source exists:
if [ ! -f "$SRC" ]; then
  echo "Error: source file “$SRC” not found."
  exit 1
fi

# 4) Derive base name and output names:
BASENAME="$(basename "$SRC" .c)"    # “foo” from “foo.c”
TARGET="$BASENAME.exe"              # “foo.exe”

# 5) Compile and link in one step:
echo "Compiling and linking $SRC → $TARGET …"
gcc "$SRC" -o "$TARGET"
if [ $? -ne 0 ]; then
  echo "Error: build failed."
  exit 1
fi

echo "Build complete: ./$TARGET"
exit 0
