#! /bin/bash  
# a simple script to build UtilDF
#_______________________________________________________________________________
function cleanup { 
   echo "Cleaning up previous build..."
   rm -r CMakeFiles *.cmake *.txt *.cxx *.pcm *.rootmap Makefile *.so *.dylib
   echo "--> Done!"
}
#_______________________________________________________________________________
function configure { 
   echo "Configuring..."
   cmake -DCMAKE_INSTALL_PREFIX=../install \
   ../util_df 
   echo "--> Done!"
}
#_______________________________________________________________________________
function build_lib { 
   echo "Building..."
   make && make install
   cp *.pcm *.rootmap ../install/lib
   # for macOS
   cd ../install/lib && rm *.so && ln -s libUtilDF.dylib libUtilDF.so
   echo "--> Done!"
}
#_______________________________________________________________________________
# main 
cleanup
configure
build_lib
