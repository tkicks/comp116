// Vect.h

#ifndef VECT
#define VECT

//-----------------------------------------------------------------------

#include <iostream>

using namespace std;

//-----------------------------------------------------------------------

class Vect
{
      public:
	         // Constructors (CTOR)
             Vect();                                            // Default CTOR (size = 2)
             Vect( /*in*/ long n);                              // Initializes with a given size
             Vect( /*in*/ const Vect& vect2);                   // Copy CTOR
             
	         // Destructor (DTOR)
             ~Vect();
             
	         // --------- Get magnitude of vector ---------
             double getMagnitude();
             
	         // --------- Set elements of vector ---------
             double& operator[]( /*in*/ long i) const;          // Sets a single element
             Vect& operator=( /*in*/ const Vect& vect2);        // Sets vector = to another
             
	         // --------- Vector arithmetic ---------
             const Vect operator+(/*in*/const Vect& vect2);     // Addition
             const Vect operator-(/*in*/const Vect& vect2);     // Subtraction
             
             const Vect operator*(/*in*/const double& mult);    // Scalar Multiplication
             
             const double operator*(/*in*/const Vect& vect2);   // Dot Product
             const Vect operator^(/*in*/const Vect& vect2);     // Cross Product
             
	         // --------- Compare vectors (based on magnitude) ---------
             bool operator==(/*inout*/Vect& vect2);             // Equal to
             bool operator!=(/*inout*/Vect& vect2);             // Not equal to
             bool operator<(/*inout*/Vect& vect2);              // Less than
             bool operator>(/*inout*/Vect& vect2);              // Greater than
             bool operator<=(/*inout*/Vect& vect2);             // Less than or equal to
             bool operator>=(/*inout*/Vect& vect2);             // Greater than or equal to
             
	         // --------- Print vectors ---------
             // enables client to do:  cout << V;
             friend ostream& operator<<(/*inout*/ostream& output, /*in*/const Vect& vector);

             
      private:
	          // ------------- data structure -----------------
	          // Pointer to a block of doubles that hold elements of vector
              double* pVect;
              
              // Holds size (dimension) of the current vector
              long size;
              // -----------------------------------------------
};

//-----------------------------------------------------------------------

#endif
