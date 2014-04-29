// Vect.cpp
#ifndef CLOSE_ENOUGH
#define CLOSE_ENOUGH  0.01
#include "vect.h"

#include <iostream>
#include <stdlib.h>
#include <iomanip>
#include "math.h"

using namespace std;

//-----------------------------------------------------------------------
//----- Constructors (CTOR) ---------------------------------------------

Vect::Vect()
/*
PRE:  None
POST: Will create a new vector object with the default settings
*/
{
      this->size = 3;                          // Default size
      this->pVect = new double[size];          // Creates a new block of doubles
}

//-----------------------------------------------------------------------

Vect::Vect(/*in*/long n)
/*
PRE:  n is assigned
POST: Will create a new vector object of the desired size n
*/
{
     // you do this ...
    this->size = n;                          // Default size
    this->pVect = new double[size];          // Creates a new block of doubles
    
    
}

//-----------------------------------------------------------------------
// COPY CTOR
Vect::Vect(/*in*/const Vect& vect2)
/*
PRE:  vect2 is assigned
POST: Will create a new vector object of the same size as vect2 and 
      with the same values
*/
{
       this->size = vect2.size;                // Size set to the size of vect2
       this->pVect = new double[this->size];   // Creates a new block of doubles
       
       // Copy all elements of vect2 into the new vector
       // you do this ...
       
       for (short i = 0; i < size; i++) {
          pVect[i] = vect2[i];
       }    
       
}

//-----------------------------------------------------------------------
//----- Destructor (DTOR) -----------------------------------------------

Vect::~Vect()
/*
PRE:  None
POST: Will free pVect so that memory can be used again
*/
{
    // you do this ....
    delete(pVect);  
    
    
}

//-----------------------------------------------------------------------
//----- Get magnitude of vector -----------------------------------------

double Vect::getMagnitude()
/*
PRE:  None
POST: Returns the magnitude of the vector
*/
{
      double magnitude;        // Holds final magnitude of vector
      double sum = 0;          // Holds sum of all elements squared
      short i = 0;             // Counter Declaration
      
      // Loops through all elements in the vector and adds up the sqaures of each element
 
      // you do this ...
      while (i < this->size) {
        sum += (pVect[i]*pVect[i]);
        i++;
      }
      
      magnitude = sqrt(sum);   
      
      return magnitude;
}

//-----------------------------------------------------------------------
//----- Set elements of vector ------------------------------------------

double& Vect::operator[] (/*in*/long i) const
/*
PRE:  i is assigned
POST: Returns desired dereferenced vector element 
*/
{
      // Checks that i is a valid index, if not the program exits
      if (i < 0 || i >= this->size)
      {
            cerr << "ERROR:index [" << i << "] is out of bounds." << endl;
            system("PAUSE");
            exit(-1);
      }// end if
      
      return pVect[i];
}

//-----------------------------------------------------------------------

Vect& Vect::operator=(/*in*/const Vect& vect2)
/*
PRE:  vect2 is an assigned vector
POST: Copies all elements of vect2 to vector making the call and
      changes its size if needed to match vect2
      Returns cloned vector
*/
{
      // you do this ...
      if (this->size < vect2.size) {
        cout << "There is not enough space in the vector..." << endl;
        this->size = vect2.size;
        cout << "Enlarged the vector." << endl;
      }
      
      for (short i = 0; i < this->size; i++) {
        this->pVect[i] = vect2[i];
      }    
    
      return *this;
}

//-----------------------------------------------------------------------
//----- Vector arithmetic ----------------------------------------------

