#include "Live.h"
#include <iostream>
#include <list>
#pragma once




class Fox :public Live
{
	const static int ROW = 25;
	const static int COL = 40;

	const static int r_lifespan = 20;
	const static int rep_adulty = 10;
	const static int hungry = 12;
	const static int vision = 2;
	enum Gender { MALE, FEMALE };
	Gender gen;
	int fullness;
	static const char type = 'F';
public:
	Fox(int x_, int y_, int time_, int gen_, int full) :Live(x_, y_, time_), gen((Gender)gen_), fullness(full) {};
	virtual void reproduction(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals);

	virtual void living(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals);
	virtual void death(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals);
	virtual void eating(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals);
	virtual void search_food(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals);
	std::pair<int, int> jump_fox (std::pair<Live*, Live*> mat_g[], const int&, const int&);

	void print();
	virtual void search_partner(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals);

	int get_fullness() { return fullness; };
	virtual bool get_gen() const;
	virtual char get_type()const { return type; };
	virtual void plus_iteration();

	~Fox()=default;
};

