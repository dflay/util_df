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
      //______________________________________________________________________________
      double GetSkinDepth(double f,double rho,double mu_r,double eps_r){
	 // input: 
	 // - f     = frequency (Hz) 
	 // - rho   = resistivity (Ohm-m) 
         // - mu_r  = relative magnetic permeability 
         // - eps_r = relative electric permittivity
         // output: 
         // - the maximum depth (in m) an RF signal at frequency f penetrates the material with 
         //   parameters rho, mu_r, eps_r  
         double omega = 2.*TMath::Pi()*f; 
         double mu    = mu_r*Constants::mu_0; 
         double eps   = eps_r*Constants::eps_0;
         double roe   = rho*omega*eps;  
         double T1    = TMath::Sqrt( 2.*rho/(omega*mu) ); 
         double T2a   = TMath::Sqrt( 1. + roe*roe ); 
         double T2b   = roe; 
         double T2    = TMath::Sqrt(T2a + T2b); 
         double delta = T1*T2; 
	 return delta; 
      }
   } // ::Radiation
} // ::util_df
