#include "rabbit.h"
#include <algorithm>
#include <map>


void Rabbit::print()
{
	std::cout << get_x() << " " << get_y() << " " << get_age() << std::endl;
}

void Rabbit::search_partner(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals)
{
	int x = get_x(), y = get_y();
	Live* patner = nullptr;
	double dist_for_patner= 20;
	for (short del_x = -vision-2; del_x <= vision+2; ++del_x)
		for (short del_y = -vision-2; del_y <= vision+2; ++del_y)
		{
			if ((x + del_x >= 0) && (x + del_x <= ROW - 1) && (y + del_y >= 0) && (y + del_y <= COL - 1))
			{
				Live* patn = (*(mat_g + (x + del_x)*COL + y + del_y)).second;
				if (patn != nullptr)
					if ((patn->get_type() == 'R') && (patn->get_age() >= rep_adulty) && (patn->get_gen() + get_gen() == 1))
					{
						if (dist(x + del_x, y + del_y, x, y) < dist_for_patner)
						{
							patner = (*(mat_g + (x + del_x)*COL + y + del_y)).second;
							dist_for_patner = dist(x + del_x, y + del_y, x, y);
						}
					}
			}
		}
	if (patner == nullptr) //ne nashel'((((((((((
	{
		auto do_step = find_place(mat_g, x, y, get_type());
		(*(mat_g + x*COL + y)).second = nullptr;
		(*(mat_g + (x + do_step.first)*COL + y + do_step.second)).second = this;
		

		step(x + do_step.first, y + do_step.second);
		return;
	}


	int i = patner->get_x();
	int j = patner->get_y();

	std::map<double, std::pair<int, int>> myMap;
	if ((x < ROW - 1) && ((*(mat_g + (x + 1)*COL + y)).second == nullptr))
		myMap.insert(std::make_pair(dist(x + 1, y, i, j), std::make_pair(x + 1, y)));

	if ((x > 0) && ((*(mat_g + (x - 1)*COL + y)).second == nullptr))
		myMap.insert(std::make_pair(dist(x - 1, y, i, j), std::make_pair(x - 1, y)));

	if ((y < COL - 1) && ((*(mat_g + x*COL + y+1)).second == nullptr))
		myMap.insert(std::make_pair(dist(x, y + 1, i, j), std::make_pair(x, y + 1)));

	if ((y > 0) && ((*(mat_g + x*COL + y-1)).second == nullptr))
		myMap.insert(std::make_pair(dist(x, y - 1, i, j), std::make_pair(x, y - 1)));


	if (myMap.begin() == myMap.end()) return;
	auto it = (myMap.begin()->second);
	int next_x = it.first;
	int next_y = it.second;

	(*(mat_g + x*COL + y)).second = nullptr;
	(*(mat_g + (next_x)*COL + next_y)).second = this;
	

	step(next_x, next_y);
}

bool Rabbit::run_away(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals)
{
	int x = get_x(), y = get_y();
	Live* danger = nullptr;
	double dist_for_danger = 20;
	for (short del_x = -vision; del_x <= vision; ++del_x)
		for (short del_y = -vision; del_y <= vision; ++del_y)
		{
			if ((x + del_x >= 0) && (x + del_x <= ROW - 1) && (y + del_y >= 0) && (y + del_y <= COL - 1))
			{
				Live* dang = (*(mat_g + (x + del_x)*COL + y + del_y)).second;
				if ((dang!=nullptr)&&(dang->get_type() == 'F'))
				{
					if (dist(x + del_x, y + del_y, x, y) < dist_for_danger)
					{
						danger = (*(mat_g + (x + del_x)*COL + y + del_y)).second;
						dist_for_danger = dist(x + del_x, y + del_y, x, y);
					}
				}
			}
		}
	if (danger == nullptr) //fux, nikogo))))))
	{
		auto do_step = find_place(mat_g, x, y, get_type());
		(*(mat_g + x*COL + y)).second = nullptr;
		(*(mat_g + (x + do_step.first)*COL + y + do_step.second)).second = this;
	

		step(x + do_step.first, y + do_step.second);
		return 0;
	}

	int i = danger->get_x();
	int j = danger->get_y();

	std::map<double, std::pair<int, int>> myMap;
	if ((x < ROW - 1) && ((*(mat_g + (x + 1)*COL + y)).second == nullptr))
		myMap.insert(std::make_pair(dist(x + 1, y, i, j), std::make_pair(x + 1, y)));

	if ((x > 0) && ((*(mat_g + (x - 1)*COL + y)).second == nullptr))
		myMap.insert(std::make_pair(dist(x - 1, y, i, j), std::make_pair(x - 1, y)));

	if ((y < COL - 1) && ((*(mat_g + x*COL + y + 1)).second == nullptr))
		myMap.insert(std::make_pair(dist(x, y + 1, i, j), std::make_pair(x, y + 1)));

	if ((y > 0) && ((*(mat_g + x*COL + y - 1)).second == nullptr))
		myMap.insert(std::make_pair(dist(x, y - 1, i, j), std::make_pair(x, y - 1)));

	if (myMap.begin() == myMap.end()) return 1;
	auto it = (myMap.rbegin()->second); //the last distance from fox, the safest step
	int next_x = it.first;
	int next_y = it.second;

	(*(mat_g + x*COL + y)).second = nullptr;
	(*(mat_g + (next_x)*COL + next_y)).second = this;
	

	step(next_x, next_y);
	return 1;
}

