#!/bin/bash
#Reads the regions contained in the HS*.oxch.seg files and outputs a file for each chromosome
#containing the length of the region and the url for that region in NCBI's sequence viewer (sorted from biggest to smallest)

chr_Array=(empty NC_000001.11 NC_000002.12 NC_000003.12 NC_000004.12 NC_000005.10 NC_000006.12 NC_000007.14 NC_000008.11 NC_000009.12 NC_000010.11 NC_000011.10 NC_000012.12 NC_000013.11 NC_000014.9 NC_000015.10 NC_000016.10 NC_000017.11 NC_000018.10 NC_000019.10 NC_000020.11 NC_000021.9 NC_000022.11 NC_000023.11 NC_000024.10)
url="https://www.ncbi.nlm.nih.gov/projects/sviewer/?id="
for i in {1..24}
do
FILE=HS$i.oxch.seg
line=0
while read CMD; do
    if [ $line -ne 0 ]
    then
    IFS=: read posi posf <<< $CMD
    dif=$((posf-posi))
    echo $dif $url${chr_Array[$i]}"&v="$posi:$posf >> temp
    fi
    ((line++))
done < "$FILE"

sort -n -r -k 1 < temp > sortedChr$i
rm -f temp
done
