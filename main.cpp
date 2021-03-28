#include "amatrix.hpp"
#include <iostream>
#include <time.h>
#include <sstream>
#include <string>
#include <algorithm>
int main()
{
	Amatrix amatrix("distances.txt");
	int nextCityPush=10; //when we push, this is what will be pushed next
	std::vector<int> numCities;
	for(int i=1;i<10;i++) // this will load 1-9. 0 is also a city.
	{
		numCities.push_back(i); // initialization of number of cities
	}
	double seconds_since_start =0;
	//BRUTE FORCE
	clock_t start = clock(); //initialization of timer
	float tempCost;
	float bestCost=9999999.9;
	std::vector<int> bestPermutation;
	std::stringstream ss;
	std::string bestString;
	while(seconds_since_start<=300)
	{
		start=clock();

		do {
			tempCost=amatrix.calculateCost(numCities, nextCityPush-1);
			if(tempCost<bestCost)
			{
				bestCost=tempCost;
				bestPermutation=numCities;
			}
			
		} while(std::next_permutation(numCities.begin(), numCities.end()));

		ss<<0<< " ";
		for(int j=0; j<nextCityPush-1; j++)
		{
			ss<<bestPermutation.at(j)<<" ";
		}
		seconds_since_start=(clock()-start)*1.0 /CLOCKS_PER_SEC;
		ss<<0;
		bestString=ss.str();
		std::cout<<bestString << std::endl << bestCost<< std::endl <<seconds_since_start<< std::endl;

		ss.str(""); //resetting all the values
		bestString="";
		bestCost=9999999.9;
		numCities.push_back(nextCityPush);
		nextCityPush++;
	}
	return 0;
}
