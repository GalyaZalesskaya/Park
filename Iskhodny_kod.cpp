#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <map>
#include "Park.h"

/*int x = 5, y = 5;
inline double dist(const int x_, const int y_) { return sqrt(pow(x_ - x, 2) + pow(y_ - y, 2)); }*/
void main()
{
	int ROW=25, COL=40;
	int N_grass = 10;
	Park my_park;
	my_park.set_in_begin(N_grass,16);
	my_park.print();
	//my_park.content();
	int k = 0;
	
	while (1)
	{
		my_park.change_iteration();
		my_park.print();
		k++;
		std::cout << k << " iteration" << std::endl;
		//my_park.content();
		std::cin.get();
		std::cin.get();
	}
	/*int x = 5, y = 5;

	std::map<double, std::pair<int, int>> myMap;
	if (x < ROW - 1)
		//myMap[dist(x + 1, y)] = std::make_pair(x + 1, y);
		myMap.insert(std::make_pair(dist(x + 1, y), std::make_pair(x + 1, y)));
	if (x > 0)
		//myMap[dist(x - 1, y)] = std::make_pair(x - 1, y);
		myMap.insert(std::make_pair(dist(x , y), std::make_pair(x - 1, y)));
	if (y < COL - 1)
		//myMap[dist(x, y + 1)] = std::make_pair(x, y + 1);
		myMap.insert(std::make_pair(dist(x, y + 2), std::make_pair(x, y + 1)));
	if (y > 0)
		//myMap[dist(x, y - 1)] = std::make_pair(x, y - 1);
		myMap.insert(std::make_pair(dist(x, y - 1), std::make_pair(x, y - 1)));

	for (auto it = myMap.begin(); it != myMap.end(); ++it)
	{
		std::cout << it->first << " " << (it->second).first << " " << (it->second).second << std::endl;
	}
	auto it = (myMap.begin()->second);
	std::cout << it.first << " " << it.second << std::endl;*/
	//std::cout << dist(x + 1, y) << " " << dist(x - 1, y) << " " << dist(x, y + 1) << " " << dist(x, y - 1) << std::endl;


	/*HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hOUTPUT,FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout<<"GREEN TEXT\n";
    SetConsoleTextAttribute(hOUTPUT,FOREGROUND_RED   | FOREGROUND_INTENSITY);
    cout<<"RED TEXT\n";
    SetConsoleTextAttribute(hOUTPUT,FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );*/
	
		
	
	/*std::list<int> lis = { 1,2,2,3,4,56,7,5 };
	lis.remove_if([](int n) { return n ==3; });
	for (auto it : lis)
	{
		std::cout << it << " ";
	}
	std::cin.get();*/

	std::cin.get();
}