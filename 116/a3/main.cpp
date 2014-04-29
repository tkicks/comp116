// =======================================================================================================
// Programmer: Tyler Kickham
// Summary: Job queue that takes in jobs and does timeslices of each until they are finished, occasionally
//			adding a new one
// DLM 03/07/2014 (tkk) - JOB class compiling
//	   03/19/2014 (tkk) - JOB queue compiling, Bug in .getJobName()
//	   03/21/2014 (tkk) - fixed .getJobName(), Bug in printing
//	   03/24/2014 (tkk) - fixed bug in printing, did idleTime and timeUsed
//	   03/25/2014 (tkk) - fixed bug in adding new jobs, new bug that adds too many after queue is empty
//						  but runs, messes up in excel
// ----------------------------------------------------------------------------------------------
// INPUT: stdin from keyboard for - 1. length of timeslice
//									2. length of time new jobs can enter
//									3. probability of a new job entering
// OUTPUT: stdout of the information for the current job in the queue
// ======================================================================================================
#include <iostream>
#include "job.cpp"
#include <queue>
#include <string>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

short CLOSE_ENOUGH = .01; 	// job is close enough to being done

int main() {
// PRE: ----------------
// POST: ---------------
// SIDE EFFECTS: job's running function
// ===============================================
	// ----- variables -------------------------------------------------------------------------------------
	queue<JOB> jobs;		// jobs queue
	short simLength;		// length of time for adding a new job
	double jobId, timeLeft, timeSlice,			// job's id#, job's time left, the inputted timeslice
		probNewJob, idleTime, idleTimeNow,		// probability of a new job, total idle time, current idle time
		timeUsed, newJobProb, totalTimeUsed;	// total time CPU has been used, probability of a new job, total time used
	srand(time(NULL));
	time_t		start, now;
	// -----------------------------------------------------------------------------------------------------
	
	string outFile;						// string to hold the file name			//
	fstream fileOut;					// filestream							//
	outFile = "output.csv";														//
	fileOut.open(outFile.c_str());												//==== opening a new file to write to
	fileOut.clear();															//
	if (fileOut.fail()) {														//
		cout <<"ERROR: file called " << outFile << " did not open" << endl;		//
	}

	cout << "\nEnter the time slice: ";						//
	cin >> timeSlice;										//
	cout << "Enter length of time new jobs can enter: ";	//
	cin >> simLength;										//
	time(&start);											//==== setting the variables
	cout << "Enter the probability of a new job: ";			//
	cin >> probNewJob;										//
	cout << "\n";											//
	probNewJob *= 100;										//
	//int nowTime = time(&now) + simLength;
	//time(&now) = time(&start) + simLength;

	JOB one(timeSlice);			//
	JOB two(timeSlice);			//
	JOB three(timeSlice);		//
	JOB four(timeSlice);		//
	JOB five(timeSlice);		//==== creating jobs and pushing them to the queue
	jobs.push(one);				//
	jobs.push(two);				//
	jobs.push(three);			//
	jobs.push(four);			//
	jobs.push(five);			//

	while (!jobs.empty() /*simulation still running*/) {

		JOB thisJob;				//
		thisJob = jobs.front();		//==== create temp variable to hold current job and pop it off queue
		jobs.pop();					//

		jobId = thisJob.getID();					//
		string jobsName = thisJob.getJobName();		//
		timeLeft = thisJob.getTimeLeft();			//
		short totalTime = thisJob.getTotalTime();	//==== get job's information and reset time left to after timeslice
		timeUsed = totalTime - timeLeft;			//
		totalTimeUsed += timeUsed;
		thisJob.setTimeLeft(timeSlice);				//
		thisJob.setTimeUsed(timeUsed);

		printf("------------------------------------------------------------------------------------------\n");
		printf("Job #%0.0f is DeQueued and enters the CPU with %4.2f seconds remaining\n", jobId, timeLeft);

		if (thisJob.getTimeLeft() - CLOSE_ENOUGH > CLOSE_ENOUGH) {	// if the job is close enough to being done

			timeLeft = thisJob.getTimeLeft();
			thisJob.print();
			printf("Job #%0.0f leaves CPU with %4.2f seconds remaining(%4.2f seconds total CPU time used so far)\n",
				jobId, timeLeft, timeUsed);
			cout << "Job #" << jobId << " is EnQueued again" << endl;
			jobs.push(thisJob);		// push the job back into the queue

		}
		else {		// if there is no time left on the job

			timeLeft = thisJob.getTimeLeft();
			idleTimeNow = 0;
			idleTimeNow += ((timeLeft - 0)*-1);
			idleTime += idleTimeNow;
			cout << "Job #" << jobId << " -- " << jobsName << " -- in CPU" << endl;
			//printf("Job #%0.0f -- %s -- has finished without using all the time slice; CPU idles for %4.2f seconds\n", jobId, jobsName, idleTimeNow);
			cout << "Job #" << jobId << " -- " << jobsName << " -- has finished without using all the time slice; CPU idles for " << idleTimeNow << " seconds" << endl;
			//printf("Job #%0.0f -- %s -- has 0 seconds remaining (%4.2f seconds total CPU time used so far)\n", jobId, jobsName, timeUsed);
			cout << "Job #" << jobId << " -- " << jobsName << " -- has 0 seconds remaining (" << timeUsed << " seconds total CPU time used so far)" << endl;
			cout << "Job #" << jobId << " is FINISHED" << endl;
			sleep(.1); 	// do not push back to queue, sleep to show done

		}

		// send to .csv file
		fileOut << "time" << DELIMITER << "# jobs" << endl;
		fileOut << totalTimeUsed << DELIMITER << jobs.size() << endl;

		time(&now);
		if (difftime(now, start) < simLength) {	// if there is still time left in the simulation
			newJobProb = rand() % 100 + 1;
			/*SEE IF NEW JOB HAS SHOWN UP*/
			if (newJobProb < probNewJob) {		// if a new job has shown up create a new one
				JOB nextID(timeSlice);			//   |
				JOB *newJob = new JOB(nextID);	//   |
				jobs.push(*newJob);				// --|
			}
		}
		time(&now);
	}
	cout << "\nTotal idle time: " << idleTime << " seconds" << endl;	// total idle time
}