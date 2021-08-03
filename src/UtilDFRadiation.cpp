#include "UtilDFRadiation.hh"
//______________________________________________________________________________
namespace util_df {
   namespace Radiation {
      //______________________________________________________________________________
      double GetDose(double edep,double mass,int units){
	 // dose in Gray (Gy) = J/kg
	 // input
	 // - energy deposition (GeV) 
	 // - mass of material (grams)
         double mass_kg = mass/1E+3; 
	 double edep_j  = edep*Constants::joule_per_gev;
         double dose=0;
	 if(mass!=0){
	    dose = edep_j/mass_kg;
	    if(units==Units::rad) dose *= 100; 
	 }else{
	    std::cout << "[util_df::Radiation::GetDose]: ERROR! mass = 0; returning 0." << std::endl;
         }
	 return dose;
      }
   } // ::Radiation
} // ::util_df
