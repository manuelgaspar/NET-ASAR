# NET-ASAR
<br>

Automatic system for approximate and noncontiguous DNA sequence search. Based on data compression methods using Finite-Context Models (FCMs).

To install on Linux:

<pre>
git clone https://github.com/manuelgaspar/NET-ASAR
cd goose/src/
make
</pre>

Included programs:
<pre>
NET-ASAR-map
NET-ASAR-visual
NET-ASAR-regionFinder
</pre>

## Execution

Run **NET-ASAR-map**:

<pre>./NET-ASAR-map -c [context size] -f [target file path] -s [reference file path]</pre>

The results should be filtered for visualization, so a filter program that provides pipes support, such as goose-filter, found in the [GOOSE](https://github.com/pratas/goose) toolkit.

Run **NET-ASAR-visual**:

<pre>./NET-ASAR-visual -f [data file full path] -t [threshold value] </pre>

NET-ASAR-visual takes the intervals below the threshold through the standard input.

[Gnuplot](http://www.gnuplot.info/) is needed to plot the script created with **NET-ASAR-visual**. The plot is created with:

<pre>gnuplot
'load [file path]/plotScript.gp'</pre>
Run **NET-ASAR-regionFinder**:

<pre>./NET-ASAR-regionFinder -f [filtered values file path] -t [threshold value]</pre>

## Parameters

All program option can be viewed by running the program using the parameter -h, for example:

<pre>./NET-ASAR-map -h</pre>

Which will print the following:

<pre> Usage: ./NET-ASAR-map [options]
options: -c context size(*)
         -f target file name(*)
         -s reference file name(*)
         -i (do not include inverted complements)
         -a alpha (default:1/100)
         -h (print this help)
Results are directed to standard output.
Note: options marked with (*) are mandatory
</pre>


## Example use

An example use of the programs provided is available in the folder [Example_use](Example_use). This example can be used to assess the correction functioning of the installed programs.

The parameters used in the example are provided in the Readme available in the folder. 
