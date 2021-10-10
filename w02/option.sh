#!/bin/bash

echo "1.Create a file"
echo "2.Create a directory"
echo "3.Remove a file"
echo "4.Remove a directory"
echo "Enter:"
read num

if [ "$num" -eq "1" ]
then
	echo "Enter filename:"
	read name
	touch ${name}
elif [ "$num" -eq "2" ]
then
	echo "Enter directory name:"
	read name
	mkdir ${name}
elif [ "$num" -eq "3" ]
then
	echo "Enter filename"
	read name
	rm ${name}
elif [ "$num" -eq "4" ]
then
	echo "Enter directory name:"
	read name
	rm -d ${name}
fi

