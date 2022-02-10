#ifndef UTIL_DF_JSON_MANAGER_HH
#define UTIL_DF_JSON_MANAGER_HH

#include <cstdlib>
#include <iostream>
#include <fstream>

#include "json.hh"

#include "UtilDFConstants.hh" 

using json = nlohmann::json; 

namespace util_df { 

   class JSONManager { 

      private:
	 json fObject;

	 template <typename T>
	    int CheckType(T data) const{
	       int rc=0;
	       if( std::is_arithmetic<T>::value ){
		  if( std::is_integral<T>::value ){
		     // it's an integer or boolean 
		     rc = Constants::kInteger;
		  }else{
		     // it's a double or float 
		     rc = Constants::kDouble;
		  }
	       }else{
		  rc = Constants::kString; // it's a string
	       }
	       return rc;
	    }

      public:
	 JSONManager(const char *filepath="NONE");
	 ~JSONManager();

	 int Print(); 
	 int ReadFile(const char *filepath);

         bool DoesKeyExist(std::string keyName) const;

         int GetVectorFromKey_str(std::string key,std::vector<std::string> &data);

         std::string GetValueFromKey_str(std::string key) const; 
         std::string GetValueFromSubKey_str(std::string key,std::string subKey) const;   

	 // templated methods 
	 template <typename T> T GetValueFromKey(std::string key) const {
	    // this function is to retrieve a number, but could be stored as a string in the JSON object 
            T val; 
            int outDataType = CheckType<T>(val); 
            bool exist = DoesKeyExist(key);
            std::string DATA="";
	    if(exist){ 
	       // key exists 
	       if( fObject[key].is_string() ){
		  // data is a string type, convert to int or double 
		  DATA = fObject[key].get<std::string>(); 
		  if(outDataType==Constants::kInteger) val = std::atoi( DATA.c_str() ); 
		  if(outDataType==Constants::kDouble)  val = std::atof( DATA.c_str() ); 
	       }else{
		  // data isn't a string, just typecast and store the value  
		  val = (T)(fObject[key]);
	       } 
	    }else{
	       // key doesn't exist, return 0
	       val = (T)(0);
            }
	    return val; 
         }  

	 template <typename T> T GetValueFromSubKey(std::string key,std::string subKey) const {
	    // this function is to retrieve a number, but could be stored as a string in the JSON object 
            T val; 
            int outDataType = CheckType<T>(val); 
            bool exist = DoesKeyExist(key);
            std::string DATA="";
	    if(exist){ 
	       // key exists 
	       if( fObject[key][subKey].is_string() ){
		  // data is a string type, convert to int or double 
		  DATA = fObject[key][subKey].get<std::string>(); 
		  if(outDataType==Constants::kInteger) val = std::atoi( DATA.c_str() ); 
		  if(outDataType==Constants::kDouble)  val = std::atof( DATA.c_str() ); 
	       }else{
		  // data isn't a string, just typecast and store the value  
		  val = (T)(fObject[key][subKey]);
	       } 
	    }else{
	       // key doesn't exist, return 0
	       val = (T)(0);
            }
	    return val; 
         }

         template <typename T> 
	    int GetVectorFromKey(std::string key,std::vector<T> &data){
	       T arg;
               int N=0;
	       int outDataType = CheckType<T>(arg); 
               std::string DATA="";
               // first check if the key exists
	       bool exist = DoesKeyExist(key);
	       if(exist){
		  // found the key, fill the vector
		  N = fObject[key].size();
		  for(int i=0;i<N;i++){
		     if( fObject[key][i].is_string() ){
			// data is a string type, convert to int or double 
			DATA = fObject[key][i].get<std::string>(); 
			if(outDataType==Constants::kInteger) arg = std::atoi( DATA.c_str() ); 
			if(outDataType==Constants::kDouble)  arg = std::atof( DATA.c_str() ); 
		     }else{
			// data isn't a string, just typecast and store the value  
			arg = (T)(fObject[key][i]);
		     } 
		     data.push_back(arg);
		  }
	       }else{
		  return 1;
	       } 
	       return 0;
         }

   }; 

} // ::util_df


#endif 
