#!/bin/bash

URL='http://tais.fdi.ucm.es/tais.zip'
OUTPUT_NAME="tais-`date '+%d-%m-%Y'`.zip"
TEMP_FOLDER='temp'
EXERCISE_PATH='Exercises'
EXERCISE_NAME=''

function cleanEnviroment {
	printf ">>> Cleaning files... "
	rm -rf $TEMP_FOLDER 
	rm $OUTPUT_NAME
	printf " OK\n"
}

printf ">>> Downloading updated resource files..."
curl -o $OUTPUT_NAME $URL &>/dev/null

if [[ $? -ne 0 ]]; then
	printf "Cannot download source files from $URL! Exiting..."
	exit -1
fi

printf " OK\n"


printf ">>> Unziping template files into temporal folder..."
unzip $OUTPUT_NAME -d $TEMP_FOLDER > /dev/null
printf " OK\n"


read -p "Enter a name for the exercise folder: " EXERCISE_NAME
if [ -d $EXERCISE_PATH/$EXERCISE_NAME ]; then
	printf "CAUTION! Folder $EXERCISE_PATH/$EXERCISE_NAME already exists!\n"
fi

cleanEnviroment
