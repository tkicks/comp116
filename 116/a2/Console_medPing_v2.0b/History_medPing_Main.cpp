/*--------------------------------------------------------------
Programmer: Tyler Kickham
 
Summary: Stores randomized medPing data into a struct after which the user chooses one file to delete
 
Date last modified: 
 01/02/2014 (mdl) - Set up StarterKit
 02/21/2014 (tkk) - Worked on addHistory
 02/23/2014 (tkk) - Worked on addHistory and printAllRecords
 02/24/2014 (tkk) - Finished addHistory and printAllRecords to working condition except for that temperature always displayed
 02/26/2014 (tkk) - Fixed all existing bugs and completed remaining functions to working condition; documentation undone
 02/27/2014 (tkk) - Documentation
----------------------------------------------------------------*/

/*--------------------------------------------------------------
INPUT: stdin from keyboard to give runtime and raw time; data into a struct to store it from medPing.h
 
OUTPUT: printf current vital records to "cell phone" (console)
---------------------------------------------------------------*/

#include "medPing.h"

#include <cassert>

//-----------------------------------------------------------------------
#include <time.h>
#include <unistd.h>
#include <iostream>

using namespace std;

const long MAX_HISTORY  = 5;	// can store upto (last) 5 sets of vital signs

const long MAX_WAIT_SEC = 4;	// will random pause from 1 to MAX_WAIT_SEC 

//========================================
struct oneVitalHistoryRecord
{
	double	bodyTemp_F;			// a double variable to hold the body temperature 	(later seen as new_mp_bodyTemp_F)
	short	pulseRate,			// a short variable to hold the pulse rate 			(later seen as new_mp_pulseRate)
			respiratoryRate,	// a short variable to hold the respiration rate 	(later seen as new_mp_respiratoryRate)
			glucose,			// a short variable to hold the glucose level 		(later seen as new_mp_glucose)
			systolic,			// a short variable to hold the systolic level 		(later seen as new_mp_systolic)
			diastolic;			// a short variable to hold the diastolic level 	(later seen as new_mp_diastolic)
	long 	nSecs;				// a long variable to hold the raw number of seconds
	
};

//========================================

// function prototypes for keeping track of HISTORY
void AddHistoryRecord(long nSecs,
					  double new_mp_bodyTemp_F, 
					  short  new_mp_pulseRate,
					  short new_mp_respiratoryRate,
					  short new_mp_glucose,
					  short new_mp_systolic,
					  short new_mp_diastolic,
					  oneVitalHistoryRecord vitalHistory[ ],	// array to hold the vital signs
					  long& hmr);


const long NOT_FOUND = -1;  // used to indicate failure on linear search
long FindVitalRecord(long raw_time, oneVitalHistoryRecord vitalHistory[ ], long& thisRecord);

void DeleteHistoryRecord(long recordIndex, oneVitalHistoryRecord vitalHistory[ ], long&);
 

void printAllVitalRecords(medPing& mP, const oneVitalHistoryRecord vitalHistory[ ], long hmr);
// end function prototypes



//-----------------------------------------------------------------------
//create a medPing object (mP object has global file scope)
medPing mP;	

