#!/bin/bash

# Make sure globstar is enabled
shopt -s globstar
for i in **/*.pdf; do # Whitespace-safe and recursive
	IFS=/ read -ra files <<< $i
	echo "* Problema ${files[1]} - ${files[2]:5}"
done

