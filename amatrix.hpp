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
