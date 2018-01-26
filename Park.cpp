#include "Park.h"
#include <iostream>





void Park::set_in_begin(int N_grass)
{
	int x_,y_;
	for (int i = 0; i < N_grass; i++)
	{
		while (1)
		{
			x_ = rand() % 25;
			y_ = rand() % 70;
			if (mat_g[x_][y_] == nullptr)
			{
				Grass grass(x_, y_, 1);
				animals.push_back(&grass);
				mat_g[x_][y_] = &grass;
				break;
			}
		}

	}


}

void Park::print()
{
	for (int k = 0; k < 70; k++)
		std::cout << "_" ;
	for (int i = 0; i < 25; i++)
	{
		for (int j = 0; j < 70; j++)
		{
			if (mat_g[i][j] == nullptr)
				std::cout << " ";
			else
				std::cout << "G";
		}
		std::cout <<"|"<< std::endl;
	}
	for (int k = 0; k < 70; k++)
		std::cout << "_" ;
}

void Park::change_iteration()
{
	for (int i=0; i<animals.size(); i++)
	{
		std::cout << animals[i] << std::endl;
		//animals[i]->living( &(mat_g[0][0]),  &animals);

	}
}


Park::~Park()
{
}
