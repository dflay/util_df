#ifndef UTIL_DF_HISTOGRAM_HH
#define UTIL_DF_HISTOGRAM_HH

// useful functions for algorithms involving histograms  

#include <cstdlib>
#include <iostream>

#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"

namespace util_df { 
   namespace Histogram {
      double GetSum(TH1F *h,double min,double max);
      double GetIntegral(TH1F *h,double min,double max);
      double GetSum2D_rect(TH2F *h,double xmin,double xmax,double ymin,double ymax);
      double GetSum2D_circ(TH2F *h,double R,double XC=0,double YC=0);
      double GetIntegral2D(TH2F *h,double xmin,double xmax,double ymin,double ymax);
   } // ::Histogram 
} // ::util_df

#endif