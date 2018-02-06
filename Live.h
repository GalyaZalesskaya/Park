#include<list>
#include <math.h>
#pragma once
//extern const int ROW;
//extern const int COL;
class Live
{
	int x;
	int y;
	int age;
	bool alive = 1;
	const static int ROW = 25;
	const static int COL = 40;

public:
	
	Live(int x_ = 0, int y_ = 0, int age_ = 0) :x(x_), y(y_), age(age_){};
	virtual void reproduction(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals) = 0;
	virtual void living(std::pair<Live*,Live*> mat_g[], std::list<Live*>* animals)=0;
	virtual void death(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals) = 0;
	virtual void eating(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals) = 0;
	virtual void search_food(std::pair<Live*, Live*> mat_g[], std::list<Live*>* animals) = 0;

	std::pair<int, int> find_place(std::pair<Live*, Live*> mat_g[], const int&, const int&, const char);

	inline double dist(const int& x_, const int& y_, const int& i, const int& j) { return sqrt(pow(x_ - i, 2) + pow(y_ - j, 2)); } 
	virtual void print() = 0;
	virtual void plus_iteration() = 0;
	virtual char get_type()const = 0;

	void step(int a, int b){ x = a; y = b; };
	int get_x(){ return x; };
	int get_y(){ return y; };
	int get_age(){ return age; };
	bool get_alive() { return alive; }
	void plus_age(){ age++; };
	void not_alive() { alive = 0; }

	virtual bool get_gen() = 0;
	//virtual void search_partner();
	//virtual void run_away();

	virtual ~Live();
};