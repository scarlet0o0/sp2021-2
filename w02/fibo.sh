#!/bin/bash


pibo()
{
	if [ "0" -eq "$1" ]
	then
		echo "0"
	elif [ "1" -eq "$1" ]
	then
		echo "1"
	elif [ "1" -lt "$1" ] 
	then
		pibo1=$(expr $1 - 1)
		pibo2=$(expr $1 - 2)
		result=$(expr $(pibo $pibo1) + $(pibo $pibo2))
		echo "$result"
	fi
}
echo Enter num text:
read num

p=$(pibo $num)
echo "답 $p"

exit 0

