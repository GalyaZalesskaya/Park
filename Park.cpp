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
			y_ = rand() % 40;
			if (mat_g[x_][y_] == nullptr)
			{
				Grass* p_grass= new Grass (x_, y_, 1);
				animals.push_back(p_grass);
				mat_g[x_][y_] = p_grass;
				std::cout << p_grass << std::endl;
				p_grass->print();
				break;
			}
		}

	}


}

void Park::print()
{
	for (int k = 0; k < COL; k++)
		std::cout << k<<std::flush;
	std::cout << std::endl;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if (mat_g[i][j] == nullptr)
				std::cout << "_";
			else
				std::cout << "G";
		}
		std::cout <<i<< std::endl;
	}
	for (int k = 0; k < COL; k++)
		std::cout << "x"<<std::flush ;
	std::cout <<  std::endl;
	std::cout << "The count of grass is: " << animals.size() << std::endl;
}

void Park::change_iteration()
{
	for (auto it=animals.begin(); it!=animals.end(); ++it)
	{
		(*it)->living( &(mat_g[0][0]),  &animals);

	}

	animals.remove_if([](Live* p) { return (p->get_alive()) == 0; }); 
}


Park::~Park()
{
}
