#!/bin/bash

truncate -s 0 *.txt

for i in {0..1000}
do
	./a.out $i
done
