#include "amatrix.hpp"

Amatrix::Amatrix(std::string file)
{
	input.open(file);
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(i==j)
			{
				amatrix[i][j]=0;
			}
			else
			{
				input>>amatrix[i][j];
			}
		}
	}
	input.close();
}

float Amatrix::calculateCost(std::vector<int> vec, int length)
{
	float totalCost = 0;
	for(int i =0; i<=length;i++)
	{
		if(i==0)
		{
			totalCost+=amatrix[0][vec.at(i)];
		}
		else if(i==length)
		{
			totalCost+=amatrix[vec.at(i-1)][0];
		}
		else
		{
			totalCost+=amatrix[vec.at(i-1)][vec.at(i)];
		}
	}
	return totalCost;
}
