# Project 3

A simulation of a trival OS memory manager.

Adam Nelson

files:
flag_parser.cpp : processes the command-line flags for the simulator
frame.cpp : stores a process and the pages associated with it
page.cpp : stores data and converts it via an offset
page_table.cpp : stores pages and tracks meta-data about them
physcial_address.cpp : converts virutal addresses to physical addresses in main memory
process.cpp : reads input data and produces other page information
simulation.cpp : runs the simulator
virtual_address.cpp : creates virtual addresses from input data
main.cpp : reads the input data and calls the simulator to perform on said data

Each of the above files (with the exception of main) also has a .h file with it.

