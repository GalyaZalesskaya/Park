#pragma once
#include "Live.h"
#include "Grass.h"
#include <vector>
#include <utility>

//const int ROW = 25;
//const int COL = 70;
class Park
{
public:
	std::vector<Live*> animals;
	Live* mat_g[25][70];

	void print();
	void change_iteration();
	void set_in_begin(int);
	~Park();
};
