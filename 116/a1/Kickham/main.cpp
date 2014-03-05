/* --------------------------------------------------------------
 Programmer: Tyler Kickham
 
 Summary: This program will take 3 body temperatures (F/x) and 3 heart rates (BPM/y) and see if there is any correlation between the
 x and y pairs.
 
 Date last modified: 2/6/14
 ----------------------------------------------------------------*/

/*--------------------------------------------------------------
 INPUT: real numbers from the keyboard or randomly generated depending on which part is commented out, stdin to the x and y variables
 
 OUTPUT: stdout list of the 3 pairs of (x, y) to the screen along with the strength of correlation in numeric and word forms
 ---------------------------------------------------------------
 */


#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;

#include "vitalSigns.h"


int main()
{
	cout << endl << "Find the strength of association between three pairs of body temperatures and heart rates." << endl << endl;
	// DECLARE CONSTANTS
	const short								// ----- CONSTANT declarations -----
            N = 3;                          // number of (x,y) pairs
	
	const double STRENGTH = 0.50;			// value to measure strength of association
	
	
	// DECLARE VARIABLES	
	double									// ----- VARIABLE declarations -----
	x1, y1,									// first  (x,y) pair
	x2, y2,									// second (x,y) pair
	x3, y3;									// third  (x,y) pair

    // obtaining the xs and ys ========================================================

	// through random number generation
	// comment out between here and single dotted line and uncomment next section for keyboard input
	srand(time(0));		// create a seed to get different random numbers each run
	x1 = 97 + rand() % 3;		// this will tak the first number (97 or 60) and then add a random number
	y1 = 60 + rand() % 40;		// (between either 0-3 or 0-40) and add that to the base number to generate
	x2 = 97 + rand() % 3;		// a "random" body temperature for xs and bpm for ys
	y2 = 60 + rand() % 40;
	x3 = 97 + rand() % 3;
	y3 = 60 + rand() % 40;
	// -------------------------------------------------------------------------------

	printf("(F,BPM) pair 1:  (%6.2f, %6.2f)\n", x1, y1);
	printf("(F,BPM) pair 2:  (%6.2f, %6.2f)\n", x2, y2);
	printf("(F,BPM) pair 3:  (%6.2f, %6.2f)\n", x3, y3);

    /*	// through keyboard input
	x1 = getBodyTemperature_F();
	y1 = getRespirationRate_BPM();
	x2 = getBodyTemperature_F();
	y2 = getRespirationRate_BPM();
	x3 = getBodyTemperature_F();
	y3 = getRespirationRate_BPM();
	*/

	// ==================================================================================

	// x and y code
	double sumX = x1 + x2 + x3;		// summation of xs
	double sumXsq = x1*x1 + x2*x2 + x3*x3;		// squared summation of xs
	double sumY = y1 + y2 + y3;		// summation of ys
	double sumYsq = y1*y1 + y2*y2 + y3*y3;		// squared summation of ys
	
	// numerator code
	double numerator1 = x1*y1 + x2*y2 + x3*y3;	// the first part of the numerator
	double numerator = (N*numerator1) - (sumX*sumY);		// numerator for r
	cout << "Numerator = " << numerator << endl;

	// denominator code
	double denom1 = sqrt(N*(sumXsq) - (sumX*sumX));		// first part of the denominator of r
	double denom2 = sqrt(N*(sumYsq) - (sumY*sumY));		// second part of the denominator of r
	double checkDenom = denom1*denom2;			// variable to check division by 0

	// checks
	if (checkDenom == 0) {			// divide by zero
		cout << "You cannot divide by zero" << endl;
		return -1;
	}
	else if (N*(sumXsq) - (sumX*sumX) < 0 || N*(sumYsq) - (sumY*sumY) < 0) {		// imaginary number
		cout << "You cannot take the square root of a negative number." << endl;
		return -1;
	}
	else {
		cout << "Denominator = " << denom1*denom2 << endl;
		double r = numerator/(denom1*denom2);		// correlation variable
		double r2 = r*r;							// strength of association
		cout << endl;

	    printf("Correlation coefficient: %6.2f\n", r);
	    printf("Strength of association: %6.2f\n", r2);

	    // strength of correlation
	    if (r2 >= STRENGTH) {
	    	cout << endl << "There is a STRONG (greater than 0.5) correlation." << endl;
	    }
	    else {
	    	cout << "There is a WEAK (less than 0.5) correlation." << endl;
	    }
	}
    
    cout << endl << "Finished." << endl << endl;
	return 0;
	
} // end main()