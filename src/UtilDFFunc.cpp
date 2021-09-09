#include "UtilDFFunc.hh"
//______________________________________________________________________________
namespace util_df {
   //______________________________________________________________________________
   int RemoveWhiteSpace(std::string &str){
      str.erase(remove(str.begin(),str.end(),' '),str.end());
      return 0;
   }
   //______________________________________________________________________________
   bool IsInCharString(const char *str1,const char *search){
      // find phrase in a string  
      for(int i=0;i<strlen(str1);i++){
	 if(strncmp (&str1[i], search, strlen(search)) == 0){
	    return true;
	 }
      }
      return false;
   }
   //______________________________________________________________________________
   int SplitString_whiteSpace(const std::string myStr,std::vector<std::string> &out){
      std::istringstream buffer(myStr);
      std::copy(std::istream_iterator<std::string>(buffer), 
	    std::istream_iterator<std::string>(),
	    std::back_inserter(out));
      return 0;
   }
   //______________________________________________________________________________
   int SplitString(const char delim,const std::string myStr,std::vector<std::string> &out){
      // split a string by a delimiter
      std::stringstream ss(myStr);
      std::vector<std::string> result;

      while( ss.good() ){
	 std::string substr;
	 std::getline(ss,substr,delim);
	 out.push_back(substr);
      }
      return 0;
   }
   //______________________________________________________________________________
   int MakeClass(const char *path,const char *className,const char *treeName){
      // create a class using TTree::MakeClass
      TFile *f = new TFile(path); 
      TTree *myTree; 
      f->GetObject(treeName,myTree);
      myTree->MakeClass(className);
      f->Close();
      return 0; 
   }
   //______________________________________________________________________________
   std::string GetStringTimeStampFromUTC(unsigned long unix_time){
      time_t     utime = unix_time;
      struct tm  ts;
      char       buf[100];
      // Format time as "ddd yyyy-mm-dd hh:mm:ss zzz"
      ts = *localtime(&utime);
      strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
      std::string timeStamp = buf;
      return timeStamp;
   }
   //______________________________________________________________________________
   unsigned long int GetUTCTimeStampFromString(std::string timeStamp,bool isDST){
      // takes a time stamp string and converts to UTC integer
      // returns the UTC time in SECONDS
      // note the format of the timestamp (ddd yyyy-mm-dd hh:mm::ss zzz)  
      char dayOfWeek[5],timeZone[5];  
      int yy,mm,dd,hour,min,sec;
      std::sscanf(timeStamp.c_str(),"%s %04d-%02d-%02d %02d:%02d:%02d %s",
                  dayOfWeek,&yy,&mm,&dd,&hour,&min,&sec,timeZone);
      struct tm timeinfo = {0};
      timeinfo.tm_year = yy-1900;  // years since 1900 
      timeinfo.tm_mon  = mm-1;     // months since january (0--11)  
      timeinfo.tm_mday = dd;
      timeinfo.tm_hour = hour;
      timeinfo.tm_min  = min;
      timeinfo.tm_sec  = sec;
      int corr = 0;
      // FIXME: there's got to be a better way to do this... 
      // int isDST = timeinfo.tm_isdst; 
      if(isDST) corr = 3600; // daylight savings time, subtract 1 hour  
      time_t timeSinceEpoch = mktime(&timeinfo) - corr;
      return timeSinceEpoch;    
   }
   //______________________________________________________________________________
   int MakeDirectory(const char *path){
      int rc=0;
      struct stat SB;

      const int SIZE = 200;
      char *dir_path = new char[SIZE];

      sprintf(dir_path,"%s",path);

      // check to see if the directory exists
      if( (stat(dir_path,&SB)==0)&&(S_ISDIR(SB.st_mode)) ){
	 // the directory exists!  Do nothing.  
	 // You can also check for other file types using other S_IS* macros:
	 // S_ISDIR — directory
	 // S_ISREG — regular file
	 // S_ISCHR — character device
	 // S_ISBLK — block device
	 // S_ISFIFO — FIFO
	 // S_ISLNK — symbolic link
	 // S_ISSOCK — socket
      }else{
	 rc = mkdir(dir_path,0700);
      }

      if(rc!=0) std::cout << "[util_df::MakeDirectory]: Cannot make the directory: " << path << std::endl;

      delete[] dir_path;

      return rc;
   }
   //______________________________________________________________________________
   int GetBit16(int k,u_int16_t data){
      int n        = data;
      int mask     = 1 << k;        // move "1" k spaces to the left
      int masked_n = n & mask;      // AND n with mask -- this picks out the bit at position k 
      int the_bit  = masked_n >> k; // move the masked_n k spaces to the right  
      return the_bit; 
   }
   //______________________________________________________________________________
   int GetBit32(int k,u_int32_t data){
      int n        = data;
      int mask     = 1 << k;        // move "1" k spaces to the left
      int masked_n = n & mask;      // AND n with mask -- this picks out the bit at position k 
      int the_bit  = masked_n >> k; // move the masked_n k spaces to the right  
      return the_bit; 
   }
   //______________________________________________________________________________
   char *BinaryToAscii(int N,int binary_data[]){
      // works for bytes (that is, nbits >= 8) 

      int length = N; // strlen(input);     // get length of string

      const int SIZE = length/8; 

      int binary[8];    // array used to store 1 byte of binary number (1 character)
      int asciiNum = 0; // the ascii number after conversion from binary
      char ascii;       // the ascii character itself

      char *ascii_array = (char *)malloc( sizeof(char)*(SIZE+1) ); 

      int power[8];
      int i=0,j=0,z=0; 
      for(i=0;i<8;i++) power[i] = i; 

      double a=0,b=0;

      // printf("Num bits = %d, N = %d \n",length,length/8); 

      for(i=length/8-1;i>=0;i--){
	 // reading in bytes. total characters = length / 8
	 for(j=0;j<8;j++){    
	    // store info into binary[0] through binary[7]
	    // binary[j] = data[z] - 48;      // z never resets.  why 48?? 
	    binary[j] = binary_data[z];      // z never resets 
	    // printf("bit %d: %d \n",j+4*i,binary[j]);
	    z++;
	 }
	 // compute the ascii number
	 for(j=0;j<8;j++){
	    a = binary[j];            // store the element from binary[] as "a"
	    b = power[j];             // store the lement from power[] as "b"
	    asciiNum += a*pow(2, b);  // asciiNum = sum of a * 2^power where 0 <= power <= 7, power is int
	 }
	 ascii    = asciiNum;         // assign the asciiNum value to ascii, to change it into an actual character
	 asciiNum = 0;                // reset asciiNum for next loop

	 ascii_array[i] = ascii; 

	 // printf("%c",ascii);         // display the ascii character
      }

      return ascii_array; 
   }
   //______________________________________________________________________________
   void AsciiToBinary(int N,char *ascii,int binary[]){
      // int SIZE = N*8 + 1;   // 1 extra for the \n 
      int num_value=0;
      // int binary[SIZE]; 

      int length = strlen(ascii);                          
      int count  = 0;
      int pos    = 0;

      int i=0;
      for (i = length-1; i>=0; i--){
	 num_value = ascii[i];
	 while(count<8){
	    if( (num_value%2) == 0){
	       binary[pos] = 0;
	       num_value = num_value/2;
	       count++;
	       pos++;
	    }else{
	       binary[pos] = 1;
	       num_value = num_value/2;
	       count++;
	       pos++;
	    } 
	 }
	 count = 0; /*resets loop counter*/
      }

      // printf("Binary representation of %s: ",ascii);

      // int space=0; 
      // int j=0; 
      // for(j = pos-1; j >= 0; j--){
      //    printf("%d", binary[j]);
      //    space++;
      //    if(space == 8){
      //       printf(" "); /*white space between bytes*/
      //       space = 0; 
      //    }
      // } 

      // printf("\n"); 
   }
   //______________________________________________________________________________
   int HexToBinary(char hex[]){
      int i, length, decimal=0, binary=0;
      for(length=0; hex[length]!='\0'; ++length);
      for(i=0; hex[i]!='\0'; ++i, --length){
	 if(hex[i]>='0' && hex[i]<='9')
	    decimal+=(hex[i]-'0')*pow(16,length-1);
	 if(hex[i]>='A' && hex[i]<='F')
	    decimal+=(hex[i]-55)*pow(16,length-1);
	 if(hex[i]>='a' && hex[i]<='f')
	    decimal+=(hex[i]-87)*pow(16,length-1);
      }

      // At this point, the variable decimal contains the hexadecimal number 
      // in decimal format. 

      i=1;
      while (decimal!=0){
	 binary+=(decimal%2)*i;
	 decimal/=2;
	 i*=10;
      }

      return binary;
   }
   //______________________________________________________________________________
   unsigned int BinaryToHex16(int binary[]){
      const int NBITS = 16; 
      int pwr[NBITS]; 

      int i=0;
      for(i=0;i<NBITS;i++) pwr[i] = i; 

      // convert binary array to decimal  
      int dec=0;
      // start with LSB 
      for(i=NBITS-1;i>=0;i--){
	 dec += binary[i]*pow(2,pwr[i]); 
      }

      unsigned int hex = (unsigned int)dec;
      return hex; 
   }
   //______________________________________________________________________________
   unsigned long BinaryToHex32(int binary[]){
      const int NBITS = 32;  
      int pwr[NBITS]; 

      int i=0;
      for(i=0;i<NBITS;i++) pwr[i] = i; 

      // convert binary array to decimal  
      int dec=0;
      // start with LSB 
      for(i=NBITS-1;i>=0;i--){
	 dec += binary[i]*pow(2,pwr[i]); 
      }

      unsigned long hex = (unsigned long)dec;
      return hex; 
   }
} // ::util_df
