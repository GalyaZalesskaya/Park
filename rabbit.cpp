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
	for (short del_x = -vision; del_x <= vision; ++del_x)
		for (short del_y = -vision; del_y <= vision; ++del_y)
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
		(*(mat_g + (x + do_step.first)*COL + y + do_step.second)).second = this;
		(*(mat_g + x*COL + y)).second = nullptr;

		step(x + do_step.first, y + do_step.second);
		return;
	}

	std::cout << "I find smb ";
	print();
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

	/*for (auto it = myMap.begin(); it != myMap.end(); ++it)
	{
	std::cout << it->first << " " << (it->second).first << " " << (it->second).second << std::endl;
	}*/
	if (myMap.begin() == myMap.end()) return;
	auto it = (myMap.begin()->second);
	int next_x = it.first;
	int next_y = it.second;

	(*(mat_g + (next_x)*COL + next_y)).second = this;
	(*(mat_g + x*COL + y)).second = nullptr;

	step(next_x, next_y);
	std::cout << "Step ";
	print();
}

void Rabbit::run_away(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals)
{
	int x = get_x(), y = get_y();
	Live* danger = nullptr;
	double dist_for_danger = 20;
	for (short del_x = -vision; del_x <= vision; ++del_x)
		for (short del_y = -vision; del_y <= vision; ++del_y)
		{
			Live* dang = (*(mat_g + (x + del_x)*COL + y + del_y)).second;
			if ((x + del_x >= 0) && (x + del_x <= ROW - 1) && (y + del_y >= 0) && (y + del_y <= COL - 1))
				if (dang->get_type() == 'F') 
				{
					if (dist(x + del_x, y + del_y, x, y) < dist_for_danger)
					{
						danger = (*(mat_g + (x + del_x)*COL + y + del_y)).second;
						dist_for_danger = dist(x + del_x, y + del_y, x, y);
					}
				}
		}
	if (danger == nullptr) //fux, nikogo))))))
	{
		auto do_step = find_place(mat_g, x, y, get_type());
		(*(mat_g + (x + do_step.first)*COL + y + do_step.second)).second = this;
		(*(mat_g + x*COL + y)).second = nullptr;

		step(x + do_step.first, y + do_step.second);
		return;
	}

	int i = danger->get_x();
	int j = danger->get_y();

	std::map<double, std::pair<int, int>> myMap;
	if (x < ROW - 1)
		myMap.insert(std::make_pair(dist(x + 1, y, i, j), std::make_pair(x + 1, y)));
	if (x > 0)
		myMap.insert(std::make_pair(dist(x - 1, y, i, j), std::make_pair(x - 1, y)));
	if (y < COL - 1)
		myMap.insert(std::make_pair(dist(x, y + 1, i, j), std::make_pair(x, y + 1)));
	if (y > 0)
		myMap.insert(std::make_pair(dist(x, y - 1, i, j), std::make_pair(x, y - 1)));

	/*for (auto it = myMap.begin(); it != myMap.end(); ++it)
	{
	std::cout << it->first << " " << (it->second).first << " " << (it->second).second << std::endl;
	}*/
	if (myMap.begin() == myMap.end()) return;
	auto it = (myMap.rbegin()->second); //the last distance from fox, the safest step
	int next_x = it.first;
	int next_y = it.second;

	(*(mat_g + (next_x)*COL + next_y)).second = this;
	(*(mat_g + x*COL + y)).second = nullptr;

	step(next_x, next_y);
}

