#pragma once
#include "Live.h"
#include "Grass.h"
#include "rabbit.h"
#include "Fox.h"
#include <list>
#include <utility>

const int ROW = 25;
const int COL = 40;
class Park
{
public:
	std::list<Live*> animals;
	std::pair<Live*,Live*> mat_g[25][40];
	void content();
	void print();
	void change_iteration();
	void set_in_begin(int,int,int);
	~Park();
};
