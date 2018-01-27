#include "Grass.h"

void Grass::reproduction(Live* mat_g[], std::list<Live*>* animals)
{
	short choice = rand() % 4 + 1;
	short del_x = 0, del_y = 0, att = 0;
	int x = get_x(), y = get_y();

	/*if ((y < COL) && (*(mat_g + (x - 1)*COL + y + 1) == nullptr))
	{
		del_y = 1;
	}
	else 
		if ((y > 1) && (*(mat_g + (x - 1)*COL + y - 1) == nullptr))
		{
			del_y = -1;
		}
		else
			if ((x > 0) && (*(mat_g + (x - 1)*COL + y) == nullptr))
			{
				del_x = -1;
			}
			else
				if ((x < ROW) && (*(mat_g + (x)*COL + y) == nullptr))
				{
				del_x = 1;
	}*/


	switch (choice)
	{
	case 1: //right
		if ((y < COL) && (*(mat_g + (x-1)*COL + y + 1) == nullptr))
		{
			del_y = 1;
			break;
		}
	case 2://left
		if ((y > 1) && (*(mat_g + (x-1)*COL + y - 1) == nullptr))
		{
			del_y = -1;
			break;
		}
	case 3://up
		if ((x > 0) && (*(mat_g + (x - 1)*COL + y) == nullptr))
		{
			del_x = -1;
			break;
		}
	case 4://down
		if ((x < ROW) && (*(mat_g + (x)*COL + y) == nullptr))
		{
			del_x = 1;
			break;
		}
	}

	if ((del_x!=0)||(del_y!=0)) 
	{
		Grass* p_grass = new Grass(x + del_x, y + del_y, 1);
		animals->push_back(p_grass);
		*(mat_g + (x+del_x)*ROW + (y+del_y)) =p_grass;
	}

}

void Grass::living(Live * mat_g[], std::list<Live*>* animals)
{
	if (get_age() >= g_lifespan)
	{
		death(mat_g, animals);
		return;
	}
	if (get_age() >= rep_adulty)
		reproduction(mat_g, animals);
	iteration_plus();

}


void Grass::death(Live* mat_g[], std::list<Live*>* animals)
{
	*(mat_g+get_x()*ROW+get_y()) = nullptr;
	not_alive();
	//animals -> remove(this);
	//delete this;
}

void Grass::print()
{
	std::cout << get_x() << " " << get_y() << " " << get_age() << std::endl;
}

Grass::~Grass()
{
}


