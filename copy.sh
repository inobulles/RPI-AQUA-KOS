
#!/bin/bash

xterm -e "\
\
ssh pi@192.168.1.58 -t \"rm -r ~/Desktop/aqua/src\";\
ssh pi@192.168.1.58 -t \"rm -r ~/Desktop/aqua/aqua\";\
ssh pi@192.168.1.58 -t \"rm -r ~/Desktop/aqua/objects/aqua.o\";\
ssh pi@192.168.1.58 -t \"rm -r ~/Desktop/aqua/objects/main.o\";\
scp -r ~/Desktop/Projects/aqua3/src/ pi@192.168.1.58:~/Desktop/aqua/src;\
scp -r ~/Desktop/Projects/aqua3/aqua/ pi@192.168.1.58:~/Desktop/aqua/aqua;\
ssh pi@192.168.1.58 -t \"sh ~/Desktop/aqua/run.sh\";\
read a;\
ssh pi@192.168.1.58 -t htop;\
";

exit;
