file_name=1605062
g++ -D _REENTRANT $file_name.cpp -o $file_name -lpthread
./$file_name
rm $file_name