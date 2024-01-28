#!/bin/bash

# Input file (concatenated header files)
#input_file="$1"

# Output file (filtered header file)
name="$1"
input_file="${name}.cpp"
output_file="${name}_merged.cpp"

# Pattern to match #include statements starting with "std_"
pattern='#\s?include\s+"std.*"'
pattern2='#pragma once'

# Use grep to filter out matching lines and save the result to the output file
cat std.h std_*.h "$input_file" | grep -vE "$pattern|$pattern2" > "$output_file"
