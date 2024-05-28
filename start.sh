#!/bin/bash
#
day=$(date +%g-%m-%d)
echo $day

if [ ! -d "days/$day" ]; then
	mkdir "days/$day"
fi
