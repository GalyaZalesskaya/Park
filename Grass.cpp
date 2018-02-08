#include "Grass.h"

void Grass::reproduction(std::pair<Live*,Live*> mat_g[], std::list<Live*>* animals)
{
	//std::cout << get_x() << " " << get_y() << std::endl;
	//short choice = rand() % 4 ;
	//short del_x = 0, del_y = 0, att = 0;
	int x = get_x(), y = get_y();

	std::pair<int,int> place = find_place(mat_g, x, y,get_type());
	/*do {
		switch (choice)
		{
		case 0: //right
			if ((y < COL-1) && (((*(mat_g + (x )*COL + y + 1)).first == nullptr)))
			{
				del_y = 1;
				break;
			}
			else
			{
					++att;
					choice = (++choice) % 4;
			}
		case 1://left
			if ((y > 0) && (((*(mat_g + (x)*COL + y - 1)).first == nullptr)))
			{
				del_y = -1;
				break;
			}
			else
			{
					++att;
					choice = (++choice) % 4;
			}
		case 2://up
			if ((x > 0) && (((*(mat_g + (x - 1)*COL + y)).first == nullptr)))
			{
				del_x = -1;
				break;
			}
			else
			{
					++att;
					choice = (++choice) % 4;
			}
		case 3://down
			if ((x < ROW-1) && (((*(mat_g + (x+1)*COL + y)).first == nullptr)))
			{
				del_x = 1;
				break;
			}
			else
			{
					++att;
					choice = (++choice) % 4;
			}
		}
	} while ((att < 4)&& ((del_x||del_y) == 0));*/
	short del_x = place.first, del_y = place.second;


	if ((del_x || del_y) != 0)
	{
		Grass* p_grass = new Grass(x + del_x, y + del_y, 1);
		animals->push_back(p_grass);
		(*(mat_g + (x+del_x)*COL + (y+del_y))).first =p_grass;
	}


}

void Grass::living(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals)
{
	if (get_age() >= g_lifespan)
	{
		death(mat_g, animals);
		return;
	}
	if (get_age() >= rep_adulty)
		reproduction(mat_g, animals);
	plus_age();

}


void Grass::death(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals)
{
	(*(mat_g+get_x()*COL+get_y())).first = nullptr;
	not_alive();
}

void Grass::print()
{
	std::cout << get_x() << " " << get_y() << " " << get_age() << std::endl;
}

Grass::~Grass()
{
}


