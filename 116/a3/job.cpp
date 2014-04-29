#include <iostream>
#include <string>
#include "JOB.h"
#include <stdlib.h>
#include <fstream>
using namespace std;

short PRINT_JOB = 20;		//							  print job
short COMPILE_JOB = 50;		// type of job max to be a... compile job
short EMAIL_JOB = 90;		//							  email job
short OTHER_JOB = 100;		//							  other job
char DELIMITER = ',';		// delimiter for .csv file

JOB::JOB() {
	// Default CTOR
}

JOB::JOB(/*in*/ short timeSlice) {
// PRE: timeSlice > 0
// POST: jobName = string, 1 < jobID < 100, totalTime > 0, timeLeft = totalTime
// RETURNS: none
// ============================================================================

	short typeOfJob = rand() % 100 + 1;		// random number to determine the type of the job
	short jobsID = rand() % 100 + 1;		// random job ID number
	
	// if it's a printing job
	if (typeOfJob <= PRINT_JOB) {
		jobName = "print";
		jobID = jobsID;	// FIX THIS
		totalTime =  rand() % 5 + 1;
		timeLeft = totalTime;
		timeUsed = 0;
	}
	// or a compile job
	else if (typeOfJob <= COMPILE_JOB) {
		jobName = "compile";
		jobID = jobsID;	// FIX THIS
		totalTime =  rand() % 100 + 10;
		timeLeft = totalTime;
		timeUsed = 0;
	}
	// or an email job
	else if (typeOfJob <= EMAIL_JOB) {
		jobName = "email";
		jobID = jobsID;	// FIX THIS
		totalTime =  rand() % 20 + 3;
		timeLeft = totalTime;
		timeUsed = 0;
	}
	// or an other job
	else if (typeOfJob <= OTHER_JOB) {
		jobName = "other";
		jobID = jobsID;	// FIX THIS
		totalTime =  rand() % 45 + 0;
		timeLeft = totalTime;
		timeUsed = 0;
	}
	// or a bug
	else {
		jobName = "BUG IN typeOfJob";
		jobID = jobsID;	// FIX THIS
		totalTime =  rand() % 5+1;
		timeLeft = totalTime;
		timeUsed = 0;
	}	
}

JOB::~JOB() {
	// Default DTOR
}

// GET FUNCTIONS =================================
short JOB::getID(/*out*/) {
	return jobID;
}

string JOB::getJobName(/*out*/) {
	return jobName;
}

double JOB::getTotalTime(/*out*/) {
	return totalTime;
}

double JOB::getTimeLeft(/*out*/) {
	return timeLeft;
}

double JOB::getTimeUsed(/*out*/) {
	return timeUsed;
}
// SET FUNCTIONS =================================
void JOB::setID(/*in*/ int jobID) {
	jobID = jobID;
}

void JOB::setName(/*in*/ string jobName) {
	jobName = jobName;
}

void JOB::setTotalTime(/*in*/ double totalTime) {
	totalTime = totalTime;
}

void JOB::setTimeLeft(/*in*/ double timeSlice) {
	timeLeft -= timeSlice;
}

void JOB::setTimeUsed(/*in*/ double timeUsed) {
	timeUsed = timeUsed;
}


// PRINT ============================================
void JOB::print() {
	short jobId = getID();
	string jobsName = getJobName();
	double timesLeft = getTimeLeft();
	cout << "Job #" << jobId << " -- " << jobsName << " -- is now in the CPU" << endl;
	cout << "Job #" << jobId << " leaves CPU with " << timesLeft << " seconds remaining" << endl;
	if (timesLeft < 0) {
		//fileOut << "Time Remaining: 0" << endl;
		cout << "Time Remaining: 0" << endl;
	}
}