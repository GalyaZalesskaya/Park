#include <Windows.h>
#include "Park.h"
#include <iostream>
#include <cstdlib>






void Park::set_in_begin(int N_grass,int N_rabbit)
{
	int x_,y_,gen;
	for (int i = 0; i < N_grass; i++)
	{
		while (1)
		{
			x_ = rand() % 25;
			y_ = rand() % 40;
			if (mat_g[x_][y_].first == nullptr)
			{
				Grass* p_grass= new Grass (x_, y_, 1);
				animals.push_back(p_grass);
				mat_g[x_][y_].first = p_grass;
				//std::cout << p_grass << std::endl;
				//p_grass->print();
				break;
			}
		}

	}
	for (int i = 0; i < N_rabbit; i++)
	{
		while (1)
		{
			x_ = rand() % 25;
			y_ = rand() % 40;
			gen = rand() % 1;
			if (mat_g[x_][y_].second == nullptr)
			{
				Rabbit* p_rabbit = new Rabbit(x_, y_, 1,gen,8);
				animals.push_back(p_rabbit);
				mat_g[x_][y_].second = p_rabbit;
				//std::cout << p_rabbit << std::endl;
				//p_rabbit->print();
				break;
			}
		}

	}


}

void Park::print()
{
	HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
	for (int k = 0; k < COL; k++)
		std::cout << "_"<<std::flush;
	std::cout << std::endl;
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			if ((mat_g[i][j].first != nullptr) && (mat_g[i][j].second != nullptr))
			{
				SetConsoleTextAttribute(hOUTPUT, BACKGROUND_GREEN | BACKGROUND_INTENSITY);
				std::cout << mat_g[i][j].second->get_type();
				SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else
				if (mat_g[i][j].first != nullptr)
				{
					SetConsoleTextAttribute(hOUTPUT, BACKGROUND_GREEN | BACKGROUND_INTENSITY); 
					std::cout << " ";
					SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);		
				}
				else
					if (mat_g[i][j].second != nullptr)
					{
						std::cout << mat_g[i][j].second->get_type();
					}
					else	
						std::cout << " ";
		}
		std::cout <<"|"<< std::endl;
	}
	for (int k = 0; k < COL; k++)
		std::cout << "_"<<std::flush ;
	std::cout <<  std::endl;
	int grass = 0, rabbit = 0;
	for (auto it = animals.begin(); it != animals.end(); ++it)
	{
		if ((*it)->get_type() == 'G') ++grass;
		else
			++rabbit;
	}
	std::cout << "The count of grass is: " << grass << std::endl;
	std::cout << "The count of rabbit is: " << rabbit << std::endl;
}

void Park::change_iteration()
{
	std::list<Live*> lis = animals;
	for (auto it = lis.begin(); it != lis.end(); ++it)
	{
		(*it)->living( &(mat_g[0][0]),  &animals);


	}
	std::cout << std::endl;

	animals.remove_if([](Live* p) { return (p->get_alive()) == 0; }); 
}

void Park::content()
{
	for (auto it = animals.begin(); it != animals.end(); ++it)
	{
		(*it)->print();
	}
}




Park::~Park()
{
}
