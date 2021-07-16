/*******************************************
 * Student Name: Tristan Stevens
 * File Name: main.cpp
 * Project 3
 *
 *
 * This is the main file. I didn't include a lot of different classes because there wasn't much reuse of functions
 * I made a class for amatrix since I ended up using calculateCost a lot of times
 * *****************************************/
#include "amatrix.hpp"
#include <iostream>
#include <time.h>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <algorithm>

int main()
{
	std::cout<<"Please enter number of cities" << std::endl << "--> " ;
	int cities;
	std::cin>>cities;
	std::cout<<std::endl<<"Please enter how many tours per generation" << std::endl <<"--> ";
	int tours;
	std::cin>>tours;
	std::cout<<std::endl<<"Please enter how many generations to run" << std::endl << "--> ";
	int generations;
	std::cin>>generations;
	std::cout<<std::endl<<"Please enter a percent chance of mutation (0-100)" << std::endl << "--> "; // this doesn't range check so don't intentionally break it!
	float mutation;
	std::cin>> mutation;
	Amatrix amatrix("distances.txt");
	std::vector<int> numCities;
	for(int i=1;i<cities;i++) // this will load the vector with the number of cities
	{
		numCities.push_back(i); // initialization of number of cities
	}
	//BRUTE FORCE
	float tempCost;
	float bestCost=9999999.9;
	std::vector<int> bestPermutation;// used to store the best known permutation
	std::stringstream ss;
	std::string bestString;
	clock_t start=clock();

	do {
		tempCost=amatrix.calculateCost(numCities, cities-1);
		if(tempCost<bestCost)
		{
			bestCost=tempCost;
			bestPermutation=numCities;
		}

	} while(std::next_permutation(numCities.begin(), numCities.end()));

	ss<<0<< " ";
	for(int j=0; j<cities-1; j++)
	{
		ss<<bestPermutation.at(j)<<" ";
	}
	double seconds_since_start=(clock()-start)*1.0 /CLOCKS_PER_SEC;
	ss<<0;
	bestString=ss.str();

	std::cout<<std::endl<<"Number of cities ran: " <<cities<<std::endl<<std::endl <<"Brute Force Algorithm"<<std::endl
	<<"Optimal Permutation:"<<std::endl << bestString << std::endl
	<<"Optimal Cost:"<<std::endl << bestCost<< std::endl
	<<"time:"<<std::endl <<seconds_since_start<<" seconds" <<std::endl;
	float bfCost=bestCost;
	ss.str("");
	ss.clear();// I'm clearing out the stringstream because I'll be using it again later
	//GENETIC
	std::vector<std::vector<int>> geneticList;
	std::vector<int> tempChild;
	int toggle1=0;
	int toggle2=0; //these are toggles to check for duplicates. If they've been switched to 1, then duplicates for bestCost and bestCost2 aren't allowed
	int temp; // used for holding swap
	int swap1;
	int swap2;//random swap locations
	int cullCount=tours;
	geneticList.push_back(numCities);//initialization, loading of the two parents
	geneticList.push_back(numCities);
	bestPermutation=numCities; // will probably remove
	bestCost=amatrix.calculateCost(numCities,cities-1); // reusing my previous variables to initialize the values for the genetic algorithm
	float bestCost2=bestCost; // two parents require two best costs
	int mutationRoll; // rolls the mutation chance and compares it against the value you have given
	start=clock();
	for(int k=0; k<generations;k++)//this will run for how ever many generations you have set
	{
		while(geneticList.size()<tours) // this will load in the children, while also mutating them
		{
			mutationRoll=rand()%100;
			if(mutation>=mutationRoll)// mutation is happening
			{
				mutationRoll=rand()%2; // which of the two parents it will get its genetics from
				tempChild=geneticList.at(mutationRoll);
				swap1=rand()%(cities-1);
				swap2=rand()%(cities-1);//generates two random swap locations
				temp=tempChild.at(swap1);
				tempChild.at(swap1)=tempChild.at(swap2);
				tempChild.at(swap2)=temp;
				tempCost=amatrix.calculateCost(tempChild, cities-1);
				if(tempCost<bestCost)
				{
					bestPermutation=tempChild;
					bestCost=tempCost;
				}
				else if(tempCost<bestCost2)
				{
					bestCost2=tempCost;
				}
				geneticList.push_back(tempChild);
			}
			else // if there is no mutation, select one of the parents to copy over.
			{
				mutationRoll=rand()%2;
				geneticList.push_back(geneticList.at(mutationRoll));
			}
		}

		for(int n=0; n<cullCount; n++) // this is for culling the children. Absolutely brootal.
		{
			if(amatrix.calculateCost(geneticList.at(n),cities-1)==bestCost && toggle1 !=1)
			{
				toggle1=1; //this means we are keeping this entry, but no more duplicates!
			}
			else if(amatrix.calculateCost(geneticList.at(n),cities-1)==bestCost2 && toggle2 !=1)
			{
				toggle2=1; // this is keeping it as well
			}
			else
			{
				geneticList.erase(geneticList.begin()+n);
				n--; //since we deleted a position, we need to go back one to stay in the same place, or else I'm sure to get a memory leak
				cullCount--;
			}
		}
		toggle1=0;
		toggle2=0;//toggle reset
	}

	ss<<0<<" ";
	for(int l=0;l<cities-1;l++)
	{
		ss<<bestPermutation.at(l)<<" ";
	}
	ss<<0;
	bestString=ss.str();

	seconds_since_start=(clock()-start)*1.0/CLOCKS_PER_SEC;

	std::cout<<std::endl<<"Genetic Algorithm" << std::endl
	<<"Genetic Permutation:" << std::endl << bestString << std::endl
	<<"Cost:" << std::endl << bestCost << std::endl
	<<"Time:" << std::endl << seconds_since_start<< " seconds"<<std::endl<<std::endl
	<<"Cost of Genetic Algorithm vs. Optimal Cost" << std::endl<<((bfCost-bestCost)/bfCost)*-100+100<<"%"<<std::endl;
	return 0;
}
