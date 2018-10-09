/*
**
**  Compilation command:
**  % g++ -std=c++14 PSAI.cpp -pthread -O3 -o a.out -fopenmp
**
**  MinGW Compilation command: 
**  x86_64-w64-mingw32-c++ PSAI.cpp -std=c++14 -pthread -O3 -o a.exe -static-libgcc -static-libstdc++ -Wl,-Bstatic -lstdc++ -lpthread -lgomp -fopenmp
**
**  Execution command:
**  % ./a.out <board> <seed>
**
**  Info:
**  -O3 optimization will likely be needed for quickest success rate (Or just a really good computer)
**  This is tested on Ubuntu 16.04.3 & 17.04 only, with GCC/G++ version 7.0.1
**
*/ 



#include <random>
#include <iostream>
#include <sstream> 
#include <inttypes.h>
#include <stdio.h>
//#include <math.h>
#include <thread>
//#include <unistd.h>
#include <pthread.h>
#include <cstring>
//Comment out "mingw.threads.h" for compiling on Linux
//#include "mingw.thread.h"
#include <unistd.h>
#include <fstream>
#include <bitset>
#include <omp.h>
#include <algorithm>
#include <cmath>


typedef int_fast8_t i8;



/********************************************************************************************************
 SHARED VARIABLES.
********************************************************************************************************/
std::string c = "111111111111111111111111111111111";
i8 piece_count = -1;
int xy_to_char[97] = {33,33,33,33,33,33,33,33,33,33,33,33,33,0,1,2,33,33,33,33,33,33,33,3,4,5,33,33,33,33,33,6,7,8,9,10,11,12,33,33,33,13,14,15,16,17,18,19,33,33,33,
20,21,22,23,24,25,26,33,33,33,33,33,27,28,29,33,33,33,33,33,33,33,30,31,32,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33,33};
signed long ID;
unsigned long long counter; 


/********************************************************************************************************
 FUNCTIONS ARE DECLARED HERE.
********************************************************************************************************/
int window(char* argv[], int x);
unsigned long long hashIt(std::string board);
std::string unHash(unsigned long long hash);
int printBoard();
std::string toHex(unsigned long long num);
unsigned long long unHex(std::string str);


/********************************************************************************************************
 MAIN SETS BOARD STARTING SETUP, CHECKS FOR THE APPROPRIATE INPUT, STARTS THE THREADS.
********************************************************************************************************/
int main(int argc, char* argv[]){

	c = "OOOOOOOOOOOOOOOO@OOOOOOOOOOOOOOOO";

	ID = hashIt(c);
	for(i8 m = 0; m <= 32; ++m) {
		if(argv[1][m] == '@'){
			piece_count++;
		}
	}

	std::time_t result = std::time(nullptr);

	printBoard();
	#pragma omp parallel for
		for (int i = 0; i < omp_get_num_threads(); ++i)
			window(argv, atoi(argv[2])+omp_get_thread_num());	


}




/********************************************************************************************************
 HASHES THE BOARD LAYOUTS, AND TRANSLATES THE HASH NUMBER.  
********************************************************************************************************/
unsigned long long hashIt(std::string board){
	std::bitset<64> hashNum;
	unsigned long long hashedStep;
	for(int i = 0; i < 33; i++){
		if(board[i] == 'O'){
			hashNum[i] = 1;
		} else {
			hashNum[i] = 0;
		}
	}
	hashedStep = (unsigned long long)hashNum.to_ullong();

	return hashedStep;
}

std::string unHash(unsigned long long hash){
	std::bitset<33> hashNum = hash;
	std::string path = "@@@@@@@@@@@@@@@@O@@@@@@@@@@@@@@@@";
	for(int x = 0; x < 33; ++x){
		if(hashNum[x] == 1){
			path[x] = 'O';
		} else {
			path[x] = '@';
		}
	}
	return path;
	//hashedStep = (unsigned long)hashNum.to_ulong();
}

