#!/bin/bash

for j in {2..6}
do
    for i in {1..9}
    do
        echo test "data/input/s$j-0$i.txt"
        ./a.out "data/input/s$j-0$i.txt" out.txt
        diff -u out.txt "data/ref/s$j-0$i-ref.txt"
    done
done
