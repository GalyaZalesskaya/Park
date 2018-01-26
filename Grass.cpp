#include "Grass.h"

void Grass::reproduction(Live* mat_g[], std::vector<Live*>* animals) 
{
	short choice = rand() % 4 + 1;
	short del_x = 0, del_y = 0;
	switch (choice)
	{
	case 1: //right
		if ((get_y() < COL) && (*(mat_g + get_x()*ROW + get_y() + 1) == nullptr))
		{
			del_y = 1;
		}
	case 2://left
		if ((get_y() > 1) && (*(mat_g + get_x()*ROW + get_y() - 1) == nullptr))
		{
			del_y = -1;
		}
	case 3://up
		if ((get_x() > 1) && (*(mat_g + (get_x() - 1)*ROW + get_y()) == nullptr))
		{
			del_x = -1;
		}
	case 4://down
		if ((get_x() < ROW) && (*(mat_g + (get_x() + 1)*ROW + get_y()) == nullptr))
		{
			del_x = 1;
		}
	}
	if ((del_x!=0)||(del_y!=0)) 
	{
		Grass grass(get_x()+del_x, get_y()+del_y, 1);
		animals->push_back(&grass);
		*(mat_g + (get_x()+del_x)*ROW + (get_y()+del_y)) = &grass;
	}

}

void Grass::living(Live * mat_g[], std::vector<Live*>* animals)
{
	if (get_age() >= g_lifespan)
		death(mat_g, animals);
	else
		if (get_age() >= rep_adulty)
			reproduction(mat_g, animals);
}


void Grass::death(Live* mat_g[], std::vector<Live*>* animals)
{
	*(mat_g+get_x()*ROW+get_y()) = nullptr;
	auto itFound = std::find(animals->begin(), animals->end(), this);
		if (itFound != animals->end())
		{
			animals->erase(itFound);
		}
}

Grass::~Grass()
{
}


