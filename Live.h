#include<vector>
#pragma once
//extern const int ROW;
//extern const int COL;
class Live
{
	int x;
	int y;
	int age;
public:
	Live(int x_ = 0, int y_ = 0, int age_ = 0) :x(x_), y(y_), age(age_){};
	virtual void reproduction(Live* mat_g[], std::vector<Live*>* animals)=0;
	virtual void living(Live* mat_g[], std::vector<Live*>* animals)=0;
	virtual void death(Live* mat_g[], std::vector<Live*>* animals)=0;
	//virtual void death_hungry();
	//virtual void death_eated();
	//virtual void search_partner();
	//virtual void search_food();
	//virtual void run_away();
	//virtual void eating();
	int get_x(){ return x; };
	int get_y(){ return y; };
	int get_age(){ return age; };


	virtual ~Live();
};