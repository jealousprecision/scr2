#!/bin/bash

if [ ${#@} -ne 3 ]; then
    echo usage: "$0" mask n_days tarball_name
    exit
fi

tar -czvf $3 $(find -name "$1" -type f -mtime -$2)
