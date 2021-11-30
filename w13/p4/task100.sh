#!/bin/sh

NUM=0
NUM1=1
STR="CHuild won\n"
i=1
while [ ${i} -le 100 ]
do
	cp game_0.txt game.txt
	cat game.txt
	./memPlay2 game.txt
	VAR='./countp game.txt'
	if [ $VAE == $SRT ]
	then
		NUM=$(expr $NUM + $NUM1)
	fi
	cat game.txt
	i=`expr ${i} + 1`
done
echo "$NUM"