void Rabbit::living(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals)
{
	plus_iteration();
	//std::cout << get_age() << " " << fullness << std::endl;

	if (((get_age()-1) >= r_lifespan) || ((get_fullness()+1) <=0))
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
		//search_partner(mat_g, animals);
	}
	//std::cout << get_age() << " " << fullness << std::endl;
	

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
				auto pos = (*(mat_g + (x+del_x)*COL + y+del_y)); 
				Live* G = pos.first;
				if ((x + del_x >= 0) && (x + del_x <= ROW - 1) && (y + del_y >= 0) && (y + del_y <= COL - 1))
				if ((G != nullptr) && (G->get_alive() != 0))
					if 	(((pos.second == nullptr) || (pos.second == this))) 
					{
						fullness = std::min(fullness+ G->get_age(), 10);//10 - max fullness
						G->not_alive();
						G = nullptr;
						
						(*(mat_g + (x+del_x)*COL + y+del_y)).second = this;
						(*(mat_g + x*COL + y)).second = nullptr;
						step(x + del_x, y + del_y);
						return;	
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
		(*(mat_g + (x+do_step.first)*COL + y+ do_step.second)).second = this;
		(*(mat_g + x*COL + y)).second = nullptr;

		step(x+ do_step.first, y+ do_step.second);
		return;
	}
		
	int i = food->get_x();
	int j = food->get_y();

	std::map<double, std::pair<int, int>> myMap; 
	if (x < ROW - 1)
		myMap.insert(  std::make_pair (dist(x + 1, y, i, j), std::make_pair(x + 1, y)));
	if (x > 0) 
		myMap.insert(std::make_pair(dist(x - 1, y, i, j), std::make_pair(x - 1, y)));
	if (y < COL - 1) 
		myMap.insert(std::make_pair(dist(x, y+1, i, j), std::make_pair(x, y+1)));
	if (y > 0)
		myMap.insert(std::make_pair(dist(x, y-1, i, j), std::make_pair(x, y-1)));

	/*for (auto it = myMap.begin(); it != myMap.end(); ++it)
	{
		std::cout << it->first << " " << (it->second).first << " " << (it->second).second << std::endl;
	}*/
	if (myMap.begin() == myMap.end()) return;
	auto it = (myMap.begin()->second);
	int next_x = it.first;
	int next_y = it.second;



	(*(mat_g + (next_x)*COL + next_y)).second = this;
	(*(mat_g + x*COL + y)).second = nullptr;

	step(next_x, next_y);


	/*if (food != nullptr)
	{
		std::cout << "\t dist_for_food: " << dist_for_food << std::endl;
		food->print();
	}
	else
		std::cout << "\t Ni nashel(((((\n";*/

	

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
							std::cout << "I find parter: ";
							R->print();
							print();
							/*short choice = rand() % 4;
							short alph_x = 0, alph_y = 0, att = 0;

							do {
								switch (choice)
								{
								case 0: //right
									if ((y < COL - 1) && (((*(mat_g + (x)*COL + y + 1)).second == nullptr)))
									{
										alph_y = 1;
										break;
									}
									else
									{
										++att;
										choice = (++choice) % 4;
									}
								case 1://left
									if ((y > 0) && (((*(mat_g + (x)*COL + y - 1)).second == nullptr)))
									{
										alph_y = -1;
										break;
									}
									else
									{
										++att;
										choice = (++choice) % 4;
									}
								case 2://up
									if ((x > 0) && (((*(mat_g + (x - 1)*COL + y)).second == nullptr)))
									{
										alph_x = -1;
										break;
									}
									else
									{
										++att;
										choice = (++choice) % 4;
									}
								case 3://down
									if ((x < ROW - 1) && (((*(mat_g + (x + 1)*COL + y)).second == nullptr)))
									{
										alph_x = 1;
										break;
									}
									else
									{
										++att;
										choice = (++choice) % 4;
									}
								}
							} while ((att < 4) && ((alph_x || alph_y) == 0));*/

							auto step = find_place(mat_g, x, y, get_type());
							auto alph_x = step.first;
							auto alph_y = step.second;
							

							if ((alph_x || alph_y) != 0)
							{

								Rabbit* p_rabbit = new Rabbit(x + alph_x, y + alph_y, 1, rand() % 2, 8);
								std::cout << "Child: ";
								p_rabbit->print();
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
