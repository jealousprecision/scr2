#!/bin/bash

#Z4_ARCHIVE_NAME
#Z4_FILEMASK
#Z4_DAYS_OFF

while getopts 'n:m:a:' c
do
    case $c in
        a) Z4_ARCHIVE_NAME=$OPTARG ;;
        m) Z4_FILEMASK=$OPTARG ;;
        n) Z4_DAYS_OFF=$OPTARG ;;
    esac
done

if [[ -z $Z4_ARCHIVE_NAME ]]; then
    echo -n 'archive_name: '
    read Z4_ARCHIVE_NAME;
fi

if [[ -z $Z4_FILEMASK ]]; then
    echo -n 'filemask: '
    read Z4_FILEMASK
fi

if [[ -z $Z4_DAYS_OFF ]]; then
    echo -n 'days off: '
    read Z4_DAYS_OFF
fi

tar -czvf $Z4_ARCHIVE_NAME $(find -name "$Z4_FILEMASK" -type f -mtime -$Z4_DAYS_OFF)
