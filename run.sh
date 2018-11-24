#!/bin/bash

cd ~/Desktop/aqua/;

if [ ! -d asm ]; then
	echo "Downloading CW ..."
	git clone https://github.com/inobulles/AQUA-CW
	mv AQUA-CW asm
fi

rm a.out;
make output.bin;

./a.out;

exit;
