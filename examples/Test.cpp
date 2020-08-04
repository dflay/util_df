// Test the UtilDF library 

#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

#include "CSVManager.hh"
#include "UtilDFGraph.hh"
#include "UtilDFMath.hh"

int Test(){

   // read data from a csv file and make a plot 
   util_df::CSVManager *myCSV = new util_df::CSVManager(); 
   myCSV->ReadFile("data.csv",true); 

   std::vector<std::string> header;
   myCSV->GetHeader(header); 
   std::string xAxisLabel = header[0]; 
   std::string yAxisLabel = header[1]; 

   // get vectors of data   
   std::vector<double> x,y;
   myCSV->GetColumn_byName<double>(xAxisLabel,x); 
   myCSV->GetColumn_byName<double>(yAxisLabel,y); 
 
   // do basic statistics  
   double my = util_df::Math::GetMean<double>(y); 
   double sy = util_df::Math::GetStandardDeviation<double>(y); 
   std::cout << Form("y stats: mean = %.3lf, stdev = %.3lf",my,sy) << std::endl; 
 
   // create graphs    
   TGraph *g = util_df::Graph::GetTGraph(x,y); 
   util_df::Graph::SetGraphParameters(g,20,kBlue);

   TCanvas *c1 = new TCanvas("c1","Data",500,500);

   c1->cd();
   g->Draw("ap");
   util_df::Graph::SetGraphLabels(g,"Test Data",xAxisLabel,yAxisLabel);
   g->Draw("ap");
   c1->Update();

   // create and print to file a table of data
   util_df::CSVManager *myCSV2 = new util_df::CSVManager(); 
   myCSV2->InitTable(2,2);      // set size of table 
   myCSV2->SetHeader("x,y");    // set the header 
   // set data by row (first index) and column (second index) 
   myCSV2->SetElement<double>(0,0,5); 
   myCSV2->SetElement<double>(0,1,10);
   myCSV2->SetElement<double>(1,0,16);
   myCSV2->SetElement<double>(1,1,27);
   myCSV2->WriteFile("table.csv"); 

   delete myCSV;
   delete myCSV2;
   return 0;
}
