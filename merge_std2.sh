#!/bin/bash

# Input file (concatenated header files)
#input_file="$1"

if [ $# -lt 1 ]; then
	echo "Usage: $0 <name> [file1] [file2] [file3]"
	exit 1
fi

# Output file (filtered header file)
name="$1"
input_file="${name}.cpp"
output_file="${name}_merged.cpp"
copy_this="$2"

# Pattern to match #include statements starting with "std_"
pattern='#\s?include\s+"std.*"'
pattern2='#pragma once'

echo "Copying ${copy_this}."

# Use grep to filter out matching lines and save the result to the output file
cat std.h "$copy_this" "$3" "$4" "$input_file" | grep -vE "$pattern|$pattern2" > "$output_file"
