#!/bin/bash

# Check if correct number of arguments is provided
if [ "$#" -ne 1 ] && [ "$#" -ne 2 ] && [ "$#" -ne 3 ]; then
    echo "Usage: $0 <name> [sample-name] <validator>"
    exit 1
fi

# Assign arguments to variables
NAME="$1"
SAMPLE="$2"
VALIDATOR="$3"

set -x

set -e

if [ "$#" -eq 1 ]; then
	(cd build/source && make $NAME)
	./test.sh ./build/source/$NAME samples/$NAME
else
	# Build the program
	reset
	make -f build/source/Makefile $NAME
	# if [ "$?" -ne 0 ]; then
	# 	echo "Failed to build $NAME."
	# 	exit 1
	# fi
	if [ "$#" -eq 3 ]; then
		# Build the validator
		make -f build/source/Makefile $VALIDATOR
		cat samples/$NAME/$SAMPLE.in | ./build/source/$NAME | ./build/source/$VALIDATOR samples/$NAME/$SAMPLE
	else
		cat samples/$NAME/$SAMPLE.in | ./build/source/$NAME
		set +x
		if [ "$?" -eq 0 ]; then
			echo "WANT:"
			cat samples/$NAME/$SAMPLE.ans
		else
			echo "Failed with exit code $?"
		fi
	fi
fi
