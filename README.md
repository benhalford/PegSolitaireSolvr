# SimplePegSolitaireSolver

This is a simple brain dead program to solve the peg solitaire board game, programmed in C++.  
  
  
### Instructions ###  
Compilation command:  
% g++ *.cpp `wx-config --cxxflags --libs` -O3 -o app -std=c++11 -DUSE_INLINE
  
MinGW Compilation command (Linux only -> wxWidget not yet working on Windows):  
% x86_64-w64-mingw32-c++ main.cpp -O3 -o a.exe -static-libgcc -static-libstdc++  
  
Execution command:  
% ./app  
  
Info:  
-O3 optimization will likely be needed for quickest success rate (Or just a really good computer)  
-This is tested on Ubuntu 16.04.3, 17.04 & 17.10 only, Arch Linux 14/02/2018, with GCC/G++ version 7.0.1  
  
  
  
### Disclaimer ###  
The other version in 'old', is OLD! It has no frontend, some multithreading, methods 
for saving board starting layout and their paths to completion in hex format to save on 
space - features that were made redundant by the newer one. But all told, both the 
programming & method is flawed & shoddy and is therefore disavowed.  
