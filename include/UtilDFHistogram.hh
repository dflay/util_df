#ifndef UTIL_DF_HISTOGRAM_HH
#define UTIL_DF_HISTOGRAM_HH

// useful functions for algorithms involving histograms  

#include <cstdlib>
#include <iostream>

#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"

#include "UtilDFMath.hh"
#include "CSVManager.hh"

namespace util_df { 
   namespace Histogram {
      TH1F *GetTH1F(CSVManager *data,const char *var,int NBin,double min=-1,double max=-1); 
      TH1F *GetTH1F(const char *name,std::vector<double> x,int NBin,double min=-1,double max=-1);
      double GetSum(TH1F *h,double min,double max);
      double GetIntegral(TH1F *h);
      double GetIntegral(TH1F *h,double min,double max);
      double GetSum2D_rect(TH2F *h,double xmin,double xmax,double ymin,double ymax);
      double GetSum2D_circ(TH2F *h,double R,double XC=0,double YC=0);
      double GetIntegral2D(TH2F *h,double xmin,double xmax,double ymin,double ymax);
      void SetLabels(TH1F *h,TString Title,TString xAxisTitle,TString yAxisTitle); 
      void SetLabels(TH2F *h,TString Title,TString xAxisTitle,TString yAxisTitle); 
      void SetParameters(TH1F *h,int mStyle,int color,double mSize=0.5,int lWidth=1); 
      void SetParameters(TH2F *h,int mStyle,int color,double mSize=0.5,int lWidth=1); 
   } // ::Histogram 
} // ::util_df

#endif
