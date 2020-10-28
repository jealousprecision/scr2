#!/bin/sh

for i in $(seq 1 15)
do
	trap '' $i
done

while [ 1 ]
do
	date
	sleep 1
done
