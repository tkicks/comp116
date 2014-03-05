#include "vitalSigns.h"

// -------------------\
//  getBodyTemperature \
// --------------------------------------------------------------
// IN: (no arguments)
// RETURNS: simulated body temperature in degrees F
// --------------------------------------------------------------
double getBodyTemperature_F(void)
{
    double temp;	// temperature
    
    // for now, just enter value at keyboard
    cout << "Enter a body temp(F): ";
    cin >> temp;
    
    return temp;
}


// -------------------\
//  getBodyTemperature \
// --------------------------------------------------------------
// IN: (no arguments)
// RETURNS: simulated body temperature in degrees F
// --------------------------------------------------------------
double getRespirationRate_BPM(void)
{
    double rate;	// heart rate

    cout << "Enter a respiration rate (BPM): ";
    cin >> rate;

    return rate;
}
