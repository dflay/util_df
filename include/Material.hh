#ifndef UTIL_DF_MATERIAL_HH
#define UTIL_DF_MATERIAL_HH

// material struct to make energy loss calcs easier to manage
#include <cstdlib>
#include <iostream> 
#include <string> 

#include "TString.h" 

#include "UtilDFConstants.hh"

namespace util_df {
   typedef struct material {
      std::string name;         // name of material
      double A;                 // molecular mass (g/mol) 
      double Z;                 // mass number (number of protons) 
      double rho;               // density (g/cm^3) 
      double length;            // length or thickness of material (cm) 
      double radLength;         // radiation length (g/cm^2) 
      int ID;                   // material ID (for density corrections) 
      // constructor 
      material(): 
	 name("NONE"),A(0),Z(0),rho(0),length(0),radLength(0),ID(-1) 
      {}
      // functions
      void Print(){
	 std::cout << Form("name: %s"   ,name.c_str()) << std::endl;
	 std::cout << Form("A:    %.2lf",A)            << std::endl;
	 std::cout << Form("Z:    %.2lf",Z)            << std::endl;
	 std::cout << Form("rho:  %.3lf",rho)          << std::endl;
	 std::cout << Form("X_0:  %.3lf",radLength)    << std::endl;
	 std::cout << Form("L:    %.3lf",length)       << std::endl;
      } 
   } material_t; 
}

#endif 
