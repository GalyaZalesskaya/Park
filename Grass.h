#include "Live.h"
#include <vector>
#pragma once

const int ROW=25;
const int COL=70;
class Grass :public Live
{
	int g_lifespan = 5;
	int rep_adulty = 2;
public:
	Grass(int x_, int y_, int time) :Live(x_, y_, time){};
	virtual void reproduction(Live* mat_g[], std::vector<Live*>* ) ;
	virtual void living(Live* mat_g[], std::vector<Live*>  *animals ) ;
	virtual void death(Live* mat_g[], std::vector<Live*>* animals) ;
	//void death(Live * mat_g[], std::vector<Live*>* animals, int ROW, int COL);
	//virtual void death_eated();
	~Grass();
};
