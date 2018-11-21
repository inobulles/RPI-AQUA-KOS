#!/bin/bash

cd ~/Desktop/aqua/;

rm bin/output.bin;
gcc obj/main.o -o src/main.c

bin/output.bin;

exit;
