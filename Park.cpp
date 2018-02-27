#include <Windows.h>
#include "Park.h"
#include <iostream>
#include <cstdlib>



void Park::set_in_begin(int N_grass,int N_rabbit, int N_fox)
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
			gen = rand() % 2;
			
			if (mat_g[x_][y_].second == nullptr)
			{
				Rabbit* p_rabbit = new Rabbit(x_, y_, 1,gen,8);
				animals.push_back(p_rabbit);
				mat_g[x_][y_].second = p_rabbit;
				//std::cout << p_rabbit << std::endl;
				//std::cout << gen << std::endl;
				//p_rabbit->print();
				break;
			}
		}

	}
	for (int i = 0; i < N_fox; i++)
	{
		while (1)
		{
			x_ = rand() % 25;
			y_ = rand() % 40;
			gen = rand() % 2;

			if (mat_g[x_][y_].second == nullptr)
			{
				Fox * p_fox = new Fox(x_, y_, 1, gen, 17);
				animals.push_back(p_fox);
				mat_g[x_][y_].second = p_fox;
				//std::cout << p_rabbit << std::endl;
				//std::cout << gen << std::endl;
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
			if ((mat_g[i][j].first != nullptr) && (mat_g[i][j].second != nullptr)&&(mat_g[i][j].first ->get_alive() ==1) &&(mat_g[i][j].second->get_alive() == 1))
			{
				if (mat_g[i][j].second->get_gen() == 0)
					SetConsoleTextAttribute(hOUTPUT, FOREGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY);
				else 
					SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY | FOREGROUND_INTENSITY);
				if (mat_g[i][j].second->get_type()=='R')
					std::cout << 'r';
				if ((mat_g[i][j].second->get_type() == 'F'))
					std::cout << 'F';
				SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else
				if ((mat_g[i][j].first != nullptr)&& (mat_g[i][j].first ->get_alive() == 1))
				{
					SetConsoleTextAttribute(hOUTPUT, BACKGROUND_GREEN | BACKGROUND_INTENSITY );
					std::cout << " ";
					SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);		
				}
				else
					if ((mat_g[i][j].second != nullptr) && (mat_g[i][j].second->get_alive() == 1))
					{
						if (mat_g[i][j].second->get_gen() == 0)
							SetConsoleTextAttribute(hOUTPUT, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
						else
							SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_INTENSITY);
						if (mat_g[i][j].second->get_type() == 'R')
							std::cout << 'r';
						if ((mat_g[i][j].second->get_type() == 'F'))
							std::cout << 'F';
						//std::cout << mat_g[i][j].second->get_type();
						SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
					}
					else	
						std::cout << " ";
		}
		std::cout <<"|"<< std::endl;
	}
	for (int k = 0; k < COL; k++)
		std::cout << "_"<<std::flush ;
	std::cout <<  std::endl;

	int grass_ = 0, rabbit_ = 0, fox_=0;
	for (auto it = animals.begin(); it != animals.end(); ++it)
	{
		if ((*it)->get_type() == 'G') ++grass_;
		else
			if ((*it)->get_type() == 'R') ++rabbit_;
			else 
				if ((*it)->get_type() == 'F') ++fox_;
	}
	std::cout << "The count of grass is: " << grass_ << std::endl;
	std::cout << "The count of rabbites is: " << rabbit_ << std::endl;
	std::cout << "The count of foxes is: " << fox_ << std::endl;
	std::cout << "The count of creatures is: " << animals.size() << std::endl;
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
