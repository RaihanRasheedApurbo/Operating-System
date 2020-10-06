file_name=ipc using triple mutex
g++ -D _REENTRANT $file_name.cpp -o $file_name -lpthread
./$file_name > $file_name.txt
rm $file_name