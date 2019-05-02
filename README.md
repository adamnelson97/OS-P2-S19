# Project 3

A simulation of a trival OS memory manager.

## Adam Nelson
## Files

- flag_parser.cpp : processes the command-line flags for the simulator
- frame.cpp : stores a process and the pages associated with it
- page.cpp : stores data and converts it via an offset
- page_table.cpp : stores pages and tracks meta-data about them
- physcial_address.cpp : converts virutal addresses to physical addresses in main memory
- process.cpp : reads input data and produces other page information
- simulation.cpp : runs the simulator
- virtual_address.cpp : creates virtual addresses from input data
- main.cpp : reads the input data and calls the simulator to perform on said data

Each of the above files (with the exception of main) also has a .h file with it.

## Time Estimate
Approx. number of hours spent: 15

## Belady's Anomaly
Belady's Anomaly is the concept that increasing the number of frames can increase the number of page faults. This is because the most frequent pages are often the oldest pages, which have a higher chance of being swapped out when using FIFO.

To see an example of this, run:

$ ./mem-sim -f 3 inputs/belady1    // 9 page faults

$ ./mem-sim -f 4 inputs/belady2    // 10 page faults

The belady file contains 5 pages from process_1, for a total of 12 accesses using the page order [1,2,3,4,1,2,5,1,2,3,4,5].