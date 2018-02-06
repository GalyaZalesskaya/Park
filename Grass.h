#include "Live.h"
#include <iostream>
#include <list>
#pragma once

const int ROW=25;
const int COL=40;
const int g_lifespan = 5;
const int rep_adulty = 1;
class Grass :public Live
{

public:
	Grass(int x_, int y_, int time) :Live(x_, y_, time){};
	virtual void reproduction(Live* mat_g[], std::list<Live*>* ) ;
	virtual void living(Live* mat_g[], std::list<Live*>  *animals ) ;
	virtual void death(Live* mat_g[], std::list<Live*>* animals) ;

	void print();

	//void death(Live * mat_g[], std::vector<Live*>* animals, int ROW, int COL);
	//virtual void death_eated();
	~Grass();
};
