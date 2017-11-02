reset
set terminal png size 3000,750 enhanced font 'Verdana,30'
set tics font "Helvetica,26"
set style line 12 lc rgb '#000000' lt 0 lw 1
set grid back ls 12
unset object
set output '/home/manuelgaspar/Desktop/TEMP/TEST/Filtered.png'
unset log
unset label
set nokey
set xlabel "Base Index" offset 0,0.5
set ylabel "Bits" offset 3,0
set style line 11 lc rgb '#000000' lt 1
set border 3 back ls 11
set tics nomirror
stats '/home/manuelgaspar/Desktop/TEMP/TEST/Filtered' using 1:2 name 'data'
set arrow 1 from graph 0,graph 0.98 to graph 1, graph 0.98 nohead lw 4 lc rgb "#DC143C" front
set arrow 2 from 0, 0.2 to data_max_x, 0.2 nohead lw 3 lc rgb "#FF4500" front
set label 1 "Threshold" at data_max_x,0.2 rotate left tc rgb "#FF4500" font "Verdana:/Bold,30" front
set label 2 "0.2" at data_min_x,0.2 offset -3,0 tc rgb "#FF4500" font "Verdana:/Bold,30" front
set xrange [data_min_x:data_max_x]
set yrange [data_min_y - 0.1:data_max_y + 0.15]
d = 1/data_max_x
set object 1 rect from graph (1000131-0.005*data_max_x)*d,graph 1 to graph (1017687+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 3 rect from graph (2031106-0.005*data_max_x)*d,graph 1 to graph (2031546+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 5 rect from graph (7106957-0.005*data_max_x)*d,graph 1 to graph (7124502+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 7 rect from graph (2021888-0.005*data_max_x)*d,graph 1 to graph (2022196+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 9 rect from graph (3047902-0.005*data_max_x)*d,graph 1 to graph (3048122+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 11 rect from graph (2033768-0.005*data_max_x)*d,graph 1 to graph (2034483+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 13 rect from graph (2032294-0.005*data_max_x)*d,graph 1 to graph (2032503+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 15 rect from graph (2027333-0.005*data_max_x)*d,graph 1 to graph (2027542+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 17 rect from graph (2019864-0.005*data_max_x)*d,graph 1 to graph (2020370+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 19 rect from graph (2024726-0.005*data_max_x)*d,graph 1 to graph (2024913+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 21 rect from graph (2033042-0.005*data_max_x)*d,graph 1 to graph (2033196+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 23 rect from graph (2018533-0.005*data_max_x)*d,graph 1 to graph (2018665+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 25 rect from graph (2020579-0.005*data_max_x)*d,graph 1 to graph (2020722+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 27 rect from graph (2023549-0.005*data_max_x)*d,graph 1 to graph (2023681+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 29 rect from graph (2018929-0.005*data_max_x)*d,graph 1 to graph (2019039+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 31 rect from graph (3044470-0.005*data_max_x)*d,graph 1 to graph (3044580+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 33 rect from graph (2026167-0.005*data_max_x)*d,graph 1 to graph (2026552+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 35 rect from graph (2030182-0.005*data_max_x)*d,graph 1 to graph (2030281+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 37 rect from graph (2028455-0.005*data_max_x)*d,graph 1 to graph (2028543+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 39 rect from graph (2031766-0.005*data_max_x)*d,graph 1 to graph (2031865+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 41 rect from graph (3042886-0.005*data_max_x)*d,graph 1 to graph (3042963+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 43 rect from graph (3037815-0.005*data_max_x)*d,graph 1 to graph (3037903+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 45 rect from graph (2022977-0.005*data_max_x)*d,graph 1 to graph (2023043+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 47 rect from graph (2021283-0.005*data_max_x)*d,graph 1 to graph (2021349+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 49 rect from graph (2030886-0.005*data_max_x)*d,graph 1 to graph (2030963+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 51 rect from graph (2028873-0.005*data_max_x)*d,graph 1 to graph (2028906+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
set object 53 rect from graph (2021371-0.005*data_max_x)*d,graph 1 to graph (2021371+ 0.005*data_max_x)*d,graph 0.96 front fc rgb "#DC143C" fs noborder
plot '/home/manuelgaspar/Desktop/TEMP/TEST/Filtered' w l lw 0.5 lc rgb "#00008B"
