Include all the headfile you need.
Input a file as arg and use fget to read it line by line.
Get the variable you need by using "strtok strcpy".

Then use ctime() to get the start time.

Start the child process by using fork() and use pid to hold the return.
If pid is 0 then it is a child process. 
So in the child process start execute the commend in the file.
Then use wait() to wait for the child process to terminate.
Then use ctime() to get the end time.
Then get the second loop and do the same thing from start the child process.

Use a mode to creat a log file.
Use fprintf to write the commend, start time and the end time.
