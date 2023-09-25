#!/bin/bash

truncate -s 0 "min_max_search_loop_cost.txt"
truncate -s 0 "min_max_search_recursion_cost.txt"

for i in {0..1000}
do
	echo $i
	./a.out $i
done
