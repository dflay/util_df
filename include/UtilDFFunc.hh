#ifndef UTIL_DF_FUNC_HH
#define UTIL_DF_FUNC_HH

// miscellaneous functions that are helpful

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <string> 
#include <sstream>
#include <iterator> 
#include <sys/stat.h>
#include <sys/dirent.h>

#include "TTree.h"
#include "TFile.h"

namespace util_df{
   std::string GetStringTimeStampFromUTC(unsigned long unix_time); 
   unsigned long int GetUTCTimeStampFromString(std::string timeStamp,bool isDST=false);
   bool IsInCharString(const char *str1,const char *search);
   int RemoveWhiteSpace(std::string &str); 
   int MakeDirectory(const char *path); 
   int SplitString(const char delim,const std::string myStr,std::vector<std::string> &out);
   int SplitString_whiteSpace(const std::string myStr,std::vector<std::string> &out); 
   int MakeClass(const char *path,const char *className,const char *treeName="T");  
   char *BinaryToAscii(int N,int binary_data[]);
   int GetBit16(int k,u_int16_t data); 
   int GetBit32(int k,u_int32_t data); 
   int HexToBinary(char hex[]);
   int HexToDecimal(char hex[]); 
   unsigned int BinaryToHex16(int binary[]);
   unsigned long BinaryToHex32(int binary[]); 
   void AsciiToBinary(int N,char *ascii,int binary[]); 
} // ::util_df

#endif 
