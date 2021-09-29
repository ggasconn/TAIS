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
	if [[ $? -eq 0 ]]; then printf " OK\n"; fi
}

## GET .ZIP FILE FROM SOURCE
printf ">>> Downloading updated resource files..."
status=`curl -s -o $OUTPUT_NAME -I -w "%{http_code}" $URL`

if [[ $status -ne 200 ]]; then
	printf " Cannot download source files from $URL!\n"
	cleanEnviroment
	exit -1
fi


## UNZIP IT
printf ">>> Unziping template files into temporal folder..."
unzip $OUTPUT_NAME -d $TEMP_FOLDER
#unzip $OUTPUT_NAME -d $TEMP_FOLDER &> /dev/null

if [[ $? -ne 0 ]]; then
	printf " FAILED!\n"
	cleanEnviroment
	exit -1
else
	printf " OK\n"
fi


read -p "Enter a name for the exercise folder: " EXERCISE_NAME
if [ -d $EXERCISE_PATH/$EXERCISE_NAME ]; then
	printf "CAUTION! Folder $EXERCISE_PATH/$EXERCISE_NAME already exists!\n"
	read -p "Do you really want to overwrite $EXERCISE_PATH/$EXERCISE_NAME? (y/n): " op

	if [[ $op -eq 'n' ]]; then
		cleanEnviroment
		exit -1
	fi
fi

printf ">>> Creating $EXERCISE_PATH/$EXERCISE_NAME and copying files..."
mkdir $EXERCISE_PATH/$EXERCISE_NAME
mv $TEMP_FOLDER/* $EXERCISE_PATH/$EXERCISE_NAME
printf " OK\n"

cleanEnviroment
