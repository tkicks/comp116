#ifndef myJOB#define myJOB//----------------------------------------------------------------------//  SPECIFICATION FILE (JOB.h)//  This module declares a new type for ONE JOB//----------------------------------------------------------------------#include "constants.h"class JOB{  public:	  JOB();   // CTOR	  	  int id();	  string jobName();	  double totalTime();	  double timeLeft();        		  private:					};  // end class JOB#endif