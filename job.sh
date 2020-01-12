#!/bin/bash
echo "N,straight,random,balance,map" >> benchmark_results/results.txt

for i in 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 #65536 131072
	do
	echo ${i}
	./bst.x ${i} >>  benchmark_results/results.txt
	cp benchmark_results/results.txt results_so_far.txt
	done
