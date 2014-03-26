Tyler Kickham
a3

This program takes three user inputs (1 - timeslice, 2 - length new jobs can enter, 3 - probability of a new job entering). It generates five jobs and then enqueues and dequeues taking the timeslice off of the time remaining to complete the job each time. At the end it displays how many seconds the CPU idled for.
main.cpp runs the program and contains the core function calls
job.cpp does the grunt work adding all the information to the new jobs and printing out the job progress with each De/Enqueue
job.h has all the function prototypes for job.cpp and stores the private variables
It provides the data necessary, but it goes on for a bit too long in the .csv file, and restarts itself when the jobs.size() = 0 and continues on.  I didn't have enough time to fix that part and adapted the graph by deleting the excess jobs.
