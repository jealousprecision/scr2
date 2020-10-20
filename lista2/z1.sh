#!/bin/bash

if [ $(date +%u) -le 5 ]; then
    echo Dzien roboczy
else
    echo Weekend
fi
