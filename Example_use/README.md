# Example

## Execution

<pre>./NET-ASAR-map -c 12 -f Target_Sequence -s Reference_GENE | ./goose-filter -d 10 -w 200 -1 > ~/Desktop/Filtered_Values

./NET-ASAR-regionFinder -f ~/Desktop/Filtered_Values -t 0.2 | ./NET-ASAR-visual -f ~/Desktop/Filtered_Values -t 0.2

gnuplot

load '~/Desktop/plotScript.gp'</pre>


Note that **NET-ASAR-visual** requires the file full path so that gnuplot can find the file when plotting.

