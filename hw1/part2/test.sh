#!/bin/bash

truncate -s 0 .txt

for i in {0..129}
do
        ./a.out $i
done

