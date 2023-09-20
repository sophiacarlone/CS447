#!/bin/bash

truncate -s 0 "max_search_loop_cost.txt"
truncate -s 0 "min_search_loop_cost.txt"
truncate -s 0 "max_search_recurse_cost.txt"
truncate -s 0 "min_search_recurse_cost.txt"

for i in {0..1000}
do
	./a.out $i
done