//--------------
// medPing_Main \
//---------------------------------------------------------------------------------------------
// Main function
// PRE: -------------
// POST: ------------
// SIDE EFFECTS: entire program
//---------------------------------------------------------------------------------------------
//----------------------------------------------------------------------
// called from iPhone runSim-tab
int medPing_Main()
{
	// print a message to the cell phone
	mP.CELL_PrintF("Hello medPing patient ...\n\n");
	
	//======= DATA STRUCTURE ======================================
	// to hold patient's history of vital signs
	//oneVitalHistoryRecord	vitalHistory[MAX_HISTORY];	

	oneVitalHistoryRecord	vitalHistory[5];	
	// hmr (how many really) vital signs  0 <= hmr < MAX_HISTORY
	long hmr = 0;  
	//=============================================================
	
	RandGen		randGenerator;	// i need a random number generator
	time_t		start, now;		// keep track of time in simulation

	
	// ask user at CELL to input length of simulation
	mP.CELL_PrintF("How many SECONDS would you like to simulate?\n");
	double simulationTime = mP.CELL_fetchReal();
	time(&start);
	
	// simulation loop ....
	time(&now);

	while ( difftime(now,start) < simulationTime ) {		// while still time to simulate ...
		
		long waitThisLongSEC = randGenerator.RandInt(1, MAX_WAIT_SEC);
		mP.CELL_PrintF("\n--------------------------\n");
		mP.CELL_PrintF("\n[PAUSE ... (%d seconds) ]\n", waitThisLongSEC);
		sleep(waitThisLongSEC);	// ZZzzzz.....		
		
		// check our watch ...
		long nSecs = time(&now);				// corresponding variable to struct
		// new variables to store medPing data into before adding
		double newTemp; 						// corresponding variable to struct
		short sys, dia, pulse, resp, gluc;		// corresponding variables to struct
		// get the new data ----------------
		newTemp = mP.getBodyTemperature_F();
		resp = mP.getRespirationRate_BPM();
		pulse = mP.getPulseRate_BPM();
		mP.getBloodPressure_mmHg(sys, dia);
		gluc = mP.getGlucoseLevel_mgdL();
		// ---------------------------------
				
		// now ADD these new vital signs to our history DATA STRUCTURE
		AddHistoryRecord(nSecs, newTemp, pulse, resp, gluc, sys, dia, vitalHistory, hmr);
		if (hmr < MAX_HISTORY) {	// only increment hmr if it is under MAX_HISTORY
			hmr++;
		}
		// PRINT ALL of the series of vital signs so far
		printAllVitalRecords(mP, vitalHistory, hmr);

	} // while still more to simulate ...
		
	// after simulation is finished...
	mP.CELL_PrintF("\n\nSIMULATION OVER.\n\n");
	
	// Search for a record to delete ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	if (hmr > 0) {			// only ask to delete a record if there are any records (i.e. time entered > 0)
		long thisRecord;	// variable to hold which record to delete
	    long raw_time;		// variable to hold which time is being searched for
	    bool found;			// boolean to say whether it was found or not
	    mP.CELL_PrintF("Enter the record to delete by raw_time (secs): ");
	    cin >> raw_time;
	    // find it (using your Find function)
	    found = FindVitalRecord(raw_time, vitalHistory, thisRecord);
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~    
	    // and delete it if found (using your Delete function) ~~~~
		if (found) {
			DeleteHistoryRecord(thisRecord, vitalHistory, hmr);
			printAllVitalRecords(mP, vitalHistory, hmr);
		}
		else {
			printAllVitalRecords(mP, vitalHistory, hmr);
		}
		// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	}
	// end search/delete ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	
	mP.CELL_PrintF("\n\nThank you for choosing medPing.\n");
	
	return 0;
	
} // end medPing_Main()
// ==============================================================================================================================



// =====================
//	AddHistoryRecord 	\\
//---------------------------------------------------------------------------------------------
// Adds one (current) set of vital records to struct
// PRE: 0 < len(vitalHistory) <= MAX_HISTORY
// POST: Nothing returned
// SIDE EFFECTS: struct has new set of vital records
//---------------------------------------------------------------------------------------------
// ==============================================================================================================================
void AddHistoryRecord(/*all in but hmr*/long nSecs, double new_mp_bodyTemp_F, short new_mp_pulseRate, short new_mp_respiratoryRate,
					  short new_mp_glucose, short new_mp_systolic, short new_mp_diastolic, oneVitalHistoryRecord vitalHistory[ ],
					  /*inout*/long& hmr) {

	if (hmr < MAX_HISTORY) { 	// if there is still room in struct to add new data
		// add new data
		vitalHistory[/*i*/hmr].nSecs = nSecs;
		vitalHistory[/*i*/hmr].bodyTemp_F = new_mp_bodyTemp_F;
		vitalHistory[/*i*/hmr].pulseRate = new_mp_pulseRate;
		vitalHistory[/*i*/hmr].respiratoryRate = new_mp_respiratoryRate;
		vitalHistory[/*i*/hmr].systolic = new_mp_systolic;
		vitalHistory[/*i*/hmr].diastolic = new_mp_diastolic;
		vitalHistory[/*i*/hmr].glucose = new_mp_glucose;
	}
	else {		// if there is not sufficient space left in struct...
		// move the current data down one spot
		short x = 0;
		short y = 1;
		short maxNumber = MAX_HISTORY - 1;
		for (short x = 0; x < maxNumber; x++) {
			vitalHistory[x].nSecs = vitalHistory[y].nSecs;
			vitalHistory[x].bodyTemp_F = vitalHistory[y].bodyTemp_F;
			vitalHistory[x].pulseRate = vitalHistory[y].pulseRate;
			vitalHistory[x].respiratoryRate = vitalHistory[y].respiratoryRate;
			vitalHistory[x].systolic = vitalHistory[y].systolic;
			vitalHistory[x].diastolic = vitalHistory[y].diastolic;
			vitalHistory[x].glucose = vitalHistory[y].glucose;
			y++;
		}
		// add the new data in to the highest spot available
		vitalHistory[maxNumber].nSecs = nSecs;
		vitalHistory[maxNumber].bodyTemp_F = new_mp_bodyTemp_F;
		vitalHistory[maxNumber].pulseRate = new_mp_pulseRate;
		vitalHistory[maxNumber].respiratoryRate = new_mp_respiratoryRate;
		vitalHistory[maxNumber].systolic = new_mp_systolic;
		vitalHistory[maxNumber].diastolic = new_mp_diastolic;
		vitalHistory[maxNumber].glucose = new_mp_glucose;
	} // end else

}
// =============================================================================================================================


