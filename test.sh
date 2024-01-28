#!/bin/bash

# Check if correct number of arguments is provided
if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <executable> <samples_dir>"
    exit 1
fi

# Assign arguments to variables
EXECUTABLE="$1"
SAMPLES_DIR="$2"

# Check if the provided executable does not exist
if [ ! -f "$EXECUTABLE" ]; then
    echo "Error: Executable $EXECUTABLE not found."
    exit 1
fi

# Check if the provided directory does not exist
if [ ! -d "$SAMPLES_DIR" ]; then
    echo "Error: Directory $SAMPLES_DIR not found."
    exit 1
fi

# Loop through all the .in files in the samples directory
for input_file in $SAMPLES_DIR/*.in; do
    # Determine the corresponding .ans file
    output_file="${input_file%.in}.ans"
	output_file_temp="${input_file%.in}.tmp"

    # Check if corresponding .ans file exists
    if [ ! -f "$output_file" ]; then
        echo "Expected output file ${output_file} does not exist. Skipping test."
        continue
    fi

    # Show which test is being run
    echo "Running test with input ${input_file} and expected output ${output_file}" and tmp ${output_file_temp}

    # Run the program with the current input file and capture the output
    #result=$("$EXECUTABLE" < "$input_file")
	cat "$input_file" | $EXECUTABLE > "$output_file_temp"

    # Use 'diff' to compare the output of the program with the expected output
    diff_output=$(diff "$output_file_temp" "$output_file")

    # Check the exit status of 'diff' to determine if the test passed
    if [ $? -eq 0 ]; then
        echo "Test passed with input ${input_file}"
    else
        echo "Test failed with input ${input_file}"
        # Optional: output the diff result
        echo "$diff_output"
    fi

	#cat "$output_file_temp"

	rm "$output_file_temp"

    echo "" # Newline for better readability between tests
done
