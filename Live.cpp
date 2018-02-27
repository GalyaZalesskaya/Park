#include "Live.h"


Live::~Live()
{
}

std::pair<int, int> Live::find_place(std::pair<Live*, Live*> mat_g[], const int& x, const int& y, const char type)
{
	short del_x = 0, del_y = 0;
	short att = 0;
	short choice = rand() % 4;
	if (type == 'G') //grass
	{
		do {
			switch (choice)
			{
			case 0: //right
				if ((y < COL - 1) && (((*(mat_g + (x)*COL + y + 1)).first == nullptr)))
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
				if ((x < ROW - 1) && (((*(mat_g + (x + 1)*COL + y)).first == nullptr)))
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
		} while ((att < 4) && ((del_x || del_y) == 0));
	}
	else //fox or rabbit
		do {
			switch (choice)
			{
			case 0: //right
				if ((y < COL - 1) && (((*(mat_g + (x)*COL + y + 1)).second == nullptr)))
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
				if ((y > 0) && (((*(mat_g + (x)*COL + y - 1)).second == nullptr)))
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
				if ((x > 0) && (((*(mat_g + (x - 1)*COL + y)).second == nullptr)))
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
				if ((x < ROW - 1) && (((*(mat_g + (x + 1)*COL + y)).second == nullptr)))
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
		} while ((att < 4) && ((del_x || del_y) == 0));


	return std::pair<int, int>(del_x, del_y);
}
