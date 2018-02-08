#include "Live.h"
#include <iostream>
#include <list>
#pragma once


class Grass :public Live
{
	const static int ROW = 25;
	const static int COL = 40;
	const static  int g_lifespan = 3;
	const static int rep_adulty = 1;

	static const char type = 'G';

public:
	Grass(int x_, int y_, int time) :Live(x_, y_, time){};
	virtual void reproduction(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals);
	virtual void living(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals);
	virtual void death(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals);
	virtual char get_type()const  { return type; };
	virtual bool get_gen() const { return 0; };
	virtual void eating(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals) {};
	virtual void search_food(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals) {};

	virtual void plus_iteration() { plus_age(); };
	virtual void print();

	//void death(Live * mat_g[], std::vector<Live*>* animals, int ROW, int COL);
	//virtual void death_eated();
	~Grass();
};
