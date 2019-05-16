#!/bin/sh
# Migalin
# counter of interruptions
counter=0
# file name
filename=''

# checks if file <filename> exists, doing until user do not write correct filename
getCorrectFileName(){
	while true
	do
		# gets user input
		read -p "Filename: " filename
		# checks if file exists
		if [ ! -f "$filename" ]; then
			echo "File $filename not found"
		else
			# in <filename> now correct file name, exit from inf cycle
			break
		fi
	done
}

# SIGINT handler
sigintHandler(){
	# beautifier
	echo ''
	# increase interrupt counter
	counter=$((counter+1))
	# every odd interruption
	if [ $((counter % 2)) -eq 1 ]; then
		# prints all non-binary files in current directory
		find . -maxdepth 1 -type f -exec grep -Iq . {} \; -print
	fi
}

# rewrite SIGINT handler
trap 'sigintHandler' 2

# get filename from user input
getCorrectFileName

# get words count, print info to STDOUT and file info.txt
wc $filename | awk {'print "Words count: " $2'} | tee info.txt

# command cycle (for interruptions)
while true
do
	echo 'Enter "exit" to stop or Ctrl+C to show the list of non-binary files in current dir'
	read command
	if [ "$command" = "exit" ]; then
		exit 0
	fi
done