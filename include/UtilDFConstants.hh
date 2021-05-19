#ifndef UTIL_DF_CONSTANTS_HH
#define UTIL_DF_CONSTANTS_HH

// constants and enumerated types 

namespace util_df {
 
   namespace Constants {

      enum freqType{
	 Hz  = 0,
	 kHz = 1,
	 MHz = 2,
	 GHz = 3,
         ppm = 4,
	 ppb = 5 
      }; 

      enum statsType {
	 kBesselsCorrectionDisabled = 0,
	 kBesselsCorrectionEnabled  = 1 
      };

      enum materialName{
	 kHelium,
	 kAluminum,
	 kCopper,
	 kTungsten,
	 kGlass
      }; 

      enum unitClass{
	 kCGS,
	 kMKS
      };

      static const int FTSIZE           = 1E+7; 

      static const double alpha         = 1.0/137.0359895;
      static const double PI            = 3.14159265;

      static const double radian        = 1.; 
      static const double deg           = 0.017453293; // 1 deg = pi/180 radians 
      static const double electron_mass = 0.511E-3;    // GeV 
      static const double proton_mass   = 0.9383;      // GeV 
      static const double pion_mass     = 0.140;       // GeV

      static const double mu_0          = 1.2566371e-06; // 4pi*1E-7

      static const double Gauss         = 1E-4;         // 1 Gauss    = 1E-4 Tesla 
      static const double Oerstead      = 79.577471546; // 1 Oerstead = 79.6 A/m  

   } //::constants 

} //::util_df

#endif 
