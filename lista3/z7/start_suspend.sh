#!/bin/bash
$@ &
PID=$!
kill -SIGSTOP $PID
echo $PID
wait $PID
