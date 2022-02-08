// Test the UtilDF library 

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

#include "JSONManager.hh"
#include "CSVManager.hh"
#include "UtilDFGraph.hh"
#include "UtilDFMath.hh"
#include "UtilDFCrossSection.hh"

int Test(){

   // luminosity for a LD2 target (per nucleon)  
   double A   = 2;           // number of nucleons (= Z + N)  
   double rho = 0.161246;    // density in g/cm^3  
   double I = 30E-6;  // 30 uA  
   double x = 15.0;   // 15 cm thick 
   double L = util_df::CrossSection::GetLuminosity(I,rho,x,A);
   std::cout << Form("Target = LD2, I_beam = %.1E A, x = %.1lf cm, Lumi = %.3E cm^-2 s^-1",I,x,L) << std::endl;

   // read data from a csv file and make a plot 
   util_df::CSVManager *myCSV = new util_df::CSVManager(); 
   myCSV->ReadFile("./input/data.csv",true); 

   std::vector<std::string> header;
   myCSV->GetHeader(header); 
   std::string xAxisLabel = header[0]; 
   std::string yAxisLabel = header[1]; 

   // get vectors of data   
   std::vector<double> X,Y;
   myCSV->GetColumn_byName<double>(xAxisLabel,X); 
   myCSV->GetColumn_byName<double>(yAxisLabel,Y); 
 
   // do basic statistics  
   double my = util_df::Math::GetMean<double>(Y); 
   double sy = util_df::Math::GetStandardDeviation<double>(Y); 
   std::cout << Form("y stats: mean = %.3lf, stdev = %.3lf",my,sy) << std::endl; 

   // read a JSON file
   util_df::JSONManager *myJSON = new util_df::JSONManager();
   myJSON->ReadFile("./input/data.json"); 
   myJSON->Print(); 

   std::string v1 = myJSON->GetValueFromKey_str("key-01"); 
   double v2      = myJSON->GetValueFromKey<double>("key-02"); 
   double v3      = myJSON->GetValueFromKey<double>("key-03"); 
   double v4      = myJSON->GetValueFromSubKey<double>("key-04","subkey"); 

   int NPTS = myJSON->GetValueFromKey<int>("npts");
   std::vector<int> vv; 
   myJSON->GetVectorFromKey<int>("key-05",NPTS,vv);
   std::vector<int> vv2; 
   myJSON->GetVectorFromKey<int>("key-06",NPTS,vv2);
   
   std::cout << Form("JSON data: key-01: %s, key-02: %.2lf, key-03: %.2lf, key-04: %.2lf",v1.c_str(),v2,v3,v4) << std::endl;

   std::cout << "Vector from key-05: " << std::endl; 
   for(int i=0;i<NPTS;i++) std::cout << vv[i] << std::endl;  
   std::cout << "Vector from key-06: " << std::endl; 
   for(int i=0;i<NPTS;i++) std::cout << vv2[i] << std::endl;   
 
   // create graphs    
   TGraph *g = util_df::Graph::GetTGraph(X,Y); 
   util_df::Graph::SetParameters(g,20,kBlue);

   TCanvas *c1 = new TCanvas("c1","Data",500,500);

   c1->cd();
   g->Draw("ap");
   util_df::Graph::SetLabels(g,"Test Data",xAxisLabel,yAxisLabel);
   g->Draw("ap");
   c1->Update();

   const int N = X.size();

   // create and print to file a table of data
   util_df::CSVManager *myCSV2 = new util_df::CSVManager(); 
   myCSV2->InitTable(N,2);      // set size of table: N rows, 2 columns 
   myCSV2->SetHeader("x,y");    // set the header 
   // set data by column using vector data 
   myCSV2->SetColumn<double>(0,X); 
   myCSV2->SetColumn<double>(1,Y); 
   myCSV2->WriteFile("./output/table.csv"); 

   delete myCSV;
   delete myCSV2;
   delete myJSON; 

   return 0;
}
