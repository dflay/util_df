#ifndef UTIL_DF_RADIATION_HH
#define UTIL_DF_RADIATION_HH

#include <cstdlib>
#include <iostream>  

#include "UtilDFConstants.hh"
#include "UtilDFUnits.hh"

#include "TMath.h"

namespace util_df { 
   namespace Radiation {
      double GetDose(double edep,double mass,int units=Units::Gy);
      double GetSkinDepth(double f,double rho,double mu_r,double eps_r);  
   } //::Radiation
} //::util_df

#endif 
