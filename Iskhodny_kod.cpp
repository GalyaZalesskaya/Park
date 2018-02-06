#include <iostream>
#include "Park.h"

void main()
{
	int ROW=25, COL=40;
	int N_grass = 10;
	Park my_park;
	/*int number_of_grass;
	std::cout << "Enter number of grass" << std::endl;
	std::cin >> number_of_grass;
	my_park.set_in_begin(number_of_grass);*/
	my_park.set_in_begin(N_grass);
	my_park.print();

	
	while (1)
	{
		my_park.change_iteration();
		my_park.print();
		std::cin.get();
		std::cin.get();
	}
		/*
		std::cin.get();*/
		/*std::cin.get();
	
	/*std::list<int> lis = { 1,2,2,3,4,56,7,5 };
	lis.remove_if([](int n) { return n ==3; });
	for (auto it : lis)
	{
		std::cout << it << " ";
	}
	std::cin.get();*/


}