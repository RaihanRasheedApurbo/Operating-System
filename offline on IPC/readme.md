**Inter Process Communciation(IPC)**
You can see specification of this assignment on IPC Assignment.pdf
Solution is on ipc_using_triple_mutex.cpp and ipc_using_busywaiting_and_yield.cpp (2 different solution)
you can run code using script.sh and test.sh 
script.sh create txt file to show output on the other hand test.sh shows it on console

If you want to solve this problem or understand what's the code doing you need some context. Those contexts can be gained from below materials- 
1. Read producer consumer and reader-writer problem (I read from OS book of Andrew Tanenbaum)
2. Try to understand practice.cpp that solves producer consumer problem so that you get familar with 
   CPP thread syntax and library functions. 
3. Now read the specification from IPC Assignment.pdf
4. Now try to understand the solution written on ipc_using_busywaiting_and_yield.cpp
5. Now try to understand the solution written on ipc_using_triple_mutex.cpp
6. if you find the solution in ipc_using_triple_mutex.cpp unintuitive then read triple mutex strategy.txt 

**Unressolved Issue**
ipc_using_triple_mutex.cpp has one issue. It can't give complete priority to the thread that has completed payment and ready to exit. In order to solve this problem All you need to do is remove the semphore named pipline and use another mutex in that same place... new mutex should lock like the pipeline semaphore did but unlock when first servicemen mutex is received unlike pipeline semaphore which increased value after the loop. Sorry I am now feeling to lazy to solve this and test.