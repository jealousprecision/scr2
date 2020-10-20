#!/bin/bash

while read line
do
    echo mutt -a spec*.pdf -- ${line}
done

# cat adresy.txt | ./z2.sh
