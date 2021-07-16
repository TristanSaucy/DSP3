/*******************************************
 * Student Name: Tristan Stevens
 * File Name: amatrix.hpp
 * Project 3
 *
 * this class is used to create the adjacency matrix and for using to adjacency matrix to calculate cost
 *
 * *****************************************/
#ifndef AMATRIX_HPP
#define AMATRIX_HPP
#include <fstream>
#include <vector>
class Amatrix
{
	public:
		Amatrix(std::string file); // just a simple constructor used to initialize the adjacency matrix
		float calculateCost(std::vector<int>, int length); // inputting a genetic code here will return a cost.
	private:
		float amatrix[20][20];
		std::ifstream input;
};
#endif