const Vect Vect::operator+(/*in*/const Vect& vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns vector temp which is the sum of the vector making 
      the call and vect2
*/
{
      short tempSize;
      if (this->size > vect2.size) {
        tempSize = this->size;
      }
      else if (this->size < vect2.size) {
        tempSize = vect2.size;
      }
      else {
        tempSize = this->size;
      }
      Vect temp(tempSize);
      for (short i = 0; i < tempSize; i++) {
        if (i > vect2.size-1) {
          vect2[i] = 0;
        }
        if (i > this->size-1) {
          this->pVect[i] = 0;
        }
        temp[i] = this->pVect[i] + vect2[i];
      }
      
      return temp;
}

//-----------------------------------------------------------------------


const Vect Vect::operator-(/*in*/const Vect& vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns vector temp which is the difference between the vector making 
      the call and vect2
*/
{
      // reverse direction of vect2 (*-1)
      //vect2 = (vect2 * -1);
      short tempSize;
      Vect temp;
      if (this->size > vect2.size) {
        tempSize = this->size;
      }
      else if (this->size < vect2.size) {
        tempSize = vect2.size;
      }
      else {
        tempSize = this->size;
      }
      temp.size = tempSize;
      for (short i = 0; i < tempSize; i++) {
        temp[i] = this->pVect[i] + (-1*vect2[i]);
      }
      
      return temp;    
}

//-----------------------------------------------------------------------



//----- Compare vectors -------------------------------------------------

bool Vect::operator==(/*inout*/Vect& vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns true if mag vect1 == mag vect2
*/
{
      return fabs(this->getMagnitude() - vect2.getMagnitude()) < CLOSE_ENOUGH;
}
//-----------------------------------------------------------------------


bool Vect::operator!=(/*inout*/Vect& vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns true if mag vect1 != mag vect2
*/
{
      return fabs(this->getMagnitude() - vect2.getMagnitude()) > CLOSE_ENOUGH;
}
//-----------------------------------------------------------------------


bool Vect::operator>(/*inout*/Vect& vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns true if mag vect1 > mag vect2
*/
{
      return this->getMagnitude() > vect2.getMagnitude();
}
//-----------------------------------------------------------------------


bool Vect::operator<(/*inout*/Vect& vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns true if mag vect1 < mag vect2
*/
{
      return this->getMagnitude() < vect2.getMagnitude();
}
//-----------------------------------------------------------------------

bool Vect::operator>=(/*inout*/Vect& vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns true if mag vect1 >= mag vect2
*/
{
      return this->getMagnitude() > vect2.getMagnitude() || this->getMagnitude() == vect2.getMagnitude();
}
//-----------------------------------------------------------------------


bool Vect::operator<=(/*inout*/Vect& vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns true if mag vect1 <= mag vect2
*/
{
      return this->getMagnitude() < vect2.getMagnitude() || this->getMagnitude() == vect2.getMagnitude();
}
//-----------------------------------------------------------------------



//----- Dot Product -----------------------------------------------------

const double Vect::operator*(/*in*/const Vect& vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns product of the multiplication of the two vectors into a double
*/
{
      short tempSize;
      double sum = 0;
      Vect temp;
      if (this->size > vect2.size) {
        tempSize = this->size;
      }
      else if (this->size < vect2.size) {
        tempSize = vect2.size;
      }
      else {
        tempSize = this->size;
      }
      temp.size = tempSize;
      for (short i = 0; i < tempSize; i++) {
        sum += this->pVect[i] * vect2[i];
      }

      return sum;
}
//-----------------------------------------------------------------------

const Vect Vect::operator*(/*in*/const double& mult)
/*
PRE:  vect2 is an assigned vector
POST: Returns product of the scalar multiplication
*/
{
      for (short i = 0; i < this->size; i++) {
        this->pVect[i] = this->pVect[i] * mult;
      }

      return *this;
}
//-----------------------------------------------------------------------

const Vect Vect::operator^(/*in*/const Vect& vect2)
/*
PRE:  vect2 is an assigned vector
POST: Returns cross product of the vector into another vector
*/
{
      short tempSize;
      Vect temp;
      if (this->size == 3 && vect2.size == 3) {
        tempSize = this->size;
        temp.size = tempSize;
      }
      else {
        cout << "Can only find cross product of vectors size 3" << endl;
        return *this;
      }

      for (short i = 0; i < tempSize; i++) {
        switch (i) {
          case 0:
            temp[i] = this->pVect[i+1] * vect2[i+2] - this->pVect[i+2] * vect2[i+1];
            break;
          case 1:
            temp[i] = this->pVect[i+1] * vect2[i-1] - this->pVect[i-1] * vect2[i+1];
            break;
          case 2:
            temp[i] = this->pVect[i-2] * vect2[i-1] - this->pVect[i-1] * vect2[i-2];
            break;
          default:
            cout << "Error" << endl;
        }  
      }

      return temp;
}


//-----------------------------------------------------------------------
//----- Print vectors ---------------------------------------

ostream& operator<<(/*inout*/ostream& output, /*in*/const Vect& vector)
/*
PRE:  << operators still used with cout and vector is an assigned vector
POST: Returns ostream output for the vector

operator assignment "<<": prints vector in <a,b,c...> format
*/
{ 
      output << '<' << vector.pVect[0]; //front bracket
     
      // Loops through remaing elements and prints them
      for(short i=1; i < vector.size; i++)
            output << ',' << vector.pVect[i]; //dimen. values
     
      output << '>'; //back bracket
     
      return output; 
}

//-----------------------------------------------------------------------
#endif