#!/bin/bash

while [ 1 ]
do
	for i in $@
	do
		echo $i
		sleep 1
	done
done
