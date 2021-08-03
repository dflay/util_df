#ifndef UTIL_DF_UNITS_HH
#define UTIL_DF_UNITS_HH

// constants and enumerated types 

namespace util_df {
 
   namespace Units {
      // unit system
     enum unitClass{
	 kCGS,
	 kMKS
      };
     // magnetic field
     enum bFieldUnits { 
	kTesla,
	kGauss
     };
     // radiation
     enum radiationUnits {
	Gy,
	rad
     }; 

   } //::units 

} //::util_df

#endif 