/********************************************************************************************************
 CONVERTS THE HASHES INTO HEX VALUES, AND CONVERTS THE HEX NUMBER TO DECIMAL.  
********************************************************************************************************/
std::string toHex(unsigned long long num){
	std::stringstream ss;
	ss<< std::hex << num; // int decimal_value
	std::string str ( ss.str() );

	return str;
}

unsigned long long unHex(std::string str){
	unsigned long long num;
	std::stringstream ss;
	ss << str;
	ss >> std::hex >> num;

	return num;
}


/********************************************************************************************************
 4 OF THESE WINDOWS ARE CALLED FOR EACH THREAD, EACH ARE GIVEN A DIFFERENT SEED.
********************************************************************************************************/
int window(char* argv[], int x) {
	printf("<Seed: %lf, Thread: %d>\n", pow(x, 2), x-atoi(argv[2]));

	std::array<std::string,31> _b;
	_b.fill(c);
	i8 mv_clockr;

	std::string b;
	b = c;

	std::mt19937 gen(x);


	i8 empty = 31 - piece_count;
	uint16_t i = 0;

	while(true) {
		i = i + 1;

		if(i > 5000){
			std::string steps;
			steps.append(toHex(hashIt(b))).append("\\");
			for (int i = 0 + piece_count; i <= 29; ++i){
				steps.append(toHex(hashIt(_b[i]))).append("\\");
			}

			std::ifstream iMethodsFile("methods.txt");
			std::string hash;
			std::string path;
			int time;
			std::string buffer;
			bool p = false;
			while(iMethodsFile >> hash >> path){
				if(hash != toHex(_b[30])){
					buffer.append(hash).append(" ").append(path).append("\n");
				} else {
					p = true;
					buffer.append(toHex(_b[30])).append(" ").append(steps).append("\n");
				}
			}
			if(p == false){
				buffer.append(toHex(_b[30])).append(" ").append(steps.c_str()).append("\n");
			}

			iMethodsFile.close();
			remove("methods.txt");
			std::ofstream oMethodsFile("methods.txt");
			oMethodsFile << buffer;
			oMethodsFile.close();
			printBoard();
		}

		if(1 == 0){
			std::cout << "WTF";
		} else {
			i8 ten = gen() % 7 + 1;
			i8 unit = gen() % 7 + 1;

			i8 coords = (ten*10)+unit;

			i8 direc = 0;
			i8 _direc = 0;

			switch(gen() % 4){
				case(0): if(coords < 58){direc = 10; _direc= 20;} break;
				case(1): if(coords < 76){direc = 1; _direc= 2;} break;
				case(2): if(coords > 30){direc = -10; _direc= -20;} break;
				case(3): if(coords > 12){direc = -1; _direc= -2;} break;
			}

			if(b[xy_to_char[coords]] == '@'){
				if(b[xy_to_char[coords+direc]] == '@'){
					if(b[xy_to_char[coords+_direc]] == 'O'){
					b[xy_to_char[coords]] = 'O';
					b[xy_to_char[coords+direc]] = 'O';
					b[xy_to_char[coords+_direc]] = '@';
						for(i8 x = 0; x <= 29; x++){
							i8 y = x + 1;
							_b[x] = _b[y];
						}
						counter++;

						_b[30] = b;    
						mv_clockr++;
					}
				}
			}
		}
	}
	return 0;
}


int printBoard(){
	std::ifstream iMethodsFile("methods.txt");
	std::string hash;
	std::string path;
	bool p = false;
	while(iMethodsFile >> hash >> path){
		if(hash == toHex(ID)){

			int unHashedValues[30];

			std::stringstream ss{path};

			std::string word;
			int count = 0;
			while(ss >> word){
				unHashedValues[count] = unHex(word.c_str());
				count++;
			}
		
		printf("%llu\n", counter);
		getchar();
		exit(0);
		}
	}
	return 0;
}