void Rabbit::living(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals)
{
	plus_iteration();

	if (((((get_age()-1) >= r_lifespan) || (get_fullness()+1) <=0)) && (get_alive() == 1))
	{
		death(mat_g, animals);
		return;
	}
	if (((get_fullness()+1) <= hungry)&&(get_alive()==1))
	{
		eating(mat_g, animals);
		return;
	}
	

	if ((get_age()-1 >= rep_adulty) && (get_alive() == 1))
	{
		reproduction(mat_g, animals);
		return;
	}
	//if (run_away(mat_g, animals) == 0) 
		search_partner(mat_g, animals);
	

}


void Rabbit::plus_iteration()
{
	plus_age();
	fullness--;
}


void Rabbit::eating(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals)
{
	int x = get_x(), y = get_y();
	short del_x = -1, del_y = -1;
	for (del_x=-1; del_x<=1; ++del_x)
		for (del_y = -1; del_y <= 1; ++del_y)
			if ((del_x && del_y) == 0)
			{
				if ((x + del_x >= 0) && (x + del_x <= ROW - 1) && (y + del_y >= 0) && (y + del_y <= COL - 1))
				{
					auto pos = (*(mat_g + (x + del_x)*COL + y + del_y));
					Live* G = pos.first;
					if ((G != nullptr) && (G->get_alive() != 0))
						if (((pos.second == nullptr) || (pos.second == this)))
						{
							fullness = std::min(fullness + G->get_age(), 10);//10 - max fullness
							G->death(mat_g, animals);
							G = nullptr;

							(*(mat_g + x*COL + y)).second = nullptr;
							(*(mat_g + (x + del_x)*COL + y + del_y)).second = this;
							
							step(x + del_x, y + del_y);
							return;
						}
				}
			}
	search_food(mat_g, animals);
}
void Rabbit::search_food(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals)
{
	int x = get_x(), y = get_y();
	Live* food=nullptr;
	double dist_for_food = 20;
	for (short del_x = -vision; del_x <=vision; ++del_x)
		for (short del_y = -vision; del_y <= vision; ++del_y)
		{
			if ((x + del_x >= 0) && (x + del_x <= ROW - 1) && (y + del_y >= 0) && (y + del_y <= COL - 1))
				if ((*(mat_g + (x + del_x)*COL + y + del_y)).first != nullptr)
				{
					if (dist(x + del_x, y + del_y,x,y) < dist_for_food)
					{
						food = (*(mat_g + (x + del_x)*COL + y + del_y)).first;
						dist_for_food = dist(x + del_x, y + del_y,x,y);
					}
				}
		}
	if (food == nullptr) //ne nashel'((((((((((
	{
		auto do_step = find_place(mat_g, x, y, get_type());
		(*(mat_g + x*COL + y)).second = nullptr;
		(*(mat_g + (x+do_step.first)*COL + y+ do_step.second)).second = this;
		

		step(x+ do_step.first, y+ do_step.second);
		return;
	}
		
	int i = food->get_x();
	int j = food->get_y();

	std::map<double, std::pair<int, int>> myMap;
	if ((x < ROW - 1) && ((*(mat_g + (x + 1)*COL + y)).second == nullptr))
		myMap.insert(std::make_pair(dist(x + 1, y, i, j), std::make_pair(x + 1, y)));

	if ((x > 0) && ((*(mat_g + (x - 1)*COL + y)).second == nullptr))
		myMap.insert(std::make_pair(dist(x - 1, y, i, j), std::make_pair(x - 1, y)));

	if ((y < COL - 1) && ((*(mat_g + x*COL + y + 1)).second == nullptr))
		myMap.insert(std::make_pair(dist(x, y + 1, i, j), std::make_pair(x, y + 1)));

	if ((y > 0) && ((*(mat_g + x*COL + y - 1)).second == nullptr))
		myMap.insert(std::make_pair(dist(x, y - 1, i, j), std::make_pair(x, y - 1)));

	if (myMap.begin() == myMap.end()) return;
	auto it = (myMap.begin()->second);
	int next_x = it.first;
	int next_y = it.second;


	(*(mat_g + x*COL + y)).second = nullptr;
	(*(mat_g + (next_x)*COL + next_y)).second = this;
	

	step(next_x, next_y);


	

}

bool Rabbit::get_gen() const
{
	if (gen == MALE)
		return 0;
	return 1;
}

void Rabbit::reproduction(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals)
{
	//std::cout << "Time  for reproduction" << std::endl;
	//print();

	int x = get_x(), y = get_y();
	Live* R=nullptr;
	short del_x = -1, del_y = -1;

	for (del_x = -1; del_x <= 1; ++del_x)
		for (del_y = -1; del_y <= 1; ++del_y)
			if ((del_x || del_y) != 0)
			{
				if ((x + del_x >= 0) && (y + del_y >= 0) && (x + del_x <= ROW - 1) && (y + del_y <= COL - 1))
				{
					R = (*(mat_g + (x + del_x)*COL + (y + del_y))).second;
					if ((R != nullptr))
					{
						if ((R->get_age() >= rep_adulty) && (R->get_type() == 'R') && (R->get_alive() != 0) && ((R->get_gen() + get_gen()) == 1))
						{

							auto step = find_place(mat_g, x, y, get_type());
							auto alph_x = step.first;
							auto alph_y = step.second;
							

							if ((alph_x || alph_y) != 0)
							{

								Rabbit* p_rabbit = new Rabbit(x + alph_x, y + alph_y, 1, rand() % 2, 8);
								animals->push_back(p_rabbit);
								(*(mat_g + (x + alph_x)*COL + (y + alph_y))).second = p_rabbit;
								return;
							}
							if ((alph_x || alph_y) == 0) return;
						}		
					}
				}
			}
	search_partner(mat_g, animals);
}
void Rabbit::death(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals)
{
	(*(mat_g + get_x()*COL + get_y())).second = nullptr;
	not_alive();

}


Rabbit::~Rabbit()
{
}
