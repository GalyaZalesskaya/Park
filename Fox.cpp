#include "fox.h"
#include <map>
#include <algorithm>



void Fox::reproduction(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals)
{
	
}

void Fox::living(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals)
{
	plus_iteration();

	if (((get_age() - 1) >= r_lifespan) || ((get_fullness() + 1) <= 0))
	{
		death(mat_g, animals);
		return;
	}
	if (((get_fullness() + 1) <= hungry))
	{
		eating(mat_g, animals);
		return;
	}

	if ((get_age() - 1 >= rep_adulty))
	{
		reproduction(mat_g, animals);
	}
	else search_partner(mat_g, animals);
}



void Fox::death(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals)
{
	(*(mat_g + get_x()*COL + get_y())).second = nullptr;
	not_alive();

}

void Fox::eating(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals)
{
	int x = get_x(), y = get_y();
	short del_x = -1, del_y = -1;
	for (del_x = -1; del_x <= 1; ++del_x)
		for (del_y = -1; del_y <= 1; ++del_y)
		{
			//if ((del_x || del_y) != 0) //eat at diagonal too
			{
				if ((x + del_x >= 0) && (x + del_x <= ROW - 1) && (y + del_y >= 0) && (y + del_y <= COL - 1))
				{
					Live* R = (*(mat_g + (x + del_x)*COL + y + del_y)).second;
					if ((R != nullptr) && (R->get_alive() == 1))
						if (R->get_type() == 'R')
						{
							fullness = std::min(fullness + R->get_age(), 20);//20 - max fullness
							std::cout << std::endl;
							print();
							R->print();
							std::cout << "omnomnom" << std::endl;
							R->death(mat_g, animals);
							(*(mat_g + (x + del_x)*COL + y + del_y)).second = nullptr;

							(*(mat_g + (x + del_x)*COL + y + del_y)).second = this;
							(*(mat_g + x*COL + y)).second = nullptr;

							step(x + del_x, y + del_y);
							print();

							return;
						}
				}
			}
		}
	search_food(mat_g, animals);
}

void Fox::search_food(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals)
{
	std::cout << "Search" << std::endl;
	int x = get_x(), y = get_y();
	Live* food = nullptr;
	double dist_for_food = 20;
	for (short del_x = -vision; del_x <= vision; ++del_x)
		for (short del_y = -vision; del_y <= vision; ++del_y)
		{
			
			if ((x + del_x >= 0) && (x + del_x <= ROW - 1) && (y + del_y >= 0) && (y + del_y <= COL - 1))
			{
				auto pos = (*(mat_g + (x + del_x)*COL + y + del_y)).second;
				if ((pos != nullptr) && (pos->get_type() == 'R'))
				{
					if (dist(x + del_x, y + del_y, x, y) < dist_for_food)
					{
						food = pos;
						dist_for_food = dist(x + del_x, y + del_y, x, y);
					}
				}
			}
		}
	if (food == nullptr) //ne nashel'((((((((((
	{
		auto do_step = find_place(mat_g, x, y, get_type());
		(*(mat_g + x*COL + y)).second = nullptr;
		(*(mat_g + (x + do_step.first)*COL + y + do_step.second)).second = this;


		step(x + do_step.first, y + do_step.second);
		return;
	}

	int i = food->get_x();
	int j = food->get_y();
	print();
	std::cout << "My food " << i << "  " << j << std::endl;

	std::map<double, std::pair<int, int>> myMap;
	if ((x < ROW - 1) && ((*(mat_g + (x + 1)*COL + y)).second == nullptr))
		myMap.insert(std::make_pair(dist(x + 1, y, i, j), std::make_pair(x + 1, y)));
	if ((x < ROW - 2) && ((*(mat_g + (x + 2)*COL + y)).second == nullptr))
		myMap.insert(std::make_pair(dist(x + 2, y, i, j), std::make_pair(x + 2, y)));

	if ((x > 0) && ((*(mat_g + (x - 1)*COL + y)).second == nullptr))
		myMap.insert(std::make_pair(dist(x - 1, y, i, j), std::make_pair(x - 1, y)));
	if ((x > 1) && ((*(mat_g + (x - 2)*COL + y)).second == nullptr))
		myMap.insert(std::make_pair(dist(x - 2, y, i, j), std::make_pair(x - 2, y)));

	if ((y < COL - 1) && ((*(mat_g + x*COL + y + 1)).second == nullptr))
		myMap.insert(std::make_pair(dist(x, y + 1, i, j), std::make_pair(x, y + 1)));
	if ((y < COL - 2) && ((*(mat_g + x*COL + y + 2)).second == nullptr))
		myMap.insert(std::make_pair(dist(x, y + 2, i, j), std::make_pair(x, y + 2)));

	if ((y > 0) && ((*(mat_g + x*COL + y - 1)).second == nullptr))
		myMap.insert(std::make_pair(dist(x, y - 1, i, j), std::make_pair(x, y - 1)));
	if ((y > 1) && ((*(mat_g + x*COL + y - 2)).second == nullptr))
		myMap.insert(std::make_pair(dist(x, y - 2, i, j), std::make_pair(x, y - 2)));

	if (myMap.begin() == myMap.end()) return;
	auto it = (myMap.begin()->second);
	int next_x = it.first;
	int next_y = it.second;


	(*(mat_g + x*COL + y)).second = nullptr;
	(*(mat_g + (next_x)*COL + next_y)).second = this;


	step(next_x, next_y);
}

void Fox::print()
{
	std::cout << get_x() << " " << get_y() << " " << get_age() << std::endl;
}

void Fox::search_partner(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals)
{
}

void Fox::plus_iteration()
{
	plus_age();
	fullness--;
}

bool Fox::get_gen() const
{
	if (gen == MALE)
		return 0;
	return 1;
}

