// Author: Thanh Doan
// Submission for project 3
// Minimum spanning tree (mst) algorithm.

Submission file, thanh_hw3.zip, consists of 10 files below:

  1.  README.txt
  2.  graph.h
  3.  kruskal.h
  4.  main.cpp
  5.  makefile
  6.  medium_input.graph
  7.  mst_test_data
  8.  pq.h
  9.  tiny_input.graph
  10. uf.h

To compile the program:
  1. create a new directory 
  2. unzip the zip file to new directory
  3. make

  Make will compile, link and output executable file "mst"

Program compiled succesffuly with GNU make 4.1 and gcc/g++ 5.4.0 20160609
on Ubuntu version 16.04.1

To run the mst executable
   ./mst <input_file_name>

For example, to run mst on test sample data named mst_test_data:
    ./mst mst_test_data

Program has been tested on at least 3 test data files as below
./mst tiny_input.graph
./mst medium_input.graph
./mst mst_test_data

And test results appear correct as below:
./mst tiny_input.graph   --> Returns MST cost 1.81
./mst medium_input.graph --> Returns cost 10.4635
./mst mst_test_data	 --> Returns cost 30