// =====================
//	FindVitalRecord 	\\
//---------------------------------------------------------------------------------------------
// Finds a single record
// PRE: 0 < hmr <= MAX_HISTORY; raw_time (assigned)
// POST: returns true (if stdin found) or false (if stdin not found)
// SIDE EFFECTS: -----
//---------------------------------------------------------------------------------------------
// =============================================================================================================================
long FindVitalRecord(/*in*/long raw_time, /*in*/oneVitalHistoryRecord vitalHistory[ ], /*inout*/long& thisRecord) {
	long found; // holds the nSecs time from the struct
	for (short i = 0; i < MAX_HISTORY; i++) { 		// i holds the number of iterations
		found = vitalHistory[i].nSecs;
		// if nSecs from the struct is the same as the time given
		if (found == raw_time) {
			cout << "Found" << endl;
			thisRecord = i;
			return true;
		}
	}
	cout << "Record not found, none deleted." << endl;
	return false;
}
// =============================================================================================================================


// =================
//	Delete History 	\\
//---------------------------------------------------------------------------------------------
// Deletes a single record from the current (last set of) history
// PRE: 0 < len(vitalHistory) <= MAX_HISTORY; recordIndex != -1
// POST: Nothing returned
// SIDE EFFECTS: single vital record is deleted
//---------------------------------------------------------------------------------------------
// =============================================================================================================================
void DeleteHistoryRecord(/*in*/long recordIndex, /*in*/oneVitalHistoryRecord vitalHistory[ ], /*inout*/long& hmr) {
	short y = recordIndex + 1; 			// holds the next vital record in for loop
	short maxNumber = MAX_HISTORY - 1; 	// limit the number of records to move over as the last slot will be removed
	// move the records down one
	for (short x = recordIndex; x < maxNumber; x++) { 	// x is to show what iteration it is in the record
		vitalHistory[x].nSecs = vitalHistory[y].nSecs;
		vitalHistory[x].bodyTemp_F = vitalHistory[y].bodyTemp_F;
		vitalHistory[x].pulseRate = vitalHistory[y].pulseRate;
		vitalHistory[x].respiratoryRate = vitalHistory[y].respiratoryRate;
		vitalHistory[x].systolic = vitalHistory[y].systolic;
		vitalHistory[x].diastolic = vitalHistory[y].diastolic;
		vitalHistory[x].glucose = vitalHistory[y].glucose;
		y++;
	}
	hmr--;
}
// =============================================================================================================================


//---------------------\
// printAllVitalRecords \
//---------------------------------------------------------------------------------------------
// Prints history (last set of) hmr vital signs (to medPing output)
// PRE: 0 < len(vitalHistory) <= MAX_HISTORY
// POST: Nothing returned
// SIDE EFFECTS: vital records printed to console
//---------------------------------------------------------------------------------------------
void printAllVitalRecords(/*in*/medPing& mP, /*in*/const oneVitalHistoryRecord vitalHistory[ ], /*in*/long hmr)
{
	if (hmr > 0)
	{
		mP.CELL_PrintF("\n---- Records (so far) ----");


		for(short i = 0; i < hmr; i++)		// i holds number of iterations
			{
				mP.CELL_PrintF("\nRECORD [%02d]\n", i);
				mP.CELL_PrintF("\t time(secs): \t%d\n", 			vitalHistory[i].nSecs);
				mP.CELL_PrintF("\t temp(F): \t%4.1f\n", 			vitalHistory[i].bodyTemp_F);
				mP.CELL_PrintF("\t pulse(BPM): \t%4d\n",   			vitalHistory[i].pulseRate);
				mP.CELL_PrintF("\t resp rate: \t%4.1d\n", 			vitalHistory[i].respiratoryRate);
				mP.CELL_PrintF("\t pressure: %hd over %hd\t\n",vitalHistory[i].systolic, vitalHistory[i].diastolic);
				mP.CELL_PrintF("\t glucose: \t%4.1d\n",          	vitalHistory[i].glucose);
			}

		mP.CELL_PrintF("\n---- end History ----\n\n");

	} // if any records
	else 
		mP.CELL_PrintF("\nNo History so far ...\n\n");
	
} // printAllVitalRecords() ====================================================================================================