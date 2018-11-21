
#!/bin/bash

xterm -e "\
\
ssh pi@192.168.1.3 -t \"cd ~/Desktop/aqua/;git pull origin master\";\
ssh pi@192.168.1.3 -t \"sh ~/Desktop/aqua/run.sh\";\
read a;\
ssh pi@192.168.1.3 -t htop;\
";

exit;
