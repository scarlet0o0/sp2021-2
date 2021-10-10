#!/bin/bash

while :
do
	ps > ps.txt
	if [[ -z `grep hello ps.txt` ]] 
	then
		./hello
	fi
	sleep .5
done


exit 0
