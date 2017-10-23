#!/bin/bash
#Opens the NCBI sequence viewer with the urls contained in the files sortedChr* created with region_sorter.sh
#Takes as an argument the minimum length of the region to be viewed (default = 800)
#Pressing <ENTER> opens the url of the next chromosome (when possible)

if [ -z $1 ]
then
    minLength=800
else
    minLength=$1
fi

for i in {1..24}
do
    FILE=sortedChr$i
    while read CMD; do
        read dif url <<< $CMD
        if [ $dif -gt $minLength ]
        then
        xdg-open $url
        fi
    done < "$FILE"
read -p "Press enter to continue"
done
