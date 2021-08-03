#ifndef UTIL_DF_RADIATION_HH
#define UTIL_DF_RADIATION_HH

#include <cstdlib>
#include <iostream>  

#include "UtilDFConstants.hh"
#include "UtilDFUnits.hh"

namespace util_df { 
   namespace Radiation {
      double GetDose(double edep,double mass,int units=Units::Gy); 
   } //::Radiation
} //::util_df

#endif 
